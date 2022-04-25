#ifdef WIO_TERMINAL

#include <samd.h>

void ioInitPin () {
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(WIO_5S_UP, INPUT_PULLUP);
  pinMode(WIO_5S_DOWN, INPUT_PULLUP);
  pinMode(WIO_5S_LEFT, INPUT_PULLUP);
  pinMode(WIO_5S_RIGHT, INPUT_PULLUP);
  pinMode(WIO_5S_PRESS, INPUT_PULLUP);

  pinMode(PIN_LED, OUTPUT);
  pinMode(WIO_BUZZER, OUTPUT);
}

void wioLed (bool flg) {
  if (flg) {
    digitalWrite(PIN_LED, HIGH);
  } else {
    digitalWrite(PIN_LED, LOW);
  }
}

void wioBeep (int ms) {
  if (ms == 0) {
    analogWrite(WIO_BUZZER, 0);
  } else
  if (ms == 1) {
    analogWrite(WIO_BUZZER, 128);
  } else {
    analogWrite(WIO_BUZZER, 128);
    delay(ms);
    analogWrite(WIO_BUZZER, 0);
  }
}

void wioBackLight (bool flg) {
  if (flg) {
    digitalWrite(LCD_BACKLIGHT, HIGH);
  } else {
    digitalWrite(LCD_BACKLIGHT, LOW);
  }
}

#endif
