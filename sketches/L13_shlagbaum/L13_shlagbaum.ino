// Занятие 13. Шлагбаум по кнопке
#include <Servo.h>

Servo gate;
int buttonPin = 2;
int buzzerPin = 8;
int gateOpen = 0;                    // 0 — закрыт, 1 — открыт (переменная состояния)

void moveGate(int from, int to) {    // плавное движение
  if (from < to) {
    for (int a = from; a <= to; a++) {
      gate.write(a);
      delay(15);
    }
  } else {
    for (int a = from; a >= to; a--) {
      gate.write(a);
      delay(15);
    }
  }
}

void setup() {
  gate.attach(9);
  gate.write(0);                     // стартуем с закрытого шлагбаума
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    tone(buzzerPin, 1500, 100);      // короткий "бип"
    if (gateOpen == 0) {
      moveGate(0, 90);
      gateOpen = 1;
    } else {
      moveGate(90, 0);
      gateOpen = 0;
    }
    delay(300);                      // защита от дребезга
  }
}
