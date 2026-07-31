// Final Version: Arduino Parking Sensor
// Uses an ultrasonic sensor to measure distance and display Safe/Caution/Warning/STOP zones.
// Includes LCD output, LED indicators, buzzer alerts, non-blocking STOP flashing with millis(),
// and missed-reading filtering to reduce false "No object found" messages.

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int trigPin = 9;
int echoPin = 10;
float distance = 0.00;
int greenPin = 8;
int yellowPin = 7;
int redPin = 6;
int buzzerPin = 13;

int missedReadings = 0;


unsigned long lastDistanceTime = 0;
unsigned long lastBlinkTime = 0;

int distanceInterval = 300;
int blinkInterval = 200;

bool redLedState = LOW;
String currentZone = "Safe";
bool objectDetected = true;




void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

}

void loop() {



 
  unsigned long currentTime = millis();

  if (currentTime - lastDistanceTime >= distanceInterval) {

    lastDistanceTime = currentTime;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    
    unsigned long duration = pulseIn (echoPin, HIGH, 30000);

    

  if (duration == 0) {

  ++missedReadings;

  if(missedReadings >= 6) {
  objectDetected = false;
  currentZone = "None";
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No object found");
  }
  
} else {

  missedReadings = 0;

  objectDetected = true;

  distance = duration * 0.0343 / 2;


  if (distance >= 260) {

    currentZone = "Safe";
  }
  else if (distance >= 143 ) {
    
    currentZone = "Caution";
  }
  else if (distance >= 50 ) {

    currentZone = "Warning";
    
  }
  else {

    currentZone = "Stop";
    
    }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(distance);
  lcd.print(" cm");

  lcd.setCursor(0, 1);
  lcd.print(currentZone);
  }
  }

  if (currentZone == "None") {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  noTone(buzzerPin);
}

else if (currentZone == "Safe") {
  digitalWrite(greenPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  noTone(buzzerPin);
}

else if (currentZone == "Caution") {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(redPin, LOW);
  tone(buzzerPin, 500, 100);
}

else if (currentZone == "Warning") {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  tone(buzzerPin, 750, 150);
}

else if (currentZone == "Stop") {
  digitalWrite(greenPin, LOW);
  digitalWrite(yellowPin, LOW);

  if (currentTime - lastBlinkTime >= blinkInterval) {
    lastBlinkTime = currentTime;
    redLedState = !redLedState;
    digitalWrite(redPin, redLedState);

    if (redLedState == HIGH) {
      tone(buzzerPin, 1000, 100);
    } else {
      noTone(buzzerPin);
    }
  }
}
 
  



  

  

}
