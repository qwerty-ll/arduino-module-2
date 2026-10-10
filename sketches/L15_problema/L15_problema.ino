// Занятие 15. ПРОБЛЕМА: пока идёт delay, кнопка "не слышит"
int ledPin = 10;
int buttonPin = 2;
int buzzerPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  digitalWrite(ledPin, HIGH);
  delay(1000);                       // плата "спит" 1 секунду
  digitalWrite(ledPin, LOW);
  delay(1000);                       // и ещё 1 секунду

  if (digitalRead(buttonPin) == LOW) {   // кнопку проверяем раз в 2 секунды!
    tone(buzzerPin, 1000, 200);
  }
}
