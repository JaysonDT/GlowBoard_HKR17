
int button1Pin = 8;
int button2Pin = 9;
int button3Pin = 10;

int firsttime = 1;
unsigned long startTime;
unsigned long pressTime;

void setup()
{
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  digitalWrite(button1Pin, LOW);
  digitalWrite(button2Pin, LOW);
  digitalWrite(button3Pin, LOW);

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
    if (pressTime >= 15) {
      Serial.print("1Time: ");
      Serial.println(pressTime);
    }
    if (pressTime > 3000) {
      //
    }
  } else if (digitalRead(button2Pin) == HIGH){
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      Serial.print("2Time: ");
      Serial.println(pressTime);
    }
    if (pressTime > 3000) {
      //
    }
  } else if (digitalRead(button3Pin) == HIGH){
    if (firsttime == 1) {
      startTime = millis();
      firsttime = 0;
    }
    pressTime = millis() - startTime;
    if (pressTime >= 15) {
      Serial.print("3Time: ");
      Serial.println(pressTime);
    }
    if (pressTime > 3000) {
      //
    }
  } else if (firsttime == 0) {
    firsttime = 1;
    Serial.println("Time: 0 milleseconds; 0 seconds");
    //
  }
}
