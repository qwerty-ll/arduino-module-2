// Занятие 15. РЕШЕНИЕ: мигаем по часам millis(), кнопка работает мгновенно
int ledPin = 10;
int buttonPin = 2;
int buzzerPin = 8;

unsigned long lastBlink = 0;         // когда последний раз переключали светодиод
bool ledOn = false;                  // bool: только true (да) или false (нет)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Задача 1: мигать раз в секунду
  if (millis() - lastBlink >= 1000) {   // прошла секунда?
    lastBlink = millis();               // запоминаем время
    ledOn = !ledOn;                     // ! переворачивает: true <-> false
    digitalWrite(ledPin, ledOn);
  }

  // Задача 2: пищать, пока нажата кнопка
  if (digitalRead(buttonPin) == LOW) {
    tone(buzzerPin, 1000);
  } else {
    noTone(buzzerPin);
  }
}
