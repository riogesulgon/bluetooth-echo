#include "Keyboard.h"

char ctrlKey = KEY_LEFT_GUI; // OSX
char ctrlKeyWin = KEY_LEFT_CTRL; // Windows

String inputString = "";         // a String to hold incoming data
String modifier = "";
bool stringComplete = false;  // whether the string is complete
bool hasModifier = false;
bool startRx = true;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Keyboard.begin();
  inputString.reserve(200);
}

void loop() {
  while (Serial1.available() > 0){   
    char inChar = (char)Serial1.read();
    if (startRx && (inChar == '!' || inChar == '^' || inChar == '+' || inChar == '#')) {
      String output = "Modifier key: ");
      Serial.println(output + inChar);
      hasModifier = true;
      modifier += inChar;
    } else {
      inputString += inChar;
      startRx = false;
    }
    if (inChar == '\r') {
      stringComplete = true;
    }
  }
  if (stringComplete) {
    String output = String("Received: ");
    Serial.println(output + inputString);
    if (hasModifier) {
      if (modifier.indexOf('^' > 0)) {
         Serial.println("Handling modifier ^");
         Keyboard.press(ctrlKey);
         Keyboard.press(inputString[0]);
         delay(100);
         Keyboard.releaseAll();
      }
    } else {
      Keyboard.print(inputString);
    }
    stringComplete = false;
    inputString = "";
    startRx = true;
    hasModifier = false;
    modifier = "";
 }
 delay(100);
}
