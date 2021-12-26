// include the library code:
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte cursor[8] = {
  0b00000,
  0b00100,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00000
};
String days[7] = {
  "Saturday",
  "Sunday",
  "Monday",
  "Tuesday",
  "Wednesday",
  "Thursday",
  "Friday"
};

int months[12] = {
  31,
  28,
  31,
  30,
  31,
  30,
  31,
  31,
  30,
  31,
  30,
  31
};

int secOnes = 0;
int secTens = 5;
int minOnes = 9;
int minTens = 5;
int hOnes = 1;
int hTens = 1;
int dayName = 6;
int dayNum = 31;
int monthIndex = 11;
int thisYear = 2021;
boolean date = false;
const int numRows = 2;
const int numCols = 16;
int button1 = 2;
int button2 = 3;
int button3 = 8;
int button4 = 9;
int buzzer = 10;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;
const unsigned long interval = 1000;
const unsigned long interval2 = 2000;
unsigned long previousTime = 0;
unsigned long previousTime2 = 0;
boolean morning = false;
boolean evening = true;

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  lcd.begin(numCols, numRows);
  lcd.createChar(7, cursor);
}

void loop() {
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2);
  buttonState3 = digitalRead(button3);
  buttonState4 = digitalRead(button4);
  unsigned long currentTime = millis();
  if (buttonState1 == HIGH) {
    minOnes = minOnes + 1;
    if (hOnes == 2 && hTens == 1 && minOnes == 0 && minTens == 0) {
      if (evening == true) {
        evening = false;
        morning = true;
        lcd.clear();
        dayName = dayName + 1;
        if (dayName == 7) dayName = 0;
      } else if (morning == true) {
        morning = false;
        evening = true;
      }
    }
    increaseTime(currentTime);
    delay(250);
  }
  if (buttonState2 == HIGH) {
    hOnes = hOnes + 1;
    if (hOnes == 2 && hTens == 1) {
      if (evening == true) {
        evening = false;
        morning = true;
        lcd.clear();
        dayName = dayName + 1;
        if (dayName == 7) dayName = 0;
      } else if (morning == true) {
        morning = false;
        evening = true;
      }
    }
    increaseTime(currentTime);
    delay(250);
  }
  if (buttonState3 == HIGH) {
    monthIndex = monthIndex + 1;
    if (monthIndex > 11) {
      monthIndex = 0;
    }
    increaseTime(currentTime);
    delay(250);
  }
  if (buttonState4 == HIGH) {
    dayNum = dayNum + 1;
    if (dayNum > months[monthIndex]) {
      dayNum = 1;
    }
    increaseTime(currentTime);
    delay(250);
  }
  if (currentTime - previousTime >= interval) {
    secOnes = secOnes + 1;
    increaseTime(currentTime);
    previousTime = currentTime;
  }
}

void increaseTime(unsigned long currentTime) {
  if (secOnes == 10) {
    secOnes = 0;
    secTens = secTens + 1;
  }
  if (secTens == 6) {
    secOnes = 0;
    secTens = 0;
    minOnes = minOnes + 1;
  }
  if (minOnes == 10) {
    minOnes = 0;
    minTens = minTens + 1;
  }
  if (minTens == 6) {
    minOnes = 0;
    minTens = 0;
    hOnes = hOnes + 1;
  }
  if (hOnes == 10) {
    hOnes = 0;
    hTens = hTens + 1;
  }
  if (hTens == 1 && hOnes == 2 && minOnes == 0 && minTens == 0 && secOnes == 0 && secTens == 0) {
    if (evening == true) {
      evening = false;
      morning = true;
      lcd.clear();
      dayName = dayName + 1;
      if (dayName == 7) {
        dayName = 0;
      }
      dayNum = dayNum + 1;
      if (dayNum > months[monthIndex]) {
        dayNum = 1;
        monthIndex = monthIndex + 1;
        if (monthIndex > 11) {
          monthIndex = 0;
          thisYear = thisYear + 1;
        }
      }
    } else if (morning == true) {
      morning = false;
      evening = true;
    }
  }
  if (hOnes == 3 && hTens == 1) {
    hOnes = 1;
    hTens = 0;
  }
  if (minOnes == 0 && minTens == 0 && secOnes == 0 && secTens == 0) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(100);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  }
  if (currentTime - previousTime2 >= interval2 || buttonState3 == HIGH || buttonState4 == HIGH) {
    lcd.clear();
    if (date || buttonState3 == HIGH || buttonState4 == HIGH) {
      lcd.setCursor(4, 1);
      lcd.print(dayNum);
      if (dayNum < 10) {
        lcd.print(" ");
      }
      lcd.print(" ");
      lcd.print(monthIndex + 1);
      if (monthIndex < 10) {
        lcd.print(" ");
      }
      lcd.print(" ");
      lcd.print(thisYear);
      date = false;
    } else {
      lcd.setCursor(4, 1);
      lcd.print(days[dayName]);
      date = true;
    }
    previousTime2 = currentTime;
  }
  lcd.setCursor(10, 0);
  lcd.print(secTens);
  lcd.setCursor(11, 0);
  lcd.print(secOnes);
  lcd.setCursor(8, 0);
  lcd.print(minOnes);
  lcd.setCursor(7, 0);
  lcd.print(minTens);
  lcd.setCursor(4, 0);
  lcd.print(hTens);
  lcd.setCursor(5, 0);
  lcd.print(hOnes);
  lcd.setCursor(13, 0);
  if (evening == true) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }
  lcd.setCursor(6, 0);
  lcd.write(7);
  lcd.setCursor(9, 0);
  lcd.write(7);
}
