// USA CYCLE

void usaCycle(uint8_t wait) {
  /*
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i <= Glowstrip.numPixels() / 2; i++) {
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
    }

    Glowstrip.show();
    delay(wait);
    }
  */

  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait && j < 256) {
    for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i-1, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255, i));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255, i));
    }
    Glowstrip.show();
    j++;
    modetimerprev = modetimer;
  } else if (j > 255) {
    j = 0;
  }
}

uint32_t usaWheel(byte WheelPos, byte i) {
  WheelPos = 255 - WheelPos;
  /*
  if (WheelPos < 85) {
    return Glowstrip.Color(180, 180, 180);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Glowstrip.Color(230, 0, 0);
  } else {
    WheelPos -= 170;
    return Glowstrip.Color(0, 0, 255);
  }
  */
  //made more american
  if (WheelPos < 86) {
    if ((i & 0x01) == 0) {
      return Glowstrip.Color(180, 180, 180);
    } else {
      return Glowstrip.Color(230, 0, 0);
    }

  } else if (WheelPos < 170) {
    WheelPos -= 86;
    if ((i & 0x01) == 0) {
      return Glowstrip.Color(180, 180, 180);
    } else {
      return Glowstrip.Color(230, 0, 0);
    }
  } else {
    WheelPos -= 170;
    return Glowstrip.Color(0, 0, 255);
  }
}
