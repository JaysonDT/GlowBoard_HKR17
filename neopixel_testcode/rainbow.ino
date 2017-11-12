void rainbow(uint8_t wait) {
  /*
    uint16_t i, j;
    for (j = 0; j < 256; j++) {

      for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
        Glowstrip.setPixelColor(i, Wheel((i + j) & 255));
        Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Wheel((i + j) & 255));
      }
      Glowstrip.show();
      delay(wait);
    }
  */

  //without delay

  modetimer = millis();
  if (modetimer - modetimerprev >= wait && j < 256) {
    for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
      Glowstrip.setPixelColor(i, Wheel((i + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() - i-1, Wheel((i + j) & 255));
    }
    Glowstrip.show();
    j++;
    modetimerprev = modetimer;
  } else if(j > 255) {
    j = 0;
  }

}
