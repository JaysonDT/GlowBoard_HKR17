//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {

    for (int q = 0; q < 4; q++) {
      for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 4) {
        Glowstrip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      Glowstrip.show();


      delay(wait);

      for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 4) {
        Glowstrip.setPixelColor(i + q, 0);      //turn every third pixel off
      }

    }

}
