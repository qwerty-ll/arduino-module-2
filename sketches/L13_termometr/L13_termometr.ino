// Занятие 13 (усложнение). Стрелочный термометр: DHT22 -> стрелка-серва
#include <Servo.h>
#include <DHT.h>

Servo arrow;
DHT dht(4, DHT22);

void setup() {
  arrow.attach(9);
  dht.begin();
}

void loop() {
  float t = dht.readTemperature();
  if (!isnan(t)) {
    int angle = map((int)t, -10, 40, 180, 0);  // -10 °C слева, +40 °C справа
    angle = constrain(angle, 0, 180);           // не выходим за пределы 0..180
    arrow.write(angle);
  }
  delay(2000);
}
