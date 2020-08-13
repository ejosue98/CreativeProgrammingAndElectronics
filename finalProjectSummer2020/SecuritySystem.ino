

// To configure Arduino as controller device for an OpenMV Cam using the RPC library.
#include <openmvrpc.h>
#include "pitches.h"

// Define a scratch buffer for holding messages
uint8_t scratch_buffer[256 + 4];


// Using Software Serial to Establish UART Communication
// OpenMV Cam Ground Pin   ----> Arduino Ground
// OpenMV Cam UART3_TX(P4) ----> Arduino Uno UART_RX(2)
// OpenMV Cam UART3_RX(P5) ----> Arduino Uno UART_TX(3)
openmv::rpc_software_serial_uart_master interface(scratch_buffer, sizeof(scratch_buffer), 2, 3, 19200);

//Load custom library for Button attributes & library for LCD
#include <Button.h>
#include <LiquidCrystal.h>



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = A2, en = A3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


//Ultrasonic Sensor Initialization
const int trig = A5;
const int echo = A4;
float distance;



//////////////////////////////////////////////////////////////
// Variables Responding Depending on States
//////////////////////////////////////////////////////////////

//redLED -- Pin A1
//greenLEd -- Pin A0
// buzzer -- Pin 13

int buzz = 13; // Buzzer Pin


boolean greenFlash = false;
String result;//Camera Findings
boolean triggered = false; //variable to state if person has been previously detected
boolean lockDisplay = false;
int state = 0; //initial state should be standby mode


/* Different States dedicated for each stage in Security System
  0 - Stand By
  1 - Combination Mode
  2 - Alarm Triggered
  3 - Access Granted
*/

boolean unlocked = false; //access begins as locked
int urgency; //speed of led flashes
int ledPin; //pin of LED to be used
boolean outcome = false; //outcome from comparison between user input and correct combination
unsigned long time_now = 0; //used for wait function


//////////////////////////////////////////////////////////////
// Button Variables
//////////////////////////////////////////////////////////////
int buttonState;             // the current reading from the input pin
int  lastButtonState = LOW;   // the previous reading from the input pin
int pressCount = 0; //number of times buttons have been pressed
int tries = 0; //number of attempts user has tried to enter password
char newCombination [4] = {}; //new user input array to be copied
boolean serialActive = false;

Button redButton(8, 'r'); //initialize an instance of the class
Button greenButton(9, 'g');
Button blueButton(10, 'b');
Button yellowButton(11, 'y');

Button buttons [4] = {redButton, greenButton, blueButton, yellowButton }; //array of buttons for quicker access
char userCombination [4] = {}; //will store user's button combination



//////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////
void setup() {
  lcd.begin(16, 2); //begin lCD display
  pinMode(trig, OUTPUT); //Declare Ultrasonic Sensor


}
void loop() {
  checkReset(); //check if reset button has been pressed

  if (state == 0) {
    standBy (); //standBy mode
  } else {
    edgeDetection(); //check for button presses
  }
}


//////////////////////////////////////////////////////////////
// Call Backs
//////////////////////////////////////////////////////////////


/* this method is principle of button security functionality
  If buttons are clicked, the method keeps track of user inputs and dictates when alarm is to be (dis)activated */

// ----Edge Detection: processing of determining when a button changes state from off to on----------//
void checkReset() {
  // Check if Reset Button hasn't been Pressed
  buttons[3].buttonState = digitalRead(11); //read from pin 11
  if (buttons[3].buttonState != buttons[3].lastButtonState) {

    //if pressed, re-initiate all variables
    if (buttons[3].buttonState == HIGH) {
      lcd.clear();
      lcd.setCursor(0, 1);
      //Copy Blank LCD Display
      memcpy(userCombination, newCombination, sizeof(newCombination));
      state = 0;
      tries = 0;
      pressCount = 0;
      lockDisplay = false;
      serialActive = false;
      triggered = false;
      unlocked = false;
      outcome = false;
      greenFlash = false;
      standBy();
    }
    // save the current state as the last state, for next time through the loop
    buttons[3].lastButtonState = buttons[3].buttonState;
  }
}

void edgeDetection() {
  for ( int i = 8; i <= 10; i++) { //for buttons located in pins 8-10

    //buttons[i-8] is the current Button being used from buttons array
    buttons[i - 8].buttonState = digitalRead(i); //read from pin i

    /*this is the main edge detection portion */

    // compare the buttonState to its previous state
    if (buttons[i - 8].buttonState != buttons[i - 8].lastButtonState) {

      // if the state has changed, increment the press count and flash LED
      if (buttons[i - 8].buttonState == HIGH) {
        tone(13, NOTE_B0, 50); //play tone to indicate press
        userCombination[pressCount] = buttons[i - 8].color; //add clicked button input to combination

        //Flash LED light to indicate Button Press
        analogWrite(A1, 255);
        // wait to see the dimming effect
        time_now = millis();
        wait(time_now, 50.0);
        analogWrite(A1, 0);
        pressCount++;
      }

      //the combination is made up of 3 characters, once 3 buttons are clicked, verify data
      if (pressCount == 3) {
        outcome = compareKeys(userCombination); //comparison method is called
        pressCount = 0; //reset the button counter to 0

        lcd.clear();
        lcd.setCursor(0, 1);

        tries++;
        lcd.print("Attempts:" + String(" ") +  String(tries)); //display number of attempts as user types

        //Copy Blank LCD Display
        memcpy(userCombination, newCombination, sizeof(newCombination));
      }

      if (outcome == true) { //user input matches Correct Combination
        unlocked = true;
        state = 3; //enter granted access stage
      }
      if (tries == 3 && unlocked == false ) { //tries are up and correct combination wasn't entered
        state = 2; //enter alaram triggered stage
      }
      // Delay a little bit to avoid bouncing
      time_now = millis();
      wait(time_now, 30.0);
    }
    // save the current state as the last state, for next time through the loop
    buttons[i - 8].lastButtonState = buttons[i - 8].buttonState;
  }
  if (state == 2 || state == 3) { //check if alarm should be triggered
    fadeUrgency(state);
  }
}

//-----------this method is used as a timer without delay()
void wait(long currentTime, float timeToWait) {
  while (abs(millis() - currentTime) < timeToWait) {
  }
}


//--------------------method that displays blink intensity based on urgency
void fadeUrgency(int state) {   //A1 is red LED, A0 is green LED

  //Look at the state to determine scenario//
  if (state == 2)
  { //wrong combination
    wrongCombination();
  }
  else if (state == 3)
  { //access granted
    accessGranted();
    if (greenFlash == false) { //play unlocked tone only once
      
      time_now = millis();
      wait(time_now, 800);
      
      tone(13, NOTE_B0, 1000);
      greenFlash = true;
    }
    // fade proper Pin from min to max in increments of urgency points:
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += urgency) {

      // sets the value (range from 0 to 255):
      analogWrite(ledPin, 255);
      // wait to see the dimming effect

      time_now = millis();
      wait(time_now, 30.0);
    }

    // fade out from max to min in increments of urgency points:
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= urgency) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait to see the dimming effect
      time_now = millis();
      wait(time_now, 30.0);
    }
  }




}


//-------------------inital state (0)
void standBy () {
  if (serialActive == false) {
    serialActive = true;
    Serial.begin(115200);
  }

  if (lockDisplay == false) {
    lockDisplay = true; //show that system is locked
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(" Access Locked");
  }

  digitalWrite(trig, HIGH);
  time_now = millis();
  wait(time_now, 0.01);
  digitalWrite(trig, LOW);
  float timeToEcho = pulseIn(echo, HIGH);
  distance = timeToEcho / 148.0; //inches

  exe_person_detection();

  if (triggered == false && result == "person" && distance <= 30) {
    triggered = true;
    Serial.end();
    serialActive = false;


    lcd.clear();
    lcd.setCursor(0, 1);
    //Copy Blank LCD Display
    memcpy(userCombination, newCombination, sizeof(newCombination));

    if (tries == 0) {
      lcd.setCursor(0, 0);
      lcd.print("  Enter 3 Color");
      lcd.setCursor(0, 1);
      lcd.print("   Combination  ");
      state = 1;
    }

  }
  else if (triggered == false && result == "person" && distance > 30 && distance <= 200) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    Presence");
    lcd.setCursor(0, 1);
    lcd.print("    Detected");
    //Copy Blank LCD Display
    memcpy(userCombination, newCombination, sizeof(newCombination));

  }
}



//-------------------state to be called if user doesn't enter proper combination
void wrongCombination () {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Alarm Activated");
  urgency = 20; //quick flashes
  ledPin = A1; //red LED
  Serial.end();
  Serial.begin(1200);
  Serial.write(2);
  serialActive = false;
  Serial.end();

  alarm();
}

//-------------------state to be called if user enters proper combination
void accessGranted() {

  unlocked = true;
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print(" Access Granted");
  urgency = 10; //normal flashes
  ledPin = A0; //green LED

  Serial.end();
  serialActive = false;
}

//-------------------tone to be called if user enters wrong combination

void alarm() {
  // Whoop up
  for (int hz = 440; hz < 1000; hz += 25) {
    tone(buzz, hz, 50);

    time_now = millis();
    wait(time_now, 5);

  }
  analogWrite(A1, 255);

  // Whoop down
  for (int hz = 1000; hz > 440; hz -= 25) {
    tone(buzz, hz, 50);
    time_now = millis();
    wait(time_now, 5);

  }
  analogWrite(A1, 0);
}


//--This method will be used to compare the combination entered by the user with the correct combination
boolean compareKeys( char pressed []) {
  char combination [3] = { 'r', 'g', 'b'}; //correct combination
  boolean result = true; //the outcome is true by default

  //will be checking element by element
  for ( int i = 0; i < 3; i++) {
    char test1 = combination[i];
    char test2 = pressed[i];

    if (test1 != test2) {
      result = false; //as soon as user input doesn't match, the outcome is wrong
    }
  }
  return result;
}


//////////////////////////////////////////////////////////////
// OpenMV Camera Call Back Handlers
//////////////////////////////////////////////////////////////
void exe_face_detection() {
  struct {
    uint16_t x, y, w, h;
  } face_detection_result;
  if (interface.call_no_args(F("face_detection"), &face_detection_result, sizeof(face_detection_result))) {
    Serial.print(F("Largest Face Detected [x="));
    Serial.print(face_detection_result.x);
    Serial.print(F(", y="));
    Serial.print(face_detection_result.y);
    Serial.print(F(", w="));
    Serial.print(face_detection_result.w);
    Serial.print(F(", h="));
    Serial.print(face_detection_result.h);
    Serial.println(F("]"));
  }
}


void exe_person_detection() {
  char buff[32 + 1] = {}; // null terminator
  if (interface.call_no_args(F("person_detection"), buff, sizeof(buff) - 1)) {
    result = String(buff);
    Serial.println(buff +  String(",") + String(distance));
  }
}
