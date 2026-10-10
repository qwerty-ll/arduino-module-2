// Занятие 10. Электронный игральный кубик
// Сегменты a, b, c, d, e, f, g -> пины 4, 5, 6, 7, 8, 9, 10
int segPins[7] = {4, 5, 6, 7, 8, 9, 10};
int buttonPin = 2;

// Общий катод: ON = HIGH. Если цифры горят "наоборот" (общий анод) — поменяйте местами.
const int ON = HIGH;
const int OFF = LOW;

// Таблица цифр: 1 = сегмент горит. Порядок: a, b, c, d, e, f, g
int digits[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},  // 0
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1},  // 4
  {1, 0, 1, 1, 0, 1, 1},  // 5
  {1, 0, 1, 1, 1, 1, 1},  // 6
  {1, 1, 1, 0, 0, 0, 0},  // 7
  {1, 1, 1, 1, 1, 1, 1},  // 8
  {1, 1, 1, 1, 0, 1, 1}   // 9
};

void showDigit(int n) {              // функция с параметром
  for (int s = 0; s < 7; s++) {
    if (digits[n][s] == 1) {
      digitalWrite(segPins[s], ON);
    } else {
      digitalWrite(segPins[s], OFF);
    }
  }
}

int rollDice() {                     // функция, которая ВОЗВРАЩАЕТ число
  return random(1, 7);               // от 1 до 6 (7 не входит!)
}

void setup() {
  for (int s = 0; s < 7; s++) {
    pinMode(segPins[s], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
  randomSeed(analogRead(A0));        // "перемешиваем" случайные числа
  showDigit(0);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    for (int i = 0; i < 10; i++) {   // анимация: кубик катится
      showDigit(rollDice());
      delay(80);
    }
    showDigit(rollDice());           // итоговый бросок
    delay(300);                      // защита от дребезга
  }
}
