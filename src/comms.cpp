#include "comms.h"
#include "language.h"
#include "constants.h"
#include <EEPROM.h>

extern mem presets[];

void Communication() {
  if (!menu) {
    if (wifi) {
      int packetSize = Udp.parsePacket();
      if (packetSize) {
        char packetBuffer[packetSize];
        Udp.read(packetBuffer, packetSize);
        Udp.endPacket();
        String packet = String(packetBuffer);
        if (strcmp(packetBuffer, "from=StationList;freq=?;bandwidth=?") == 0) {
          ShowFreq(0);
        } else {
          externaltune = true;
          int symPos = packet.indexOf("freq=");
          String stlfreq = packet.substring(symPos + 5, packetSize);
          if (afscreen) BuildAdvancedRDS();

          if ((stlfreq.toInt()) / 10000 > (TEF == 205 ? 6400 : 6500) && (stlfreq.toInt()) / 10000 < 10800) {
            unsigned int tempfreq = (stlfreq.toInt()) / 10000;
            if (scandxmode) cancelDXScan();
            if (tempfreq >= FREQ_FM_OIRT_START && tempfreq <= FREQ_FM_OIRT_END) {
              if (band != BAND_OIRT) {
                band = BAND_OIRT;
                frequency_OIRT = tempfreq;
                SelectBand();
              }
            } else {
              if (band != BAND_FM) {
                band = BAND_FM;
                frequency = tempfreq;
                SelectBand();
              }
            }
            if (band == BAND_OIRT) {
              frequency_OIRT = tempfreq;
              radio.SetFreq(frequency_OIRT);
            } else {
              frequency = tempfreq;
              radio.SetFreq(frequency);
            }
          }

          if ((stlfreq.toInt()) / 1000 > 144 && (stlfreq.toInt()) / 1000 < 27000) {
            if (scandxmode) cancelDXScan();
            if (afscreen || advancedRDS) {
              BuildDisplay();
              SelectBand();
              ScreensaverTimerReopen();
            }
            unsigned int tempfreq = (stlfreq.toInt()) / 1000;
            if (tempfreq >= FREQ_LW_LOW_EDGE_MIN && tempfreq <= FREQ_LW_HIGH_EDGE_MAX) {
              frequency_LW = tempfreq;
              if (band != BAND_LW) {
                band = BAND_LW;
                SelectBand();
              } else {
                radio.SetFreqAM(frequency_LW);
                frequency_AM = frequency_LW;
              }
            } else if (tempfreq >= FREQ_MW_LOW_EDGE_MIN_9K && tempfreq <= FREQ_MW_HIGH_EDGE_MAX_9K) {
              frequency_MW = tempfreq;
              if (band != BAND_MW) {
                band = BAND_MW;
                SelectBand();
              } else {
                radio.SetFreqAM(frequency_MW);
                frequency_AM = frequency_MW;
              }
            } else {
              frequency_SW = tempfreq;
              if (band != BAND_SW) {
                band = BAND_SW;
                SelectBand();
              } else {
                radio.SetFreqAM(frequency_SW);
                frequency_AM = frequency_SW;
              }
            }
          }
          radio.clearRDS(fullsearchrds);
          ShowFreq(0);
          store = true;
          externaltune = false;
        }
      }
    }

    if (Server.hasClient()) {
      if (RemoteClient.connected()) {
        Server.available().stop();
      } else {
        wificonnected = true;
        RemoteClient = Server.available();
        passwordcrypt();
        RemoteClient.print(saltkey + "\n");
      }
    } else {
      if (Server.hasClient()) Server.available().stop();
    }

    if (wificonnected && !RemoteClient.connected()) {
      wificonnected = false;
      RDSSPYTCP = false;
      XDRGTKTCP = false;
    }

    if (!RDSSPYTCP && !XDRGTKTCP && RemoteClient.available()) {
      String data_str = RemoteClient.readStringUntil('\n');
      if (data_str.indexOf("?F") != -1 || data_str.indexOf("*F") != -1) {
        RDSSPYTCP = true;
        RDSSPYUSB = false;
      } else {
        if (data_str.equals(cryptedpassword)) {
          radio.setFMABandw();
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
          }
          XDRGTKTCP = true;
          if (XDRGTKMuteScreen) MuteScreen(1);
          RemoteClient.print("o1,0\n");
          RemoteClient.print("G" + String(!EQset) + String(!iMSset) + "\n");
          store = true;
        } else {
          RemoteClient.print("a0\n");
        }
      }
    }

    if (RDSSPYTCP && RemoteClient.available()) {
      String data_str = RemoteClient.readStringUntil('\n');
      int symPos = data_str.indexOf("*F");
      if (symPos >= 5) {
        String freq = data_str.substring(0, symPos);
        freq = freq.substring(0, freq.length() - 1);
        frequency = freq.toInt();
        if (scandxmode) cancelDXScan();
        radio.SetFreq(frequency);
        radio.clearRDS(fullsearchrds);
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        ShowFreq(0);
        store = true;
      }
    }

    if (!RDSSPYUSB && !XDRGTKUSB && Serial.available()) {
      String data_str = Serial.readStringUntil('\n');
      if (data_str.indexOf("?F") != -1 || data_str.indexOf("*F") != -1) {
        RDSSPYUSB = true;
        RDSSPYTCP = false;
      } else if (data_str.charAt(0) == 'x') {
        radio.setFMABandw();
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        Serial.print("OK\nT" + String(frequency * 10) + "\nG" + String(!EQset) + String(!iMSset) + "\n");
        XDRGTKUSB = true;
        if (XDRGTKMuteScreen) MuteScreen(1);
      } else if (data_str.charAt(0) == 's') {
        Serial.print("r:0\n");
        Serial.print("v:" + String(VERSION) + "\n");
        Serial.print("m:" + String(EE_PRESETS_CNT) + "\n");
        Serial.print("s:" + String(EE_PRESETS_FREQUENCY) + "\n");
        Serial.print("o:" + String(ConverterSet) + "\n");
        Serial.print("a:" + String(FREQ_LW_LOW_EDGE_MIN) + "," + String(FREQ_SW_END) + "\n");
        Serial.print("f:" + String((TEF == 205 ? 64000 : 65000)) + "," + String(108000) + "\n");

        for (byte x = 0; x < EE_PRESETS_CNT; x++) {
          Serial.print(x + 1);
          Serial.print(",");
          Serial.print(presets[x].frequency);
          if (presets[x].band == BAND_FM || presets[x].band == BAND_OIRT) Serial.print("0");
          Serial.print(",");
          Serial.print(presets[x].bw);
          Serial.print(",");
          Serial.print(presets[x].ms);
          Serial.print(",");
          Serial.print(String(presets[x].RDSPI).substring(0, 4));
          Serial.print(",");
          Serial.print(String(presets[x].RDSPS).substring(0, 8));
          Serial.print("\n");
        }
      } else if (data_str.startsWith("S")) {
        byte mempos = 0;
        byte memband = 0;
        unsigned int memfreq = 0;
        byte membw;
        byte memms;
        byte error = 0;
        data_str.remove(0, 1);
        int commaPos = data_str.indexOf(',');

        if (commaPos != -1) {
          mempos = data_str.substring(0, commaPos).toInt() - 1;

          data_str.remove(0, commaPos + 1);
          commaPos = data_str.indexOf(',');

          if (commaPos != -1) {
            memfreq = data_str.substring(0, commaPos).toInt();
            data_str.remove(0, commaPos + 1);
            commaPos = data_str.indexOf(',');

            if (commaPos != -1) {
              membw = data_str.substring(0, commaPos).toInt();
              data_str.remove(0, commaPos + 1);
              commaPos = data_str.indexOf(',');

              if (commaPos != -1) {
                memms = data_str.substring(0, commaPos).toInt();
                data_str.remove(0, commaPos + 1);
                commaPos = data_str.indexOf(',');

                if (commaPos != -1) {
                  String rdsPiStr = data_str.substring(0, commaPos);
                  char rdsPi[5];
                  rdsPiStr.toCharArray(rdsPi, sizeof(rdsPi));
                  data_str.remove(0, commaPos + 1);
                  commaPos = data_str.indexOf(',');

                  String rdsPs = data_str;


                  if (memfreq >= FREQ_LW_LOW_EDGE_MIN && memfreq <= FREQ_LW_HIGH_EDGE_MAX) {
                    memband = BAND_LW;
                  } else if (memfreq > FREQ_LW_HIGH_EDGE_MAX && memfreq <= FREQ_MW_HIGH_EDGE_MAX_10K) {
                    memband = BAND_MW;
                  } else if (memfreq > FREQ_MW_HIGH_EDGE_MAX_10K && memfreq <= FREQ_SW_END) {
                    memband = BAND_SW;
                  } else if (ConverterSet != 0 && memfreq >= FREQ_FM_OIRT_START * 10 && memfreq <= FREQ_FM_OIRT_END * 10) {
                    memband = BAND_OIRT;
                    memfreq /= 10;
                  } else if ((ConverterSet != 0 && memfreq > FREQ_FM_OIRT_START * 10) || ((ConverterSet == 0 && memfreq > FREQ_FM_OIRT_END * 10) && memfreq <= 108000 * 10)) {
                    memband = BAND_FM;
                    memfreq /= 10;
                  } else if (memfreq == EE_PRESETS_FREQUENCY) {
                    memband = BAND_FM;
                  } else {
                    error |= (1 << 0);
                  }

                  if (mempos == 0 && memfreq == EE_PRESETS_FREQUENCY) error |= (1 << 4);

                  if (mempos >= EE_PRESETS_CNT) error |= (1 << 1);

                  if (memband != BAND_FM && memband != BAND_OIRT) {
                    if (membw < 1 || membw > 4) error |= (1 << 2);
                  } else if (membw > 16) {
                    error |= (1 << 2);
                  }

                  if (memms > 1) error |= (1 << 3);

                  if (rdsPi[0] != '\0') {
                    for (int i = 0; i < 4; i++) {
                      char c = rdsPi[i];
                      if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))) {
                        error |= (1 << 5);
                        break;
                      }
                    }
                  }

                  if (error == 0) {
                    error |= (1 << 7);
                    memorypos = mempos;
                    presets[mempos].band = memband;
                    presets[mempos].frequency = memfreq;
                    presets[mempos].bw = membw;
                    presets[mempos].ms = memms;

                    EEPROM.writeByte(mempos + EE_PRESETS_BAND_START, memband);
                    EEPROM.writeByte(mempos + EE_PRESET_BW_START, membw);
                    EEPROM.writeByte(mempos + EE_PRESET_MS_START, memms);
                    EEPROM.writeUInt((mempos * 4) + EE_PRESETS_FREQUENCY_START, memfreq);

                    for (int i = 0; i < 5; i++) {
                      presets[mempos].RDSPI[i] = rdsPi[i];
                      EEPROM.writeByte((mempos * 5) + i + EE_PRESETS_RDSPI_START, rdsPi[i]);
                    }

                    for (int i = 0; i < 9; i++) {
                      if (i < rdsPs.length()) {
                        presets[mempos].RDSPS[i] = rdsPs.charAt(i);
                      } else {
                        presets[mempos].RDSPS[i] = '\0';
                      }
                      EEPROM.writeByte((mempos * 9) + i + EE_PRESETS_RDSPS_START, presets[mempos].RDSPS[i]);
                    }

                    EEPROM.commit();
                  }
                  Serial.print("S:" + String(error, DEC) + "\n");
                }
              }
            }
          }
        }
      }
    }

    if (RDSSPYUSB && Serial.available()) {
      String data_str = Serial.readStringUntil('\n');
      int symPos = data_str.indexOf("*F");
      if (symPos >= 5) {
        String freq = data_str.substring(0, symPos);
        freq = freq.substring(0, freq.length() - 1);
        frequency = freq.toInt();
        if (scandxmode) cancelDXScan();
        radio.SetFreq(frequency);
        if (afscreen) BuildAdvancedRDS();
        radio.clearRDS(fullsearchrds);
        if (band != BAND_FM) {
          band = BAND_FM;
          SelectBand();
        }
        ShowFreq(0);
        store = true;
      }
    }

    if (XDRGTKUSB || XDRGTKTCP) XDRGTKRoutine();
  }
}

void XDRGTKRoutine() {
  if (XDRGTKUSB) {
    while (Serial.available() > 0) {
      char c = Serial.read();
      if (buff_pos < 16 && c != '\n') {
        buff[buff_pos++] = c;
      } else {
        buff[buff_pos] = '\0';
        buff_pos = 0;
        XDRGTKdata = true;
        break;
      }
    }
  }

  if (XDRGTKTCP && RemoteClient.available() > 0) {
    while (RemoteClient.available() > 0) {
      char c = RemoteClient.read();
      if (buff_pos < 16 && c != '\n') {
        buff[buff_pos++] = c;
      } else {
        buff[buff_pos] = '\0';
        buff_pos = 0;
        XDRGTKdata = true;
        break;
      }
    }
  }

  if (XDRGTKdata) {
    switch (buff[0])
    {
      case 'A':
        int AGC;
        AGC = atol(buff + 1);
        DataPrint("A" + String(AGC) + "\n");
        switch (AGC) {
          case 0: if (band == BAND_FM || BAND_OIRT) radio.setAGC(92); else radio.setAMAGC(102); break;
          case 1: if (band == BAND_FM || BAND_OIRT) radio.setAGC(90); else radio.setAMAGC(99); break;
          case 2: if (band == BAND_FM || BAND_OIRT) radio.setAGC(87); else radio.setAMAGC(96); break;
          case 3: if (band == BAND_FM || BAND_OIRT) radio.setAGC(84); else radio.setAMAGC(94); break;
        }
        break;

      case 'B':
        byte stmo;
        stmo = atol(buff + 1);
        DataPrint("B" + String(stmo) + "\n");
        if (stmo == 0) StereoToggle = false; else StereoToggle = true;
        doStereoToggle();
        break;

      case 'C':
        if (afscreen || advancedRDS) {
          BuildDisplay();
          SelectBand();
        }
        byte scanmethod;
        scanmethod = atol(buff + 1);

        if (band < BAND_GAP) {
          stepsize = 0;
          ShowStepSize();
        }

        if (scanmethod == 1) {
          DataPrint("C1\n");
          direction = false;
          Seek(direction);
          ShowFreq(0);
        }
        if (scanmethod == 2) {
          DataPrint("C2\n");
          direction = true;
          Seek(direction);
          ShowFreq(0);
        }
        DataPrint("C0\n");
        break;

      case 'D':
        byte demp;
        demp = atol(buff + 1);
        DataPrint("D" + String(demp) + "\n");
        switch (demp) {
          case 0: DeEmphasis = 1; break;
          case 1: DeEmphasis = 2; break;
          case 2: DeEmphasis = 0; break;
        }
        radio.setDeemphasis(DeEmphasis);
        break;

      case 'F':
        XDRBWset = atol(buff + 1);
        DataPrint("F" + String(XDRBWset) + "\n");
        if (XDRBWset < 0) {
          XDRBWsetold = XDRBWset;
          BWset = 0;
        } else if (XDRBWset < 16) {
          BWset = XDRBWset + 1;
          XDRBWsetold = XDRBWset;
        } else {
          XDRBWset = XDRBWsetold;
        }
        doBW();
        break;

      case 'G':
        byte offsetg;
        offsetg = atol(buff + 1);
        if (offsetg == 0) {
          iMSset = 1;
          EQset = 1;
          DataPrint("G00\n");
        }
        if (offsetg == 10) {
          iMSset = 1;
          EQset = 0;
          DataPrint("G10\n");
        }
        if (offsetg == 1) {
          iMSset = 0;
          EQset = 1;
          DataPrint("G01\n");
        }
        if (offsetg == 11) {
          iMSset = 0;
          EQset = 0;
          DataPrint("G11\n");
        }
        updateiMS();
        updateEQ();
        break;

      case 'H':
        byte autosq_read;
        autosq_read = atol(buff + 1);
        if (autosq_read == 0) {
          autosquelch = false;
          DataPrint("H0\n");
        } else if (autosq_read == 1) {
          autosquelch = true;
          DataPrint("H1\n");
        } else {
          autosquelch = !autosquelch;
        }

        if (autosquelch) {
          DataPrint("H1\n");
          if (!screenmute) {
            tftPrint(-1, "SQ:", 212, 145, ActiveColor, ActiveColorSmooth, 16);
            showAutoSquelch(1);
          }
        } else {
          DataPrint("H0\n");
          if (!screenmute) {
            if (!usesquelch) {
              tftPrint(-1, "SQ:", 212, 145, BackgroundColor, BackgroundColor, 16);
              showAutoSquelch(0);
            } else {
              Squelch = -150;
            }
          }
        }
        break;

      case 'I':
        byte fmscansenstemp;
        fmscansenstemp = atol(buff + 1);
        if (fmscansenstemp > 0 && fmscansenstemp < 31) {
          fmscansens = fmscansenstemp;
          EEPROM.writeByte(EE_BYTE_FMSCANSENS, fmscansens);
          EEPROM.commit();
        }
        DataPrint("I" + String(fmscansens) + "\n");
        break;

      case 'J':
        byte scandxtemp;
        scandxtemp = atol(buff + 1);
        if (scandxtemp == 0 && scandxmode) cancelDXScan();
        if (scandxtemp == 1 && !scandxmode) startFMDXScan();
        DataPrint("J" + String(scandxtemp) + "\n");
        break;

      case 'K':
        byte scanholdtemp;
        scanholdtemp = atol(buff + 1);
        if (scanholdtemp < 31) {
          scanhold = scanholdtemp;
          EEPROM.writeByte(EE_BYTE_SCANHOLD, scanhold);
          EEPROM.commit();
        }
        DataPrint("K" + String(scanhold) + "\n");
        break;

      case 'M':
        if (scandxmode) cancelDXScan();
        byte XDRband;
        XDRband = atol(buff + 1);
        if (XDRband == 0) DataPrint("M0\n"); else DataPrint("M1\n");
        if (XDRband == 1) {
          if (frequency_AM >= LWLowEdgeSet && frequency_AM <= LWHighEdgeSet) {
            if (band != BAND_LW) {
              band = BAND_LW;
              SelectBand();
            }
          }
          if (frequency_AM >= MWLowEdgeSet && frequency_AM <= MWHighEdgeSet) {
            if (band != BAND_MW) {
              band = BAND_MW;
              SelectBand();
            }
          }
          if (frequency_AM >= SWLowEdgeSet && frequency_AM <= SWHighEdgeSet) {
            if (band != BAND_SW) {
              band = BAND_SW;
              SelectBand();
            }
          }
          radio.SetFreqAM(frequency_AM);
          DataPrint("M1\n");
          DataPrint("T" + String(frequency_AM) + "\n");
        } else {
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
          }
          DataPrint("M0\n");
          DataPrint("T" + String((frequency + ConverterSet * 100) * 10) + "\n");
          radio.SetFreq(frequency);
          radio.clearRDS(fullsearchrds);
          RDSstatus = false;
        }
        store = true;
        break;

      case 'T':
        if (scandxmode) cancelDXScan();
        unsigned int freqtemp;
        freqtemp = atoi(buff + 1);

        if (BAND_FM) freqtemp -= ConverterSet * 1000;
        if (seek) seek = false;
        radio.clearRDS(fullsearchrds);

        if (freqtemp >= LWLowEdgeSet && freqtemp <= LWHighEdgeSet) {
          frequency_LW = freqtemp;
          frequency_AM = freqtemp;
          if (afscreen || advancedRDS) {
            BuildDisplay();
            SelectBand();
          }
          if (band != BAND_LW) {
            band = BAND_LW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_LW);
        } else if (freqtemp >= MWLowEdgeSet && freqtemp <= MWHighEdgeSet) {
          frequency_AM = freqtemp;
          frequency_MW = freqtemp;
          if (afscreen || advancedRDS) {
            BuildDisplay();
            SelectBand();
          }
          if (band != BAND_MW) {
            band = BAND_MW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_MW);
        } else if (freqtemp >= SWLowEdgeSet && freqtemp <= SWHighEdgeSet) {
          frequency_SW = freqtemp;
          frequency_AM = freqtemp;
          if (afscreen || advancedRDS) {
            BuildDisplay();
            SelectBand();
          }
          if (band != BAND_SW) {
            band = BAND_SW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_SW);
        } else if (freqtemp >= LowEdgeOIRTSet * 10 && freqtemp <= HighEdgeOIRTSet * 10) {
          frequency_OIRT = freqtemp / 10;
          if (afscreen || advancedRDS) {
            BuildDisplay();
            SelectBand();
          }
          if (band != BAND_OIRT) {
            band = BAND_OIRT;
            SelectBand();
            DataPrint("M0\n");
          }
          radio.SetFreq(frequency_OIRT);
        } else if (freqtemp >= (TEF == 205 ? 64000 : 65000) && freqtemp <= 108000) {
          frequency = freqtemp / 10;
          if (afscreen || advancedRDS) {
            BuildDisplay();
            SelectBand();
          }
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
            DataPrint("M0\n");
          }
          radio.SetFreq(frequency);
        }

        if (band == BAND_FM) {
          DataPrint("T" + String((frequency + ConverterSet * 100) * 10) + "\n");
        } else if (band == BAND_OIRT) {
          DataPrint("T" + String(frequency_OIRT * 10) + "\n");
        } else {
          DataPrint("T" + String(frequency_AM) + "\n");
        }
        ShowFreq(0);
        RDSstatus = false;
        store = true;
        aftest = true;
        aftimer = millis();
        break;

      case 'Q':
        Squelch = atoi(buff + 1);
        if (Squelch == -1) {
          DataPrint("Q-1\n");
        } else {
          Squelch *= 10;
          DataPrint("Q");
          DataPrint(String(Squelch / 10));
          DataPrint("\n");
        }
        break;

      case 'S':
        if (scandxmode) cancelDXScan();
        if (!XDRScan) BWsetRecall = BWset;
        XDRScan = true;
		Data_Accelerator = true;

        switch (buff[1]) {
          case 'a': scanner_start = (atol(buff + 2) + 5) / 10; break;
          case 'b': scanner_end = (atol(buff + 2) + 5) / 10; return;
          case 'c': scanner_step = (atol(buff + 2) + 5) / 10; break;
          case 'f':
            scanner_filter = atol(buff + 2);
            switch (scanner_filter) {
              case 0: BWset = 1; break;
              case 26: BWset = 2; break;
              case 1: BWset = 3; break;
              case 28: BWset = 4; break;
              case 29: BWset = 5; break;
              case 3: BWset = 6; break;
              case 4: BWset = 7; break;
              case 5: BWset = 8; break;
              case 7: BWset = 9; break;
              case 8: BWset = 10; break;
              case 9: BWset = 11; break;
              case 10: BWset = 12; break;
              case 11: BWset = 13; break;
              case 12: BWset = 14; break;
              case 13: BWset = 15; break;
              case 15: BWset = 16; break;
            }
            doBW();
            break;
          case 'w':
            unsigned int bwtemp;
            bwtemp = atoi(buff + 2);
            switch (bwtemp) {
              case 0: BWset = 0; break;
              case 56000: BWset = 1; break;
              case 64000: BWset = 2; break;
              case 72000: BWset = 3; break;
              case 84000: BWset = 4; break;
              case 97000: BWset = 5; break;
              case 114000: BWset = 6; break;
              case 133000: BWset = 7; break;
              case 151000: BWset = 8; break;
              case 168000: BWset = 9; break;
              case 184000: BWset = 10; break;
              case 200000: BWset = 11; break;
              case 217000: BWset = 12; break;
              case 236000: BWset = 13; break;
              case 254000: BWset = 14; break;
              case 287000: BWset = 15; break;
              case 311000: BWset = 16; break;
            }
            doBW();
            break;

          case '\0':
            radio.setMute();
            if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
            if (!screenmute) {
              tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
              tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
              tftPrint(0, myLanguage[language][34], 160, 100, ActiveColor, ActiveColorSmooth, 28);
            }

            DataPrint("U");
            frequencyold = frequency;

            for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += scanner_step) {
              radio.SetFreq(freq_scan);
              delay(5);
              DataPrint(String(freq_scan * 10, DEC));
              DataPrint(" = ");
              if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else  radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
              DataPrint(String((SStatus / 10) + 10, DEC));
              DataPrint(", ");
            }
            DataPrint("\n");

            radio.SetFreq(frequencyold);
            BuildDisplay();
            SelectBand();
            BWset = BWsetRecall;
            doBW();
            XDRScan = false;
            if (VolSet != 0) {
              radio.setUnMute();
              if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
              radio.setVolume(((VolSet * 10) - 40) / 10);
            }
            break;
        }
		Data_Accelerator = false;
        break;

      case 'W':
        unsigned int bwtemp;
        bwtemp = atoi(buff + 1);
        switch (bwtemp) {
          case 0: BWset = 0; break;
          case 56000: BWset = 1; break;
          case 64000: BWset = 2; break;
          case 72000: BWset = 3; break;
          case 84000: BWset = 4; break;
          case 97000: BWset = 5; break;
          case 114000: BWset = 6; break;
          case 133000: BWset = 7; break;
          case 151000: BWset = 8; break;
          case 168000: BWset = 9; break;
          case 184000: BWset = 10; break;
          case 200000: BWset = 11; break;
          case 217000: BWset = 12; break;
          case 236000: BWset = 13; break;
          case 254000: BWset = 14; break;
          case 287000: BWset = 15; break;
          case 311000: BWset = 16; break;
        }
        doBW();
        DataPrint("W" + String(bwtemp) + "\n");
        break;

      case 'Y':
        VolSet = atoi(buff + 1);
        if (VolSet == 0) {
          radio.setMute();
          if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, PrimaryColor);
          XDRMute = true;
          SQ = true;
        } else {
          radio.setUnMute();
          if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
          radio.setVolume((VolSet - 40) / 10);
          XDRMute = false;
        }
        DataPrint("Y" + String(VolSet) + "\n");
        VolSet /= 10;
        break;

      case 'x':
        DataPrint("OK\n");
        if (BAND_FM) {
          DataPrint("T" + String((frequency + ConverterSet * 100) * 10) + "\n");
        } else if (BAND_OIRT) {
          DataPrint("T" + String(frequency_OIRT * 10) + "\n");
        } else {
          DataPrint("T" + String(frequency_AM) + "\n");
        }
        if (StereoToggle) DataPrint("B0\n"); else DataPrint("B1\n");
        if (XDRGTKMuteScreen) MuteScreen(1);
        break;

      case 'X':
        XDRGTKTCP = false;
        XDRGTKUSB = false;
        store = true;
        XDRMute = false;
        radio.setUnMute();
        if (!screenmute) tft.drawBitmap(92, 4, Speaker, 26, 22, GreyoutColor);
        VolSet = EEPROM.readByte(EE_BYTE_VOLSET);
        LowLevelSet = EEPROM.readByte(EE_BYTE_LOWLEVELSET);
        softmuteam = EEPROM.readByte(EE_BYTE_SOFTMUTEAM);
        softmutefm = EEPROM.readByte(EE_BYTE_SOFTMUTEFM);
        radio.setVolume(VolSet);
        radio.setSoftmuteFM(softmutefm);
        radio.setSoftmuteAM(softmuteam);
        if (!usesquelch) radio.setUnMute();
        if (XDRGTKMuteScreen) MuteScreen(0);
        break;

      case 'Z':
        byte ANT;
        ANT = atol(buff + 1);
        switch (ANT) {
          case 0:
            if (BAND_FM || BAND_OIRT) radio.setCoax(2); else radio.setCoax(0);
            break;

          case 1:
            if (BAND_FM || BAND_OIRT) radio.setCoax(3); else radio.setCoax(1);
            break;

          case 2:
            // Antenna C
            break;

          case 3:
            // Antenna D
            break;
        }
        DataPrint("Z" + String(ANT) + "\n");
        break;
    }
    XDRGTKdata = false;
  }

  if (millis() >= signalstatustimer + 66) {
    if (band > BAND_GAP) {
      DataPrint("Sm");
    } else {
      if (!StereoToggle) {
        DataPrint("SM");
      } else if (Stereostatus) {
        DataPrint("Ss");
      } else {
        DataPrint("Sm");
      }
    }

    DataPrint(String(((SStatus * 100) + 10875) / 1000) + "." + String(((SStatus * 100) + 10875) / 100 % 10) + "," + String(WAM / 10) + "," + String(USN / 10) + "," + String(BW) + "\n\n");
    signalstatustimer = millis();
  }
}

void passwordcrypt() {
  int generated = 0;
  while (generated < 16)
  {
    byte randomValue = random(0, 26);
    char letter = randomValue + 'a';
    if (randomValue > 26) letter = (randomValue - 26);
    saltkey.setCharAt(generated, letter);
    generated ++;
  }
  salt = saltkey + XDRGTK_key;
  cryptedpassword = String(sha1(salt));
}

void tryWiFi() {
  if (!setupmode && wifi) {
    tft.drawRoundRect(1, 60, 319, 140, 5, ActiveColor);
    tft.fillRoundRect(3, 62, 315, 136, 5, BackgroundColor);
    tftPrint(0, myLanguage[language][55], 155, 88, ActiveColor, ActiveColorSmooth, 28);
  }
  if (wifi) {
    if (wc.autoConnect()) {
      Server.begin();
      Udp.begin(9031);
      remoteip = IPAddress (WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], subnetclient);
      if (!setupmode) tftPrint(0, myLanguage[language][57], 155, 128, InsignificantColor, InsignificantColorSmooth, 28);
    } else {
      if (!setupmode) tftPrint(0, myLanguage[language][56], 155, 128, SignificantColor, SignificantColorSmooth, 28);
      Server.end();
      Udp.stop();
      WiFi.mode(WIFI_OFF);
      wifi = false;
      XDRGTKTCP = false;
      RDSSPYTCP = false;
    }
  } else {
    Server.end();
    Udp.stop();
    WiFi.mode(WIFI_OFF);
  }
}