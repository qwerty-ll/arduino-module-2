// Занятие 9. Светофор с кнопкой для пешехода
int redPin = 10;     // красный для машин
int yellowPin = 11;  // жёлтый
int greenPin = 12;   // зелёный
int buttonPin = 2;   // кнопка пешехода
int buzzerPin = 8;   // звуковой сигнал для пешехода

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);  // кнопка без внешнего резистора
  Serial.begin(9600);
  Serial.println("Светофор запущен");
}

void loop() {
  digitalWrite(greenPin, HIGH);        // машинам горит зелёный

  int button = digitalRead(buttonPin);
  if (button == LOW) {                 // LOW = кнопку нажали!
    Serial.println("Пешеход нажал кнопку");
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);     // жёлтый — 2 секунды
    delay(2000);
    digitalWrite(yellowPin, LOW);
    digitalWrite(redPin, HIGH);        // красный — пешеходы идут
    for (int i = 0; i < 10; i++) {     // 10 писков по 0,5 с = 5 секунд
      tone(buzzerPin, 1000, 100);
      delay(500);
    }
    digitalWrite(redPin, LOW);
  }
}
