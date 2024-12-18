#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbool-compare"
#include "rds.h"
#include "language.h"
#include "constants.h"
#include <TimeLib.h>

bool rtABold;
int RadiotextWidth;
int PSLongWidth;
int AIDWidth;
int afstringWidth;
int eonstringWidth;
int rtplusstringWidth;

String afstringold;
String eonstringold;
String rtplusstringold;
String stationNameLongOld;
String AIDStringold;

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
        tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, ptynold, 216, 109, BackgroundColor, BackgroundColor, 16);
      }
      if (!radio.rds.hasPTYN) radio.rds.PTYN = "PTYN N/A";
      tftPrint(-1, String(radio.rds.PTYN), 216, 109, RDSColor, RDSColorSmooth, 16);
      ptynold = radio.rds.PTYN;
    }
  }

  if (licold != radio.rds.LIC || rdsreset) {
    if (!screenmute) {
      if (radio.rds.hasLIC) LICString = (radio.rds.LICtext.length() == 0 ? myLanguage[language][73] : radio.rds.LICtext); else LICString = "N/A";
      if (LICString != LIColdString) {
        tftPrint(-1, "N/A", 242, 208, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, LIColdString, 242, 208, BackgroundColor, BackgroundColor, 16);
      }
      tftPrint(-1, LICString, 242, 208, RDSColor, RDSColorSmooth, 16);
      LIColdString = LICString;
      licold = radio.rds.LIC;
    }
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    if (!screenmute)  {
      tftPrint(-1, "N/A", 242, 223, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, pinstringold, 242, 223, BackgroundColor, BackgroundColor, 16);

      if (radio.rds.hasPIN) tftPrint(-1, pinstring, 242, 223, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "N/A", 242, 223, RDSColor, RDSColorSmooth, 16);
      pinstringold = pinstring;
    }
  }

  String afstring;
  if (radio.rds.hasAF && radio.af_counter > 0) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (i == radio.af_counter - 1 ? "        " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (!screenmute) {
      if (radio.rds.hasAF) tftPrint(-1, "AF", 50, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "AF", 50, 51, GreyoutColor, BackgroundColor, 16);
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
  if (radio.eon_counter > 0) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "        " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (!screenmute)  {
      if (radio.eon_counter > 0) tftPrint(-1, "EON", 153, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "EON", 153, 51, GreyoutColor, BackgroundColor, 16);
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
  if (radio.rds.hasRDSplus) rtplusstring = (radio.rds.rdsplusTag1 != 169 ? String(myLanguage[language][radio.rds.rdsplusTag1]) + ": " + String(radio.rds.RTContent1) : "") + (radio.rds.rdsplusTag2 != 169 ? " - " + String(myLanguage[language][radio.rds.rdsplusTag2]) + ": " + String(radio.rds.RTContent2) : "") + "        "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (!screenmute) {
      if (radio.rds.hasRDSplus) tftPrint(-1, "RT+", 123, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "RT+", 123, 51, GreyoutColor, BackgroundColor, 16);
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
      if (radio.rds.hasTP) tftPrint(-1, "TP", 2, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "TP", 2, 51, GreyoutColor, BackgroundColor, 16);
    }
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    if (!screenmute) {
      if (radio.rds.hasTA) tftPrint(-1, "TA", 24, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "TA", 24, 51, GreyoutColor, BackgroundColor, 16);
    }
    TAold = radio.rds.hasTA;
  }

  if (afmethodBold != radio.afmethodB || rdsreset) {
    if (!screenmute) {
      if (radio.afmethodB) tftPrint(-1, "-B", 68, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "-B", 68, 51, GreyoutColor, BackgroundColor, 16);
    }
    afmethodBold = radio.afmethodB;
  }

  if (MSold != radio.rds.MS) {
    if (!screenmute) {
      switch (radio.rds.MS) {
        case 0:
          tftPrint(-1, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "S", 185, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 1:
          tftPrint(-1, "M", 196, 51, RDSColor, RDSColorSmooth, 16);
          tftPrint(-1, "S", 185, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 2:
          tftPrint(-1, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "S", 185, 51, RDSColor, RDSColorSmooth, 16);
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
      if (radio.rds.hasTMC) tftPrint(-1, "TMC", 88, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "TMC", 88, 51, GreyoutColor, BackgroundColor, 16);
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
        if (radio.rds.hasECC) ECCString = (radio.rds.ECCtext.length() == 0 ? myLanguage[language][73] : radio.rds.ECCtext); else ECCString = "N/A";
        if (ECCString != ECColdString) {
          tftPrint(-1, "N/A", 242, 193, BackgroundColor, BackgroundColor, 16);
          tftPrint(-1, ECColdString, 242, 193, BackgroundColor, BackgroundColor, 16);
        }
        tftPrint(-1, ECCString, 242, 193, RDSColor, RDSColorSmooth, 16);
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
  if (band < BAND_GAP) {
    radio.readRDS(showrdserrors);
    RDSstatus = radio.rds.hasRDS;
    ShowRDSLogo(RDSstatus);

    if (!screenmute && !afscreen) {
      if (!RDSstatus) {
        if (radio.rds.correctPI != 0 && !dropout) {
          if (region == REGION_EU) {
            if (advancedRDS) {
              tftPrint(0, PIold, 275, 75, RDSDropoutColor, RDSDropoutColorSmooth, 28);
            } else {
              tftPrint(0, PIold, 275, 187, RDSDropoutColor, RDSDropoutColorSmooth, 28);
            }
          }

          if (region == REGION_US) {
            if (advancedRDS) {
              tftPrint(-1, PIold, 240, 72, RDSDropoutColor, RDSDropoutColorSmooth, 16);
              tftPrint(-1, stationIDold, 240, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16);
              tftPrint(1, stationStateold, 318, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            } else {
              tftPrint(-1, PIold, 240, 184, RDSDropoutColor, RDSDropoutColorSmooth, 16);
              tftPrint(-1, stationIDold, 240, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
              tftPrint(1, stationStateold, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            }
          }

          if (!radio.rds.hasLongPS) {
            PSSprite.fillSprite(BackgroundColor);
            PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
            PSSprite.drawString(PSold, 0, 2);

            if (advancedRDS) {
              PSSprite.pushSprite(36, 72);
            } else {
              PSSprite.pushSprite(36, 185);
            }
          }

          if (advancedRDS) {
            tftPrint(-1, PTYold, 36, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          } else {
            tftPrint(-1, PTYold, 36, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          }

          if (advancedRDS) {
            tft.fillCircle(86, 41, 5, SignificantColor);
            tft.fillCircle(124, 41, 5, SignificantColor);
            tft.fillCircle(162, 41, 5, SignificantColor);
            tft.fillCircle(200, 41, 5, SignificantColor);
          }

          if (radio.rds.hasCT) {
            if (advancedRDS) {
              tftPrint(1, rds_clock, 208, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            } else {
              tftPrint(1, rds_clock, 208, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            }
          }
          dropout = true;
        }
      } else {
        if (dropout || memreset) {
          if (region == REGION_EU) {
            if (advancedRDS) {
              tftPrint(0, PIold, 275, 75, RDSColor, RDSColorSmooth, 28);
            } else {
              tftPrint(0, PIold, 275, 187, RDSColor, RDSColorSmooth, 28);
            }
          }

          if (region == REGION_US) {
            if (advancedRDS) {
              tftPrint(-1, PIold, 240, 72, RDSColor, RDSColorSmooth, 16);
              tftPrint(-1, stationIDold, 240, 89, RDSColor, RDSColorSmooth, 16);
              tftPrint(1, stationStateold, 318, 89, RDSColor, RDSColorSmooth, 16);
            } else {
              tftPrint(-1, PIold, 240, 184, RDSColor, RDSColorSmooth, 16);
              tftPrint(-1, stationIDold, 240, 201, RDSColor, RDSColorSmooth, 16);
              tftPrint(1, stationStateold, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            }
          }

          if (!radio.rds.hasLongPS) {
            PSSprite.fillSprite(BackgroundColor);
            PSSprite.setTextColor(RDSColor, RDSColorSmooth, false);
            PSSprite.drawString(PSold, 0, 2);

            if (advancedRDS) {
              PSSprite.pushSprite(36, 72);
            } else {
              PSSprite.pushSprite(36, 185);
            }
          }

          if (advancedRDS) {
            tftPrint(-1, PTYold, 36, 109, RDSColor, RDSColorSmooth, 16);
          } else {
            tftPrint(-1, PTYold, 36, 163, RDSColor, RDSColorSmooth, 16);
          }

          if (!advancedRDS) {
            tft.fillCircle(314, 223, 2, GreyoutColor);
            tft.fillCircle(314, 234, 2, GreyoutColor);
          } else {
            tft.fillCircle(203, 223, 2, GreyoutColor);
            tft.fillCircle(203, 234, 2, GreyoutColor);
          }

          if (radio.rds.hasCT) {
            if (advancedRDS) {
              tftPrint(1, rds_clock, 208, 109, RDSColor, RDSColorSmooth, 16);
            } else {
              tftPrint(1, rds_clock, 208, 163, RDSColor, RDSColorSmooth, 16);
            }
          }
          dropout = false;
          memreset = false;
        }
      }
    }

    if (bitRead(radio.rds.rdsStat, 9)) {
      if ((RDSstatus && RDSSPYUSB) || (RDSstatus && RDSSPYTCP)) {
        RDSSPYRDS = "G:\r\n";
        if (radio.rds.rdsAerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
        if (radio.rds.rdsBerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX) + String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
        if (radio.rds.rdsCerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX) + String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
        if (radio.rds.rdsDerror) RDSSPYRDS += "----"; else RDSSPYRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX) + String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);
        RDSSPYRDS += "\r\n\r\n";

        if (RDSSPYRDS != RDSSPYRDSold) {
          if (RDSSPYUSB) Serial.print(RDSSPYRDS); else RemoteClient.print(RDSSPYRDS);
          RDSSPYRDSold = RDSSPYRDS;
        }
      }

      if ((RDSstatus && XDRGTKUSB) || (RDSstatus && XDRGTKTCP)) {
        XDRGTKRDS = "R";
        XDRGTKRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
        XDRGTKRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
        XDRGTKRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
        XDRGTKRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
        XDRGTKRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
        XDRGTKRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);

        uint8_t erroutput = 0;
        erroutput |= ((radio.rds.rdsErr >> 8) & B00110000) >> 4;
        erroutput |= ((radio.rds.rdsErr >> 8) & B00001100);
        erroutput |= ((radio.rds.rdsErr >> 8) & B00000011) << 4;

        XDRGTKRDS += String((erroutput >> 4) & 0xF, HEX);
        XDRGTKRDS += String(erroutput & 0xF, HEX);
        XDRGTKRDS += "\n";

        if (XDRGTKRDS != XDRGTKRDSold) {
          uint8_t piError = radio.rds.rdsErr >> 14;
          if (piError < 3) {
            uint8_t piState = radio.rds.piBuffer.add(radio.rds.rdsA, piError);

            if (piState != RdsPiBuffer::STATE_INVALID) {
              DataPrint ("P");
              String PIcodeToSend;
              PIcodeToSend = String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX) + String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
              PIcodeToSend.toUpperCase();
              DataPrint (PIcodeToSend);
              while (piState != 0) {
                DataPrint("?");
                piState--;
              }
              DataPrint ("\n");
            }
          }
          XDRGTKRDSold = XDRGTKRDS;
          XDRGTKRDS.toUpperCase();
          DataPrint(XDRGTKRDS);
        }
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
  if ((region == REGION_US && (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold || radio.rds.stationStatetext != stationStateold)) || (region != REGION_US && String(radio.rds.picode) != PIold)) {
    if (!afscreen && !radio.rds.rdsAerror && !radio.rds.rdsBerror && !radio.rds.rdsCerror && !radio.rds.rdsDerror && radio.rds.rdsA != radio.rds.correctPI && PIold.length() > 1) {
      radio.clearRDS(fullsearchrds);
      if (RDSSPYUSB) Serial.print("G:\r\nRESET-------\r\n\r\n");
      if (RDSSPYTCP) RemoteClient.print("G:\r\nRESET-------\r\n\r\n");
    }

    if (!screenmute) {
      if (advancedRDS) {
        if (region == REGION_EU) {
          if (!RDSstatus) {
            tftReplace(0, PIold, radio.rds.picode, 275, 75, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 28);
          } else {
            tftReplace(0, PIold, radio.rds.picode, 275, 75, RDSColor, RDSColorSmooth, BackgroundColor, 28);
          }
        }
        if (region == REGION_US) {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 72, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
            tftReplace(-1, stationIDold, radio.rds.stationIDtext, 240, 89, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
          } else {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 72, RDSColor, RDSColorSmooth, BackgroundColor, 16);
            tftReplace(-1, stationIDold, radio.rds.stationIDtext, 240, 89, RDSColor, RDSColorSmooth, BackgroundColor, 16);
          }
          tftReplace(1, stationStateold, radio.rds.stationStatetext, 318, 89, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        }
      } else if (afscreen) {
        tftReplace(-1, PIold, radio.rds.picode, 30, 201, BWAutoColor, BWAutoColorSmooth, BackgroundColor, 16);
      } else {
        if (region == REGION_EU) {
          if (!RDSstatus) {
            tftReplace(0, PIold, radio.rds.picode, 275, 187, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 28);
          } else {
            tftReplace(0, PIold, radio.rds.picode, 275, 187, RDSColor, RDSColorSmooth, BackgroundColor, 28);
          }
        }
        if (region == REGION_US) {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold) {
              tftReplace(-1, PIold, radio.rds.picode, 240, 184, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
              tftReplace(-1, stationIDold, radio.rds.stationIDtext, 240, 201, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
            }
          } else {
            if (String(radio.rds.picode) != PIold || radio.rds.stationIDtext != stationIDold) {
              tftReplace(-1, PIold, radio.rds.picode, 240, 184, RDSColor, RDSColorSmooth, BackgroundColor, 16);
              tftReplace(-1, stationIDold, radio.rds.stationIDtext, 240, 201, RDSColor, RDSColorSmooth, BackgroundColor, 16);
              tftReplace(1, stationStateold, radio.rds.stationStatetext, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
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
    String PTYString = (radio.rds.region == 1 ? radio.rds.stationType : myLanguage[language][228 + radio.rds.stationTypeCode]);
    if (radio.rds.stationTypeCode == 32) PTYString = "";

    if (!screenmute) {
      if (advancedRDS) {
        if (!RDSstatus) {
          tftReplace(-1, PTYold, PTYString, 36, 109, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        } else {
          tftReplace(-1, PTYold, PTYString, 36, 109, RDSColor, RDSColorSmooth, BackgroundColor, 16);
        }
      } else {
        if (!RDSstatus) {
          tftReplace(-1, PTYold, PTYString, 36, 163, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
        } else {
          tftReplace(-1, PTYold, PTYString, 36, 163, RDSColor, RDSColorSmooth, BackgroundColor, 16);
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
  if (radio.rds.stationName != PSold || (radio.rds.hasLongPS && showlongps)) {
    if (afscreen) {
      if (!screenmute) tftReplace(0, PSold, radio.rds.stationName, 160, 201, BWAutoColor, BWAutoColorSmooth, BackgroundColor, 16);
    } else {
      if (radio.rds.hasLongPS && showlongps) {
        String stationNameLongString = String(radio.rds.stationNameLong) + "     ";
        if (stationNameLongString != stationNameLongOld) {
          PSLongWidth = PSSprite.textWidth(stationNameLongString);
          stationNameLongOld = stationNameLongString;
        }

        if (PSSprite.textWidth(radio.trimTrailingSpaces(radio.rds.stationNameLong)) < 150) {
          xPos5 = 0;
          PSSprite.fillSprite(BackgroundColor);
          if (RDSstatus) PSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
          PSSprite.drawString(stationNameLongString, xPos5, 2);
        } else {
          if (millis() - pslongticker >= 5) {
            if (xPos5 < -PSLongWidth) xPos5 = 0;
            if (xPos5 == 0) {
              if (millis() - pslongtickerhold >= 2000) {
                xPos5 --;
                pslongtickerhold = millis();
              }
            } else {
              xPos5 --;
              pslongtickerhold = millis();
            }
            PSSprite.fillSprite(BackgroundColor);
            if (RDSstatus) PSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
            PSSprite.drawString(stationNameLongString, xPos5, 2);
            PSSprite.drawString(stationNameLongString, xPos5 + PSLongWidth, 2);
            pslongticker = millis();
          }
        }
      } else {
        xPos5 = 0;
        PSSprite.fillSprite(BackgroundColor);
        if (!RDSstatus || band > BAND_GAP) PSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false); else PSSprite.setTextColor(RDSColor, RDSColorSmooth, false);
        PSSprite.drawString(radio.rds.stationName, 0, 2);
      }
      if (!screenmute) {
        if (advancedRDS) {
          PSSprite.pushSprite(36, 72);
        } else {
          PSSprite.pushSprite(36, 185);
        }
      }

      if (wifi && radio.rds.stationName.length() > 0 && PSold != radio.rds.stationName) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";PS=");
        char PShex[9];
        radio.rds.stationName.toCharArray(PShex, 9);
        for (int i = 0; i < 8; i++)
        {
          if (PShex[i] < 0x10) Udp.print("0");
          if (PShex[i] == 0x20) PShex[i] =  '_';
          Udp.print(String(PShex[i], HEX));
        }
        Udp.endPacket();
      }
    }
    PSold = radio.rds.stationName;
  }
}

void showCT() {
  char str[6];
  time_t t;
  if (!screenmute && showclock) {
    if (radio.rds.hasCT && !dropout) {
      t = radio.rds.time + radio.rds.offset;
    } else if (!radio.rds.hasCT || dropout) {
      t = rtc.getEpoch() + radio.rds.offset;
      if (dropout) {
        radio.rds.time = static_cast<time_t>(rtc.getEpoch());
      }
    }
    strftime(str, 6, "%H:%M", localtime(&t));
    rds_clock = String(str);
    if (rds_clock != rds_clockold || hasCTold != radio.rds.hasCT) {
      if (radio.rds.hasCT && RDSstatus) {
        rtcset = true;
        rtc.setTime(radio.rds.time);
        if (advancedRDS) {
          tftReplace(1, rds_clockold, rds_clock, 208, 109, RDSColor, RDSColorSmooth, BackgroundColor, 16);
        } else {
          tftReplace(1, rds_clockold, rds_clock, 208, 163, RDSColor, RDSColorSmooth, BackgroundColor, 16);
        }
      } else {
        if (rtcset) {
          if (advancedRDS) {
            tftReplace(1, rds_clockold, rds_clock, 208, 109, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
          } else {
            tftReplace(1, rds_clockold, rds_clock, 208, 163, RDSDropoutColor, RDSDropoutColorSmooth, BackgroundColor, 16);
          }
        } else {
          if (advancedRDS) {
            tftPrint(1, rds_clockold, 208, 109, BackgroundColor, BackgroundColor, 16);
            tftPrint(1, rds_clock, 208, 109, BackgroundColor, BackgroundColor, 16);
          } else {
            tftPrint(1, rds_clockold, 208, 163, BackgroundColor, BackgroundColor, 16);
            tftPrint(1, rds_clock, 208, 163, BackgroundColor, BackgroundColor, 16);
          }
        }
      }
    }
    rds_clockold = rds_clock;
    hasCTold = radio.rds.hasCT;
  }
}

void showRadioText() {
  String RTString = String(radio.rds.stationText + " " + radio.rds.stationText32 + (radio.rds.hasEnhancedRT ? " eRT: " + String(radio.rds.enhancedRTtext) : "") + "      ");

  if (radio.rds.hasRT && radio.rds.rtAB != rtABold) {
    xPos = 0;
    rttickerhold = millis();
    rtABold = radio.rds.rtAB;
  }

  if (!screenmute) {
    if (radio.rds.hasRT && radio.rds.stationText.length() > 0) {
      if (advancedRDS && RDSSprite.textWidth(radio.trimTrailingSpaces(RTString)) < 165) {
        xPos = 0;
        RDSSprite.fillSprite(BackgroundColor);
        RDSSprite.setTextDatum(TL_DATUM);
        RDSSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
        RDSSprite.drawString(RTString, xPos, 2);
        RDSSprite.pushSprite(36, 220);
      } else if (!advancedRDS && RDSSprite.textWidth(radio.trimTrailingSpaces(RTString)) < 270) {
        xPos = 0;
        FullLineSprite.fillSprite(BackgroundColor);
        FullLineSprite.setTextDatum(TL_DATUM);
        FullLineSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
        FullLineSprite.drawString(RTString, xPos, 2);
        FullLineSprite.fillRect(275, 0, 8, 19, BackgroundColor);
        FullLineSprite.drawLine(283, 0, 283, 19, FrameColor);
        if (radio.rds.hasRT) {
          FullLineSprite.fillCircle(278, 3, 2, radio.rds.rtAB ? GreyoutColor : InsignificantColor);
          FullLineSprite.fillCircle(278, 14, 2, radio.rds.rtAB ? InsignificantColor : GreyoutColor);
        }
        FullLineSprite.pushSprite(36, 220);
      } else {
        if (millis() - rtticker >= (advancedRDS ? 5 : 15)) {
          if (xPos == 0 && millis() - rttickerhold < 1000) {
            // Do nothing, just wait
          } else {
            xPos--;
            rttickerhold = millis();  // Update hold time only when xPos changes
          }

          if (xPos < -RadiotextWidth) xPos = 0;

          if (advancedRDS) {
            RDSSprite.fillSprite(BackgroundColor);
            RDSSprite.setTextDatum(TL_DATUM);
            RDSSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
            RDSSprite.drawString(RTString, xPos, 2);
            RDSSprite.drawString(RTString, xPos + RadiotextWidth, 2);
            RDSSprite.pushSprite(36, 220);
          } else {
            FullLineSprite.fillSprite(BackgroundColor);
            FullLineSprite.setTextDatum(TL_DATUM);
            FullLineSprite.setTextColor(RDSstatus ? RDSColor : RDSDropoutColor, RDSstatus ? RDSColorSmooth : RDSDropoutColorSmooth, false);
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

    if (radio.rds.hasRT && advancedRDS) {
      tft.fillCircle(203, 223, 2, radio.rds.rtAB ? GreyoutColor : InsignificantColor);
      tft.fillCircle(203, 234, 2, radio.rds.rtAB ? InsignificantColor : GreyoutColor);
    }
  }

  if (RTold != RTString) {
    RadiotextWidth = (advancedRDS ? RDSSprite.textWidth(RTString) : FullLineSprite.textWidth(RTString));

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner_" + String(stationlistid, DEC) + ";RT1=");
      char RThex[65];
      radio.rds.stationText.toCharArray(RThex, 65);
      for (int i = 0; i < 64; i++) {
        if (RThex[i] < 0x10) Udp.print("0");
        if (RThex[i] == ' ') RThex[i] =  '_';
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
        tftPrint(1, String(afpagenr) + "/2", 315, 201, BackgroundColor, BackgroundColor, 16);
      }
    }

    if (afpage) tftPrint(1, String(afpagenr) + "/3", 315, 201, ActiveColor, ActiveColorSmooth, 16); else tftPrint(1, String(afpagenr) + "/2", 315, 201, ActiveColor, ActiveColorSmooth, 16);

    if (radio.rds.hasAF && afpagenr == 1) {
      if (!hasafold) {
        tftPrint(-1, myLanguage[language][87], 6, 48, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, "AF:", 4, 32, ActiveColor, ActiveColorSmooth, 16);
        hasafold = true;
      }

      if (af_counterold != radio.af_updatecounter) {
        tft.fillRect(2, 48, 316, 150, BackgroundColor);
        for (byte i = 0; i < radio.af_counter; i++) {
          tftPrint(-1, (radio.afmethodB && !radio.af[i].regional && radio.af[i].same) ? "S " : (radio.afmethodB && radio.af[i].regional && radio.af[i].same) ? "M " : (radio.afmethodB && radio.af[i].regional && !radio.af[i].same) ? "R " : "", 10 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), ActiveColor, ActiveColorSmooth, 16);
          if (radio.af[i].checked) {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), InsignificantColor, InsignificantColorSmooth, 16);
          } else if (!radio.af[i].afvalid) {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), SignificantColor, SignificantColorSmooth, 16);
          } else {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (i > 9 ? 54 : 0) + (i > 19 ? 54 : 0) + (i > 29 ? 54 : 0) + (i > 39 ? 54 : 0), 48 + (15 * i) - (i > 9 ? 150 : 0) - (i > 19 ? 150 : 0) - (i > 29 ? 150 : 0) - (i > 39 ? 150 : 0), RDSColor, RDSColorSmooth, 16);
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
        tftPrint(-1, myLanguage[language][88], 6, 48, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, "PI", 4, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(0, "TA", 250, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(0, "TP", 276, 32, ActiveColor, ActiveColorSmooth, 16);
        tftPrint(0, "PTY", 304, 32, ActiveColor, ActiveColorSmooth, 16);
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
            tftPrint(-1, eonpicodeold[i + y], 4, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }
          tftPrint(-1, radio.eon[i + y].picode, 4, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
          strcpy(eonpicodeold[i + y], radio.eon[i + y].picode);

          if (radio.eon[i + y].ps.length() > 0) {
            tftPrint(-1, "PS", 46, 32, ActiveColor, ActiveColorSmooth, 16);

            if (strcmp(radio.eon[i + y].ps.c_str(), eonpsold[i + y].c_str()) != 0) {
              tftPrint(-1, eonpsold[i + y].c_str(), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            tftPrint(-1, radio.eon[i + y].ps.c_str(), 46, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            eonpsold[i + y] = radio.eon[i + y].ps;
          } else {
            tftPrint(-1, eonpsold[i + y].c_str(), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq > 0) {
            tftPrint(-1, "MF", 119, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq != mappedfreqold[i + y]) {
              char oldFreq[10];
              dtostrf(mappedfreqold[i + y] / 100.0, 5, 1, oldFreq);
              tftPrint(-1, oldFreq, 115, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq[10];
            dtostrf(radio.eon[i + y].mappedfreq / 100.0, 5, 1, newFreq);
            tftPrint(-1, newFreq, 115, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold[i + y] = radio.eon[i + y].mappedfreq;
          } else {
            char oldFreq[10];
            dtostrf(mappedfreqold[i + y] / 100.0, 5, 1, oldFreq);
            tftPrint(-1, oldFreq, 115, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq2 > 0) {
            tftPrint(-1, "MF2", 162, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq2 != mappedfreqold2[i + y]) {
              char oldFreq2[10];
              dtostrf(mappedfreqold2[i + y] / 100.0, 5, 1, oldFreq2);
              tftPrint(-1, oldFreq2, 160, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq2[10];
            dtostrf(radio.eon[i + y].mappedfreq2 / 100.0, 5, 1, newFreq2);
            tftPrint(-1, newFreq2, 160, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold2[i + y] = radio.eon[i + y].mappedfreq2;
          } else {
            char oldFreq2[10];
            dtostrf(mappedfreqold2[i + y] / 100.0, 5, 1, oldFreq2);
            tftPrint(-1, oldFreq2, 160, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq3 > 0) {
            tftPrint(-1, "MF3", 207, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq3 != mappedfreqold3[i + y]) {
              char oldFreq3[10];
              dtostrf(mappedfreqold3[i + y] / 100.0, 5, 1, oldFreq3);
              tftPrint(-1, oldFreq3, 205, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            }
            char newFreq3[10];
            dtostrf(radio.eon[i + y].mappedfreq3 / 100.0, 5, 1, newFreq3);
            tftPrint(-1, newFreq3, 205, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            mappedfreqold3[i + y] = radio.eon[i + y].mappedfreq3;
          } else {
            char oldFreq3[10];
            dtostrf(mappedfreqold3[i + y] / 100.0, 5, 1, oldFreq3);
            tftPrint(-1, oldFreq3, 205, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].pty > 0) {
            if (eonptyold[i + y] != radio.eon[i + y].pty) tft.fillRect(290, 48 + (15 * i), 29, 16, BackgroundColor);
            if (radio.eon[i + y].pty != 254) tftPrint(1, String(radio.eon[i + y].pty), 310, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            eonptyold[i + y] = radio.eon[i + y].pty;
          } else {
            tft.fillRect(290, 48 + (15 * i), 29, 16, BackgroundColor);
          }

          if (radio.eon[i + y].ta) tftPrint(0, "X", 250, 48 + (15 * i), RDSColor, RDSColorSmooth, 16); else tftPrint(0, "X", 250, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          if (radio.eon[i + y].tp) tftPrint(0, "X", 276, 48 + (15 * i), RDSColor, RDSColorSmooth, 16); else tftPrint(0, "X", 276, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
        }
      }
    }
  }
}

#pragma GCC diagnostic pop