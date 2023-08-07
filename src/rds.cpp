#include "rds.h"
#include "language.h"
#include "constants.h"
#include <TimeLib.h>

void ShowAdvancedRDS() {
  if (radio.rds.rdsAerror != errorAold || rdsreset) {
    if (radio.rds.rdsAerror) tft.fillCircle(86, 41, 5, SignificantColor); else tft.fillCircle(86, 41, 5, InsignificantColor);
    errorAold = radio.rds.rdsAerror;
  }

  if (radio.rds.rdsBerror != errorBold || rdsreset) {
    if (radio.rds.rdsBerror) tft.fillCircle(124, 41, 5, SignificantColor); else tft.fillCircle(124, 41, 5, InsignificantColor);
    errorBold = radio.rds.rdsBerror;
  }

  if (radio.rds.rdsCerror != errorCold || rdsreset) {
    if (radio.rds.rdsCerror) tft.fillCircle(162, 41, 5, SignificantColor); else tft.fillCircle(162, 41, 5, InsignificantColor);
    errorCold = radio.rds.rdsCerror;
  }

  if (radio.rds.rdsDerror != errorDold || rdsreset) {
    if (radio.rds.rdsDerror) tft.fillCircle(200, 41, 5, SignificantColor); else tft.fillCircle(200, 41, 5, InsignificantColor);
    errorDold = radio.rds.rdsDerror;
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

  if (ptynold != radio.rds.PTYN) {
    tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, 16);
    tftPrint(-1, ptynold, 216, 109, BackgroundColor, BackgroundColor, 16);
    if (radio.rds.PTYN.length() == 0) radio.rds.PTYN = "PTYN N/A";
    tftPrint(-1, String(radio.rds.PTYN), 216, 109, PrimaryColor, PrimaryColorSmooth, 16);
    ptynold = radio.rds.PTYN;
  }

  if (licold != radio.rds.LIC) {
    tftPrint(-1, "N/A", 242, 208, BackgroundColor, BackgroundColor, 16);
    tftPrint(-1, LIColdString, 242, 208, BackgroundColor, BackgroundColor, 16);

    if (radio.rds.LIC > 0 && radio.rds.LIC < 44) {
      if (radio.rds.hasLIC) tftPrint(-1, myLanguages[radio.rds.LIC], 242, 208, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 208, PrimaryColor, PrimaryColorSmooth, 16);
      LIColdString = myLanguages[radio.rds.LIC];
    } else {
      byte lic;
      switch (radio.rds.LIC) {
        case 73: lic = 44; break;
        case 86: lic = 45; break;
        case 96: lic = 46; break;
        case 99: lic = 47; break;
        case 108: lic = 48; break;
        case 112: lic = 49; break;
        case 113: lic = 50; break;
        case 119: lic = 51; break;
        case 125: lic = 52; break;
        case 126: lic = 53; break;
        default: lic = 0; break;
      }
      if (radio.rds.hasLIC) tftPrint(-1, myLanguages[lic], 242, 208, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 208, PrimaryColor, PrimaryColorSmooth, 16);
      LIColdString = myLanguages[lic];
    }
    licold = radio.rds.LIC;
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    tftPrint(-1, "N/A", 242, 223, BackgroundColor, BackgroundColor, 16);
    tftPrint(-1, pinstringold, 242, 223, BackgroundColor, BackgroundColor, 16);

    if (radio.rds.hasPIN) tftPrint(-1, pinstring, 242, 223, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 223, PrimaryColor, PrimaryColorSmooth, 16);
    pinstringold = pinstring;
  }

  String afstring;
  if (radio.rds.hasAF) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (i == radio.af_counter - 1 ? "          " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (radio.rds.hasAF) tftPrint(-1, "AF", 47, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "AF", 47, 51, GreyoutColor, BackgroundColor, 16);
    hasafold = radio.rds.hasAF;
  }

  if (afstring.length() < 20) {
    if (afstringold != afstring) {
      xPos2 = 0;
      sprite5.fillSprite(BackgroundColor);
      sprite5.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite5.drawString(afstring, xPos2, 2);
      sprite5.pushSprite(35, 197);
    }
  } else {
    if (millis() - afticker >= 15) {
      if (xPos2 == 0) {
        if (millis() - aftickerhold >= 2000) {
          xPos2 --;
          aftickerhold = millis();
        }
      } else {
        xPos2 --;
        aftickerhold = millis();
      }
      if (xPos2 < -tft.textWidth(afstring) + (charWidth * 14)) xPos2 = 0;
      sprite5.fillSprite(BackgroundColor);
      sprite5.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite5.drawString(afstring, xPos2, 2);
      sprite5.pushSprite(35, 197);
      afticker = millis();
    }
  }
  afstringold = afstring;

  String eonstring;
  if (radio.rds.hasEON) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "          " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (radio.rds.hasEON) tftPrint(-1, "EON", 150, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "EON", 150, 51, GreyoutColor, BackgroundColor, 16);
    haseonold = radio.rds.hasEON;
  }
  if (eonstring.length() < 20) {
    if (eonstringold != eonstring) {
      xPos3 = 0;
      sprite3.fillSprite(BackgroundColor);
      sprite3.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite3.drawString(eonstring, xPos3, 2);
      sprite3.pushSprite(35, 172);
    }
  } else {
    if (millis() - eonticker >= 15) {
      if (xPos3 == 0) {
        if (millis() - eontickerhold >= 2000) {
          xPos3 --;
          eontickerhold = millis();
        }
      } else {
        xPos3 --;
        eontickerhold = millis();
      }
      if (xPos3 < -tft.textWidth(eonstring) + (charWidth * 14)) xPos3 = 0;
      sprite3.fillSprite(BackgroundColor);
      sprite3.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite3.drawString(eonstring, xPos3, 2);
      sprite3.pushSprite(35, 172);
      eonticker = millis();
    }
  }
  eonstringold = eonstring;

  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = (radio.rds.rdsplusTag1 != 169 ? String(myLanguage[language][radio.rds.rdsplusTag1]) + ": " + String(radio.rds.RTContent1) : "") + (radio.rds.rdsplusTag2 != 169 ? " - " + String(myLanguage[language][radio.rds.rdsplusTag2]) + ": " + String(radio.rds.RTContent2) : "") + "         "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (radio.rds.hasRDSplus) tftPrint(-1, "RT+", 122, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "RT+", 122, 51, GreyoutColor, BackgroundColor, 16);
    hasrtplusold = radio.rds.hasRDSplus;
  }
  if (rtplusstring.length() < 20) {
    if (rtplusstringold != rtplusstring) {
      xPos4 = 0;
      sprite4.fillSprite(BackgroundColor);
      sprite4.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite4.drawString(rtplusstring, xPos4, 2);
      sprite4.pushSprite(35, 146);
    }
  } else {
    if (millis() - rtplusticker >= 15) {
      if (xPos4 == 0) {
        if (millis() - rtplustickerhold >= 2000) {
          xPos4 --;
          rtplustickerhold = millis();
        }
      } else {
        xPos4 --;
        rtplustickerhold = millis();
      }
      if (xPos4 < -tft.textWidth(rtplusstring) + (charWidth * 14)) xPos4 = 0;
      sprite4.fillSprite(BackgroundColor);
      sprite4.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      sprite4.drawString(rtplusstring, xPos4, 2);
      sprite4.pushSprite(35, 146);
      rtplusticker = millis();
    }
  }
  rtplusstringold = rtplusstring;

  if (TPold != radio.rds.hasTP) {
    if (radio.rds.hasTP == true) tftPrint(-1, "TP", 3, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TP", 3, 51, GreyoutColor, BackgroundColor, 16);
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    if (radio.rds.hasTA == true) tftPrint(-1, "TA", 25, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TA", 25, 51, GreyoutColor, BackgroundColor, 16);
    TAold = radio.rds.hasTA;
  }

  if (MSold != radio.rds.MS) {
    switch (radio.rds.MS) {
      case 0:
        tftPrint(-1, "M", 183, 51, GreyoutColor, BackgroundColor, 16);
        tftPrint(-1, "S", 199, 51, GreyoutColor, BackgroundColor, 16);
        break;

      case 1:
        tftPrint(-1, "M", 183, 51, PrimaryColor, PrimaryColorSmooth, 16);
        tftPrint(-1, "S", 199, 51, GreyoutColor, BackgroundColor, 16);
        break;

      case 2:
        tftPrint(-1, "M", 183, 51, GreyoutColor, BackgroundColor, 16);
        tftPrint(-1, "S", 199, 51, PrimaryColor, PrimaryColorSmooth, 16);
        break;
    }
    MSold = radio.rds.MS;
  }

  rds_clock = ((hour() < 10 ? "0" : "") + String(hour()) + ":" + (minute() < 10 ? "0" : "") + String(minute()));
  if (rds_clock != rds_clockold) {
    if (radio.rds.hasCT) {
      tftReplace(1, rds_clockold, rds_clock, 205, 109, PrimaryColor, PrimaryColorSmooth, 16);
      tftPrint(-1, "CT", 69, 51, PrimaryColor, PrimaryColorSmooth, 16);
    } else {
      tftPrint(1, rds_clock, 205, 109, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, "CT", 69, 51, GreyoutColor, BackgroundColor, 16);
    }
    rds_clockold = rds_clock;
  }

  if (rdsblockold != radio.rdsblock) {
    if (rdsblockold < 33) tft.fillCircle((6 * rdsblockold) + 10, 133, 2, SignificantColor);
    if (radio.rdsblock < 33) tft.fillCircle((6 * radio.rdsblock) + 10, 133, 2, InsignificantColor);
    rdsblockold = radio.rdsblock;
  }

  if (hastmcold != radio.rds.hasTMC) {
    if (radio.rds.hasTMC == true) tftPrint(-1, "TMC", 89, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TMC", 89, 51, GreyoutColor, BackgroundColor, 16);
    hastmcold = radio.rds.hasTMC;
  }

  rdsreset = false;
}

void doAF() {
  if (radio.af_counter != af_counterold && radio.rds.hasAF == true) {
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("AF=");

      for (byte af_scan = 0; af_scan < radio.af_counter; af_scan++) {
        if (wifi) {
          if ((radio.af[af_scan].frequency - 8750) / 10 < 0x10) {
            Udp.print("0");
          }
          Udp.print(String((radio.af[af_scan].frequency - 8750) / 10, HEX));
        }
      }
      af_counterold = radio.af_counter;

      for (int i = 0; i < 25 - radio.af_counter; i++) Udp.print("00");
      Udp.endPacket();
    }
  }
}

void showECC() {
  if (ECCold != radio.rds.ECC) {
    String ECC;
    if (radio.rds.picode[0] == '1') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[129];
      if (radio.rds.ECC == 163) ECC = myCountries[136];
      if (radio.rds.ECC == 164) ECC = myCountries[152];
      if (radio.rds.ECC == 208) ECC = myCountries[104];
      if (radio.rds.ECC == 209) ECC = myCountries[73];
      if (radio.rds.ECC == 210) ECC = myCountries[83];
      if (radio.rds.ECC == 224) ECC = myCountries[0];
      if (radio.rds.ECC == 225) ECC = myCountries[1];
      if (radio.rds.ECC == 226) ECC = myCountries[2];
      if (radio.rds.ECC == 227) ECC = myCountries[59];
      if (radio.rds.ECC == 228) ECC = myCountries[3];
      if (radio.rds.ECC == 240) ECC = myCountries[179];
      if (radio.rds.ECC == 241) ECC = myCountries[197];
      if (radio.rds.ECC == 242) ECC = myCountries[124];
      if (radio.rds.ECC == 243) ECC = myCountries[200];
    } else if (radio.rds.picode[0] == '2') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[130];
      if (radio.rds.ECC == 163) ECC = myCountries[141];
      if (radio.rds.ECC == 164) ECC = myCountries[155];
      if (radio.rds.ECC == 208) ECC = myCountries[106];
      if (radio.rds.ECC == 209) ECC = myCountries[126];
      if (radio.rds.ECC == 210) ECC = myCountries[95];
      if (radio.rds.ECC == 224) ECC = myCountries[4];
      if (radio.rds.ECC == 225) ECC = myCountries[5];
      if (radio.rds.ECC == 226) ECC = myCountries[6];
      if (radio.rds.ECC == 227) ECC = myCountries[7];
      if (radio.rds.ECC == 228) ECC = myCountries[8];
      if (radio.rds.ECC == 240) ECC = myCountries[180];
      if (radio.rds.ECC == 241) ECC = myCountries[187];
      if (radio.rds.ECC == 242) ECC = myCountries[77];
      if (radio.rds.ECC == 243) ECC = myCountries[218];
    } else if (radio.rds.picode[0] == '3') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[224];
      if (radio.rds.ECC == 163) ECC = myCountries[156];
      if (radio.rds.ECC == 164) ECC = myCountries[132];
      if (radio.rds.ECC == 208) ECC = myCountries[112];
      if (radio.rds.ECC == 209) ECC = myCountries[119];
      if (radio.rds.ECC == 210) ECC = myCountries[72]; 
      if (radio.rds.ECC == 211) ECC = myCountries[92];
      if (radio.rds.ECC == 224) ECC = myCountries[9];
      if (radio.rds.ECC == 225) ECC = myCountries[10];
      if (radio.rds.ECC == 226) ECC = myCountries[11];
      if (radio.rds.ECC == 227) ECC = myCountries[12];
      if (radio.rds.ECC == 228) ECC = myCountries[16];
      if (radio.rds.ECC == 229) ECC = myCountries[63];
      if (radio.rds.ECC == 240) ECC = myCountries[181];
      if (radio.rds.ECC == 241) ECC = myCountries[227];
      if (radio.rds.ECC == 242) ECC = myCountries[189];
      if (radio.rds.ECC == 243) ECC = myCountries[219];
    } else if (radio.rds.picode[0] == '4') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[148];
      if (radio.rds.ECC == 163) ECC = myCountries[157];
      if (radio.rds.ECC == 208) ECC = myCountries[127];
      if (radio.rds.ECC == 209) ECC = myCountries[69];
      if (radio.rds.ECC == 210) ECC = myCountries[91];
      if (radio.rds.ECC == 211) ECC = myCountries[103];
      if (radio.rds.ECC == 224) ECC = myCountries[13];
      if (radio.rds.ECC == 225) ECC = myCountries[14];
      if (radio.rds.ECC == 226) ECC = myCountries[15];
      if (radio.rds.ECC == 240) ECC = myCountries[182];
      if (radio.rds.ECC == 241) ECC = myCountries[210];
      if (radio.rds.ECC == 242) ECC = myCountries[213];
    } else if (radio.rds.picode[0] == '5') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[133];
      if (radio.rds.ECC == 164) ECC = myCountries[159];
      if (radio.rds.ECC == 208) ECC = myCountries[68];
      if (radio.rds.ECC == 209) ECC = myCountries[79];
      if (radio.rds.ECC == 210) ECC = myCountries[88];
      if (radio.rds.ECC == 211) ECC = myCountries[78];
      if (radio.rds.ECC == 224) ECC = myCountries[17];
      if (radio.rds.ECC == 225) ECC = myCountries[18];
      if (radio.rds.ECC == 226) ECC = myCountries[19];
      if (radio.rds.ECC == 227) ECC = myCountries[65];
      if (radio.rds.ECC == 240) ECC = myCountries[183];
      if (radio.rds.ECC == 241) ECC = myCountries[191];
      if (radio.rds.ECC == 242) ECC = myCountries[193];
    } else if (radio.rds.picode[0] == '6') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[134];
      if (radio.rds.ECC == 163) ECC = myCountries[163];
      if (radio.rds.ECC == 164) ECC = myCountries[171];
      if (radio.rds.ECC == 208) ECC = myCountries[96];
      if (radio.rds.ECC == 209) ECC = myCountries[105];
      if (radio.rds.ECC == 210) ECC = myCountries[123];
      if (radio.rds.ECC == 211) ECC = myCountries[125];
      if (radio.rds.ECC == 224) ECC = myCountries[20];
      if (radio.rds.ECC == 225) ECC = myCountries[21];
      if (radio.rds.ECC == 226) ECC = myCountries[22];
      if (radio.rds.ECC == 227) ECC = myCountries[23];
      if (radio.rds.ECC == 228) ECC = myCountries[24];
      if (radio.rds.ECC == 240) ECC = myCountries[184];
      if (radio.rds.ECC == 241) ECC = myCountries[76];
      if (radio.rds.ECC == 242) ECC = myCountries[201];
    } else if (radio.rds.picode[0] == '7') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[139];
      if (radio.rds.ECC == 163) ECC = myCountries[161];
      if (radio.rds.ECC == 164) ECC = myCountries[164];
      if (radio.rds.ECC == 208) ECC = myCountries[113];
      if (radio.rds.ECC == 209) ECC = myCountries[81];
      if (radio.rds.ECC == 210) ECC = myCountries[84];
      if (radio.rds.ECC == 224) ECC = myCountries[25];
      if (radio.rds.ECC == 225) ECC = myCountries[26];
      if (radio.rds.ECC == 226) ECC = myCountries[27];
      if (radio.rds.ECC == 228) ECC = myCountries[62];
      if (radio.rds.ECC == 240) ECC = myCountries[185];
      if (radio.rds.ECC == 241) ECC = myCountries[207];
      if (radio.rds.ECC == 242) ECC = myCountries[221];
    } else if (radio.rds.picode[0] == '8') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[142];
      if (radio.rds.ECC == 164) ECC = myCountries[170];
      if (radio.rds.ECC == 208) ECC = myCountries[116];
      if (radio.rds.ECC == 209) ECC = myCountries[117];
      if (radio.rds.ECC == 210) ECC = myCountries[74];
      if (radio.rds.ECC == 211) ECC = myCountries[82];
      if (radio.rds.ECC == 224) ECC = myCountries[28];
      if (radio.rds.ECC == 225) ECC = myCountries[29];
      if (radio.rds.ECC == 226) ECC = myCountries[30];
      if (radio.rds.ECC == 227) ECC = myCountries[31];
      if (radio.rds.ECC == 228) ECC = myCountries[32];
      if (radio.rds.ECC == 240) ECC = myCountries[186];
      if (radio.rds.ECC == 241) ECC = myCountries[195];
      if (radio.rds.ECC == 242) ECC = myCountries[212];
      if (radio.rds.ECC == 243) ECC = myCountries[190];
    } else if (radio.rds.picode[0] == '9') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[143];
      if (radio.rds.ECC == 163) ECC = myCountries[162];
      if (radio.rds.ECC == 164) ECC = myCountries[174];
      if (radio.rds.ECC == 208) ECC = myCountries[120];
      if (radio.rds.ECC == 209) ECC = myCountries[102];
      if (radio.rds.ECC == 210) ECC = myCountries[107];
      if (radio.rds.ECC == 224) ECC = myCountries[33];
      if (radio.rds.ECC == 225) ECC = myCountries[34];
      if (radio.rds.ECC == 226) ECC = myCountries[35];
      if (radio.rds.ECC == 227) ECC = myCountries[36];
      if (radio.rds.ECC == 228) ECC = myCountries[37];
      if (radio.rds.ECC == 240) ECC = myCountries[80];
      if (radio.rds.ECC == 241) ECC = myCountries[209];
      if (radio.rds.ECC == 242) ECC = myCountries[196];
      if (radio.rds.ECC == 243) ECC = myCountries[211];
      if (radio.rds.ECC == 244) ECC = myCountries[190];
    } else if (radio.rds.picode[0] == 'A') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 162) ECC = myCountries[131];
      if (radio.rds.ECC == 163) ECC = myCountries[144];
      if (radio.rds.ECC == 164) ECC = myCountries[166];
      if (radio.rds.ECC == 208) ECC = myCountries[85];
      if (radio.rds.ECC == 209) ECC = myCountries[97];
      if (radio.rds.ECC == 210) ECC = myCountries[121];
      if (radio.rds.ECC == 211) ECC = myCountries[70]; 
      if (radio.rds.ECC == 212) ECC = myCountries[86];
      if (radio.rds.ECC == 224) ECC = myCountries[38]; 
      if (radio.rds.ECC == 225) ECC = myCountries[39];
      if (radio.rds.ECC == 226) ECC = myCountries[40];
      if (radio.rds.ECC == 227) ECC = myCountries[41];
      if (radio.rds.ECC == 228) ECC = myCountries[60];
      if (radio.rds.ECC == 240) ECC = myCountries[178];
      if (radio.rds.ECC == 241) ECC = myCountries[215];
      if (radio.rds.ECC == 242) ECC = myCountries[214];
    } else if (radio.rds.picode[0] == 'B') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 161) ECC = myCountries[138];
      if (radio.rds.ECC == 162) ECC = myCountries[137];
      if (radio.rds.ECC == 163) ECC = myCountries[145];
      if (radio.rds.ECC == 164) ECC = myCountries[167];
      if (radio.rds.ECC == 165) ECC = myCountries[158];
      if (radio.rds.ECC == 208) ECC = myCountries[101];
      if (radio.rds.ECC == 210) ECC = myCountries[109];
      if (radio.rds.ECC == 209) ECC = myCountries[100];
      if (radio.rds.ECC == 224) ECC = myCountries[42];
      if (radio.rds.ECC == 225) ECC = myCountries[43];
      if (radio.rds.ECC == 226) ECC = myCountries[44];
      if (radio.rds.ECC == 227) ECC = myCountries[61];
      if (radio.rds.ECC == 228) ECC = myCountries[66];
      if (radio.rds.ECC == 240) ECC = myCountries[206];
      if (radio.rds.ECC == 241) ECC = myCountries[188];
      if (radio.rds.ECC == 242) ECC = myCountries[203];
      if (radio.rds.ECC == 243) ECC = myCountries[93];
      if (radio.rds.ECC == 244) ECC = myCountries[204];
    } else if (radio.rds.picode[0] == 'C') {
      if (radio.rds.ECC == 161) ECC = myCountries[138];
      if (radio.rds.ECC == 162) ECC = myCountries[223];
      if (radio.rds.ECC == 163) ECC = myCountries[140];
      if (radio.rds.ECC == 164) ECC = myCountries[146];
      if (radio.rds.ECC == 165) ECC = myCountries[169];
      if (radio.rds.ECC == 208) ECC = myCountries[110];
      if (radio.rds.ECC == 209) ECC = myCountries[108];
      if (radio.rds.ECC == 210) ECC = myCountries[111];
      if (radio.rds.ECC == 211) ECC = myCountries[87];
      if (radio.rds.ECC == 224) ECC = myCountries[45];
      if (radio.rds.ECC == 225) ECC = myCountries[46];
      if (radio.rds.ECC == 226) ECC = myCountries[47];
      if (radio.rds.ECC == 227) ECC = myCountries[48];
      if (radio.rds.ECC == 228) ECC = myCountries[118];
      if (radio.rds.ECC == 240) ECC = myCountries[190];
      if (radio.rds.ECC == 241) ECC = myCountries[216];
      if (radio.rds.ECC == 242) ECC = myCountries[194];
    } else if (radio.rds.picode[0] == 'D') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 161) ECC = myCountries[138];
      if (radio.rds.ECC == 162) ECC = myCountries[225];
      if (radio.rds.ECC == 163) ECC = myCountries[150];
      if (radio.rds.ECC == 164) ECC = myCountries[154];
      if (radio.rds.ECC == 165) ECC = myCountries[158];
      if (radio.rds.ECC == 208) ECC = myCountries[90];
      if (radio.rds.ECC == 209) ECC = myCountries[89];
      if (radio.rds.ECC == 224) ECC = myCountries[0];
      if (radio.rds.ECC == 225) ECC = myCountries[49];
      if (radio.rds.ECC == 227) ECC = myCountries[122];
      if (radio.rds.ECC == 240) ECC = myCountries[198];
      if (radio.rds.ECC == 241) ECC = myCountries[217];
      if (radio.rds.ECC == 242) ECC = myCountries[128];
    } else if (radio.rds.picode[0] == 'E') {
      if (radio.rds.ECC == 160) ECC = myCountries[226];
      if (radio.rds.ECC == 161) ECC = myCountries[138];
      if (radio.rds.ECC == 162) ECC = myCountries[151];
      if (radio.rds.ECC == 163) ECC = myCountries[172];
      if (radio.rds.ECC == 164) ECC = myCountries[175];
      if (radio.rds.ECC == 165) ECC = myCountries[158];
      if (radio.rds.ECC == 208) ECC = myCountries[99];
      if (radio.rds.ECC == 209) ECC = myCountries[115];
      if (radio.rds.ECC == 210) ECC = myCountries[94];
      if (radio.rds.ECC == 224) ECC = myCountries[50];
      if (radio.rds.ECC == 225) ECC = myCountries[51];
      if (radio.rds.ECC == 226) ECC = myCountries[52];
      if (radio.rds.ECC == 227) ECC = myCountries[53];
      if (radio.rds.ECC == 228) ECC = myCountries[64];
      if (radio.rds.ECC == 240) ECC = myCountries[98];
      if (radio.rds.ECC == 241) ECC = myCountries[199];
      if (radio.rds.ECC == 242) ECC = myCountries[208];
      if (radio.rds.ECC == 243) ECC = myCountries[205];
    } else if (radio.rds.picode[0] == 'F') {
      if (radio.rds.ECC == 161) ECC = myCountries[149];
      if (radio.rds.ECC == 162) ECC = myCountries[222];
      if (radio.rds.ECC == 163) ECC = myCountries[153];
      if (radio.rds.ECC == 164) ECC = myCountries[176];
      if (radio.rds.ECC == 165) ECC = myCountries[158];
      if (radio.rds.ECC == 166) ECC = myCountries[168];
      if (radio.rds.ECC == 208) ECC = myCountries[67];
      if (radio.rds.ECC == 209) ECC = myCountries[75];
      if (radio.rds.ECC == 210) ECC = myCountries[114];
      if (radio.rds.ECC == 224) ECC = myCountries[54];
      if (radio.rds.ECC == 225) ECC = myCountries[55];
      if (radio.rds.ECC == 226) ECC = myCountries[56];
      if (radio.rds.ECC == 227) ECC = myCountries[57];
      if (radio.rds.ECC == 228) ECC = myCountries[58];
      if (radio.rds.ECC == 240) ECC = myCountries[202];
      if (radio.rds.ECC == 241) ECC = myCountries[192];
      if (radio.rds.ECC == 242) ECC = myCountries[220];
      if (radio.rds.ECC == 243) ECC = myCountries[71]; 
    } else {
      ECC = myLanguage[language][73];
    }
    if (advancedRDS) {
      tftPrint(-1, "N/A", 242, 193, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, ECColdtxt, 242, 193, BackgroundColor, BackgroundColor, 16);
      if (radio.rds.hasECC) tftPrint(-1, ECC, 242, 193, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 193, PrimaryColor, PrimaryColorSmooth, 16);
      ECColdtxt = ECC;
    }

    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("ECC=");
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
    if (!afscreen) {
      if (!RDSstatus && !screenmute) {
        if (advancedRDS) tftPrint(-1, PIold, 244, 75, SecondaryColor, SecondaryColorSmooth, 28); else tftPrint(-1, PIold, 244, 187, SecondaryColor, SecondaryColorSmooth, 28);
        if (advancedRDS) tftPrint(-1, PSold, 38, 75, SecondaryColor, SecondaryColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, SecondaryColor, SecondaryColorSmooth, 28);
        if (advancedRDS) tftPrint(-1, PTYold, 38, 109, SecondaryColor, SecondaryColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, SecondaryColor, SecondaryColorSmooth, 16);
        if (advancedRDS) {
          tft.fillCircle(86, 41, 5, SignificantColor);
          tft.fillCircle(124, 41, 5, SignificantColor);
          tft.fillCircle(162, 41, 5, SignificantColor);
          tft.fillCircle(200, 41, 5, SignificantColor);
        }
        if (radio.rds.correctPI != 0) dropout = true;
        aftimer = millis();
      } else {
        if (dropout == true) {
          if (advancedRDS) tftPrint(-1, PIold, 244, 75, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(-1, PIold, 244, 187, PrimaryColor, PrimaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PSold, 38, 75, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, PrimaryColor, PrimaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, PrimaryColor, PrimaryColorSmooth, 16);
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
      DataPrint ("P");
      DataPrint (String(((radio.rds.rdsA >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsA >> 8) & 0xF, HEX));
      DataPrint (String(((radio.rds.rdsA) >> 4) & 0xF, HEX) + String((radio.rds.rdsA) & 0xF, HEX));
      if (((radio.rds.rdsErr >> 14) & 0x02) > 2) DataPrint("?");
      if (((radio.rds.rdsErr >> 14) & 0x01) > 1) DataPrint("?");
      DataPrint ("\n");

      XDRGTKRDS = "R";
      XDRGTKRDS += String(((radio.rds.rdsB >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsB >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsB) >> 4) & 0xF, HEX) + String((radio.rds.rdsB) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsC >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsC) >> 4) & 0xF, HEX) + String((radio.rds.rdsC) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD >> 8) >> 4) & 0xF, HEX) + String((radio.rds.rdsD >> 8) & 0xF, HEX);
      XDRGTKRDS += String(((radio.rds.rdsD) >> 4) & 0xF, HEX) + String((radio.rds.rdsD) & 0xF, HEX);

      uint8_t erroutput = 0;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x04) >> 2;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x02) << 2;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x01) << 6;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x08) >> 3;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x10) >> 1;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x40) << 1;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x80) >> 7;
      erroutput |= (highByte(radio.rds.rdsErr) & 0x20) << 5;

      if (highByte(radio.rds.rdsErr) < 0x10) XDRGTKRDS += "0";
      XDRGTKRDS += String(erroutput, HEX);
      XDRGTKRDS += "\n";

      if (XDRGTKRDS != XDRGTKRDSold) {
        DataPrint(XDRGTKRDS);
        XDRGTKRDSold = XDRGTKRDS;
      }
    }
  }
}

void showPI() {
  if (strcmp(radio.rds.picode, radioIdPrevious)) {
    if (advancedRDS) {
      tftReplace(-1, PIold, radio.rds.picode, 244, 75, PrimaryColor, PrimaryColorSmooth, 28);
    } else if (afscreen) {
      tftReplace(-1, PIold, radio.rds.picode, 30, 201, BWAutoColor, BWAutoColorSmooth, 16);
    } else {
      tftReplace(-1, PIold, radio.rds.picode, 244, 187, PrimaryColor, PrimaryColorSmooth, 28);
    }
    PIold = radio.rds.picode;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner;PI=" + String(radio.rds.picode, 4));
      Udp.endPacket();
    }
    strcpy(radioIdPrevious, radio.rds.picode);
  }
}

void showPTY() {
  if (strcmp(radio.rds.stationType, programTypePrevious)) {
    if (advancedRDS) tftReplace(-1, PTYold, radio.rds.stationType, 38, 109, PrimaryColor, PrimaryColorSmooth, 16); else tftReplace(-1, PTYold, radio.rds.stationType, 38, 163, PrimaryColor, PrimaryColorSmooth, 16);
    PTYold = radio.rds.stationType;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner;PTY=");
      Udp.print(String(radio.rds.stationTypeCode, HEX));
      Udp.endPacket();
    }
    strcpy(programTypePrevious, radio.rds.stationType);
  }
}

void showPS() {
  if (radio.rds.stationName != programServicePrevious) {
    if (advancedRDS) {
      tftReplace(-1, PSold, radio.rds.stationName, 38, 75, PrimaryColor, PrimaryColorSmooth, 28);
    } else if (afscreen) {
      tftReplace(0, PSold, radio.rds.stationName, 160, 201, BWAutoColor, BWAutoColorSmooth, 16);
    } else {
      tftReplace(-1, PSold, radio.rds.stationName, 38, 187, PrimaryColor, PrimaryColorSmooth, 28);
    }
    PSold = radio.rds.stationName;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner;PS=");
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
    programServicePrevious = radio.rds.stationName;
  }
}

void showRadioText() {
  if (radio.rds.hasRT && radio.rds.stationText.length() > 0) {
    if (advancedRDS && radio.rds.stationText.length() < 20) {
      xPos = 0;
      sprite2.fillSprite(BackgroundColor);
      if (RDSstatus) sprite2.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else sprite2.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
      sprite2.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
      sprite2.pushSprite(35, 220);
    } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
      if (RTold != radio.rds.stationText + " " + radio.rds.stationText32) {
        xPos = 0;
        sprite.fillSprite(BackgroundColor);
        if (RDSstatus) sprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else sprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
        sprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
        sprite.pushSprite(38, 220);
      }
    } else {
      if (millis() - rtticker >= 15) {
        if (xPos == 0) {
          if (millis() - rttickerhold >= 2000) {
            xPos --;
            rttickerhold = millis();
          }
        } else {
          xPos --;
          rttickerhold = millis();
        }
        if (advancedRDS) {
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 16)) xPos = 0;
          sprite2.fillSprite(BackgroundColor);
          if (RDSstatus) sprite2.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else sprite2.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
          sprite2.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          sprite2.pushSprite(35, 220);
        } else {
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 26)) xPos = 0;
          sprite.fillSprite(BackgroundColor);
          if (RDSstatus) sprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else sprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
          sprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          sprite.pushSprite(38, 220);
        }
        rtticker = millis();
      }
    }
  }

  if (wifi) {
    Udp.beginPacket(remoteip, 9030);
    Udp.print("from=TEF_tuner;RT1=");
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
  RTold = radio.rds.stationText + " " + radio.rds.stationText32;
}

void ShowAFEON() {
  if (radio.rds.hasAF) {
    if (hasafold == false) {
      tftPrint(-1, myLanguage[language][87], 6, 54, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, "AF:", 4, 32, ActiveColor, ActiveColorSmooth, 16);
      hasafold = true;
    }

    if (radio.af_counter > 30) {
      if (!afpage) {
        afpage = true;
        afpagenr = 1;
      }
    } else {
      afpagenr = 0;
    }

    if (af_counterold != radio.af_counter) {
      tft.fillRect(2, 48, 166, 150, BackgroundColor);
      for (byte i = 0; i < radio.af_counter; i++) {
        byte x = i - (afpagenr == 2 ? 30 : 0);
        if (radio.af[i].checked) {
          tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), InsignificantColor, InsignificantColorSmooth, 16);
        } else if (!radio.af[i].afvalid) {
          tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), SignificantColor, SignificantColorSmooth, 16);
        } else {
          tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 50 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), PrimaryColor, PrimaryColorSmooth, 16);
        }
        if (i == 29  + (afpagenr == 2 ? 30 : 0)) i = 254;
      }

      if (radio.af_counter > 10 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(59, 54, 59, 191, SecondaryColor);
      if (radio.af_counter > 20 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(113, 54, 113, 191, SecondaryColor);
      if (afpage == true) tftPrint(1, String(afpagenr) + "/2", 315, 222, SecondaryColor, SecondaryColorSmooth, 16);
    }
    af_counterold = radio.af_counter;
  }

  if (radio.rds.hasEON) {
    if (haseonold == false) {
      tftPrint(-1, myLanguage[language][88], 184, 48, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, "PI:", 170, 32, ActiveColor, ActiveColorSmooth, 16);
    }
    haseonold = true;
    for (byte i = 0; i < radio.eon_counter; i++) {
      tftPrint(-1, String(radio.eon[i].picode), 170, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, 16);
      if (radio.eon[i].ps.length() > 0) {
        tftPrint(-1, "PS:", 206, 32, ActiveColor, ActiveColorSmooth, 16);
        if (radio.eon[i].ps != eonpsold[i]) {
          tftPrint(-1, String(eonpsold[i]), 206, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          eonpsold[i] = radio.eon[i].ps;
        }
        tftPrint(-1, String(radio.eon[i].ps), 206, 48 + (15 * i), SecondaryColor, SecondaryColorSmooth, 16);
      }

      if (radio.eon[i].mappedfreq > 0) {
        tftPrint(1, "FREQ:", 316, 32, ActiveColor, ActiveColorSmooth, 16);
        if (radio.eon[i].mappedfreq != mappedfreqold[i]) {
          tftPrint(1, String(mappedfreqold[i] / 100) + "." + String((mappedfreqold[i] % 100) / 10), 316, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
        }
        tftPrint(1, String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10), 316, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, 16);
        mappedfreqold[i] = radio.eon[i].mappedfreq;
      }
      if (i == 10) i = 254;
    }
  }
}
