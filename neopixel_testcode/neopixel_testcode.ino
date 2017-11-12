#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define LEDCOUNT 56

//code for no delay
uint32_t modetimer = 0;
uint32_t modetimerprev = 0;
int i = 0;
int j = 0;
int q = 0;
int cycle = 0;

//mode stuff
int mode = 1;

//button stuff
int button1Pin = 8;
int button2Pin = 9;
int button3Pin = 10;
int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;
int buttonpressed = 0;

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

  //button code
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  digitalWrite(button1Pin, LOW);
  digitalWrite(button2Pin, LOW);
  digitalWrite(button3Pin, LOW);
  Serial.begin(9600);

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
      theaterChase(Glowstrip.Color(64, 208, 224), 50);
      break;

    case 7:
      theaterChaseRainbow(20);
      break;
    default:
      mode = 1;
      break;
  }

  //button code
  if (digitalRead(button1Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      Serial.print("1Time: ");
      Serial.println(pressTime);
      buttonpressed = 1;
    }
    if (pressTime > 3000) {
      //
    }
  } else if (digitalRead(button2Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      Serial.print("2Time: ");
      Serial.println(pressTime);
      buttonpressed = 2;
    }
    if (pressTime > 3000) {
      //
    }
  } else if (digitalRead(button3Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      Serial.print("3Time: ");
      Serial.println(pressTime);
      buttonpressed = 3;
    }
    if (pressTime > 3000) {
      //
    }
  } else if (firsttime == 0) {
    firsttime = 1;
    if (buttonpressed == 1) {
      mode = mode + 1;
    } else if (buttonpressed == 2) {

    } else {
      if (mode != 1) {
        mode = mode - 1;
      } else {
        //loop back to last number in mode
        mode = 7;
      }
    }
    Serial.println("Time: 0 milleseconds; 0 seconds");
    buttonpressed = 0;
  }

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


