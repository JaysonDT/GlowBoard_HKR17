#include <Wire.h>
#include "MMA7660.h"

MMA7660 accelemeter;

//buzzer code
#define enablebuzzer true
#define buzpin 2
int buzzermode = false;
int soundalarm = false;
int accel_sensitivity = 20;
int8_t x;
int8_t y;
int8_t z;
float ax, ay, az;
int oldx = 0;
int oldy = 0;
int oldz = 0;


// init stuff from full code
//code for no delay
uint32_t modetimer = 0;
uint32_t modetimerprev = 0;

//button stuff
int button1Pin = 8;
int button2Pin = 9;
int button3Pin = 10;
int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;
int buttonpressed = 0;


void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  digitalWrite(button1Pin, LOW);
  digitalWrite(button2Pin, LOW);
  digitalWrite(button3Pin, LOW);

  accelemeter.init();
  pinMode(buzpin, OUTPUT);
  digitalWrite(buzpin, LOW);

  Serial.begin(9600);
}
void loop()
{
  if (digitalRead(button1Pin) == HIGH) {
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime > 3000) {
      //enable buzzermode
      buttonpressed = 1;

    }
  } else if (firsttime == 0) {
    if (buttonpressed == 1) {
      if (buzzermode == false) {
        buzzermode = true;
        Serial.print("Buzzermode true");
      } else {
        //buzzermode = false;
      }
      Serial.print("Buttonpressed");
    }
    buttonpressed = 0;
  }

  if (enablebuzzer == true && buzzermode == true) {

    //colorWipe(Glowstrip.Color(0, 0, 0), 5);
    delay(100);
    //digitalWrite(buzpin, HIGH);
    Serial.print("testALARM");
    delay(5000);
    //digitalWrite(buzpin, LOW);
    Serial.print("testALARM");


    accelemeter.getXYZ(&x, &y, &z);
    int oldx = x;
    int oldy = y;
    int oldz = z;
    while (buzzermode == true) {
      accelemeter.getXYZ(&x, &y, &z);
      //if the board is moved too quickly it sounds alarm
        if ( (x > oldx + accel_sensitivity || x < oldx - accel_sensitivity) ||
             (y > oldy + accel_sensitivity || y < oldy - accel_sensitivity) ||
             (z > oldz + accel_sensitivity || z < oldz - accel_sensitivity)  ) {
          soundalarm = true;
        }
        int oldx = x;
        int oldy = y;
        int oldz = z;
      
      if (soundalarm == true) {
        //digitalWrite(buzpin, HIGH);
        Serial.print("ALARM");
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
          buzzermode = false;
          soundalarm = false;
        }
      }
    }
  }
  /*
    Serial.print("\t");
    Serial.print(x);
    Serial.print("\t");
    Serial.print(y);
    Serial.print("\t");
    Serial.println(z);
  */
}


