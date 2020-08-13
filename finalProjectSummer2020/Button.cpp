#include "Button.h" // include the declaration for this class
#include "Arduino.h"
//<<constructor>> setup the switch, make pin an INPUT
Button::Button(int pin, char colorID) {

  buttonState;             // the current reading from the input pin
  lastButtonState = 0;   // the previous reading from the input pin

  pinMode(pin, INPUT); //make that pin an INPUT
  pinNum = pin;
  color = colorID;
}
