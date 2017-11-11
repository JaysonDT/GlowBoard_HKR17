#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define LEDCOUNT 54

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

  //colorWipe(Glowstrip.Color(150, 150, 150), 20); // white
  //colorWipe(Glowstrip.Color(255, 0, 0), 20); // red
  //colorWipe(Glowstrip.Color(0, 255, 0), 20); // green
  //colorWipe(Glowstrip.Color(0, 0, 255), 20); // blue
  
  edgescolorWipe(Glowstrip.Color(200,200,200),50); //white
  delay(500);
  edgescolorWipe(Glowstrip.Color(255, 0, 0), 50); // red
  delay(500);
  edgescolorWipe(Glowstrip.Color(0, 255, 0), 50); // green
  delay(500);
  edgescolorWipe(Glowstrip.Color(0, 0, 255), 50); // blue
  delay(500);
  
  //rainbow(20);
  //rainbowCycle(15);
  //theaterChase(Glowstrip.Color(64, 208, 224), 20); // turquoise
  //coplights(225);
  //usaCycle(10);


}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {

  for (uint16_t i = 0; i < Glowstrip.numPixels(); i++) {
    Glowstrip.setPixelColor(i, c);
    Glowstrip.show();
    //delay(wait);
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

  uint16_t i, j;
  for (j = 0; j < 256; j++) {

    for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
      Glowstrip.setPixelColor(i, Wheel((i + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() - i, Wheel((i + j) & 255));
    }
    Glowstrip.show();
    delay(wait);
  }

}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {

  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++ ) { // 5 cycles of all colors on wheel

    for (i = 0; i < Glowstrip.numPixels() / 2; i++) {
      /*
        Glowstrip.setPixelColor(i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
      */
      //modified for mirrored image for board, still gotta fix the odd one pixel not updating bug
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));

    }
    Glowstrip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {

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
}

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
// <more modes>

void coplights(uint8_t wait) {
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

}
void usaCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i <= Glowstrip.numPixels() / 2; i++) {
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 - i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
      Glowstrip.setPixelColor(Glowstrip.numPixels() / 2 + i, usaWheel(((i * 256 / (Glowstrip.numPixels() / 2)) + j) & 255));
    }

    Glowstrip.show();
    delay(wait);

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
  delay(wait);
}

void fullrainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < Glowstrip.numPixels(); i++) {
      Glowstrip.setPixelColor(i, Wheel(((i * 256 / Glowstrip.numPixels()) + j) & 255));
    }
    Glowstrip.show();
    delay(wait);
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
  if (WheelPos < 85) {
    return Glowstrip.Color(180, 180, 180);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return Glowstrip.Color(230, 0, 0);
  }
  WheelPos -= 170;
  return Glowstrip.Color(0, 0, 255);
}
