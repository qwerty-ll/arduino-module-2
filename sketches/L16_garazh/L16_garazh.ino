// Занятие 16. Проект «Умный гараж»
// HC-SR04 (TRIG 7, ECHO 12), серво-шлагбаум (9), экран I2C (A4/A5), RGB (3, 5, 6), баззер (8)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo gate;

int trigPin = 7;
int echoPin = 12;
int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int buzzerPin = 8;
int gateOpen = 0;

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) {
    return 999;
  }
  return duration * 0.0343 / 2;
}

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void moveGate(int from, int to) {
  if (from < to) {
    for (int a = from; a <= to; a++) { gate.write(a); delay(10); }
  } else {
    for (int a = from; a >= to; a--) { gate.write(a); delay(10); }
  }
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  gate.attach(9);
  gate.write(0);
  lcd.init();
  lcd.backlight();
}

void loop() {
  float cm = measureDistance();

  if (cm < 30 && gateOpen == 0) {          // машина подъехала
    lcd.setCursor(0, 0);
    lcd.print("Welcome!        ");
    tone(buzzerPin, 1500, 150);
    moveGate(0, 90);
    gateOpen = 1;
  } else if (cm > 50 && gateOpen == 1) {   // машина уехала
    moveGate(90, 0);
    gateOpen = 0;
  }

  if (gateOpen == 1) {
    setColor(0, 255, 0);
  } else {
    setColor(255, 0, 0);
    lcd.setCursor(0, 0);
    lcd.print("Garage closed   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("Dist: ");
  lcd.print(cm, 0);
  lcd.print(" cm     ");

  if (gateOpen == 1 && cm < 10) {          // парковка: ближе нельзя!
    tone(buzzerPin, 2000, 100);
  }
  delay(200);
}
