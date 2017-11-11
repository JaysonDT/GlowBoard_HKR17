
void percentWipe(uint8_t wait, uint8_t percent) {
  uint16_t i, j;

  for (j = 0; j < 100; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i <= Glowstrip.numPixels() / 2; i++) {


      uint32_t WheelPos;
      WheelPos = ((i * 100 / (Glowstrip.numPixels() / 2)));
      if (WheelPos < percent) {
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, Glowstrip.Color(200, 200, 200));
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i - 1, Glowstrip.Color(200, 200, 200));
      } else {
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, Glowstrip.Color(0, 0, 0));
        Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i - 1, Glowstrip.Color(0, 0, 0));
      }
    }
    Glowstrip.show();
  }
  //delay(wait);
}
