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

  if (ptynold != radio.rds.PTYN || rdsreset) {
    if (!screenmute) tftPrint(-1, "PTYN N/A", 216, 109, BackgroundColor, BackgroundColor, 16);
    if (!screenmute) tftPrint(-1, ptynold, 216, 109, BackgroundColor, BackgroundColor, 16);
    if (radio.rds.PTYN.length() == 0) radio.rds.PTYN = "PTYN N/A";
    if (!screenmute) tftPrint(-1, String(radio.rds.PTYN), 216, 109, PrimaryColor, PrimaryColorSmooth, 16);
    ptynold = radio.rds.PTYN;
  }

  if (licold != radio.rds.LIC || rdsreset) {
    if (!screenmute) tftPrint(-1, "N/A", 242, 208, BackgroundColor, BackgroundColor, 16);
    if (!screenmute) tftPrint(-1, LIColdString, 242, 208, BackgroundColor, BackgroundColor, 16);

    if (radio.rds.LIC > 0 && radio.rds.LIC < 128) {
      if (!screenmute) {
        if (radio.rds.hasLIC) tftPrint(-1, LICtext[radio.rds.LIC], 242, 208, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 208, PrimaryColor, PrimaryColorSmooth, 16);
      }
      LIColdString = LICtext[radio.rds.LIC];
    } else {
      if (!screenmute) {
        if (radio.rds.hasLIC) tftPrint(-1, LICtext[0], 242, 208, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 208, PrimaryColor, PrimaryColorSmooth, 16);
      }
      LIColdString = LICtext[0];
    }
    licold = radio.rds.LIC;
  }

  String pinstring = String(radio.rds.pinDay) + " " + String(radio.rds.pinHour) + ":" + (radio.rds.pinMin < 10 ? "0" : "") + String(radio.rds.pinMin);
  if (pinstringold != pinstring) {
    if (!screenmute)  {
      tftPrint(-1, "N/A", 242, 223, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, pinstringold, 242, 223, BackgroundColor, BackgroundColor, 16);

      if (radio.rds.hasPIN) tftPrint(-1, pinstring, 242, 223, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 223, PrimaryColor, PrimaryColorSmooth, 16);
      pinstringold = pinstring;
    }
  }

  String afstring;
  if (radio.rds.hasAF) for (byte i = 0; i < radio.af_counter; i++) afstring += String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10) + (i == radio.af_counter - 1 ? "          " : " | "); else afstring = myLanguage[language][87];
  if (hasafold != radio.rds.hasAF) {
    if (!screenmute) {
      if (radio.rds.hasAF) tftPrint(-1, "AF", 52, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "AF", 52, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasafold = radio.rds.hasAF;
  }

  if (afstring.length() < 20) {
    if (afstringold != afstring) {
      xPos2 = 0;
      AFSprite.fillSprite(BackgroundColor);
      AFSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      AFSprite.drawString(afstring, xPos2, 2);
      AFSprite.pushSprite(35, 197);
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
      AFSprite.fillSprite(BackgroundColor);
      AFSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      AFSprite.drawString(afstring, xPos2, 2);
      AFSprite.pushSprite(35, 197);
      afticker = millis();
    }
  }
  afstringold = afstring;

  String eonstring;
  if (radio.rds.hasEON) for (byte i = 0; i < radio.eon_counter; i++) eonstring += String(radio.eon[i].picode) + (radio.eon[i].ps.length() > 0 ? String(": " + String(radio.eon[i].ps)) : "") + (radio.eon[i].mappedfreq > 0 ? String(" " + String(radio.eon[i].mappedfreq / 100) + "." + String((radio.eon[i].mappedfreq % 100) / 10))  : "") + (radio.eon[i].mappedfreq2 > 0 ? String(" / " + String(radio.eon[i].mappedfreq2 / 100) + "." + String((radio.eon[i].mappedfreq2 % 100) / 10))  : "") + (radio.eon[i].mappedfreq3 > 0 ? String(" /  " + String(radio.eon[i].mappedfreq3 / 100) + "." + String((radio.eon[i].mappedfreq3 % 100) / 10))  : "") + (i == radio.eon_counter - 1 ? "          " : " | "); else eonstring = myLanguage[language][88];
  if (haseonold != radio.rds.hasEON) {
    if (!screenmute)  {
      if (radio.rds.hasEON) tftPrint(-1, "EON", 155, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "EON", 155, 51, GreyoutColor, BackgroundColor, 16);
    }
    haseonold = radio.rds.hasEON;
  }
  if (eonstring.length() < 20) {
    if (eonstringold != eonstring) {
      xPos3 = 0;
      EONSprite.fillSprite(BackgroundColor);
      EONSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      EONSprite.drawString(eonstring, xPos3, 2);
      EONSprite.pushSprite(35, 172);
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
      EONSprite.fillSprite(BackgroundColor);
      EONSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      EONSprite.drawString(eonstring, xPos3, 2);
      EONSprite.pushSprite(35, 172);
      eonticker = millis();
    }
  }
  eonstringold = eonstring;

  String rtplusstring;
  if (radio.rds.hasRDSplus) rtplusstring = (radio.rds.rdsplusTag1 != 169 ? String(myLanguage[language][radio.rds.rdsplusTag1]) + ": " + String(radio.rds.RTContent1) : "") + (radio.rds.rdsplusTag2 != 169 ? " - " + String(myLanguage[language][radio.rds.rdsplusTag2]) + ": " + String(radio.rds.RTContent2) : "") + "         "; else rtplusstring = myLanguage[language][89];
  if (hasrtplusold != radio.rds.hasRDSplus) {
    if (!screenmute) {
      if (radio.rds.hasRDSplus) tftPrint(-1, "RT+", 127, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "RT+", 127, 51, GreyoutColor, BackgroundColor, 16);
    }
    hasrtplusold = radio.rds.hasRDSplus;
  }
  if (rtplusstring.length() < 20) {
    if (rtplusstringold != rtplusstring) {
      xPos4 = 0;
      RTPlusSprite.fillSprite(BackgroundColor);
      RTPlusSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      RTPlusSprite.drawString(rtplusstring, xPos4, 2);
      RTPlusSprite.pushSprite(35, 146);
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
      RTPlusSprite.fillSprite(BackgroundColor);
      RTPlusSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false);
      RTPlusSprite.drawString(rtplusstring, xPos4, 2);
      RTPlusSprite.pushSprite(35, 146);
      rtplusticker = millis();
    }
  }
  rtplusstringold = rtplusstring;

  if (TPold != radio.rds.hasTP) {
    if (!screenmute) {
      if (radio.rds.hasTP) tftPrint(-1, "TP", 2, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TP", 2, 51, GreyoutColor, BackgroundColor, 16);
    }
    TPold = radio.rds.hasTP;
  }

  if (TAold != radio.rds.hasTA) {
    if (!screenmute) {
      if (radio.rds.hasTA) tftPrint(-1, "TA", 25, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TA", 25, 51, GreyoutColor, BackgroundColor, 16);
    }
    TAold = radio.rds.hasTA;
  }

  if (afmethodBold != radio.afmethodB || rdsreset) {
    if (!screenmute) {
      if (radio.afmethodB) tftPrint(-1, "-B", 70, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "-B", 70, 51, GreyoutColor, BackgroundColor, 16);
    }
    afmethodBold = radio.afmethodB;
  }

  if (MSold != radio.rds.MS) {
    if (!screenmute) {
      switch (radio.rds.MS) {
        case 0:
          tftPrint(-1, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "S", 188, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 1:
          tftPrint(-1, "M", 196, 51, PrimaryColor, PrimaryColorSmooth, 16);
          tftPrint(-1, "S", 188, 51, GreyoutColor, BackgroundColor, 16);
          break;

        case 2:
          tftPrint(-1, "M", 196, 51, GreyoutColor, BackgroundColor, 16);
          tftPrint(-1, "S", 188, 51, PrimaryColor, PrimaryColorSmooth, 16);
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
      if (radio.rds.hasTMC) tftPrint(-1, "TMC", 90, 51, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "TMC", 90, 51, GreyoutColor, BackgroundColor, 16);
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
    String ECC;
    ECC = myLanguage[language][73];
    if (radio.rds.picode[0] == '1') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[129];
      if (radio.rds.ECC == 163) ECC = ECCtext[136];
      if (radio.rds.ECC == 164) ECC = ECCtext[152];
      if (radio.rds.ECC == 208) ECC = ECCtext[104];
      if (radio.rds.ECC == 209) ECC = ECCtext[73];
      if (radio.rds.ECC == 210) ECC = ECCtext[83];
      if (radio.rds.ECC == 224) ECC = ECCtext[0];
      if (radio.rds.ECC == 225) ECC = ECCtext[1];
      if (radio.rds.ECC == 226) ECC = ECCtext[2];
      if (radio.rds.ECC == 227) ECC = ECCtext[59];
      if (radio.rds.ECC == 228) ECC = ECCtext[3];
      if (radio.rds.ECC == 240) ECC = ECCtext[179];
      if (radio.rds.ECC == 241) ECC = ECCtext[197];
      if (radio.rds.ECC == 242) ECC = ECCtext[124];
      if (radio.rds.ECC == 243) ECC = ECCtext[200];
    } else if (radio.rds.picode[0] == '2') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[130];
      if (radio.rds.ECC == 163) ECC = ECCtext[141];
      if (radio.rds.ECC == 164) ECC = ECCtext[155];
      if (radio.rds.ECC == 208) ECC = ECCtext[106];
      if (radio.rds.ECC == 209) ECC = ECCtext[126];
      if (radio.rds.ECC == 210) ECC = ECCtext[95];
      if (radio.rds.ECC == 224) ECC = ECCtext[4];
      if (radio.rds.ECC == 225) ECC = ECCtext[5];
      if (radio.rds.ECC == 226) ECC = ECCtext[6];
      if (radio.rds.ECC == 227) ECC = ECCtext[7];
      if (radio.rds.ECC == 228) ECC = ECCtext[8];
      if (radio.rds.ECC == 240) ECC = ECCtext[180];
      if (radio.rds.ECC == 241) ECC = ECCtext[187];
      if (radio.rds.ECC == 242) ECC = ECCtext[77];
      if (radio.rds.ECC == 243) ECC = ECCtext[218];
    } else if (radio.rds.picode[0] == '3') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[224];
      if (radio.rds.ECC == 163) ECC = ECCtext[156];
      if (radio.rds.ECC == 164) ECC = ECCtext[132];
      if (radio.rds.ECC == 208) ECC = ECCtext[112];
      if (radio.rds.ECC == 209) ECC = ECCtext[119];
      if (radio.rds.ECC == 210) ECC = ECCtext[72];
      if (radio.rds.ECC == 211) ECC = ECCtext[92];
      if (radio.rds.ECC == 224) ECC = ECCtext[9];
      if (radio.rds.ECC == 225) ECC = ECCtext[10];
      if (radio.rds.ECC == 226) ECC = ECCtext[11];
      if (radio.rds.ECC == 227) ECC = ECCtext[12];
      if (radio.rds.ECC == 228) ECC = ECCtext[16];
      if (radio.rds.ECC == 229) ECC = ECCtext[63];
      if (radio.rds.ECC == 240) ECC = ECCtext[181];
      if (radio.rds.ECC == 241) ECC = ECCtext[227];
      if (radio.rds.ECC == 242) ECC = ECCtext[189];
      if (radio.rds.ECC == 243) ECC = ECCtext[219];
    } else if (radio.rds.picode[0] == '4') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[148];
      if (radio.rds.ECC == 163) ECC = ECCtext[157];
      if (radio.rds.ECC == 208) ECC = ECCtext[127];
      if (radio.rds.ECC == 209) ECC = ECCtext[69];
      if (radio.rds.ECC == 210) ECC = ECCtext[91];
      if (radio.rds.ECC == 211) ECC = ECCtext[103];
      if (radio.rds.ECC == 224) ECC = ECCtext[13];
      if (radio.rds.ECC == 225) ECC = ECCtext[14];
      if (radio.rds.ECC == 226) ECC = ECCtext[15];
      if (radio.rds.ECC == 240) ECC = ECCtext[182];
      if (radio.rds.ECC == 241) ECC = ECCtext[210];
      if (radio.rds.ECC == 242) ECC = ECCtext[213];
    } else if (radio.rds.picode[0] == '5') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[133];
      if (radio.rds.ECC == 164) ECC = ECCtext[159];
      if (radio.rds.ECC == 208) ECC = ECCtext[68];
      if (radio.rds.ECC == 209) ECC = ECCtext[79];
      if (radio.rds.ECC == 210) ECC = ECCtext[88];
      if (radio.rds.ECC == 211) ECC = ECCtext[78];
      if (radio.rds.ECC == 224) ECC = ECCtext[17];
      if (radio.rds.ECC == 225) ECC = ECCtext[18];
      if (radio.rds.ECC == 226) ECC = ECCtext[19];
      if (radio.rds.ECC == 227) ECC = ECCtext[65];
      if (radio.rds.ECC == 240) ECC = ECCtext[183];
      if (radio.rds.ECC == 241) ECC = ECCtext[191];
      if (radio.rds.ECC == 242) ECC = ECCtext[193];
    } else if (radio.rds.picode[0] == '6') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[134];
      if (radio.rds.ECC == 163) ECC = ECCtext[163];
      if (radio.rds.ECC == 164) ECC = ECCtext[171];
      if (radio.rds.ECC == 208) ECC = ECCtext[96];
      if (radio.rds.ECC == 209) ECC = ECCtext[105];
      if (radio.rds.ECC == 210) ECC = ECCtext[123];
      if (radio.rds.ECC == 211) ECC = ECCtext[125];
      if (radio.rds.ECC == 224) ECC = ECCtext[20];
      if (radio.rds.ECC == 225) ECC = ECCtext[21];
      if (radio.rds.ECC == 226) ECC = ECCtext[22];
      if (radio.rds.ECC == 228) ECC = ECCtext[24];
      if (radio.rds.ECC == 240) ECC = ECCtext[184];
      if (radio.rds.ECC == 241) ECC = ECCtext[76];
      if (radio.rds.ECC == 242) ECC = ECCtext[201];
    } else if (radio.rds.picode[0] == '7') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[139];
      if (radio.rds.ECC == 163) ECC = ECCtext[161];
      if (radio.rds.ECC == 164) ECC = ECCtext[164];
      if (radio.rds.ECC == 208) ECC = ECCtext[113];
      if (radio.rds.ECC == 209) ECC = ECCtext[81];
      if (radio.rds.ECC == 210) ECC = ECCtext[84];
      if (radio.rds.ECC == 224) ECC = ECCtext[25];
      if (radio.rds.ECC == 225) ECC = ECCtext[26];
      if (radio.rds.ECC == 226) ECC = ECCtext[27];
      if (radio.rds.ECC == 228) ECC = ECCtext[62];
      if (radio.rds.ECC == 240) ECC = ECCtext[185];
      if (radio.rds.ECC == 241) ECC = ECCtext[207];
      if (radio.rds.ECC == 242) ECC = ECCtext[221];
    } else if (radio.rds.picode[0] == '8') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[142];
      if (radio.rds.ECC == 164) ECC = ECCtext[170];
      if (radio.rds.ECC == 208) ECC = ECCtext[116];
      if (radio.rds.ECC == 209) ECC = ECCtext[117];
      if (radio.rds.ECC == 210) ECC = ECCtext[74];
      if (radio.rds.ECC == 211) ECC = ECCtext[82];
      if (radio.rds.ECC == 224) ECC = ECCtext[28];
      if (radio.rds.ECC == 225) ECC = ECCtext[29];
      if (radio.rds.ECC == 226) ECC = ECCtext[30];
      if (radio.rds.ECC == 227) ECC = ECCtext[31];
      if (radio.rds.ECC == 228) ECC = ECCtext[32];
      if (radio.rds.ECC == 240) ECC = ECCtext[186];
      if (radio.rds.ECC == 241) ECC = ECCtext[195];
      if (radio.rds.ECC == 242) ECC = ECCtext[212];
      if (radio.rds.ECC == 243) ECC = ECCtext[190];
    } else if (radio.rds.picode[0] == '9') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[143];
      if (radio.rds.ECC == 163) ECC = ECCtext[162];
      if (radio.rds.ECC == 164) ECC = ECCtext[174];
      if (radio.rds.ECC == 208) ECC = ECCtext[120];
      if (radio.rds.ECC == 209) ECC = ECCtext[102];
      if (radio.rds.ECC == 210) ECC = ECCtext[107];
      if (radio.rds.ECC == 224) ECC = ECCtext[33];
      if (radio.rds.ECC == 225) ECC = ECCtext[34];
      if (radio.rds.ECC == 226) ECC = ECCtext[35];
      if (radio.rds.ECC == 227) ECC = ECCtext[36];
      if (radio.rds.ECC == 228) ECC = ECCtext[37];
      if (radio.rds.ECC == 240) ECC = ECCtext[80];
      if (radio.rds.ECC == 241) ECC = ECCtext[209];
      if (radio.rds.ECC == 242) ECC = ECCtext[196];
      if (radio.rds.ECC == 243) ECC = ECCtext[211];
      if (radio.rds.ECC == 244) ECC = ECCtext[190];
    } else if (radio.rds.picode[0] == 'A') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 162) ECC = ECCtext[131];
      if (radio.rds.ECC == 163) ECC = ECCtext[144];
      if (radio.rds.ECC == 164) ECC = ECCtext[166];
      if (radio.rds.ECC == 208) ECC = ECCtext[85];
      if (radio.rds.ECC == 209) ECC = ECCtext[97];
      if (radio.rds.ECC == 210) ECC = ECCtext[121];
      if (radio.rds.ECC == 211) ECC = ECCtext[70];
      if (radio.rds.ECC == 212) ECC = ECCtext[86];
      if (radio.rds.ECC == 224) ECC = ECCtext[38];
      if (radio.rds.ECC == 225) ECC = ECCtext[39];
      if (radio.rds.ECC == 226) ECC = ECCtext[40];
      if (radio.rds.ECC == 227) ECC = ECCtext[41];
      if (radio.rds.ECC == 228) ECC = ECCtext[60];
      if (radio.rds.ECC == 240) ECC = ECCtext[178];
      if (radio.rds.ECC == 241) ECC = ECCtext[215];
      if (radio.rds.ECC == 242) ECC = ECCtext[214];
    } else if (radio.rds.picode[0] == 'B') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 161) ECC = ECCtext[138];
      if (radio.rds.ECC == 162) ECC = ECCtext[137];
      if (radio.rds.ECC == 163) ECC = ECCtext[145];
      if (radio.rds.ECC == 164) ECC = ECCtext[167];
      if (radio.rds.ECC == 165) ECC = ECCtext[158];
      if (radio.rds.ECC == 208) ECC = ECCtext[101];
      if (radio.rds.ECC == 210) ECC = ECCtext[109];
      if (radio.rds.ECC == 209) ECC = ECCtext[100];
      if (radio.rds.ECC == 224) ECC = ECCtext[42];
      if (radio.rds.ECC == 225) ECC = ECCtext[43];
      if (radio.rds.ECC == 226) ECC = ECCtext[44];
      if (radio.rds.ECC == 227) ECC = ECCtext[61];
      if (radio.rds.ECC == 228) ECC = ECCtext[66];
      if (radio.rds.ECC == 240) ECC = ECCtext[206];
      if (radio.rds.ECC == 241) ECC = ECCtext[188];
      if (radio.rds.ECC == 242) ECC = ECCtext[203];
      if (radio.rds.ECC == 243) ECC = ECCtext[93];
      if (radio.rds.ECC == 244) ECC = ECCtext[204];
    } else if (radio.rds.picode[0] == 'C') {
      if (radio.rds.ECC == 161) ECC = ECCtext[138];
      if (radio.rds.ECC == 162) ECC = ECCtext[223];
      if (radio.rds.ECC == 163) ECC = ECCtext[140];
      if (radio.rds.ECC == 164) ECC = ECCtext[146];
      if (radio.rds.ECC == 165) ECC = ECCtext[169];
      if (radio.rds.ECC == 208) ECC = ECCtext[110];
      if (radio.rds.ECC == 209) ECC = ECCtext[108];
      if (radio.rds.ECC == 210) ECC = ECCtext[111];
      if (radio.rds.ECC == 211) ECC = ECCtext[87];
      if (radio.rds.ECC == 224) ECC = ECCtext[45];
      if (radio.rds.ECC == 225) ECC = ECCtext[46];
      if (radio.rds.ECC == 226) ECC = ECCtext[47];
      if (radio.rds.ECC == 227) ECC = ECCtext[48];
      if (radio.rds.ECC == 228) ECC = ECCtext[118];
      if (radio.rds.ECC == 240) ECC = ECCtext[190];
      if (radio.rds.ECC == 241) ECC = ECCtext[216];
      if (radio.rds.ECC == 242) ECC = ECCtext[194];
    } else if (radio.rds.picode[0] == 'D') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 161) ECC = ECCtext[138];
      if (radio.rds.ECC == 162) ECC = ECCtext[225];
      if (radio.rds.ECC == 163) ECC = ECCtext[150];
      if (radio.rds.ECC == 164) ECC = ECCtext[154];
      if (radio.rds.ECC == 165) ECC = ECCtext[158];
      if (radio.rds.ECC == 208) ECC = ECCtext[90];
      if (radio.rds.ECC == 209) ECC = ECCtext[89];
      if (radio.rds.ECC == 224) ECC = ECCtext[0];
      if (radio.rds.ECC == 225) ECC = ECCtext[49];
      if (radio.rds.ECC == 226) ECC = ECCtext[23];
      if (radio.rds.ECC == 227) ECC = ECCtext[122];
      if (radio.rds.ECC == 240) ECC = ECCtext[198];
      if (radio.rds.ECC == 241) ECC = ECCtext[217];
      if (radio.rds.ECC == 242) ECC = ECCtext[128];
    } else if (radio.rds.picode[0] == 'E') {
      if (radio.rds.ECC == 160) ECC = ECCtext[226];
      if (radio.rds.ECC == 161) ECC = ECCtext[138];
      if (radio.rds.ECC == 162) ECC = ECCtext[151];
      if (radio.rds.ECC == 163) ECC = ECCtext[172];
      if (radio.rds.ECC == 164) ECC = ECCtext[175];
      if (radio.rds.ECC == 165) ECC = ECCtext[158];
      if (radio.rds.ECC == 208) ECC = ECCtext[99];
      if (radio.rds.ECC == 209) ECC = ECCtext[115];
      if (radio.rds.ECC == 210) ECC = ECCtext[94];
      if (radio.rds.ECC == 224) ECC = ECCtext[50];
      if (radio.rds.ECC == 225) ECC = ECCtext[51];
      if (radio.rds.ECC == 226) ECC = ECCtext[52];
      if (radio.rds.ECC == 227) ECC = ECCtext[53];
      if (radio.rds.ECC == 228) ECC = ECCtext[64];
      if (radio.rds.ECC == 240) ECC = ECCtext[98];
      if (radio.rds.ECC == 241) ECC = ECCtext[199];
      if (radio.rds.ECC == 242) ECC = ECCtext[208];
      if (radio.rds.ECC == 243) ECC = ECCtext[205];
    } else if (radio.rds.picode[0] == 'F') {
      if (radio.rds.ECC == 161) ECC = ECCtext[149];
      if (radio.rds.ECC == 162) ECC = ECCtext[222];
      if (radio.rds.ECC == 163) ECC = ECCtext[153];
      if (radio.rds.ECC == 164) ECC = ECCtext[176];
      if (radio.rds.ECC == 165) ECC = ECCtext[158];
      if (radio.rds.ECC == 166) ECC = ECCtext[168];
      if (radio.rds.ECC == 208) ECC = ECCtext[67];
      if (radio.rds.ECC == 209) ECC = ECCtext[75];
      if (radio.rds.ECC == 210) ECC = ECCtext[114];
      if (radio.rds.ECC == 224) ECC = ECCtext[54];
      if (radio.rds.ECC == 225) ECC = ECCtext[55];
      if (radio.rds.ECC == 226) ECC = ECCtext[56];
      if (radio.rds.ECC == 227) ECC = ECCtext[57];
      if (radio.rds.ECC == 228) ECC = ECCtext[58];
      if (radio.rds.ECC == 240) ECC = ECCtext[202];
      if (radio.rds.ECC == 241) ECC = ECCtext[192];
      if (radio.rds.ECC == 242) ECC = ECCtext[220];
      if (radio.rds.ECC == 243) ECC = ECCtext[71];
    }
    if (advancedRDS) {
      if (!screenmute) {
        tftPrint(-1, "N/A", 242, 193, BackgroundColor, BackgroundColor, 16);
        tftPrint(-1, ECColdtxt, 242, 193, BackgroundColor, BackgroundColor, 16);
        if (radio.rds.hasECC) tftPrint(-1, ECC, 242, 193, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, "N/A", 242, 193, PrimaryColor, PrimaryColorSmooth, 16);
      }
      ECColdtxt = ECC;
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
        if (radio.rds.correctPI != 0) {
          if (advancedRDS) tftPrint(0, PIold, 275, 75, SecondaryColor, SecondaryColorSmooth, 28); else tftPrint(0, PIold, 275, 187, SecondaryColor, SecondaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PSold, 38, 75, SecondaryColor, SecondaryColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, SecondaryColor, SecondaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, SecondaryColor, SecondaryColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, SecondaryColor, SecondaryColorSmooth, 16);
          if (advancedRDS) {
            tft.fillCircle(86, 41, 5, SignificantColor);
            tft.fillCircle(124, 41, 5, SignificantColor);
            tft.fillCircle(162, 41, 5, SignificantColor);
            tft.fillCircle(200, 41, 5, SignificantColor);
          }
          dropout = true;
        }
      } else {
        if (dropout) {
          if (advancedRDS) tftPrint(0, PIold, 275, 75, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(0, PIold, 275, 187, PrimaryColor, PrimaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PSold, 38, 75, PrimaryColor, PrimaryColorSmooth, 28); else tftPrint(-1, PSold, 38, 187, PrimaryColor, PrimaryColorSmooth, 28);
          if (advancedRDS) tftPrint(-1, PTYold, 38, 109, PrimaryColor, PrimaryColorSmooth, 16); else tftPrint(-1, PTYold, 38, 163, PrimaryColor, PrimaryColorSmooth, 16);
          if (!advancedRDS) {
            tft.fillCircle(314, 223, 2, GreyoutColor);
            tft.fillCircle(314, 234, 2, GreyoutColor);
          } else {
            tft.fillCircle(203, 223, 2, GreyoutColor);
            tft.fillCircle(203, 234, 2, GreyoutColor);
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
    if (!screenmute) {
      if (advancedRDS) {
        tftReplace(0, PIold, radio.rds.picode, 275, 75, PrimaryColor, PrimaryColorSmooth, 28);
      } else if (afscreen) {
        tftReplace(-1, PIold, radio.rds.picode, 30, 201, BWAutoColor, BWAutoColorSmooth, 16);
      } else {
        tftReplace(0, PIold, radio.rds.picode, 275, 187, PrimaryColor, PrimaryColorSmooth, 28);
      }
    }
    PIold = radio.rds.picode;
    if (wifi) {
      Udp.beginPacket(remoteip, 9030);
      Udp.print("from=TEF_tuner " + String(stationlistid, DEC) + ";PI=" + String(radio.rds.picode, 4));
      Udp.endPacket();
    }
    strcpy(radioIdPrevious, radio.rds.picode);
  }
}

void showPTY() {
  if (strcmp(radio.rds.stationType, programTypePrevious)) {
    if (!screenmute) {
      if (advancedRDS) tftReplace(-1, PTYold, radio.rds.stationType, 38, 109, PrimaryColor, PrimaryColorSmooth, 16); else tftReplace(-1, PTYold, radio.rds.stationType, 38, 163, PrimaryColor, PrimaryColorSmooth, 16);
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
  if (radio.rds.stationName != programServicePrevious) {
    if (!screenmute) {
      if (advancedRDS) {
        tftReplace(-1, PSold, radio.rds.stationName, 38, 75, PrimaryColor, PrimaryColorSmooth, 28);
      } else if (afscreen) {
        tftReplace(0, PSold, radio.rds.stationName, 160, 201, BWAutoColor, BWAutoColorSmooth, 16);
      } else {
        tftReplace(-1, PSold, radio.rds.stationName, 38, 187, PrimaryColor, PrimaryColorSmooth, 28);
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
    programServicePrevious = radio.rds.stationName;
  }
}

void showCT() {
  if (!screenmute) {
    rds_clock = ((radio.rds.hour < 10 ? "0" : "") + String(radio.rds.hour) + ":" + (radio.rds.minute < 10 ? "0" : "") + String(radio.rds.minute));
    if (rds_clock != rds_clockold) {
      if (radio.rds.hasCT) {
        if (advancedRDS) tftReplace(1, rds_clockold, rds_clock, 205, 109, PrimaryColor, PrimaryColorSmooth, 16); else tftReplace(1, rds_clockold, rds_clock, 205, 163, PrimaryColor, PrimaryColorSmooth, 16);
      } else {
        if (advancedRDS) tftPrint(1, rds_clock, 205, 109, BackgroundColor, BackgroundColor, 16); else tftPrint(1, rds_clock, 205, 163, BackgroundColor, BackgroundColor, 16);
      }
    }
    rds_clockold = rds_clock;
  }
}

void showRadioText() {
  if (radio.rds.hasRT && radio.rds.stationText.length() > 0) {
    if (advancedRDS && radio.rds.stationText.length() < 20) {
      xPos = 0;
      AdvRadiotextSprite.fillSprite(BackgroundColor);
      if (RDSstatus) AdvRadiotextSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else AdvRadiotextSprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
      AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
      AdvRadiotextSprite.pushSprite(35, 220);
    } else if (!advancedRDS && radio.rds.stationText.length() < 29) {
      if (RTold != radio.rds.stationText + " " + radio.rds.stationText32) {
        xPos = 0;
        RadiotextSprite.fillSprite(BackgroundColor);
        if (RDSstatus) RadiotextSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else RadiotextSprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
        RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
        RadiotextSprite.pushSprite(38, 220);
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
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 10)) xPos = 0;
          AdvRadiotextSprite.fillSprite(BackgroundColor);
          if (RDSstatus) AdvRadiotextSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else AdvRadiotextSprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
          AdvRadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
          AdvRadiotextSprite.pushSprite(35, 220);
        } else {
          if (xPos < -tft.textWidth(radio.rds.stationText + " " + radio.rds.stationText32) + (charWidth * 20)) xPos = 0;
          RadiotextSprite.fillSprite(BackgroundColor);
          if (RDSstatus) RadiotextSprite.setTextColor(PrimaryColor, PrimaryColorSmooth, false); else RadiotextSprite.setTextColor(SecondaryColor, SecondaryColorSmooth, false);
          RadiotextSprite.drawString(radio.rds.stationText + " " + radio.rds.stationText32, xPos, 2);
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
  if (radio.rds.hasAF) {
    if (!hasafold) {
      if (!screenmute) tftPrint(-1, myLanguage[language][87], 6, 54, BackgroundColor, BackgroundColor, 16);
      if (!screenmute) tftPrint(-1, "AF:", 4, 32, ActiveColor, ActiveColorSmooth, 16);
      hasafold = true;
    }

    if (radio.af_counter > 30 || radio.eon_counter > 10) {
      if (!afpage) {
        afpage = true;
        afpagenr = 1;
      }
    } else {
      afpagenr = 0;
    }

    if (af_counterold != radio.af_updatecounter) {
      tft.fillRect(2, 48, 166, 150, BackgroundColor);
      for (byte i = 0; i < radio.af_counter; i++) {
        byte x = i - (afpagenr == 2 ? 30 : 0);
        if (!screenmute) {
          tftPrint(-1, (radio.afmethodB && !radio.af[i].regional && radio.af[i].same) ? "S " : (radio.afmethodB && radio.af[i].regional && radio.af[i].same) ? "M " : (radio.afmethodB && radio.af[i].regional && !radio.af[i].same) ? "R " : "", 10 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), ActiveColor, ActiveColorSmooth, 16);
          if (radio.af[i].checked) {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), InsignificantColor, InsignificantColorSmooth, 16);
          } else if (!radio.af[i].afvalid) {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), SignificantColor, SignificantColorSmooth, 16);
          } else {
            tftPrint(1, String(radio.af[i].frequency / 100) + "." + String((radio.af[i].frequency % 100) / 10), 55 + (x > 9 ? 54 : 0) + (x > 19 ? 54 : 0), 48 + (15 * x) - (x > 9 ? 150 : 0) - (x > 19 ? 150 : 0), PrimaryColor, PrimaryColorSmooth, 16);
          }
        }
        if (i == 29  + (afpagenr == 2 ? 30 : 0)) i = 254;
      }

      if (radio.af_counter > 10 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(59, 54, 59, 191, SecondaryColor);
      if (radio.af_counter > 20 + (afpagenr == 2 ? 30 : 0)) tft.drawLine(113, 54, 113, 191, SecondaryColor);
      if (afpage && !screenmute) tftPrint(1, String(afpagenr) + "/2", 315, 222, SecondaryColor, SecondaryColorSmooth, 16);
      af_counterold = radio.af_updatecounter;
    }
  }

  if (radio.rds.hasEON) {
    if (!haseonold && !screenmute) {
      tftPrint(-1, myLanguage[language][88], 184, 48, BackgroundColor, BackgroundColor, 16);
      tftPrint(-1, "PI:", 170, 32, ActiveColor, ActiveColorSmooth, 16);
    }
    haseonold = true;

    if (!screenmute && millis() >= eonticker + 1000) {
      eonticker = millis();
      byte y = 0;
      if (afpagenr == 2) y = 10;
      for (byte i = 0; i < radio.eon_counter; i++) {
        tftPrint(-1, String(radio.eon[i + y].picode), 170, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, 16);
        if (radio.eon[i + y].ps.length() > 0) {
          tftPrint(-1, "PS:", 206, 32, ActiveColor, ActiveColorSmooth, 16);
          if (radio.eon[i + y].ps != eonpsold[i + y]) {
            tftPrint(-1, String(eonpsold[i + y]), 206, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
            eonpsold[i + y] = radio.eon[i + y].ps;
          }
          tftPrint(-1, String(radio.eon[i + y].ps), 206, 48 + (15 * i), SecondaryColor, SecondaryColorSmooth, 16);
        }

        if (radio.eon[i + y].mappedfreq > 0) {
          tftPrint(1, "FREQ:", 316, 32, ActiveColor, ActiveColorSmooth, 16);
          if (radio.eon[i + y].mappedfreq != mappedfreqold[i + y]) {
            tftPrint(1, String(mappedfreqold[i + y] / 100) + "." + String((mappedfreqold[i + y] % 100) / 10), 316, 48 + (15 * i), BackgroundColor, BackgroundColor, 16);
          }
          tftPrint(1, String(radio.eon[i + y].mappedfreq / 100) + "." + String((radio.eon[i + y].mappedfreq % 100) / 10), 316, 48 + (15 * i), PrimaryColor, PrimaryColorSmooth, 16);
          mappedfreqold[i + y] = radio.eon[i + y].mappedfreq;
        }
        if (i == 10) i = 254;
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
              char id[5];
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

    if (!screenmute) {
      if (xPos == 0) {
        if (millis() - rttickerhold >= 2000) {
          xPos --;
          rttickerhold = millis();
        }
      } else {
        xPos --;
        rttickerhold = millis();
      }
      if (xPos < -tft.textWidth(String(myLanguage[language][93]) + "  -  " + String(myLanguage[language][204]) + ": " + AIDString) + (charWidth * 14)) xPos = 0;
      RadiotextSprite.fillSprite(BackgroundColor);
      RadiotextSprite.setTextColor(ActiveColor, ActiveColorSmooth, false);
      RadiotextSprite.drawString(String(myLanguage[language][93]) + "  -  " + String(myLanguage[language][204]) + ": " + AIDString, xPos, 2);
      RadiotextSprite.pushSprite(5, 220);
    }
  }
}