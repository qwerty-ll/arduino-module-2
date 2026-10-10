// Занятие 10. SOS через собственные функции
int ledPin = 10;

void dot() {                 // точка
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}

void dash() {                // тире
  digitalWrite(ledPin, HIGH);
  delay(600);
  digitalWrite(ledPin, LOW);
  delay(200);
}

void letterS() { dot();  dot();  dot();  }
void letterO() { dash(); dash(); dash(); }

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  letterS();
  letterO();
  letterS();
  delay(2000);
}
