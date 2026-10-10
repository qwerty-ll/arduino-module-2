// Занятие 11. Табло: счётчик нажатий + шкала от потенциометра
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // адрес 0x27, 16 символов, 2 строки

int buttonPin = 2;
int potPin = A0;
int count = 0;
int lastButton = HIGH;               // память: какой кнопка была в прошлый раз

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  lcd.init();                        // будим экран
  lcd.backlight();                   // включаем подсветку
  lcd.setCursor(0, 0);
  lcd.print("Hello, robot!");
  delay(1000);
  lcd.clear();
}

void loop() {
  int button = digitalRead(buttonPin);
  if (button == LOW && lastButton == HIGH) {  // поймали МОМЕНТ нажатия
    count = count + 1;
  }
  lastButton = button;

  int pot = analogRead(potPin);
  int bar = map(pot, 0, 1023, 0, 16);        // сколько клеток закрасить

  lcd.setCursor(0, 0);
  lcd.print("Count: ");
  lcd.print(count);

  lcd.setCursor(0, 1);
  for (int i = 0; i < 16; i++) {
    if (i < bar) {
      lcd.print("#");
    } else {
      lcd.print(" ");
    }
  }
  delay(50);
}
