// Занятие 14. Парктроник: HC-SR04 + баззер + экран
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int trigPin = 7;                     // "рот" датчика — кричит
int echoPin = 12;                    // "ухо" датчика — слушает эхо
int buzzerPin = 8;

float measureDistance() {            // функция ВОЗВРАЩАЕТ расстояние в см
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);       // "крик" длиной 10 микросекунд
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000);  // ждём эхо не дольше 30 мс
  if (duration == 0) {
    return 999;                      // эхо не вернулось — препятствие очень далеко
  }
  return duration * 0.0343 / 2;      // скорость звука 0,0343 см/мкс; путь туда и обратно
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  Serial.begin(9600);
}

void loop() {
  float cm = measureDistance();
  Serial.println(cm);

  lcd.setCursor(0, 1);
  lcd.print(cm, 1);
  lcd.print(" cm      ");

  if (cm < 10) {
    tone(buzzerPin, 2000);           // СТОП! сплошной сигнал
    delay(100);
  } else if (cm < 100) {
    tone(buzzerPin, 1000, 50);       // короткий писк
    delay(map((int)cm, 10, 100, 100, 600));  // ближе -> пауза короче
  } else {
    noTone(buzzerPin);               // далеко — тишина
    delay(200);
  }
}
