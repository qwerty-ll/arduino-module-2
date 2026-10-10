// Занятие 16. Проект «Сейф 2.0»
// Клавиатура 4x4 (ряды 13, 12, 11, 10; колонки 7, 6, 5, 4), серво-замок (9), экран I2C, баззер (8)
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo lock;

char keys[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[4] = {13, 12, 11, 10};
byte colPins[4] = {7, 6, 5, 4};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4);

int buzzerPin = 8;
String secret = "1234";              // секретный код
String entered = "";                 // что набрал пользователь
int mistakes = 0;

void showPrompt() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter code:");
}

void setup() {
  lock.attach(9);
  lock.write(0);                     // 0 — закрыто
  lcd.init();
  lcd.backlight();
  showPrompt();
}

void loop() {
  char key = keypad.getKey();
  if (key == NO_KEY) {
    return;                          // ничего не нажали
  }
  tone(buzzerPin, 1200, 40);         // щелчок клавиши

  switch (key) {
    case '*':                        // стереть
      entered = "";
      showPrompt();
      break;
    case '#':                        // проверить
      if (entered == secret) {
        lcd.clear();
        lcd.print("ACCESS OK");
        tone(buzzerPin, 2000, 300);
        lock.write(90);              // открыли
        delay(3000);
        lock.write(0);               // закрыли обратно
        mistakes = 0;
      } else {
        mistakes = mistakes + 1;
        lcd.clear();
        lcd.print("WRONG! ");
        lcd.print(mistakes);
        lcd.print("/3");
        tone(buzzerPin, 300, 500);
        delay(1500);
        if (mistakes >= 3) {         // тревога
          lcd.clear();
          lcd.print("ALARM!");
          for (int i = 0; i < 5; i++) {
            tone(buzzerPin, 2500, 200);
            delay(400);
          }
          mistakes = 0;
        }
      }
      entered = "";
      showPrompt();
      break;
    default:                         // цифра или буква — добавляем
      entered += key;
      lcd.setCursor(0, 1);
      for (unsigned int i = 0; i < entered.length(); i++) {
        lcd.print('*');              // прячем код звёздочками
      }
  }
}
