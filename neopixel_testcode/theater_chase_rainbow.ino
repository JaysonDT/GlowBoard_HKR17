//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {

  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 3) {
        Glowstrip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      Glowstrip.show();

      delay(wait);

      for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 3) {
        Glowstrip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}
