// MACROS
String macro_key[] = {
  "ARDU_PORT", 
  "ARDU_MONITOR"
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

void ardu_monitor() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press('m');
  delay(100);
  Keyboard.releaseAll();
}

void (*macro_val[])() = {
  ardu_port,
  ardu_monitor
};
