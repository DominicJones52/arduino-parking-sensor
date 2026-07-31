// Version 2: Parking sensor with LCD distance zones
// Displays ultrasonic distance readings and Safe/Caution/Warning/Stop zones on the LCD

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int trigPin = 9;
int echoPin = 10;
float distance = 0.00;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {

  lcd.clear();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  unsigned long duration = pulseIn (echoPin, HIGH, 30000);

  if (duration == 0) {
  //Serial.println("No object found");
  lcd.setCursor(0, 1);
  lcd.print("No object found");
  delay(1000);
  return;
  
}

  distance = duration * 0.0343 / 2;

  if (distance >= 260) {
    lcd.setCursor(0, 1);
    lcd.print("Safe!");
  }
  else if (distance >= 143 ) {
    lcd.setCursor(0, 1);
    lcd.print("Caution!!");
  }
  else if (distance >= 50 ) {
    lcd.setCursor(0, 1);
    lcd.print("Warning!!!");
  }
  else {
    lcd.setCursor(0, 1);
    lcd.print("STOP!!!!");
  }
 
  lcd.setCursor(0, 0);
  lcd.print(distance);
  lcd.print(" cm");

  //Serial.print(distance);
  //Serial.println(" cm");

  delay(1000);

  

  

}
