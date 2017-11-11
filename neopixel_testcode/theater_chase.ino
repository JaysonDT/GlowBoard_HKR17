//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  /*
    for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
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
  */

  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait && q < 4) {
    for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 4) {
      Glowstrip.setPixelColor(i + q, c);  //turn every third pixel on
    }

    Glowstrip.show();
    for (uint16_t i = 0; i < Glowstrip.numPixels(); i = i + 4) {
      Glowstrip.setPixelColor(i + q, 0);      //turn every third pixel off
    }
    q++;
    modetimerprev = modetimer;
  } else if (q >= 4) {
    q = 0;
  }
}


//Theatre-style crawling lights with rainbow effect
//At the moment would take too long to modify, ignore this function
void theaterChaseRainbow(uint8_t wait) {
  /*
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
  */
  //without delay
}
