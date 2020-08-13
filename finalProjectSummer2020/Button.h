#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
public:
  int pressed;
    int pinNum; // the number of the pushbutton pin
    char color; //'r' - red, 'g' - green,'b'- blue

    // Variables will change:
    int buttonState;             // the current reading from the input pin
    int lastButtonState;   // the previous reading from the input pin

    // the following variables are unsigned longs because the time, measured in
    // milliseconds, will quickly become a bigger number than can be stored in an int.
    unsigned long lastDebounceTime;  // the last time the output pin was toggled
    unsigned long debounceDelay;    // the debounce time; increase if the output flickers

  public:
    Button(int pin, char color);


};

#endif
