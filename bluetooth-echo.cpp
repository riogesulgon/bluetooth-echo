#include <Arduino.h>
#include <Keyboard.h>
#include "macros.h"
#include "pitches.h"

char ctrlKey = KEY_LEFT_GUI; // OSX
char ctrlKeyWin = KEY_LEFT_CTRL; // Windows

String inputString = "";         // a String to hold incoming data
String modifier = "";
bool stringComplete = false;  // whether the string is complete
bool hasModifier = false;
bool startRx = true;
bool osx = false;
bool macroMode = false;
int macroSize = 0;
int button1 = 3;
int musicPin = 5;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  Keyboard.begin();
  inputString.reserve(200);
  macroSize = sizeof(macro_key) / sizeof(String);
  Serial.println((String) "Macro size" + macroSize);
  Serial1.println("Welcome!");
  pinMode(button1, INPUT);
  pinMode(musicPin, OUTPUT);
  playTone(minuet3_section1, sizeof(minuet3_section1) / sizeof(minuet3_section1[0]) / 2, 90);
}



void loop() {
  int buttonState = digitalRead(button1);
  if (buttonState == HIGH) {
    Serial.println("Button 1 pressed");
    Serial1.println("Ok!");
    if (osx) {
      playTone(minuet3_section3, sizeof(minuet3_section3) / sizeof(minuet3_section3[0]) / 2, 90);
    } else {
      playTone(minuet3_section2, sizeof(minuet3_section2) / sizeof(minuet3_section2[0]) / 2, 90);
    }
    osx = !osx;
  }
  while (Serial1.available() > 0){   
    char inChar = (char)Serial1.read();
    if (startRx && (inChar == '!' || inChar == '^' || inChar == '+' || inChar == '#' || inChar == '~')) {
      if (inChar == '~') {
        Serial.println("Macro mode");
        startRx = false;
        macroMode = true;
      } else {
        String output = "Modifier key: ";
        Serial.println(output + inChar);
        hasModifier = true;
        modifier += inChar;
      }
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
    Serial.println(output + modifier + inputString);
    Serial.println((String) "hasModifier=" + hasModifier);
    if (macroMode) {
      Serial.println("Handling macro=" + inputString);
      for (int count = 0; count < macroSize; count++) {
        if (inputString.indexOf(macro_key[count]) > -1) {
          Serial.println((String) "Matched=" + macro_key[count]);
          macro_val[count]();
        }
      }
    } else if (hasModifier) {
      if (modifier.indexOf('^') > -1) {
         Serial.println("Handling modifier CTRL");
         if (osx) {
          Keyboard.press(ctrlKey);
         } else {
          Keyboard.press(ctrlKeyWin);
         }
      }
      if (modifier.indexOf('!') > -1) {
         Serial.println("Handling modifier ALT");
         if (osx) {
          Keyboard.press(KEY_LEFT_ALT);
         } else {
          Keyboard.press(KEY_RIGHT_GUI); 
         }
      }
      if (modifier.indexOf('+') > -1) {
         Serial.println("Handling modifier SHIFT");
         Keyboard.press(KEY_LEFT_SHIFT);
      }
      Keyboard.press(inputString[0]);
      delay(100);
      Keyboard.releaseAll();
    } else {
      Keyboard.print(inputString);
    }
    stringComplete = false;
    inputString = "";
    startRx = true;
    hasModifier = false;
    modifier = "";
    macroMode = false;
 }
 delay(100);
}