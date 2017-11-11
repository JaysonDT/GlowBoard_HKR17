
int coplightside = 0;
void coplights(uint8_t wait) {
  /*
    for (uint16_t i = 0; i <= Glowstrip.numPixels() / 2; i++) {
    Glowstrip.setPixelColor(i, Glowstrip.Color(255, 0, 0));
    Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Glowstrip.Color(0, 0, 255));
    Glowstrip.show();
    }
    delay(wait);
    for (uint16_t i = 0; i <= Glowstrip.numPixels() / 2; i++) {
    Glowstrip.setPixelColor(i, Glowstrip.Color(0, 0, 255));
    Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Glowstrip.Color(255, 0, 0));

    Glowstrip.show();
    }
    delay(wait);
  */
  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait) {
    if (coplightside == 0) {
      for (uint16_t i = 0; i <= Glowstrip.numPixels() / 2; i++) {
        Glowstrip.setPixelColor(i, Glowstrip.Color(255, 0, 0));
        Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Glowstrip.Color(0, 0, 255));
        Glowstrip.show();
      }
      coplightside = 1;
    } else {
      for (uint16_t i = 0; i <= Glowstrip.numPixels() / 2; i++) {
        Glowstrip.setPixelColor(i, Glowstrip.Color(0, 0, 255));
        Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Glowstrip.Color(255, 0, 0));
        Glowstrip.show();
      }
      coplightside = 0;
    }
    modetimerprev = modetimer;
  }
}
