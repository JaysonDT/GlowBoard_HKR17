// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  /*
    for (uint16_t i = 0; i < Glowstrip.numPixels(); i++) {
      Glowstrip.setPixelColor(i, c);
      Glowstrip.show();
      delay(wait);
    }
  */

  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait) {
    if (i < Glowstrip.numPixels()) {
      Glowstrip.setPixelColor(i, c);
      Glowstrip.show();
      i++;
      modetimerprev = modetimer;
    } else {
      i = 0;
    }
  }

}

void edgescolorWipe(uint32_t c, uint8_t wait) {
  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait) {
    if (i < Glowstrip.numPixels()) {
    Glowstrip.setPixelColor(i, c);
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, c);
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, c);
      Glowstrip.setPixelColor(Glowstrip.numPixels() - i, c);
      Glowstrip.show();
      i++;
      modetimerprev = modetimer;
    } else {
      i = 0;
    }

  }
}

/*
for (uint16_t i = 0; i <= Glowstrip.numPixels() / 4; i++) {
  Glowstrip.setPixelColor(i, c);
  Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, c);
  Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, c);
  Glowstrip.setPixelColor(Glowstrip.numPixels() - i, c);
  Glowstrip.show();
  delay(wait);
}
}
*/

