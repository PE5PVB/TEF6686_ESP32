#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wbool-compare"
#include "rds.h"
#include "language.h"
#include "constants.h"
#include <TimeLib.h>

int Radiotextlengthold;
int RadiotextWidth;
int AIDlengthold;
int AIDWidth;
int afstringlengthold;
int afstringWidth;
int eonstringlengthold;
int eonstringWidth;
int rtplusstringlengthold;
int rtplusstringWidth;

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
    if (!screenmute) tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, 16);
    if (!screenmute) tftPrint(-1, ptynold, 216, 109, BackgroundColor, BackgroundColor, 16);
    if (radio.rds.PTYN.length() == 0) radio.rds.PTYN = "PTYN N/A";
    if (!screenmute) tftPrint(-1, String(radio.rds.PTYN), 216, 109, RDSColor, RDSColorSmooth, 16);
    ptynold = radio.rds.PTYN;
  }

  if (licold != radio.rds.LIC || rdsreset) {
    if (!screenmute) {
      tftPrint(-1, "N/A", 242, 208, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, LIColdString, 242, 208, BackgroundColor, BackgroundColor, 16);
      if (radio.rds.hasLIC) tftPrint(-1, (radio.rds.LICtext.length() == 0 ? myLanguage[language][73] : radio.rds.LICtext), 242, 208, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "N/A", 242, 208, RDSColor, RDSColorSmooth, 16);
      if (radio.rds.LICtext.length() == 0) LIColdString = myLanguage[language][73]; else LIColdString = radio.rds.LICtext;
    }
    licold = radio.rds.LIC;
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
  if (radio.rds.hasAF) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (i == radio.af_counter - 1 ? "          " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (!screenmute) {
      if (radio.rds.hasAF) tftPrint(-1, "AF", 50, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "AF", 50, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasafold = radio.rds.hasAF;
  }

  if (millis() - afticker >= 15) {
    if (radio.rds.hasAF) {
      if (afstring.length() != afstringlengthold) {
        afstringWidth = tft.textWidth(afstring) + TickerSpace;
        afstringlengthold = afstring.length();
      }
      if (xPos2 < -(afstringWidth + TickerSpace)) xPos2 = 0;
      if (xPos2 == 0) {
        if (millis() - aftickerhold >= 2000) {
          xPos2 --;
          aftickerhold = millis();
        }
      } else {
        xPos2 --;
        aftickerhold = millis();
      }
    } else {
      xPos2 = 0;
    }

    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(afstring, xPos2, 2);
    if (radio.rds.hasAF) RDSSprite.drawString(afstring, xPos2 + afstringWidth + TickerSpace, 2);
    RDSSprite.pushSprite(35, 197);
    afticker = millis();
  }

  String eonstring;
  if (radio.eon_counter > 0) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "          " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (!screenmute)  {
      if (radio.eon_counter > 0) tftPrint(-1, "EON", 153, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "EON", 153, 51, GreyoutColor, BackgroundColor, 16);
    }
    haseonold = radio.rds.hasEON;
  }

  if (millis() - eonticker >= 15) {

    if (radio.rds.hasEON) {
      if (eonstring.length() != eonstringlengthold) {
        eonstringWidth = tft.textWidth(eonstring) + TickerSpace;
        eonstringlengthold = eonstring.length();
      }
      if (xPos3 < -(eonstringWidth + TickerSpace)) xPos3 = 0;
      if (xPos3 == 0) {
        if (millis() - eontickerhold >= 2000) {
          xPos3 --;
          eontickerhold = millis();
        }
      } else {
        xPos3 --;
        eontickerhold = millis();
      }
    } else {
      xPos3 = 0;
    }
    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(eonstring, xPos3, 2);
    if (radio.rds.hasEON) RDSSprite.drawString(eonstring, xPos3 + eonstringWidth + TickerSpace, 2);
    RDSSprite.pushSprite(35, 172);
    eonticker = millis();
  }


  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = (radio.rds.rdsplusTag1 != 169 ? String(myLanguage[language][radio.rds.rdsplusTag1]) + ": " + String(radio.rds.RTContent1) : "") + (radio.rds.rdsplusTag2 != 169 ? " - " + String(myLanguage[language][radio.rds.rdsplusTag2]) + ": " + String(radio.rds.RTContent2) : "") + "         "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (!screenmute) {
      if (radio.rds.hasRDSplus) tftPrint(-1, "RT+", 123, 51, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "RT+", 123, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasrtplusold = radio.rds.hasRDSplus;
  }

  if (millis() - rtplusticker >= 15) {
    if (radio.rds.hasRDSplus) {
      if (rtplusstring.length() != rtplusstringlengthold) {
        rtplusstringWidth = tft.textWidth(rtplusstring) + TickerSpace;
        rtplusstringlengthold = rtplusstring.length();
      }
      if (xPos4 < -(rtplusstringWidth + TickerSpace)) xPos4 = 0;
      if (xPos4 == 0) {
        if (millis() - rtplustickerhold >= 2000) {
          xPos4 --;
          rtplustickerhold = millis();
        }
      } else {
        xPos4 --;
        rtplustickerhold = millis();
      }
    } else {
      xPos4 = 0;
    }
    RDSSprite.fillSprite(BackgroundColor);
    if (RDSstatus) RDSSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RDSSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
    RDSSprite.drawString(rtplusstring, xPos4, 2);
    if (radio.rds.hasRDSplus) RDSSprite.drawString(rtplusstring, xPos4 + rtplusstringWidth + TickerSpace, 2);
    RDSSprite.pushSprite(35, 146);
    rtplusticker = millis();
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
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";AF=");

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
        tftPrint(-1, "N/A", 242, 193, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, ECColdtxt, 242, 193, BackgroundColor, BackgroundColor, 16);
        if (radio.rds.hasECC) tftPrint(-1, (radio.rds.ECCtext.length() == 0 ? myLanguage[language][73] : radio.rds.ECCtext), 242, 193, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, "N/A", 242, 193, RDSColor, RDSColorSmooth, 16);
      }
      if (radio.rds.ECCtext.length() == 0) ECColdtxt = myLanguage[language][73]; else ECColdtxt = radio.rds.ECCtext;
    }

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";ECC=");
      if (radio.rds.ECC < 0x10) Udp.print("0");
      Udp.print(String(radio.rds.ECC, HEX));
      Udp.endPacket();
    }
    ECCold = radio.rds.ECC;
  }
}

void readRds() {
  radio.readRDS(showrdserrors);
  if (band < BAND_GAP) {
    RDSstatus = radio.rds.hasRDS;
    ShowRDSLogo(RDSstatus);
    if (!screenmute && !afscreen) {
      if (!RDSstatus) {
        if (radio.rds.correctPI != 0 && !dropout) {
          if (region == REGION_EU) {
            if (advancedRDS) tftPrint(0, PIold, 275, 75, RDSDropoutColor, RDSDropoutColorSmooth, 28); else tftPrint(0, PIold, 275, 187, RDSDropoutColor, RDSDropoutColorSmooth, 28);
          }

          if (region == REGION_US) {
            if (advancedRDS) tftPrint(-1, PIold, 240, 72, RDSDropoutColor, RDSDropoutColorSmooth, 16); else tftPrint(-1, PIold, 240, 184, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            if (advancedRDS) tftPrint(-1, stationIDold, 240, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16); else tftPrint(-1, stationIDold, 240, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            if (advancedRDS) tftPrint(1, stationStateold, 318, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16); else tftPrint(1, stationStateold, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          }

          if (advancedRDS) tftPrint(-1, PSold, 38, 75, RDSDropoutColor, RDSDropoutColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, RDSDropoutColor, RDSDropoutColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          if (advancedRDS) {
            tft.fillCircle(86, 41, 5, SignificantColor);
            tft.fillCircle(124, 41, 5, SignificantColor);
            tft.fillCircle(162, 41, 5, SignificantColor);
            tft.fillCircle(200, 41, 5, SignificantColor);
          }

          if (advancedRDS && radio.rds.stationText.length() < 20) {
            xPos = 0;
            AdvRadiotextSprite.fillSprite(BackgroundColor);
            AdvRadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
            AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
            AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
            AdvRadiotextSprite.pushSprite(35, 220);
          } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
            xPos = 0;
            RadiotextSprite.fillSprite(BackgroundColor);
            RadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
            RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
            RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
            RadiotextSprite.pushSprite(38, 220);
          }

          if (radio.rds.hasCT) {
            if (advancedRDS) {
              tftPrint(1, rds_clock, 205, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            } else {
              tftPrint(1, rds_clock, 205, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            }
          }
          dropout = true;
        }
      } else {
        if (dropout) {
          if (region == REGION_EU) {
            if (advancedRDS) tftPrint(0, PIold, 275, 75, RDSColor, RDSColorSmooth, 28); else tftPrint(0, PIold, 275, 187, RDSColor, RDSColorSmooth, 28);
          }

          if (region == REGION_US) {
            if (advancedRDS) tftPrint(-1, PIold, 240, 72, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, PIold, 240, 184, RDSColor, RDSColorSmooth, 16);
            if (advancedRDS) tftPrint(-1, stationIDold, 240, 89, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, stationIDold, 240, 201, RDSColor, RDSColorSmooth, 16);
          }

          if (advancedRDS) tftPrint(-1, PSold, 38, 75, RDSColor, RDSColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, RDSColor, RDSColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, RDSColor, RDSColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, RDSColor, RDSColorSmooth, 16);
          if (!advancedRDS) {
            tft.fillCircle(314, 223, 2, GreyoutColor);
            tft.fillCircle(314, 234, 2, GreyoutColor);
          } else {
            tft.fillCircle(203, 223, 2, GreyoutColor);
            tft.fillCircle(203, 234, 2, GreyoutColor);
          }

          if (advancedRDS && radio.rds.stationText.length() < 20) {
            xPos = 0;
            AdvRadiotextSprite.fillSprite(BackgroundColor);
            AdvRadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false);
            AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
            AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
            AdvRadiotextSprite.pushSprite(35, 220);
          } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
            xPos = 0;
            RadiotextSprite.fillSprite(BackgroundColor);
            RadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false);
            RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
            RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
            RadiotextSprite.pushSprite(38, 220);
          }

          if (radio.rds.hasCT) {
            if (advancedRDS) {
              tftPrint(1, rds_clock, 205, 109, RDSColor, RDSColorSmooth, 16);
            } else {
              tftPrint(1, rds_clock, 205, 163, RDSColor, RDSColorSmooth, 16);
            }
          }
          dropout = false;
        }
      }
    }

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
      XDRGTKRDS += String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX);
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
		XDRGTKRDS.toUpperCase();
        DataPrint(XDRGTKRDS);
        XDRGTKRDSold = XDRGTKRDS;
      }
    }
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
            tftReplace(0, PIold, radio.rds.picode, 275, 75, RDSDropoutColor, RDSDropoutColorSmooth, 28);
          } else {
            tftReplace(0, PIold, radio.rds.picode, 275, 75, RDSColor, RDSColorSmooth, 28);
          }
        }
        if (region == REGION_US) {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 72, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            tftReplace(-1, stationIDold, radio.rds.stationID, 240, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          } else {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 72, RDSColor, RDSColorSmooth, 16);
            tftReplace(-1, stationIDold, radio.rds.stationID, 240, 89, RDSColor, RDSColorSmooth, 16);
          }
          tftReplace(1, stationStateold, radio.rds.stationState, 318, 89, RDSDropoutColor, RDSDropoutColorSmooth, 16);
        }
      } else if (afscreen) {
        tftReplace(-1, PIold, radio.rds.picode, 30, 201, BWAutoColor, BWAutoColorSmooth, 16);
      } else {
        if (region == REGION_EU) {
          if (!RDSstatus) {
            tftReplace(0, PIold, radio.rds.picode, 275, 187, RDSDropoutColor, RDSDropoutColorSmooth, 28);
          } else {
            tftReplace(0, PIold, radio.rds.picode, 275, 187, RDSColor, RDSColorSmooth, 28);
          }
        }
        if (region == REGION_US) {
          if (!RDSstatus) {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 184, RDSDropoutColor, RDSDropoutColorSmooth, 16);
            tftReplace(-1, stationIDold, radio.rds.stationID, 240, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
          } else {
            if (String(radio.rds.picode) != PIold) tftReplace(-1, PIold, radio.rds.picode, 240, 184, RDSColor, RDSColorSmooth, 16);
            tftReplace(-1, stationIDold, radio.rds.stationID, 240, 201, RDSColor, RDSColorSmooth, 16);
          }
          tftReplace(1, stationStateold, radio.rds.stationState, 318, 201, RDSDropoutColor, RDSDropoutColorSmooth, 16);
        }
      }
      PIold = radio.rds.picode;
      stationIDold = radio.rds.stationID;
      stationStateold = radio.rds.stationState;
      if (wifi) {
        Udp.beginPacket(remoteip, 9030);
        Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";PI=" + String(radio.rds.picode, 4));
        Udp.endPacket();
      }
    }
  }
}

void showPTY() {
  if (strcmp(radio.rds.stationType, programTypePrevious)) {
    if (!screenmute) {
      if (advancedRDS) {
        if (!RDSstatus) {
          tftReplace(-1, PTYold, radio.rds.stationType, 38, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16);
        } else {
          tftReplace(-1, PTYold, radio.rds.stationType, 38, 109, RDSColor, RDSColorSmooth, 16);
        }
      } else {
        if (!RDSstatus) {
          tftReplace(-1, PTYold, radio.rds.stationType, 38, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
        } else {
          tftReplace(-1, PTYold, radio.rds.stationType, 38, 163, RDSColor, RDSColorSmooth, 16);
        }
      }
    }
    PTYold = radio.rds.stationType;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";PTY=");
      Udp.print(String(radio.rds.stationTypeCode, HEX));
      Udp.endPacket();
    }
    strcpy(programTypePrevious, radio.rds.stationType);
  }
}

void showPS() {
  if (radio.rds.stationName != PSold) {
    if (!screenmute) {
      if (advancedRDS) {
        if (!RDSstatus) {
          tftReplace(-1, PSold, radio.rds.stationName, 38, 75, RDSDropoutColor, RDSDropoutColorSmooth, 28);
        } else {
          tftReplace(-1, PSold, radio.rds.stationName, 38, 75, RDSColor, RDSColorSmooth, 28);
        }
      } else if (afscreen) {
        tftReplace(0, PSold, radio.rds.stationName, 160, 201, BWAutoColor, BWAutoColorSmooth, 16);
      } else {
        if (!RDSstatus) {
          tftReplace(-1, PSold, radio.rds.stationName, 38, 187, RDSDropoutColor, RDSDropoutColorSmooth, 28);
        } else {
          tftReplace(-1, PSold, radio.rds.stationName, 38, 187, RDSColor, RDSColorSmooth, 28);
        }
      }
    }
    PSold = radio.rds.stationName;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";PS=");
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
}

void showCT() {
  if (!screenmute) {
    if (radio.rds.hasCT && !dropout) {
      rds_clock = ((radio.rds.hour < 10 ? "0" : "") + String(radio.rds.hour) + ":" + (radio.rds.minute < 10 ? "0" : "") + String(radio.rds.minute));
    } else if (!radio.rds.hasCT || dropout) {
      rds_clock = ((rtc.getHour(true) < 10 ? "0" : "") + String(rtc.getHour(true)) + ":" + (rtc.getMinute() < 10 ? "0" : "") + String(rtc.getMinute()));
      if (dropout) {
        radio.rds.hour = rtc.getHour(true);
        radio.rds.minute = rtc.getMinute();
      }
    }
    if (rds_clock != rds_clockold || hasCTold != radio.rds.hasCT) {
      if (radio.rds.hasCT && RDSstatus) {
        rtcset = true;
        rtc.setTime(0, radio.rds.minute, radio.rds.hour, radio.rds.day, radio.rds.month, radio.rds.year);
        if (advancedRDS) tftReplace(1, rds_clockold, rds_clock, 205, 109, RDSColor, RDSColorSmooth, 16); else tftReplace(1, rds_clockold, rds_clock, 205, 163, RDSColor, RDSColorSmooth, 16);
      } else {
        if (rtcset) {
          if (advancedRDS) tftReplace(1, rds_clockold, rds_clock, 205, 109, RDSDropoutColor, RDSDropoutColorSmooth, 16); else tftReplace(1, rds_clockold, rds_clock, 205, 163, RDSDropoutColor, RDSDropoutColorSmooth, 16);
        } else {
          if (advancedRDS) {
            tftPrint(1, rds_clockold, 205, 109, BackgroundColor, BackgroundColor, 16);
            tftPrint(1, rds_clock, 205, 109, BackgroundColor, BackgroundColor, 16);
          } else {
            tftPrint(1, rds_clockold, 205, 163, BackgroundColor, BackgroundColor, 16);
            tftPrint(1, rds_clock, 205, 163, BackgroundColor, BackgroundColor, 16);
          }
        }
      }
    }
    rds_clockold = rds_clock;
    hasCTold = radio.rds.hasCT;
  }
}

void showRadioText() {
  if (radio.rds.hasRT && radio.rds.stationText.length() > 0) {
    if (String(radio.rds.stationText + radio.rds.stationText32).length() != Radiotextlengthold) {
      RadiotextWidth = tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + TickerSpace;
      Radiotextlengthold = String(radio.rds.stationText + radio.rds.stationText32).length();
    }
    if (advancedRDS && radio.rds.stationText.length() < 20) {
      xPos = 0;
      AdvRadiotextSprite.fillSprite(BackgroundColor);
      if (RDSstatus) AdvRadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false); else AdvRadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
      AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
      AdvRadiotextSprite.pushSprite(35, 220);
    } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
      xPos = 0;
      RadiotextSprite.fillSprite(BackgroundColor);
      if (RDSstatus) RadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
      RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
      RadiotextSprite.pushSprite(38, 220);
    } else {
      if (millis() - rtticker >= 15) {
        if (xPos == 0) {
          if (millis() - rttickerhold >= 1000) {
            xPos --;
            rttickerhold = millis();
          }
        } else {
          xPos --;
          rttickerhold = millis();
        }

        if (xPos < -(RadiotextWidth + TickerSpace)) xPos = 0;
        if (advancedRDS) {
          AdvRadiotextSprite.fillSprite(BackgroundColor);
          if (RDSstatus) AdvRadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false); else AdvRadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
          AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
          AdvRadiotextSprite.pushSprite(35, 220);
        } else {
          RadiotextSprite.fillSprite(BackgroundColor);
          if (RDSstatus) RadiotextSprite.setTextColor(RDSColor, RDSColorSmooth, false); else RadiotextSprite.setTextColor(RDSDropoutColor, RDSDropoutColorSmooth, false);
          RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos + RadiotextWidth + TickerSpace, 2);
          RadiotextSprite.pushSprite(38, 220);
        }
        rtticker = millis();
      }
    }
  }
  if (radio.rds.hasRT) {
    if (!advancedRDS) {
      if (radio.rds.rtAB) {
        tft.fillCircle(314, 223, 2, GreyoutColor);
        tft.fillCircle(314, 234, 2, InsignificantColor);
      } else {
        tft.fillCircle(314, 223, 2, InsignificantColor);
        tft.fillCircle(314, 234, 2, GreyoutColor);
      }
    } else {
      if (radio.rds.rtAB) {
        tft.fillCircle(203, 223, 2, GreyoutColor);
        tft.fillCircle(203, 234, 2, InsignificantColor);
      } else {
        tft.fillCircle(203, 223, 2, InsignificantColor);
        tft.fillCircle(203, 234, 2, GreyoutColor);
      }
    }
  }

  if (wifi) {
    if (RTold != (radio.rds.stationText + " " + radio.rds.stationText32)) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";RT1=");
      char RThex[65];
      radio.rds.stationText.toCharArray(RThex, 65);
      for (int i = 0; i < 64; i++)
      {
        if (RThex[i] < 0x10) Udp.print("0");
        if (RThex[i] == ' ') RThex[i] =  '_';
        Udp.print(String(RThex[i], HEX));
      }
      Udp.endPacket();
    }
  }
  if (RTold != (radio.rds.stationText + " " + radio.rds.stationText32)) xPos = 0;
  RTold = radio.rds.stationText + " " + radio.rds.stationText32;
}

void ShowAFEON() {
  if (!screenmute) {
    if (radio.eon_counter > 9) {
      if (!afpage) {
        afpage = true;
        tftPrint(1, String(afpagenr) + "/2", 315, 222, BackgroundColor, BackgroundColor, 16);
      }
    }

    if (afpage) tftPrint(1, String(afpagenr) + "/3", 315, 222, SecondaryColor, SecondaryColorSmooth, 16); else tftPrint(1, String(afpagenr) + "/2", 315, 222, SecondaryColor, SecondaryColorSmooth, 16);

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

      if (millis() >= eonticker + 1000) {
        eonticker = millis();
        byte y = 0;
        if (afpagenr == 3) y = 10;
        for (byte i = 0; i < radio.eon_counter; i++) {
          if (strcmp(eonpicodeold[i + y], radio.eon[i + y].picode) != 0) tftPrint(-1, String(eonpicodeold[i + y]), 4, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          tftPrint(-1, String(radio.eon[i + y].picode), 4, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
          strcpy(eonpicodeold[i + y], radio.eon[i + y].picode);

          if (radio.eon[i + y].ps.length() > 0) {
            tftPrint(-1, "PS", 46, 32, ActiveColor, ActiveColorSmooth, 16);

            if (strcmp(radio.eon[i + y].ps.c_str(), eonpsold[i + y].c_str()) != 0) tftPrint(-1, String(eonpsold[i + y]), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            tftPrint(-1, String(radio.eon[i + y].ps), 46, 48 + (15 * i), RDSDropoutColor, RDSDropoutColorSmooth, 16);
            eonpsold[i + y] = radio.eon[i + y].ps;
          } else {
            tftPrint(-1, String(eonpsold[i + y]), 46, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq > 0) {
            tftPrint(1, "FREQ", 156, 32, ActiveColor, ActiveColorSmooth, 16);

            if (radio.eon[i + y].mappedfreq != mappedfreqold[i + y]) tftPrint(1, String(mappedfreqold[i + y] / 100) + "." + String((mappedfreqold[i + y] % 100) / 10), 156, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            tftPrint(1, String(radio.eon[i + y].mappedfreq / 100) + "." + String((radio.eon[i + y].mappedfreq % 100) / 10), 156, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            mappedfreqold[i + y] = radio.eon[i + y].mappedfreq;
          } else {
            tftPrint(1, String(mappedfreqold[i + y] / 100) + "." + String((mappedfreqold[i + y] % 100) / 10), 156, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }

          if (radio.eon[i + y].mappedfreq2 > 0) {
            if (radio.eon[i + y].mappedfreq2 != mappedfreqold2[i + y]) tftPrint(1, String(mappedfreqold2[i + y] / 100) + "." + String((mappedfreqold2[i + y] % 100) / 10), 196, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            tftPrint(1, String(radio.eon[i + y].mappedfreq2 / 100) + "." + String((radio.eon[i + y].mappedfreq2 % 100) / 10), 196, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            mappedfreqold2[i + y] = radio.eon[i + y].mappedfreq2;
          } else {
            tftPrint(1, String(mappedfreqold2[i + y] / 100) + "." + String((mappedfreqold2[i + y] % 100) / 10), 196, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }


          if (radio.eon[i + y].mappedfreq3 > 0) {
            if (radio.eon[i + y].mappedfreq3 != mappedfreqold3[i + y]) tftPrint(1, String(mappedfreqold3[i + y] / 100) + "." + String((mappedfreqold3[i + y] % 100) / 10), 236, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            tftPrint(1, String(radio.eon[i + y].mappedfreq3 / 100) + "." + String((radio.eon[i + y].mappedfreq3 % 100) / 10), 236, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            mappedfreqold3[i + y] = radio.eon[i + y].mappedfreq3;
          } else {
            tftPrint(1, String(mappedfreqold3[i + y] / 100) + "." + String((mappedfreqold3[i + y] % 100) / 10), 236, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }


          if (radio.eon[i + y].taset) {
            if (radio.eon[i + y].ta) {
              tft.fillCircle(250, 54 + (15 * i), 4, InsignificantColor);
            } else {
              tft.fillCircle(250, 54 + (15 * i), 4, BackgroundColor);
            }
          } else {
            tft.fillCircle(250, 54 + (15 * i), 4, BackgroundColor);
          }

          if (radio.eon[i + y].tp) tft.fillCircle(276, 54 + (15 * i), 4, InsignificantColor); else tft.fillCircle(276, 54 + (15 * i), 4, BackgroundColor);

          if (radio.eon[i + y].pty != eonptyold[i + y]) {
            tftReplace(0, String(eonptyold[i + y]), (radio.eon[i + y].pty < 32 ? String(radio.eon[i + y].pty) : " "), 304, 48 + (15 * i), RDSColor, RDSColorSmooth, 16);
            eonptyold[i + y] = radio.eon[i + y].pty;
          }

          if (i == 9) i = 254;
        }
      }
    }

    if (radio.rds.hasAID) {
      if (aid_counterold != radio.rds.aid_counter) {
        AIDString = "";
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

                AIDString += String(id);
                AIDString += ": ";
                AIDString += oda_app_names[i];

                aidProcessed = true;
              }
              break;
            }
          }

          if (!AIDString.isEmpty() && y < radio.rds.aid_counter - 1 && aidProcessed) {
            AIDString += " | ";
          }
        }
        aid_counterold = radio.rds.aid_counter;
      }

      if (AIDString.length() != AIDlengthold) {
        AIDWidth = tft.textWidth(String(myLanguage[language][93]) + "  -  " + String(myLanguage[language][79]) + ": " + AIDString) + TickerSpace;
        AIDlengthold = AIDString.length();
      }

      if (xPos < -(AIDWidth + TickerSpace)) xPos = 0;
      if (xPos == 0) {
        if (millis() - rttickerhold >= 1000) {
          xPos --;
          rttickerhold = millis();
        }
      } else {
        xPos --;
        rttickerhold = millis();
      }
      RadiotextSprite.fillSprite(BackgroundColor);
      RadiotextSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
      RadiotextSprite.drawString(String(myLanguage[language][93]) + "  -  " + String(myLanguage[language][79]) + ": " + AIDString, xPos, 2);
      RadiotextSprite.drawString(String(myLanguage[language][93]) + "  -  " + String(myLanguage[language][79]) + ": " + AIDString, xPos + AIDWidth + TickerSpace, 2);
      RadiotextSprite.pushSprite(5, 220);
    }
  }
}
#pragma GCC diagnostic pop