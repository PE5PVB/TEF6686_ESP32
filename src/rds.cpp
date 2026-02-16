#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbool-compare"
#include "rds.h"
#include "constants.h"
#include <TimeLib.h>

String HexStringold;
float smoothBER = 0;

int RadiotextWidth, PSLongWidth, AIDWidth, afstringWidth, eonstringWidth, rtplusstringWidth, lengths[7];
String afstringold, eonstringold, rtplusstringold, stationNameLongOld, AIDStringold;
bool rtABold, ps12errorold, ps34errorold, ps56errorold, ps78errorold;

void ShowAdvancedRDS() {
  if (!dropout) {
    if (radio.rds.rdsAerror) tft.fillCircle(86, 41, 5, SignificantColor); else tft.fillCircle(86, 41, 5, InsignificantColor);
    if (radio.rds.rdsBerror) tft.fillCircle(124, 41, 5, SignificantColor); else tft.fillCircle(124, 41, 5, InsignificantColor);
    if (radio.rds.rdsCerror) tft.fillCircle(162, 41, 5, SignificantColor); else tft.fillCircle(162, 41, 5, InsignificantColor);
    if (radio.rds.rdsDerror) tft.fillCircle(200, 41, 5, SignificantColor); else tft.fillCircle(200, 41, 5, InsignificantColor);
  }

  if (radio.rds.hasDynamicPTY != dynamicPTYold) {
    if (radio.rds.hasDynamicPTY) tft.fillCircle(310, 137, 5, InsignificantColor); else tft.fillCircle(310, 137, 5, SignificantColor);
    dynamicPTYold = radio.rds.hasDynamicPTY;
  }

  if (radio.rds.hasArtificialhead != artheadold) {
    if (radio.rds.hasArtificialhead) tft.fillCircle(310, 153, 5, InsignificantColor); else tft.fillCircle(310, 153, 5, SignificantColor);
    artheadold = radio.rds.hasArtificialhead;
  }

  if (radio.rds.hasCompressed != compressedold) {
    if (radio.rds.hasCompressed) tft.fillCircle(310, 168, 5, InsignificantColor); else tft.fillCircle(310, 168, 5, SignificantColor);
    compressedold = radio.rds.hasCompressed;
  }

  if (radio.rds.hasStereo != rdsstereoold) {
    if (radio.rds.hasStereo) tft.fillCircle(310, 183, 5, InsignificantColor); else tft.fillCircle(310, 183, 5, SignificantColor);
    rdsstereoold = radio.rds.hasStereo;
  }

  if (ptynold != radio.rds.PTYN || rdsreset) {
    if (!screenmute) {
      if (ptynold != "PTYN N/A" || radio.rds.hasPTYN) {
        tftPrint(ALEFT, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, 16);
        tftPrint(ALEFT, ptynold, 216, 109, BackgroundColor, BackgroundColor, 16);
      }
      if (!radio.rds.hasPTYN) radio.rds.PTYN = "PTYN N/A";
      tftPrint(ALEFT, String(radio.rds.PTYN), 216, 109, RDSColor, RDSColorSmooth, 16);
      ptynold = radio.rds.PTYN;
    }
  }

  if (licold != radio.rds.LIC || rdsreset) {
    if (!screenmute) {
      if (radio.rds.hasLIC) LICString = (radio.rds.LICtext.length() == 0 ? textUI(73) : radio.rds.LICtext); else LICString = "N/A";
      if (LICString != LIColdString) {
        tftPrint(ALEFT, "N/A", 242, 208, BackgroundColor, BackgroundColor, 16);
        tftPrint(ALEFT, LIColdString, 242, 208, BackgroundColor, BackgroundColor, 16);
      }
      tftPrint(ALEFT, LICString, 242, 208, RDSColor, RDSColorSmooth, 16);
      LIColdString = LICString;
      licold = radio.rds.LIC;
    }
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    if (!screenmute)  {
      tftPrint(ALEFT, "N/A", 242, 223, BackgroundColor, BackgroundColor, 16);
      tftPrint(ALEFT, pinstringold, 242, 223, BackgroundColor, BackgroundColor, 16);

      if (radio.rds.hasPIN) tftPrint(ALEFT, pinstring, 242, 223, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "N/A", 242, 223, RDSColor, RDSColorSmooth, 16);
      pinstringold = pinstring;
    }
  }

  String afstring;
  if (radio.rds.hasAF && radio.af_counter > 0) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (i == radio.af_counter - 1 ? "        " : " | "); else afstring = textUI(87);
  if (hasafold != radio.rds.hasAF) {
    if (!screenmute) {
      if (radio.rds.hasAF) tftPrint(ALEFT, "AF", 50, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "AF", 50, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasafold = radio.rds.hasAF;
  }

  if (afstring != afstringold) {
    afstringWidth = RDSSprite.textWidth(afstring);
    afstringold = afstring;
  }

  if (RDSSprite.textWidth(radio.trimTrailingSpaces(afstring)) < 165) {
    xPos2 = 0;
    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(afstring, xPos2, 2);
    RDSSprite.pushSprite(35, 197);
  } else {
    if (millis() - afticker >= 5) {
      if (xPos2 < -afstringWidth) xPos2 = 0;
      if (xPos2 == 0) {
        if (millis() - aftickerhold >= 2000) {
          xPos2 --;
          aftickerhold = millis();
        }
      } else {
        xPos2 --;
        aftickerhold = millis();
      }
      RDSSprite.fillSprite(BackgroundColor);
      if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
      RDSSprite.drawString(afstring, xPos2, 2);
      RDSSprite.drawString(afstring, xPos2 + afstringWidth, 2);
      RDSSprite.pushSprite(35, 197);
      afticker = millis();
    }
  }

  String eonstring;
  if (radio.eon_counter > 0) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "        " : " | "); else eonstring = textUI(88);
  if (haseonold != radio.rds.hasEON) {
    if (!screenmute)  {
      if (radio.eon_counter > 0) tftPrint(ALEFT, "EON", 153, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "EON", 153, 51, GreyoutColor, BackgroundColor, 16);
    }
    haseonold = radio.rds.hasEON;
  }

  if (eonstring != eonstringold) {
    eonstringWidth = RDSSprite.textWidth(eonstring);
    eonstringold = eonstring;
  }

  if (eonstringWidth < 165) {
    xPos3 = 0;
    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(eonstring, xPos3, 2);
    RDSSprite.pushSprite(35, 172);
  } else {
    if (millis() - eonticker >= 5) {
      if (xPos3 < -eonstringWidth) xPos3 = 0;
      if (xPos3 == 0) {
        if (millis() - eontickerhold >= 2000) {
          xPos3 --;
          eontickerhold = millis();
        }
      } else {
        xPos3 --;
        eontickerhold = millis();
      }
      RDSSprite.fillSprite(BackgroundColor);
      if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
      RDSSprite.drawString(eonstring, xPos3, 2);
      RDSSprite.drawString(eonstring, xPos3 + eonstringWidth, 2);
      RDSSprite.pushSprite(35, 172);
      eonticker = millis();
    }
  }

  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = (radio.rds.rdsplusTag1 != 169 ? String(textUI(radio.rds.rdsplusTag1)) + ": " + String(radio.rds.RTContent1) : "") + (radio.rds.rdsplusTag2 != 169 ? " - " + String(textUI(radio.rds.rdsplusTag2)) + ": " + String(radio.rds.RTContent2) : "") + "        "; else rtplusstring = textUI(89);
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (!screenmute) {
      if (radio.rds.hasRDSplus) tftPrint(ALEFT, "RT+", 123, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "RT+", 123, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasrtplusold = radio.rds.hasRDSplus;
  }

  if (rtplusstring != rtplusstringold) {
    rtplusstringWidth = RDSSprite.textWidth(rtplusstring);
    rtplusstringold = rtplusstring;
  }

  if (rtplusstringWidth < 165) {
    xPos4 = 0;
    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(rtplusstring, xPos4, 2);
    RDSSprite.pushSprite(35, 146);
  } else {
    if (millis() - rtplusticker >= 5) {
      if (xPos4 < -rtplusstringWidth) xPos4 = 0;
      if (xPos4 == 0) {
        if (millis() - rtplustickerhold >= 2000) {
          xPos4 --;
          rtplustickerhold = millis();
        }
      } else {
        xPos4 --;
        rtplustickerhold = millis();
      }
      RDSSprite.fillSprite(BackgroundColor);
      if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
      RDSSprite.drawString(rtplusstring, xPos4, 2);
      RDSSprite.drawString(rtplusstring, xPos4 + rtplusstringWidth, 2);
      RDSSprite.pushSprite(35, 146);
      rtplusticker = millis();
    }
  }

  if (TPold != radio.rds.hasTP) {
    if (!screenmute) {
      if (radio.rds.hasTP) tftPrint(ALEFT, "TP", 2, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "TP", 2, 51, GreyoutColor, BackgroundColor, 16);
    }
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    if (!screenmute) {
      if (radio.rds.hasTA) tftPrint(ALEFT, "TA", 24, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "TA", 24, 51, GreyoutColor, BackgroundColor, 16);
    }
    TAold = radio.rds.hasTA;
  }

  if (afmethodBold != radio.afmethodB || rdsreset) {
    if (!screenmute) {
      if (radio.afmethodB) tftPrint(ALEFT, "-B", 68, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "-B", 68, 51, GreyoutColor, BackgroundColor, 16);
    }
    afmethodBold = radio.afmethodB;
  }

  if (MSold != radio.rds.MS) {
    if (!screenmute) {
      switch (radio.rds.MS) {
        case 0:
          tftPrint(ALEFT, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(ALEFT, "S", 185, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 1:
          tftPrint(ALEFT, "M", 196, 51, RDSColor, RDSColorSmooth, 16);
          tftPrint(ALEFT, "S", 185, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 2:
          tftPrint(ALEFT, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(ALEFT, "S", 185, 51, RDSColor, RDSColorSmooth, 16);
          break;
      }
    }
    MSold = radio.rds.MS;
  }

  if (rdsblockold != radio.rdsblock) {
    if (rdsblockold < 33) tft.fillCircle((6 * rdsblockold) + 10, 133, 2, SignificantColor);
    if (radio.rdsblock < 33) tft.fillCircle((6 * radio.rdsblock) + 10, 133, 2, InsignificantColor);
    rdsblockold = radio.rdsblock;
  }

  if (hastmcold != radio.rds.hasTMC) {
    if (!screenmute) {
      if (radio.rds.hasTMC) tftPrint(ALEFT, "TMC", 88, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(ALEFT, "TMC", 88, 51, GreyoutColor, BackgroundColor, 16);
    }
    hastmcold = radio.rds.hasTMC;
  }

  rdsreset = false;
}

void doAF() {
  if (radio.af_counter != af_counterold && radio.rds.hasAF) {
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";AF=");

      for (byte af_scan = 0; af_scan < radio.af_counter; af_scan++) {
        if (wifi) {
          if ((radio.af[af_scan].frequency - 8750) / 10 < 0x10) {
            Udp.print("0");
          }
          Udp.print(String((radio.af[af_scan].frequency - 8750) / 10, HEX));
        }
      }

      for (int i = 0; i < 25 - radio.af_counter; i++) Udp.print("00");
      Udp.endPacket();
    }
    af_counterold = radio.af_counter;
  }
}

void showECC() {
  if (ECCold != radio.rds.ECC) {
    if (advancedRDS) {
      if (!screenmute) {
        if (radio.rds.hasECC) ECCString = (radio.rds.ECCtext.length() == 0 ? textUI(73) : radio.rds.ECCtext); else ECCString = "N/A";
        if (ECCString != ECColdString) {
          tftPrint(ALEFT, "N/A", 242, 193, BackgroundColor, BackgroundColor, 16);
          tftPrint(ALEFT, ECColdString, 242, 193, BackgroundColor, BackgroundColor, 16);
        }
        tftPrint(ALEFT, ECCString, 242, 193, RDSColor, RDSColorSmooth, 16);
      }
      ECColdString = ECCString;
    }

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";ECC=");
      if (radio.rds.ECC < 0x10) Udp.print("0");
      Udp.print(String(radio.rds.ECC, HEX));
      Udp.endPacket();
    }
    ECCold = radio.rds.ECC;
  }
}

void readRds() {
  // Only process RDS on FM bands
  if (band >= BAND_GAP) return;

  // Read RDS data from tuner
  radio.readRDS(showrdserrors);
  RDSstatus = radio.rds.hasRDS;
  ShowRDSLogo(RDSstatus);

  // Handle RDS dropout / recovery only when screen is active
  if (!screenmute && !afscreen) {
    if (!RDSstatus) {
      // --- RDS dropout (lost signal) ---
      if (radio.rds.correctPI != 0 && !dropout) {
        if (!rdsstatscreen) {
          if (radio.rds.region == 0) {
            tftPrint(ACENTER, PIold, 275, advancedRDS ? 75 : 187,
                     RDSDropoutColor, RDSDropoutColorSmooth, 28);
          } else {
            tftPrint(ALEFT, PIold, 240, advancedRDS ? 72 : 184,
                     RDSDropoutColor, RDSDropoutColorSmooth, 16);
            tftPrint(ALEFT, stationIDold, 240, advancedRDS ? 89 : 201,
                     RDSDropoutColor, RDSDropoutColorSmooth, 16);
            tftPrint( 1, stationStateold, 318, advancedRDS ? 89 : 201,
                      RDSDropoutColor, RDSDropoutColorSmooth, 16);
          }

          if (!radio.rds.hasLongPS) {
            PSSprite.fillSprite(BackgroundColor);
            PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
            PSSprite.drawString(PSold, 0, 2);
            PSSprite.pushSprite(36, advancedRDS ? 72 : 185);
          }

          tftPrint(ALEFT, PTYold, 34, advancedRDS ? 109 : 163,
                   RDSDropoutColor, RDSDropoutColorSmooth, 16);

        }

        if (rdsstatscreen && berPercentold != 100) {
          tftReplace(ARIGHT, String(berPercentold) + "%", "100%",
                     318, 34, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
          berPercentold = 100;
        }

        if (advancedRDS || rdsstatscreen) {
          tft.fillCircle( 86, 41, 5, SignificantColor);
          tft.fillCircle(124, 41, 5, SignificantColor);
          tft.fillCircle(162, 41, 5, SignificantColor);
          tft.fillCircle(200, 41, 5, SignificantColor);
        }
        dropout = true;
      }
    } else {
      // --- RDS recovery or memory reset ---
      if (dropout || memreset) {
        if (!rdsstatscreen) {
          if (radio.rds.region == 0) {
            tftPrint(ACENTER, PIold, 275, advancedRDS ? 75 : 187,
                     RDSColor, RDSColorSmooth, 28);
          } else {
            tftPrint(ALEFT, PIold, 240, advancedRDS ? 72 : 184,
                     RDSColor, RDSColorSmooth, 16);
            tftPrint(ALEFT, stationIDold, 240, advancedRDS ? 89 : 201,
                     RDSColor, RDSColorSmooth, 16);
            tftPrint( 1, stationStateold, 318, advancedRDS ? 89 : 201,
                      advancedRDS ? RDSColor : RDSDropoutColor,
                      advancedRDS ? RDSColorSmooth : RDSDropoutColorSmooth, 16);
          }

          // PS handling
          if (!radio.rds.hasLongPS) {
            PSSprite.fillSprite(BackgroundColor);
            if ((ps12errorold || ps34errorold || ps56errorold || ps78errorold) && radio.ps_process) {
              // Mark partial errors
              for (uint8_t i = 0; i < 7; i++) {
                bool error = (i < 2 && ps12errorold) ||
                             (i < 4 && ps34errorold) ||
                             (i < 6 && ps56errorold) || ps78errorold;
                PSSprite.setTextColor(error ? RDSDropoutColor : RDSColor,
                                      RDSColorSmooth, false);
                PSSprite.drawString(radio.rds.stationName.substring(i, i + 1),
                                    i == 0 ? 0 : lengths[i - 1], 2);
              }
            } else {
              // Print clean PS
              PSSprite.setTextColor(RDSColor, RDSColorSmooth, false);
              PSSprite.drawString(PSold, 0, 2);
            }
            PSSprite.pushSprite(36, advancedRDS ? 72 : 185);
          }

          tftPrint(ALEFT, PTYold, 34, advancedRDS ? 109 : 163,
                   RDSColor, RDSColorSmooth, 16);

          if (!advancedRDS) {
            tft.fillCircle(314, 223, 2, GreyoutColor);
            tft.fillCircle(314, 234, 2, GreyoutColor);
          } else {
            tft.fillCircle(203, 223, 2, GreyoutColor);
            tft.fillCircle(203, 234, 2, GreyoutColor);
          }
        }
        dropout = false;
        memreset = false;
      }
    }
  }

  // --- Data output for RDS Spy / XDRGTK ---
  if (bitRead(radio.rds.rdsStat, 9)) {
    char hexbuf[5];  // buffer for 4-digit HEX

    // RDS Spy output
    if (RDSstatus && (RDSSPYUSB || RDSSPYTCP)) {
      RDSSPYRDS = F("G:\r\n");
      uint16_t blocks[4] = {radio.rds.rdsA, radio.rds.rdsB,
                            radio.rds.rdsC, radio.rds.rdsD
                           };
      bool errors[4] = {radio.rds.rdsAerror, radio.rds.rdsBerror,
                        radio.rds.rdsCerror, radio.rds.rdsDerror
                       };

      for (uint8_t i = 0; i < 4; i++) {
        if (errors[i]) {
          RDSSPYRDS += F("----");
        } else {
          sprintf(hexbuf, "%04X", blocks[i]); // format word into HEX
          RDSSPYRDS += hexbuf;
        }
      }
      RDSSPYRDS += F("\r\n\r\n");

      if (RDSSPYRDS != RDSSPYRDSold) {
        if (RDSSPYUSB) {
          Serial.print(RDSSPYRDS);
        } else {
          RemoteClient.print(RDSSPYRDS);
        }
        RDSSPYRDSold = RDSSPYRDS;
      }
    }

    // XDRGTK output
    if (RDSstatus && (XDRGTKUSB || XDRGTKTCP)) {
      XDRGTKRDS = F("R");
      sprintf(hexbuf, "%04X", radio.rds.rdsB); XDRGTKRDS += hexbuf;
      sprintf(hexbuf, "%04X", radio.rds.rdsC); XDRGTKRDS += hexbuf;
      sprintf(hexbuf, "%04X", radio.rds.rdsD); XDRGTKRDS += hexbuf;

      // Pack error bits
      uint8_t erroutput = 0;
      erroutput |= ((radio.rds.rdsErr >> 8) & B00110000) >> 4;
      erroutput |= ((radio.rds.rdsErr >> 8) & B00001100);
      erroutput |= ((radio.rds.rdsErr >> 8) & B00000011) << 4;

      sprintf(hexbuf, "%X%X", (erroutput >> 4) & 0xF, erroutput & 0xF);
      XDRGTKRDS += hexbuf;
      XDRGTKRDS += '\n';

      if (XDRGTKRDS != XDRGTKRDSold) {
        uint8_t piError = radio.rds.rdsErr >> 14;
        if (piError < 3) {
          uint8_t piState = radio.rds.piBuffer.add(radio.rds.rdsA, piError);
          if (piState != RdsPiBuffer::STATE_INVALID) {
            DataPrint(F("P"));
            sprintf(hexbuf, "%04X", radio.rds.rdsA);
            DataPrint(hexbuf);
            while (piState--) DataPrint(F("?"));
            DataPrint(F("\n"));
          }
        }
        XDRGTKRDSold = XDRGTKRDS;
        XDRGTKRDS.toUpperCase();
        DataPrint(XDRGTKRDS);
      }
    }
  }
}

void ShowErrors() {
  uint8_t calc = 4;
  if (RDSstatus && !rdsreset) {
    if (!radio.rds.rdsAerror) calc--;
    if (!radio.rds.rdsBerror) calc--;
    if (!radio.rds.rdsCerror) calc--;
    if (!radio.rds.rdsDerror) calc--;

    SAvg3 = (((SAvg3 * 9) + 5) / 10) + calc;
    calc = SAvg3 / 10;
  }

  rdsreset = false;

  if (calc != rdsqualityold || BWreset) {
    switch (calc) {
      case 0:
        tft.fillRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, BarInsignificantColor);
        tft.fillRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, BarInsignificantColor);
        tft.fillRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, BarInsignificantColor);
        tft.fillRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, BarInsignificantColor);
        break;

      case 1:
        tft.fillRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, BackgroundColor);
        tft.drawRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, GreyoutColor);

        tft.fillRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, BarInsignificantColor);
        tft.fillRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, BarInsignificantColor);
        tft.fillRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, BarInsignificantColor);
        break;

      case 2:
        tft.fillRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, BackgroundColor);
        tft.drawRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, GreyoutColor);

        tft.fillRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, BackgroundColor);
        tft.drawRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, GreyoutColor);

        tft.fillRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, BarSignificantColor);
        tft.fillRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, BarSignificantColor);
        break;

      case 3:
        tft.fillRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, BackgroundColor);
        tft.drawRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, GreyoutColor);

        tft.fillRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, BackgroundColor);
        tft.drawRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, GreyoutColor);

        tft.fillRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, BackgroundColor);
        tft.drawRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, GreyoutColor);

        tft.fillRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, BarSignificantColor);
        break;

      case 4:
        tft.fillRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, BackgroundColor);
        tft.drawRoundRect(205, (advancedRDS ? 74 : 186), 4, 26, 2, GreyoutColor);

        tft.fillRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, BackgroundColor);
        tft.drawRoundRect(199, (advancedRDS ? 80 : 192), 4, 20, 2, GreyoutColor);

        tft.fillRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, BackgroundColor);
        tft.drawRoundRect(193, (advancedRDS ? 86 : 198), 4, 14, 2, GreyoutColor);

        tft.fillRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, BackgroundColor);
        tft.drawRoundRect(187, (advancedRDS ? 92 : 204), 4, 8, 2, GreyoutColor);
        break;
    }
    rdsqualityold = calc;
  }
}

void showPI() {
  if ((radio.rds.region != 0 && (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold || radio.rds.stationStatetext != stationStateold)) || (radio.rds.region == 0 && String(radio.rds.picode) != PIold)) {
    if (!rdsstatscreen && !afscreen && !radio.rds.rdsAerror && !radio.rds.rdsBerror && !radio.rds.rdsCerror && !radio.rds.rdsDerror && radio.rds.rdsA != radio.rds.correctPI && PIold.length() > 1) {
      radio.clearRDS(fullsearchrds);
      if (RDSSPYUSB) Serial.print("G:\r\nRESET-------\r\n\r\n");
      if (RDSSPYTCP) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
    }

    if (!screenmute) {
      if (advancedRDS) {
        if (radio.rds.region == 0) {
          if (!RDSstatus) {
            tftReplace(ACENTER, PIold, radio.rds.picode, 275, 75, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 28);
          } else {
            tftReplace(ACENTER, PIold, radio.rds.picode, 275, 75, RDSColor, RDSColorSmooth, BackgroundColor, 28);
          }
        } else {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold) tftReplace(ALEFT, PIold, radio.rds.picode, 240, 72, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
            tftReplace(ALEFT, stationIDold, radio.rds.stationIDtext, 240, 89, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
          } else {
            if (String(radio.rds.picode) != PIold) tftReplace(ALEFT, PIold, radio.rds.picode, 240, 72, RDSColor, RDSColorSmooth, BackgroundColor, 16);
            tftReplace(ALEFT, stationIDold, radio.rds.stationIDtext, 240, 89, RDSColor, RDSColorSmooth, BackgroundColor, 16);
          }
          tftReplace(ARIGHT, stationStateold, radio.rds.stationStatetext, 318, 89, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        }
      } else if (afscreen) {
        tftReplace(ALEFT, PIold, radio.rds.picode, 30, 201, BWAutoColor, BWAutoColorSmooth, BackgroundColor, 16);
      } else if (!rdsstatscreen) {
        if (radio.rds.region == 0) {
          if (!RDSstatus) {
            tftReplace(ACENTER, PIold, radio.rds.picode, 275, 187, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 28);
          } else {
            tftReplace(ACENTER, PIold, radio.rds.picode, 275, 187, RDSColor, RDSColorSmooth, BackgroundColor, 28);
          }
        } else {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold || radio.rds.stationStatetext != stationStateold) {
              tftReplace(ALEFT, PIold, radio.rds.picode, 240, 184, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
              tftReplace(ALEFT, stationIDold, radio.rds.stationIDtext, 240, 201, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
              tftReplace(ARIGHT, stationStateold, radio.rds.stationStatetext, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
            }
          } else {
            if (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold) {
              tftReplace(ALEFT, PIold, radio.rds.picode, 240, 184, RDSColor, RDSColorSmooth, BackgroundColor, 16);
              tftReplace(ALEFT, stationIDold, radio.rds.stationIDtext, 240, 201, RDSColor, RDSColorSmooth, BackgroundColor, 16);
              tftReplace(ARIGHT, stationStateold, radio.rds.stationStatetext, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
            }
          }
        }
      }
      PIold = radio.rds.picode;
      stationIDold = radio.rds.stationIDtext;
      stationStateold = radio.rds.stationStatetext;
    }

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";PI=" + String(radio.rds.picode, 4));
      Udp.endPacket();
    }
  }
}

void showPTY() {
  if (strcmp(radio.rds.stationType, programTypePrevious)) {
    String PTYString = String(radio.rds.stationTypeCode) + "/" + (radio.rds.region != 0 ? radio.rds.stationType : textUI(228 + radio.rds.stationTypeCode));

    if (radio.rds.stationTypeCode == 32) PTYString = "";

    if (!screenmute) {
      if (advancedRDS) {
        if (!RDSstatus) {
          tftReplace(ALEFT, PTYold, PTYString, 34, 109, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        } else {
          tftReplace(ALEFT, PTYold, PTYString, 34, 109, RDSColor, RDSColorSmooth, BackgroundColor, 16);
        }
      } else {
        if (!RDSstatus) {
          tftReplace(ALEFT, PTYold, PTYString, 34, 163, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        } else {
          tftReplace(ALEFT, PTYold, PTYString, 34, 163, RDSColor, RDSColorSmooth, BackgroundColor, 16);
        }
      }
    }
    PTYold = PTYString;

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";PTY=");
      Udp.print(String(radio.rds.stationTypeCode, HEX));
      Udp.endPacket();
    }
    strcpy(programTypePrevious, radio.rds.stationType);
  }
}

void showPS() {
  // Check if station name or errors have changed, or long PS should be displayed
  if ((radio.rds.stationName != PSold) ||
      (RDSstatus && !(ps12errorold == radio.rds.ps12error ||
                      ps34errorold == radio.rds.ps34error ||
                      ps56errorold == radio.rds.ps56error ||
                      ps78errorold == radio.rds.ps78error)) ||
      (radio.rds.hasLongPS && showlongps)) {

    // Handle AF screen update
    if (afscreen) {
      if (!screenmute) {
        tftReplace(ACENTER, PSold, radio.rds.stationName, 160, 201, BWAutoColor, BWAutoColorSmooth, BackgroundColor, 16);
      }
    } else if (!rdsstatscreen) {
      // Handle long PS display
      if (radio.rds.hasLongPS && showlongps) {
        String stationNameLongString = String(radio.rds.stationNameLong) + "     "; // Add trailing spaces for scrolling
        if (stationNameLongString != stationNameLongOld) {
          PSLongWidth = PSSprite.textWidth(stationNameLongString); // Measure new width
          stationNameLongOld = stationNameLongString;
        }

        // Handle scrolling logic for long PS
        if (PSSprite.textWidth(radio.trimTrailingSpaces(radio.rds.stationNameLong)) < 150) {
          xPos5 = 0;
          PSSprite.fillSprite(BackgroundColor);
          PSSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
          PSSprite.drawString(stationNameLongString, xPos5, 2);
        } else {
          if (millis() - pslongticker >= 5) {
            if (xPos5 < -PSLongWidth) xPos5 = 0; // Reset position if fully scrolled
            if (xPos5 == 0 && millis() - pslongtickerhold >= 2000) {
              xPos5--; // Hold position for 2 seconds before scrolling
              pslongtickerhold = millis();
            } else {
              xPos5--; // Scroll
            }
            pslongticker = millis();

            // Draw scrolling PS
            PSSprite.fillSprite(BackgroundColor);
            PSSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
            PSSprite.drawString(stationNameLongString, xPos5, 2);
            PSSprite.drawString(stationNameLongString, xPos5 + PSLongWidth, 2);
          }
        }
      } else {
        // Handle normal PS display
        xPos5 = 0;
        PSSprite.fillSprite(BackgroundColor);

        // Calculate widths for individual characters (ensures proper spacing)
        for (int i = 0; i < 7; i++) {
          lengths[i] = PSSprite.textWidth(radio.rds.stationName.substring(0, i + 1));
          if (i > 0 && lengths[i] <= lengths[i - 1]) {
            lengths[i] = lengths[i - 1] + 23; // Ensure consistent spacing
          }
        }

        // Update error states only when their respective flags are true
        if (ps12errorold) ps12errorold = radio.rds.ps12error;
        if (ps34errorold) ps34errorold = radio.rds.ps34error;
        if (ps56errorold) ps56errorold = radio.rds.ps56error;
        if (ps78errorold) ps78errorold = radio.rds.ps78error;

        // Set text color based on RDS status and error state
        if (!RDSstatus || band > BAND_GAP) {
          PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
          PSSprite.drawString(radio.rds.stationName, 0, 2);
        } else if ((ps12errorold || ps34errorold || ps56errorold || ps78errorold) && radio.ps_process) {
          for (int i = 0; i < 7; i++) {
            PSSprite.setTextColor((i < 2 && ps12errorold) || (i < 4 && ps34errorold) ||
                                  (i < 6 && ps56errorold) || ps78errorold ?
                                  RDSDropoutColor : RDSColor,
                                  RDSColorSmooth, false);
            PSSprite.drawString(radio.rds.stationName.substring(i, i + 1), i == 0 ? 0 : lengths[i - 1], 2);
          }
        } else {
          PSSprite.setTextColor(RDSColor, RDSColorSmooth, false);
          PSSprite.drawString(radio.rds.stationName, 0, 2);
        }

        // Reset PS error flags if the station name changes
        if (PSold != radio.rds.stationName) {
          ps12errorold = ps34errorold = ps56errorold = ps78errorold = true;
        }
      }

      // Push updated sprite to screen
      if (!screenmute) {
        PSSprite.pushSprite(36, advancedRDS ? 72 : 185);
      }

      // Handle WiFi update if PS has changed
      if (wifi && radio.rds.stationName.length() > 0 && PSold != radio.rds.stationName) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";PS=");
        char PShex[9];
        radio.rds.stationName.toCharArray(PShex, 9);
        for (int i = 0; i < 8; i++) {
          if (PShex[i] < 0x10) Udp.print("0");
          if (PShex[i] == 0x20) PShex[i] = '_';
          Udp.print(String(PShex[i], HEX));
        }
        Udp.endPacket();
      }
    }

    // Save the updated station name
    PSold = radio.rds.stationName;
  }
}

void showCT() {
  // Temporary string buffers for time and date formatting
  char timeStr[16];   // Increased buffer size to 16
  char dateStr[9];    // DD-MM-YY
  time_t t;

  // Determine the current time source
  if (radio.rds.hasCT && !dropout && !NTPupdated) {
    t = radio.rds.time + radio.rds.offset;
  } else {
    t = rtc.getEpoch() + (NTPupdated ? 0 : radio.rds.offset);

    // Update RDS time during dropout
    if (dropout) {
      radio.rds.time = static_cast<time_t>(rtc.getEpoch());
    }
  }

  // Apply the GMT offset only if NTPupdated is true
  if (NTPupdated) {
    t += NTPoffset * 3600; // Convert offset from hours to seconds

    // Apply DST adjustment if autoDST is enabled
    if (autoDST && isDST(t)) {
      t += 3600; // Add 1 hour for DST
    }
  }

  // Format the time based on region
  if (clockampm) { // USA region: 12-hour AM/PM format
    int hour = localtime(&t)->tm_hour;

    // Ensure the hour is valid (between 1-12)
    if (hour < 1 || hour > 12) {
      if (hour == 0) {
        hour = 12;  // Midnight case
      } else if (hour > 12) {
        hour -= 12;  // Convert PM hours
      }
    }

    String ampm = (localtime(&t)->tm_hour >= 12) ? "PM" : "AM";
    snprintf(timeStr, sizeof(timeStr), "%d:%02d %s", hour, localtime(&t)->tm_min, ampm.c_str());
  } else { // Other regions: 24-hour format
    int hour = localtime(&t)->tm_hour;

    // Ensure the hour is valid (between 0-23)
    if (hour < 0 || hour > 23) {
      hour = 0; // Invalid hour, reset to 0
    }

    snprintf(timeStr, sizeof(timeStr), "%02d:%02d", hour, localtime(&t)->tm_min);
  }

  // Store formatted time in rds_clock
  rds_clock = String(timeStr);

  // Format the date as DD-MM-YY
  if (clockampm) {
    strftime(dateStr, sizeof(dateStr), "%m-%d-%y", localtime(&t));
  } else {
    strftime(dateStr, sizeof(dateStr), "%d-%m-%y", localtime(&t));
  }
  rds_date = String(dateStr);

  // Check if the clock or RDS CT status has changed
  if (!screenmute && showclock && (rds_clock != rds_clockold || rds_date != rds_dateold || hasCTold != radio.rds.hasCT)) {

    // Update RTC if RDS CT is available or NTP was updated
    if ((radio.rds.hasCT && RDSstatus) || NTPupdated) {
      rtcset = true;
      if (!NTPupdated) {
        rtc.setTime(radio.rds.time);
      }

      // Display the updated time and date
      tftReplace(ACENTER, rds_clockold, rds_clock, 134, 1, RDSColor, RDSColorSmooth, BackgroundColor, 16);
      tftReplace(ACENTER, rds_dateold, rds_date, 134, 15, RDSColor, RDSColorSmooth, BackgroundColor, 16);
    } else { // Handle dropout scenarios
      if (rtcset) { // Display dropout message if RTC was set
        tftReplace(ACENTER, rds_clockold, rds_clock, 134, 1, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        tftReplace(ACENTER, rds_dateold, rds_date, 134, 15, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
      } else { // Clear and reprint the clock and date
        tftPrint(ACENTER, rds_clockold, 134, 1, BackgroundColor, BackgroundColor, 16);
        tftPrint(ACENTER, rds_clock, 134, 1, BackgroundColor, BackgroundColor, 16);
        tftPrint(ACENTER, rds_dateold, 134, 15, BackgroundColor, BackgroundColor, 16);
        tftPrint(ACENTER, rds_date, 134, 15, BackgroundColor, BackgroundColor, 16);
      }
    }
  }

  // Update previous clock, date, and RDS CT status
  rds_clockold = rds_clock;
  rds_dateold = rds_date;
  hasCTold = radio.rds.hasCT;
}

void showRadioText() {
  // Build the radio text string
  String RTString = String(
                      radio.rds.stationText +
                      (radio.rds.stationText.length() > 0 ? " " : "") +
                      radio.rds.stationText32 +
                      (radio.rds.hasEnhancedRT ? " eRT: " + String(radio.rds.enhancedRTtext) : "") +
                      "      "
                    );

  // Check if RT has changed
  if (radio.rds.hasRT && radio.rds.rtAB != rtABold) {
    xPos = 0; // Reset ticker position
    rttickerhold = millis(); // Hold the ticker momentarily
    rtABold = radio.rds.rtAB; // Update old AB status
  }

  if (!screenmute) {
    // Display RDS information if RT is available
    if (radio.rds.hasRT &&
        (radio.rds.stationText.length() > 0 || radio.rds.stationText32.length() > 0)) {

      // Determine whether to use advanced RDS mode
      if (advancedRDS && RDSSprite.textWidth(radio.trimTrailingSpaces(RTString)) < 165) {
        xPos = 0;
        RDSSprite.fillSprite(BackgroundColor);
        RDSSprite.setTextDatum(TL_DATUM);
        RDSSprite.setTextColor(
          RDSstatus ? RDSColor : RDSDropoutColor,
          RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth,
          false
        );
        RDSSprite.drawString(RTString, xPos, 2);
        RDSSprite.pushSprite(36, 220);
      } else if (!advancedRDS && RDSSprite.textWidth(radio.trimTrailingSpaces(RTString)) < 270) {
        xPos = 0;
        FullLineSprite.fillSprite(BackgroundColor);
        FullLineSprite.setTextDatum(TL_DATUM);
        FullLineSprite.setTextColor(
          RDSstatus ? RDSColor : RDSDropoutColor,
          RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth,
          false
        );
        FullLineSprite.drawString(RTString, xPos, 2);
        FullLineSprite.fillRect(275, 0, 8, 19, BackgroundColor);
        FullLineSprite.drawLine(283, 0, 283, 19, FrameColor);

        if (radio.rds.hasRT) {
          FullLineSprite.fillCircle(278, 3, 2, radio.rds.rtAB ? GreyoutColor : InsignificantColor);
          FullLineSprite.fillCircle(278, 14, 2, radio.rds.rtAB ? InsignificantColor : GreyoutColor);
        }

        FullLineSprite.pushSprite(36, 220);
      } else {
        // Handle scrolling text
        if (millis() - rtticker >= (advancedRDS ? 5 : 15)) {
          if (xPos == 0 && millis() - rttickerhold < 1000) {
            // Wait for a moment before scrolling
          } else {
            xPos--;
            rttickerhold = millis(); // Update hold time only when xPos changes
          }

          if (xPos < -RadiotextWidth) xPos = 0; // Reset position if scrolled off

          if (advancedRDS) {
            RDSSprite.fillSprite(BackgroundColor);
            RDSSprite.setTextDatum(TL_DATUM);
            RDSSprite.setTextColor(
              RDSstatus ? RDSColor : RDSDropoutColor,
              RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth,
              false
            );
            RDSSprite.drawString(RTString, xPos, 2);
            RDSSprite.drawString(RTString, xPos + RadiotextWidth, 2);
            RDSSprite.pushSprite(36, 220);
          } else {
            FullLineSprite.fillSprite(BackgroundColor);
            FullLineSprite.setTextDatum(TL_DATUM);
            FullLineSprite.setTextColor(
              RDSstatus ? RDSColor : RDSDropoutColor,
              RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth,
              false
            );
            FullLineSprite.drawString(RTString, xPos, 2);
            FullLineSprite.drawString(RTString, xPos + RadiotextWidth, 2);
            FullLineSprite.fillRect(275, 0, 8, 19, BackgroundColor);
            FullLineSprite.drawLine(283, 0, 283, 19, FrameColor);

            if (radio.rds.hasRT) {
              FullLineSprite.fillCircle(278, 3, 2, radio.rds.rtAB ? GreyoutColor : InsignificantColor);
              FullLineSprite.fillCircle(278, 14, 2, radio.rds.rtAB ? InsignificantColor : GreyoutColor);
            }

            FullLineSprite.pushSprite(36, 220);
          }
          rtticker = millis();
        }
      }
    }

    // Update small indicators for RT AB status
    if (radio.rds.hasRT && advancedRDS) {
      tft.fillCircle(203, 223, 2, radio.rds.rtAB ? GreyoutColor : InsignificantColor);
      tft.fillCircle(203, 234, 2, radio.rds.rtAB ? InsignificantColor : GreyoutColor);
    }
  }

  // Update RTold and RadiotextWidth if the string has changed
  if (RTold != RTString) {
    RadiotextWidth = (advancedRDS ? RDSSprite.textWidth(RTString) : FullLineSprite.textWidth(RTString));

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";RT1=");

      char RThex[65];
      radio.rds.stationText.toCharArray(RThex, 65);
      for (int i = 0; i < 64; i++) {
        if (RThex[i] < 0x10) Udp.print("0");
        if (RThex[i] == ' ') RThex[i] = '_';
        Udp.print(String(RThex[i], HEX));
      }
      Udp.endPacket();
    }

    RTold = RTString;
  }
}

void ShowAFEON() {
  if (!screenmute) {
    if (radio.eon_counter > 9) {
      if (!afpage) {
        afpage = true;
        tftPrint(ARIGHT, String(afpagenr) + "/2", 315, 201, BackgroundColor, BackgroundColor, 16);
      }
    }

    if (afpage) tftPrint(ARIGHT, String(afpagenr) + "/3", 315, 201, ActiveColor, ActiveColorSmooth, 16); else tftPrint(ARIGHT, String(afpagenr) + "/2", 315, 201, ActiveColor, ActiveColorSmooth, 16);

    if (radio.rds.hasAF && afpagenr == 1) {
      if (!hasafold) {
        tftPrint(ALEFT, textUI(87), 6, 48, BackgroundColor, BackgroundColor, 16);
        tftPrint(ALEFT, "AF:", 4, 32, ActiveColor, ActiveColorSmooth, 16);
        hasafold = true;
      }

      if (af_counterold != radio.af_updatecounter) {
        tft.fillRect(2, 48, 316, 150, BackgroundColor);
        for (byte i = 0; i < radio.af_counter; i++) {
          tftPrint(ALEFT, (radio.afmethodB && !radio.af[i].regional && radio.af[i].same) ? "S " : (radio.afmethodB && radio.af[i].regional && radio.af[i].same) ? "M " : (radio.afmethodB && radio.af[i].regional && !radio.af[i].same) ? "R " : "", 10 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), ActiveColor, ActiveColorSmooth, 16);
          if (radio.af[i].checked) {
            tftPrint(ARIGHT, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), InsignificantColor, InsignificantColorSmooth, 16);
          } else if (!radio.af[i].afvalid) {
            tftPrint(ARIGHT, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), SignificantColor, SignificantColorSmooth, 16);
          } else {
            tftPrint(ARIGHT, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), RDSColor, RDSColorSmooth, 16);
          }
        }
        if (radio.af_counter > 10) tft.drawLine(59, 54, 59, 191, SecondaryColor);
        if (radio.af_counter > 20) tft.drawLine(113, 54, 113, 191, SecondaryColor);
        if (radio.af_counter > 30) tft.drawLine(167, 54, 167, 191, SecondaryColor);
        if (radio.af_counter > 40) tft.drawLine(221, 54, 221, 191, SecondaryColor);
        af_counterold = radio.af_updatecounter;
      }
    }

    if (radio.eon_counter > 0 && afpagenr > 1) {
      if (!haseonold) {
        tftPrint(ALEFT, textUI(88), 6, 48, BackgroundColor, BackgroundColor, 16);
        tftPrint(ALEFT, "PI", 4, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(ACENTER, "TA", 250, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(ACENTER, "TP", 276, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(ACENTER, "PTY", 304, 32, ActiveColor, ActiveColorSmooth, 16);
        haseonold = true;
      }

      if (millis() >= eonticker + 2000) {
        eonticker = millis();
        byte y = 0;
        if (afpagenr == 3) y = 10;

        byte eon_numbers;
        if (afpagenr != 3) {
          if (radio.eon_counter > 9) eon_numbers = 10; else eon_numbers = radio.eon_counter;
        } else {
          eon_numbers = radio.eon_counter - 10;
        }


        for (byte i = 0; i < eon_numbers; i++) {
          if (eonpicodeold[i + y] == nullptr) {
            strcpy(eonpicodeold[i + y], "");
          }
          if (eonpsold[i + y] == nullptr) {
            eonpsold[i + y] = "";
          }
          if (mappedfreqold[i + y] == 0) {
            mappedfreqold[i + y] = 0;
          }
          if (mappedfreqold2[i + y] == 0) {
            mappedfreqold2[i + y] = 0;
          }
          if (mappedfreqold3[i + y] == 0) {
            mappedfreqold3[i + y] = 0;
          }
          if (eonptyold[i + y] == 0) {
            eonptyold[i + y] = 0;
          }

          if (strcmp(eonpicodeold[i + y], radio.eon[i + y].picode) != 0) {
            tftPrint(ALEFT, eonpicodeold[i + y], 4, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }
          tftPrint(ALEFT, radio.eon[i + y].picode, 4, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
          strcpy(eonpicodeold[i + y], radio.eon[i + y].picode);

          if (radio.eon[i + y].ps.length() > 0) {
            tftPrint(ALEFT, "PS", 46, 32, ActiveColor, ActiveColorSmooth, 16);

            if (strcmp(radio.eon[i + y].ps.c_str(), eonpsold[i + y].c_str()) != 0) {
              tftPrint(ALEFT, eonpsold[i + y].c_str(), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            tftPrint(ALEFT, radio.eon[i + y].ps.c_str(), 46, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            eonpsold[i + y] = radio.eon[i + y].ps;
          } else {
            tftPrint(ALEFT, eonpsold[i + y].c_str(), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq > 0) {
            tftPrint(ALEFT, "MF", 119, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq != mappedfreqold[i + y]) {
              char oldFreq[10];
              dtostrf(mappedfreqold[i + y] / 100.0, 5, 1, oldFreq);
              tftPrint(ALEFT, oldFreq, 115, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq[10];
            dtostrf(radio.eon[i + y].mappedfreq / 100.0, 5, 1, newFreq);
            tftPrint(ALEFT, newFreq, 115, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold[i + y] = radio.eon[i + y].mappedfreq;
          } else {
            char oldFreq[10];
            dtostrf(mappedfreqold[i + y] / 100.0, 5, 1, oldFreq);
            tftPrint(ALEFT, oldFreq, 115, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq2 > 0) {
            tftPrint(ALEFT, "MF2", 162, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq2 != mappedfreqold2[i + y]) {
              char oldFreq2[10];
              dtostrf(mappedfreqold2[i + y] / 100.0, 5, 1, oldFreq2);
              tftPrint(ALEFT, oldFreq2, 160, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq2[10];
            dtostrf(radio.eon[i + y].mappedfreq2 / 100.0, 5, 1, newFreq2);
            tftPrint(ALEFT, newFreq2, 160, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold2[i + y] = radio.eon[i + y].mappedfreq2;
          } else {
            char oldFreq2[10];
            dtostrf(mappedfreqold2[i + y] / 100.0, 5, 1, oldFreq2);
            tftPrint(ALEFT, oldFreq2, 160, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq3 > 0) {
            tftPrint(ALEFT, "MF3", 207, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq3 != mappedfreqold3[i + y]) {
              char oldFreq3[10];
              dtostrf(mappedfreqold3[i + y] / 100.0, 5, 1, oldFreq3);
              tftPrint(ALEFT, oldFreq3, 205, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq3[10];
            dtostrf(radio.eon[i + y].mappedfreq3 / 100.0, 5, 1, newFreq3);
            tftPrint(ALEFT, newFreq3, 205, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold3[i + y] = radio.eon[i + y].mappedfreq3;
          } else {
            char oldFreq3[10];
            dtostrf(mappedfreqold3[i + y] / 100.0, 5, 1, oldFreq3);
            tftPrint(ALEFT, oldFreq3, 205, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].ptyset) {
            if (eonptyold[i + y] != radio.eon[i + y].pty) tft.fillRect(290, 48 + (15 * i), 29, 16, BackgroundColor);
            if (radio.eon[i + y].pty != 254) tftPrint(ARIGHT, String(radio.eon[i + y].pty), 310, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            eonptyold[i + y] = radio.eon[i + y].pty;
          } else {
            tft.fillRect(290, 48 + (15 * i), 29, 16, BackgroundColor);
          }

          if (radio.eon[i + y].ta) tftPrint(ACENTER, "O", 250, 48 + (15 * i), RDSColor, RDSColorSmooth, 16); else tftPrint(ACENTER, "O", 250, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          if (radio.eon[i + y].tp) tftPrint(ACENTER, "O", 276, 48 + (15 * i), RDSColor, RDSColorSmooth, 16); else tftPrint(ACENTER, "O", 276, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
        }
      }
    }
  }
  if (radio.rds.hasAID) {
    if (aid_counterold != radio.rds.aid_counter) {
      String AIDStringTemp = "";
      char id[5];

      for (int y = 0; y < radio.rds.aid_counter; y++) {
        bool aidProcessed = false;

        for (int i = 0; i < 65; i++) {
          if (radio.rds.aid[y] == oda_app_ids[i]) {
            if (!aidProcessed) {
              for (int z = 0; z < 4; z++) {
                uint8_t nibble = (radio.rds.aid[y] >> (4 * (3 - z))) & 0xF;
                if (nibble < 10) {
                  id[z] = nibble + '0';
                } else {
                  id[z] = nibble - 10 + 'A';
                }
              }
              id[4] = '\0';

              AIDStringTemp += String(id);
              AIDStringTemp += ": ";
              AIDStringTemp += oda_app_names[i];

              aidProcessed = true;
            }
            break;
          }
        }

        if (aidProcessed && y < radio.rds.aid_counter - 1) {
          AIDStringTemp += " | ";
        }
      }
      aid_counterold = radio.rds.aid_counter;

      if (AIDStringTemp != AIDStringold) {
        AIDString = String(textUI(33)) + "  -  " + String(textUI(79)) + ": " + AIDStringTemp + "       ";
        AIDWidth = FullLineSprite.textWidth(AIDString);
        AIDStringold = AIDString;
      }
    }

    if (FullLineSprite.textWidth(radio.trimTrailingSpaces(AIDString)) < 270) {
      xPos = 0;
      FullLineSprite.fillSprite(BackgroundColor);
      FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
      FullLineSprite.drawString(AIDString, xPos, 2);
      FullLineSprite.drawLine(283, 0, 283, 19, FrameColor);
      FullLineSprite.pushSprite(5, 220);
    } else {
      if (millis() - rtticker >= 5) {
        if (xPos < -AIDWidth) xPos = 0;
        if (xPos == 0) {
          if (millis() - rttickerhold >= 2000) {
            xPos--;
            rttickerhold = millis();
          }
        } else {
          xPos--;
          rttickerhold = millis();
        }
        FullLineSprite.fillSprite(BackgroundColor);
        FullLineSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
        FullLineSprite.drawString(AIDString, xPos, 2);
        FullLineSprite.drawString(AIDString, xPos + AIDWidth, 2);
        FullLineSprite.drawLine(314, 0, 314, 19, FrameColor);
        FullLineSprite.pushSprite(5, 220);
        rtticker = millis();
      }
    }
  }
}

void ShowRDSStatistics() {
  // --- Only update if RDS is active, blocks processed, and no block A-D errors ---
  if (RDSstatus && radio.processed_rdsblocks > 0 &&
      !radio.rds.rdsAerror && !radio.rds.rdsBerror &&
      !radio.rds.rdsCerror && !radio.rds.rdsDerror) {

    // --- Update total processed RDS blocks if changed ---
    if (processed_rdsblocksold[32] != radio.processed_rdsblocks) {
      tftReplace(ARIGHT, String(processed_rdsblocksold[32]), String(radio.processed_rdsblocks),
                 318, 222, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
      processed_rdsblocksold[32] = radio.processed_rdsblocks;
    }

    // --- Row Y positions (repeats every 8 groups) ---
    const uint8_t rdsYpos[] PROGMEM = {56, 76, 96, 116, 136, 156, 176, 196};

    uint8_t rb = radio.rdsblock; // current RDS block index

    // --- Determine X column positions based on group range ---
    uint16_t xpos, xposPct;
    if      (rb <= RDS_GROUP_3B )  {
      xpos =  60;
      xposPct =  70;
    }
    else if (rb <= RDS_GROUP_7B )  {
      xpos = 140;
      xposPct = 150;
    }
    else if (rb <= RDS_GROUP_11B)  {
      xpos = 220;
      xposPct = 230;
    }
    else                           {
      xpos = 300;
      xposPct = 310;
    }

    // --- Determine Y row position (wraps every 8 groups) ---
    uint8_t row  = rb & 0x07;                     // modulo 8
    uint8_t ypos = pgm_read_byte(&rdsYpos[row]);  // Y position

    // --- Persist last drawn dot between calls ---
    static int16_t lastX = -1, lastY = -1; // -1 = "none yet"

    // --- Update only if block counter has changed ---
    if (blockcounterold[rb] != radio.rds.blockcounter[rb]) {
      // Calculate old and new percentages
      float oldPerc = (blockcounterold[rb] * 100.0f) / processed_rdsblocksold[rb];
      float newPerc = (radio.rds.blockcounter[rb] * 100.0f) / radio.processed_rdsblocks;

      char oldBuf[6], newBuf[6];  // buffers for dtostrf
      dtostrf(oldPerc, 0, 1, oldBuf);
      dtostrf(newPerc, 0, 1, newBuf);

      // Draw previous position as "Significant" if different
      if (lastX >= 0 && (lastX != xpos || lastY != ypos)) {
        tft.fillCircle(lastX - 55, lastY + 7, 2, SignificantColor);
      }

      // Update percentage display
      tftReplace(ARIGHT, oldBuf, newBuf, xpos, ypos,
                 PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
      tftPrint(ACENTER, "%", xposPct, ypos,
               ActiveColor, ActiveColorSmooth, 16);

      // Draw current dot as "Insignificant"
      tft.fillCircle(xpos - 55, ypos + 7, 2, InsignificantColor);

      // Save current dot for next update
      lastX = xpos;
      lastY = ypos;

      // Store updated block counters
      blockcounterold[rb]        = radio.rds.blockcounter[rb];
      processed_rdsblocksold[rb] = radio.processed_rdsblocks;
    }

    // --- Build HEX string from 16-bit RDS blocks A..D ---
    String HexString;
    HexString = String(((radio.rds.rdsA >> 12) & 0xF), HEX) +
                String(((radio.rds.rdsA >> 8)  & 0xF), HEX) +
                String(((radio.rds.rdsA >> 4)  & 0xF), HEX) +
                String(( radio.rds.rdsA        & 0xF), HEX) + " ";

    HexString += String(((radio.rds.rdsB >> 12) & 0xF), HEX) +
                 String(((radio.rds.rdsB >> 8)  & 0xF), HEX) +
                 String(((radio.rds.rdsB >> 4)  & 0xF), HEX) +
                 String(( radio.rds.rdsB        & 0xF), HEX) + " ";

    HexString += String(((radio.rds.rdsC >> 12) & 0xF), HEX) +
                 String(((radio.rds.rdsC >> 8)  & 0xF), HEX) +
                 String(((radio.rds.rdsC >> 4)  & 0xF), HEX) +
                 String(( radio.rds.rdsC        & 0xF), HEX) + " ";

    HexString += String(((radio.rds.rdsD >> 12) & 0xF), HEX) +
                 String(((radio.rds.rdsD >> 8)  & 0xF), HEX) +
                 String(((radio.rds.rdsD >> 4)  & 0xF), HEX) +
                 String(( radio.rds.rdsD        & 0xF), HEX);

    // Uppercase HEX string
    HexString.toUpperCase();

    // Update display if string changed
    if (HexString != HexStringold) {
      tftReplace(ACENTER, HexStringold, HexString,
                 160, 222, ActiveColor, ActiveColorSmooth, BackgroundColor, 16);
      HexStringold = HexString;
    }
  }

  // --- Always draw error indicators & BER meter if blocks processed ---
  if (radio.processed_rdsblocks > 0 && !dropout) {
    // Draw A-D error circles (simple error flags)
    const uint8_t xErr[4] = {86, 124, 162, 200};
    const bool errors[4] = {radio.rds.rdsAerror, radio.rds.rdsBerror,
                            radio.rds.rdsCerror, radio.rds.rdsDerror
                           };

    for (uint8_t i = 0; i < 4; i++) {
      tft.fillCircle(xErr[i], 41, 5,
                     errors[i] ? SignificantColor : InsignificantColor);
    }

    // --- Advanced error levels (0=clean, 1=small, 2=medium, 3=big) ---
    int errA = (radio.rds.rdsErr >> 14) & 0x03;
    int errB = ((radio.rds.rdsErr >> 8) & B00110000) >> 4;
    int errC = ((radio.rds.rdsErr >> 8) & B00001100) >> 2;
    int errD = (radio.rds.rdsErr & B00000011);

    // Aggressive weights per error level
    const int weights[4] = {0, 2, 6, 12};

    // Total estimated error bits in this group
    int errorBits = weights[errA] + weights[errB] + weights[errC] + weights[errD];
    int totalBits = 4 * 26;  // 104 data bits per RDS group

    // Raw BER estimate
    float ber = (float)errorBits / (float)totalBits;

    // Non-linear boost (sqrt makes small errors show stronger)
    ber = sqrt(ber);
    if (ber > 1.0) ber = 1.0;  // clamp to 100%

    // Smooth exponential filter
    float alpha = 0.05;
    smoothBER = (1.0 - alpha) * smoothBER + alpha * ber;

    int berPercent = (int)(smoothBER * 100.0);

    // Update BER display only if value changed
    if (berPercentold != berPercent) {
      tftReplace(ARIGHT, String(berPercentold) + "%", String(berPercent) + "%",
                 318, 34, PrimaryColor, PrimaryColorSmooth, BackgroundColor, 16);
      berPercentold = berPercent;
    }
  }
}
#pragma GCC diagnostic pop