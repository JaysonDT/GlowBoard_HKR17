// GlowBoard_HKR17
//Dom Anatala & Jayson Tinsley
//
// Example help from NeoPixel Example code

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6

Adafruit_NeoPixel Glowstrip = Adafruit_NeoPixel(48, PIN, NEO_GRB + NEO_KHZ800);





void setup() {
  Glowstrip.begin();
  Glowstrip.show();

}

void loop() {
  colorWipe(Glowstrip.Color(0, 0, 255), 50); // White RGBW
  //delay();
  theaterChase(Glowstrip.Color(127, 127, 127), 50); // White

}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<Glowstrip.numPixels(); i++) {
    Glowstrip.setPixelColor(i, c);
    Glowstrip.show();
    delay(wait);
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<2; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 47; q++) {
      for (uint16_t i=0; i < Glowstrip.numPixels(); i=i+2) {
        Glowstrip.setPixelColor(i+q, 50, 10, 75);    //turn every third pixel on
      }
      Glowstrip.show();

      delay(wait);

      for (uint16_t i=0; i < Glowstrip.numPixels(); i=i+2) {
        Glowstrip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
