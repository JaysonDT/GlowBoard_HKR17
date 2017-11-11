#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define LEDCOUNT 54

//code for no delay
uint32_t modetimer = 0;
uint32_t modetimerprev = 0;
int i = 0;
int j = 0;
int q = 0;
int cycle = 0;

// Parameter 1 = number of pixels in Glowstrip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
Adafruit_NeoPixel Glowstrip = Adafruit_NeoPixel(LEDCOUNT, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code


  Glowstrip.begin();
  Glowstrip.show(); // Initialize all pixels to 'off'
}

void loop() {

  //-------------------- modes to fix ----------------------------

  //colorwipe DONE

  //colorWipe(Glowstrip.Color(150, 150, 150), 200); // white
  //colorWipe(Glowstrip.Color(0, 255, 0), 200);


  //edgescolorwipe
  /*
    edgescolorWipe(Glowstrip.Color(200, 200, 200), 50); //white
    delay(500);
    edgescolorWipe(Glowstrip.Color(255, 0, 0), 50); // red
    delay(500);
  */

  //rainbow DONE
  //rainbow(20);

  //rainbowCycle DONE
  //rainbowCycle(5);

  //fullrainbowCycle
  fullrainbowCycle(20);

  //theaterChase DONE
  //theaterChase(Glowstrip.Color(64, 208, 224), 200); // turquoise

  //theaterChaseRainbow At the moment would take too long to modify, ignore this function
  //theaterChaseRainbow(20);

  //coplights
  //coplights(225);

  //usacycle
  usaCycle(10);

  /*
    percentWipe(20,0);
    delay(500);
    percentWipe(20, 25);
    delay(500);
    percentWipe(20, 50);
    delay(500);
    percentWipe(20,75);
    delay(500);
    percentWipe(20, 101);
    delay(500);
  */

}


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
  for (uint16_t i = 0; i <= Glowstrip.numPixels() / 4; i++) {
    Glowstrip.setPixelColor(i, c);
    Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, c);
    Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, c);
    Glowstrip.setPixelColor(Glowstrip.numPixels() - i, c);
    Glowstrip.show();
    delay(wait);
  }
}

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
      Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Wheel((i + j) & 255));
    }
    Glowstrip.show();
    j++;
    modetimerprev = modetimer;
  } else if (j > 255) {
    j = 0;
  }

}


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
  } else if (j > 255) {
    j = 0;
  }
}

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
// <more modes>
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
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
    }
    Glowstrip.show();
    j++;
    modetimerprev = modetimer;
  } else if (j > 255) {
    j = 0;
  }
}

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

void fullrainbowCycle(uint8_t wait) {
  /*
     uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
      for (i = 0; i < Glowstrip.numPixels(); i++) {
        Glowstrip.setPixelColor(i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
      }
      Glowstrip.show();
      delay(wait);
    }
  */
  //without delay
  modetimer = millis();
  if (modetimer - modetimerprev >= wait && j < 256) {
    for (i = 0; i < Glowstrip.numPixels(); i++) {
      Glowstrip.setPixelColor(i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
    }
    Glowstrip.show();

    j++;
    modetimerprev = modetimer;
  } else if (j > 255) {
    j = 0;
  }
}

// <more modes/>
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return Glowstrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return Glowstrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return Glowstrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t usaWheel(byte WheelPos) {
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
  if (WheelPos < 85) {
    return Glowstrip.Color(180, 180, 180);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return Glowstrip.Color(230, 0, 0);
  } else {
    WheelPos -= 170;
    return Glowstrip.Color(0, 0, 255);
  }
}
