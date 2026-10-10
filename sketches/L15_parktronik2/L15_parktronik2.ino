// Занятие 15 (усложнение). Парктроник 2.0 без delay + кнопка "тишина"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int trigPin = 7;
int echoPin = 12;
int buzzerPin = 8;
int buttonPin = 2;

unsigned long lastMeasure = 0;       // таймер замеров
unsigned long lastBeep = 0;          // таймер писка
unsigned long lastScreen = 0;        // таймер экрана
float cm = 999;
bool mute = false;                   // режим тишины
int lastButton = HIGH;

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

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Parktronik 2.0");
}

void loop() {
  unsigned long now = millis();

  // 1. Замер расстояния — каждые 100 мс
  if (now - lastMeasure >= 100) {
    lastMeasure = now;
    cm = measureDistance();
  }

  // 2. Кнопка "тишина" — проверяем постоянно
  int button = digitalRead(buttonPin);
  if (button == LOW && lastButton == HIGH) {
    mute = !mute;
  }
  lastButton = button;

  // 3. Писк — по своему таймеру
  if (mute || cm >= 100) {
    noTone(buzzerPin);
  } else if (cm < 10) {
    tone(buzzerPin, 2000);
  } else {
    unsigned long pause = map((int)cm, 10, 100, 100, 600);
    if (now - lastBeep >= pause) {
      lastBeep = now;
      tone(buzzerPin, 1000, 50);
    }
  }

  // 4. Экран — каждые 300 мс
  if (now - lastScreen >= 300) {
    lastScreen = now;
    lcd.setCursor(0, 1);
    lcd.print(cm, 1);
    lcd.print(" cm ");
    if (mute) {
      lcd.print("MUTE    ");
    } else {
      lcd.print("        ");
    }
  }
}
