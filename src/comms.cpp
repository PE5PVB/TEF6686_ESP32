#include "comms.h"
#include "language.h"
#include "constants.h"
#include <EEPROM.h>

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

          if ((stlfreq.toInt()) / 10000 > 6500 && (stlfreq.toInt()) / 10000 < 10800) {
            unsigned int tempfreq = (stlfreq.toInt()) / 10000;
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
            if (afscreen || advancedRDS) {
              BuildDisplay();
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
      }
    }

    if (RDSSPYUSB && Serial.available()) {
      String data_str = Serial.readStringUntil('\n');
      int symPos = data_str.indexOf("*F");
      if (symPos >= 5) {
        String freq = data_str.substring(0, symPos);
        freq = freq.substring(0, freq.length() - 1);
        frequency = freq.toInt();
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

      case 'C':
        if (afscreen || advancedRDS) BuildDisplay();
        byte scanmethod;
        scanmethod = atol(buff + 1);
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

      case 'B':
        byte stmo;
        stmo = atol(buff + 1);
        DataPrint("B" + String(stmo) + "\n");
        if (stmo == 0) StereoToggle = false; else StereoToggle = true;
        doStereoToggle();
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

      case 'M':
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
        unsigned int freqtemp;
        freqtemp = atoi(buff + 1);
        if (BAND_FM) freqtemp -= ConverterSet * 1000;
        if (seek) seek = false;
        if (freqtemp >= LWLowEdgeSet && freqtemp <= LWHighEdgeSet) {
          frequency_LW = freqtemp;
          frequency_AM = freqtemp;
          if (afscreen || advancedRDS) BuildDisplay();
          if (band != BAND_LW) {
            band = BAND_LW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_LW);
        }
        if (freqtemp >= MWLowEdgeSet && freqtemp <= MWHighEdgeSet) {
          frequency_AM = freqtemp;
          frequency_MW = freqtemp;
          if (afscreen || advancedRDS) BuildDisplay();
          if (band != BAND_MW) {
            band = BAND_MW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_MW);
        }
        if (freqtemp >= SWLowEdgeSet && freqtemp <= SWHighEdgeSet) {
          frequency_SW = freqtemp;
          frequency_AM = freqtemp;
          if (afscreen || advancedRDS) BuildDisplay();
          if (band != BAND_SW) {
            band = BAND_SW;
            SelectBand();
            DataPrint("M1\n");
          }
          radio.SetFreqAM(frequency_SW);
        }
        if (freqtemp >= FREQ_FM_START && freqtemp <= FREQ_FM_END) {
          frequency = freqtemp / 10;
          if (afscreen) BuildAdvancedRDS();
          if (band != BAND_FM) {
            band = BAND_FM;
            SelectBand();
            DataPrint("M0\n");
          }
          radio.SetFreq(frequency);
        }
        if (band == BAND_FM) DataPrint("T" + String((frequency + ConverterSet * 100) * 10) + "\n"); else DataPrint("T" + String(frequency_AM) + "\n");
        ShowFreq(0);
        radio.clearRDS(fullsearchrds);
        RDSstatus = false;
        store = true;
        aftest = true;
        aftimer = millis();
        break;

      case 'Q':
        Squelch = atoi(buff + 1);
        if (Squelch == -1) {
          DataPrint("Q - 1\n");
        } else {
          Squelch *= 10;
          DataPrint("Q\n");
          DataPrint(String(Squelch / 10));
        }
        break;

      case 'S':
        if (buff[1] == 'a') {
          scanner_start = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'b') {
          scanner_end = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'c') {
          scanner_step = (atol(buff + 2) + 5) / 10;
        } else if (buff[1] == 'f') {
          scanner_filter = atol(buff + 2);
        } else if (scanner_start > 0 && scanner_end > 0 && scanner_step > 0 && scanner_filter >= 0) {
          frequencyold = frequency;
          DataPrint("U");
          if (scanner_filter < 0) {
            BWset = 0;
          } else if (scanner_filter == 0) {
            BWset = 1;
          } else if (scanner_filter == 26) {
            BWset = 2;
          } else if (scanner_filter == 1) {
            BWset = 3;
          } else if (scanner_filter == 28) {
            BWset = 4;
          } else if (scanner_filter == 29) {
            BWset = 5;
          } else if (scanner_filter == 3) {
            BWset = 6;
          } else if (scanner_filter == 4) {
            BWset = 7;
          } else if (scanner_filter == 5) {
            BWset = 8;
          } else if (scanner_filter == 7) {
            BWset = 9;
          } else if (scanner_filter == 8) {
            BWset = 10;
          } else if (scanner_filter == 9) {
            BWset = 11;
          } else if (scanner_filter == 10) {
            BWset = 12;
          } else if (scanner_filter == 11) {
            BWset = 13;
          } else if (scanner_filter == 12) {
            BWset = 14;
          } else if (scanner_filter == 13) {
            BWset = 15;
          } else if (scanner_filter == 15) {
            BWset = 16;
          }
          doBW();
          if (!screenmute) {
            tft.drawRoundRect(10, 30, 300, 170, 5, ActiveColor);
            tft.fillRoundRect(12, 32, 296, 166, 5, BackgroundColor);
            tftPrint(0, myLanguage[language][34], 160, 100, ActiveColor, ActiveColorSmooth, 28);
          }
          frequencyold = frequency;
          for (freq_scan = scanner_start; freq_scan <= scanner_end; freq_scan += scanner_step) {
            radio.SetFreq(freq_scan);
            DataPrint(String(freq_scan * 10, DEC));
            DataPrint(" = ");
            if (band < BAND_GAP) radio.getStatus(SStatus, USN, WAM, OStatus, BW, MStatus, CN); else  radio.getStatusAM(SStatus, USN, WAM, OStatus, BW, MStatus, CN);
            DataPrint(String((SStatus / 10) + 10, DEC));
            DataPrint(", ");
          }
          DataPrint("\n");
          radio.SetFreq(frequencyold);
          BuildDisplay();
          radio.setFMABandw();
          BWset = 0;
        }
        break;

      case 'W':
        unsigned int bwtemp;
        bwtemp = atoi(buff + 1);
        switch (bwtemp) {
          case 0:
            BWset = 0;
            doBW();
            break;

          case 56000:
            BWset = 1;
            doBW();
            break;

          case 64000:
            BWset = 2;
            doBW();
            break;

          case 72000:
            BWset = 3;
            doBW();
            break;

          case 84000:
            BWset = 4;
            doBW();
            break;

          case 97000:
            BWset = 5;
            doBW();
            break;

          case 114000:
            BWset = 6;
            doBW();
            break;

          case 133000:
            BWset = 7;
            doBW();
            break;

          case 151000:
            BWset = 8;
            doBW();
            break;

          case 168000:
            BWset = 9;
            doBW();
            break;

          case 184000:
            BWset = 10;
            doBW();
            break;

          case 200000:
            BWset = 11;
            doBW();
            break;

          case 217000:
            BWset = 12;
            doBW();
            break;

          case 236000:
            BWset = 13;
            doBW();
            break;

          case 254000:
            BWset = 14;
            doBW();
            break;

          case 287000:
            BWset = 15;
            doBW();
            break;

          case 311000:
            BWset = 16;
            doBW();
            break;
        }
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
          DataPrint("T" + String(frequency + (ConverterSet * 100) * 10) + "\n");
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
        VolSet = EEPROM.readInt(EE_BYTE_VOLSET);
        LowLevelSet = EEPROM.readInt(EE_BYTE_LOWLEVELSET);
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

    DataPrint(String(((SStatus * 100) + 10875) / 1000) + "." + String(((SStatus * 100) + 10875) / 100 % 10) + "," + String(WAM / 10) + ",-1\n\n");
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