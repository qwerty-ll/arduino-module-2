// Занятие 12. Метеостанция: DHT22 + экран + RGB-индикатор
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(4, DHT22);                   // датчик на пине 4, модель DHT22

int redPin = 3;                      // RGB только на пинах с ~
int greenPin = 5;
int bluePin = 6;
const bool COMMON_ANODE = false;     // если цвета "наоборот" — поставьте true

void setColor(int r, int g, int b) {
  if (COMMON_ANODE) {
    r = 255 - r;
    g = 255 - g;
    b = 255 - b;
  }
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  lcd.init();
  lcd.backlight();
  dht.begin();
  Serial.begin(9600);
}

void loop() {
  float t = dht.readTemperature();   // температура, °C
  float h = dht.readHumidity();      // влажность, %

  if (isnan(t) || isnan(h)) {        // isnan = "это не число" -> датчик не ответил
    lcd.setCursor(0, 0);
    lcd.print("Sensor error!   ");
    delay(2000);
    return;                          // начинаем loop заново
  }

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t, 1);                   // 1 знак после запятой
  lcd.print(" C    ");
  lcd.setCursor(0, 1);
  lcd.print("Hum:  ");
  lcd.print(h, 0);
  lcd.print(" %    ");

  if (t < 18) {
    setColor(0, 0, 255);             // холодно — синий
  } else if (t <= 26) {
    setColor(0, 255, 0);             // комфортно — зелёный
  } else {
    setColor(255, 0, 0);             // жарко — красный
  }

  Serial.print(t);
  Serial.print(" C, ");
  Serial.print(h);
  Serial.println(" %");
  delay(2000);                       // DHT22 нельзя опрашивать чаще раза в 2 секунды
}
