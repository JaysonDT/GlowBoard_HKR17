#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define LEDCOUNT 54

//potentiometer analog
#define enablepot true
#define potpin 0
int potval = 0;
int oldpotval = 0;
int percentval = 0;

//buzzer code
#include <Wire.h>
#include "MMA7660.h"
MMA7660 accelemeter;
#define enablebuzzer true
#define buzpin 2
int buzzermode = false;
int soundalarm = false;
float accel_sensitivity = 0.5;
int8_t x;
int8_t y;
int8_t z;
float ax, ay, az;

float oldx = 0;
float oldy = 0;
float oldz = 0;

float prevx = 0;
float prevy = 0;
float prevz = 0;

//code for no delay
uint32_t modetimer = 0;
uint32_t modetimerprev = 0;
int i = 0;
int j = 0;
int q = 0;
int cycle = 0;

//mode stuff
int mode = 1;
int submode = 0;

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

  oldpotval = analogRead(potpin);
  //buzzer
  accelemeter.init();
  pinMode(buzpin, OUTPUT);
  digitalWrite(buzpin, LOW);

  Glowstrip.begin();
  Glowstrip.show(); // Initialize all pixels to 'off'
}

void loop() {

  switch (mode) {
    case 1: colorWipe(Glowstrip.Color(150, 150, 150), 20);
      /*
        //multiple functions 1 mode
        modetimer = millis();
        //if (modetimer - modetimerprev >= 100) {
        if (submode == 0) {
          colorWipe(Glowstrip.Color(255, 0, 0), 20);
        } else if (submode == 1) {
          colorWipe(Glowstrip.Color(0, 0, 255), 20);
        } else if (submode == 2) {
          colorWipe(Glowstrip.Color(0, 255, 0), 20);
        } else if (submode == 3) {
          colorWipe(Glowstrip.Color(255, 255, 255), 20);
        }
        if (modetimer - modetimerprev >= 2000) {

          if (submode > 3) {
            submode = 0;
          } else {
            submode = submode + 1;
          }
          modetimerprev = modetimer;
        }
        //}
      */
      break;
    case 2:
      colorWipe(Glowstrip.Color(255, 0, 0), 20);
      break;
    case 3:
      colorWipe(Glowstrip.Color(0, 0, 255), 20);
      break;
    case 4:
      colorWipe(Glowstrip.Color(0, 255, 0), 20);
      break;
    case 5:
      rainbowCycle(12);
      break;
    case 6:
      coplights(225);
      break;
    case 7:
      rainbowCycle(20);
      break;
    case 8:
      usaCycle(10);
      break;
    case 9:
      theaterChase(Glowstrip.Color(64, 208, 224), 100, 7);
      break;
    case 10:
      theaterChase(Glowstrip.Color(0, 208, 224), 100, 3);
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
      //buttonpressed = 1;
    }
    if (pressTime > 3000) {
      //enable buzzermode
      buttonpressed = 1;
    }
  } else if (digitalRead(button2Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      buttonpressed = 2;
    }
  } else if (digitalRead(button3Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      buttonpressed = 3;
    }
  } else if (firsttime == 0) {
    firsttime = 1;
    if (buttonpressed == 1) {
      buzzermode = true;
    } else if (buttonpressed == 2) {
      mode = mode + 1;
      
      i = 0;
      j = 0;
      q = 0;
    } else {
      if (mode != 1) {
        mode = mode - 1;
      } else {
        //loop back to last number in mode
        mode = 10;
      }
      
      i = 0;
      j = 0;
      q = 0;
      buttonpressed = 0;
    }
    buttonpressed = 0;
  }

  // potentiometer brightnesscode
  if (enablepot == true) {
    potval = analogRead(potpin);
    Serial.print("pot: ");
    Serial.println(potval);
    if (potval >= oldpotval + 20 || potval <= oldpotval - 20) {
      modetimer = millis();
      modetimerprev = millis();
      while (modetimer - modetimerprev < 300 ) {
        potval = analogRead(potpin);
        if (potval >= oldpotval + 10 || potval <= oldpotval - 10) {
          oldpotval = analogRead(potpin);
        }

        Serial.print("potval: ");
        Serial.println(potval);
        percentval = map(potval, 1, 1024, 1, 101);
        //percentval = potval / 10;
        percentWipe(20, percentval);
        if (potval != oldpotval) {
          modetimerprev = modetimer;
        }
        Glowstrip.setBrightness(map(potval, 1, 1024, 15, 256));
        modetimer = millis();
        oldpotval = analogRead(potpin);
      }

      Glowstrip.setBrightness(map(potval, 1, 1024, 15, 255));
      i = 0;
      j = 0;
      q = 0;
    }
  }
  if (enablebuzzer == true && buzzermode == true) {
    for (int i = 0; i < 200; i++) {
      colorWipe(Glowstrip.Color(0, 0, 0), 0);
    }
    delay(100);
    digitalWrite(buzpin, HIGH);
    delay(500);
    digitalWrite(buzpin, LOW);
    delay(5000);
    digitalWrite(buzpin, HIGH);
    delay(200);
    digitalWrite(buzpin, LOW);


    accelemeter.getAcceleration(&ax, &ay, &az);
    oldx = ax;
    oldy = ay;
    oldz = az;
    while (buzzermode == true) {
      accelemeter.getAcceleration(&ax, &ay, &az);
      Serial.print(oldx);
      Serial.print(" g");
      Serial.print(oldy);
      Serial.print(" g");
      Serial.print(oldz);
      Serial.print(" g");
      Serial.print(ax);
      Serial.print(" g");
      Serial.print(ay);
      Serial.print(" g");
      Serial.print(az);
      Serial.println(" g");
      //if the board is moved too quickly it sounds alarm
      if ( (ax + prevx) / 2 > oldx + accel_sensitivity || (ax + prevx) / 2 < oldx - accel_sensitivity) {
        soundalarm = true;
      }
      if (((ay + prevy) / 2 > oldy + accel_sensitivity || (ay + prevy) / 2 < oldy - accel_sensitivity) ) {
        soundalarm = true;
      }
      if (((az + prevz) / 2 > oldz + accel_sensitivity || (az + prevz) / 2 < oldz - accel_sensitivity)  ) {
        soundalarm = true;
      }
      if (soundalarm == true) {
        digitalWrite(buzpin, HIGH);
        //Serial.print("ALARM");
      } else {
        digitalWrite(buzpin, LOW);
      }
      //check button
      if (digitalRead(button1Pin) == HIGH) {
        if (firsttime == 1) {
          startTime = millis();
          firsttime = 0;
        }
        pressTime = millis() - startTime;
        if (pressTime >= 15) {
          buttonpressed = 0;
        }
        if (pressTime > 2000) {

          Serial.print("Buzzermode false");
          digitalWrite(buzpin, LOW);
          buzzermode = false;
          soundalarm = false;
          break;
        }
      }
      prevx = ax;
      prevy = ay;
      prevz = az;
    }

  }
}

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


