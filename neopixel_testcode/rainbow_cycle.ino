// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
/*
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++ ) { // 5 cycles of all colors on wheel

    for (i = 0; i < Glowstrip.numPixels() / 2; i++) {

        //Glowstrip.setPixelColor(i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));

      //modified for mirrored image for board, still gotta fix the odd one pixel not updating bug
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));

    }
    Glowstrip.show();
    delay(wait);
  }
*/
  //without delay
    modetimer = millis();
    if (modetimer - modetimerprev >= wait && j < 256) {
      for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
      }
      Glowstrip.show();
      j++;
      modetimerprev = modetimer;
    } else if(j > 255) {
      j = 0;
    }
}
