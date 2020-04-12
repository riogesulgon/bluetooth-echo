#include "Keyboard.h"

// MACROS
String macro_key[] = {
  "ARDU_PORT"
};

void ardu_port() {
  Serial.print("Arduino port macro");
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('t');
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_UP_ARROW);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_UP_ARROW);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_UP_ARROW);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_UP_ARROW);
  delay(100);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RIGHT_ARROW);
  delay(100);
  Keyboard.releaseAll();
}
void (*macro_val[])() = {
  ardu_port
};
