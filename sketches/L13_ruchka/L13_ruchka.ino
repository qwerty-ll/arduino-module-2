// Занятие 13. Сервопривод слушается ручку
#include <Servo.h>

Servo myServo;

void setup() {
  myServo.attach(9);                 // сигнальный провод сервы — пин 9
}

void loop() {
  int pot = analogRead(A0);              // 0..1023
  int angle = map(pot, 0, 1023, 0, 180); // 0..180 градусов
  myServo.write(angle);
  delay(15);                             // даём серве доехать
}
