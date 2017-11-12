#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define LEDCOUNT 48

//code for no delay
uint32_t modetimer = 0;
uint32_t modetimerprev = 0;
int i = 0;
int j = 0;
int q = 0;
int cycle = 0;
int mode = 1;

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

  switch (mode) {
    case 1:
      //colorWipe(Glowstrip.Color(34, 76, 12), 85);
      //coplights(225);
      //rainbowCycle(5);
      edgescolorWipe(Glowstrip.Color(0, 0, 255), 200); //white
     
      break;

    case 2:
      rainbowCycle(5);
      break;

    case 3:
      coplights(225);
      break;

    case 4:
      fullrainbowCycle(20);
      break;

    case 5:
      usaCycle(10);
      break;

    case 6:
      theaterChase(Glowstrip.Color(64, 208, 224), 200);
      break;

    case 7:
      theaterChaseRainbow(20);
      break;

    case 8:

      break;

    case 9:

      break;

    case 10:

      break;
  }


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

  //fullrainbowCycle DONE
  //fullrainbowCycle(20);

  //theaterChase DONE
  //theaterChase(Glowstrip.Color(64, 208, 224), 200); // turquoise

  //theaterChaseRainbow At the moment would take too long to modify, ignore this function
  //theaterChaseRainbow(20);

  //coplights
  //coplights(225);

  //usacycle
  //usaCycle(10);

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


