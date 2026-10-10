// Занятие 16. Проект «Умная теплица»
// DHT22 (пин 4), серво-форточка (9), экран I2C (A4/A5), RGB (3, 5, 6), баззер (8)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(4, DHT22);
Servo window;

int redPin = 3;
int greenPin = 5;
int bluePin = 6;
int buzzerPin = 8;
int windowOpen = 0;                  // 0 — форточка закрыта, 1 — открыта

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void moveWindow(int from, int to) {
  if (from < to) {
    for (int a = from; a <= to; a++) { window.write(a); delay(10); }
  } else {
    for (int a = from; a >= to; a--) { window.write(a); delay(10); }
  }
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
  window.attach(9);
  window.write(0);
}

void loop() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (isnan(t) || isnan(h)) {
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!   ");
    delay(2000);
    return;
  }

  // «Окно» 25..28 °C — чтобы форточка не дёргалась туда-сюда
  if (t > 28 && windowOpen == 0) {
    moveWindow(0, 90);
    windowOpen = 1;
  } else if (t < 25 && windowOpen == 1) {
    moveWindow(90, 0);
    windowOpen = 0;
  }

  if (t < 18) {
    setColor(0, 0, 255);
  } else if (t <= 28) {
    setColor(0, 255, 0);
  } else {
    setColor(255, 0, 0);
  }

  if (t > 35) {
    tone(buzzerPin, 2000, 300);      // тревога: перегрев!
  }

  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(t, 1);
  lcd.print(" H:");
  lcd.print(h, 0);
  lcd.print("%   ");
  lcd.setCursor(0, 1);
  if (windowOpen == 1) {
    lcd.print("Window: OPEN    ");
  } else {
    lcd.print("Window: CLOSED  ");
  }
  delay(2000);
}
