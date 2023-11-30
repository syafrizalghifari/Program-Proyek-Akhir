#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define trigPin 7
#define echoPin 6
#define ledPin 9
#define redLedPin 8
#define buttonPin 10

Servo myservo;
int pos = 0;
long duration, distance;
int ledCount = 0;
bool isFull = false;

LiquidCrystal_I2C lcd(32, 16, 2);

void setup() {
  myservo.attach(4);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  lcd.setCursor(7, 0);
  lcd.print("      ");
  lcd.setCursor(7, 0);
  lcd.print(distance);

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (distance < 30 && distance > 0) {
    digitalWrite(ledPin, HIGH);
    ledCount++;
    if (ledCount == 10) {
      digitalWrite(redLedPin, HIGH);
      isFull = true;
    }
    if (!isFull) {
      myservo.write(90);
      delay(5000);
      myservo.write(0);
      delay(500);
    }
    digitalWrite(ledPin, LOW);
  }
  if (digitalRead(buttonPin) == LOW && isFull) {
    ledCount = 0;
    digitalWrite(redLedPin, LOW);
    isFull = false;
  }
  if (isFull) {
    lcd.setCursor(0, 1);
    lcd.print("PENUH");
    myservo.write(0);
  }

  delay(100);
}
