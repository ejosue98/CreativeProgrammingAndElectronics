
int led = 13;// Pin for LED
int tonePin = 9; //tone for Buzzer

int state = 0;
//state 0 = play
//state 1 = pause

int buttonState = 0;          //variable for reading the pushbutton status
int stopButton = 0;

#include <Servo.h>

Servo myservo;   //create servo object to control a servo

int pos = 180;     //variable to read the value from the analog pin

void setup() {
  int stopButton = 0;
  
  Serial.begin(9600);
  myservo.attach(6);   //attaches the servo on pin 9 to the servo object
  pinMode(2, INPUT);  //pause/play switch
  pinMode(4, INPUT);  //stop switch
}


void loop() {
  
   checkSwitch();
   if (state ==2){ 
    exit;
   }

}

int checkSwitch() { //recall state 0 (play) , state 1 (pause)
  buttonState =  digitalRead(2);
  Serial.println(buttonState);
  if (buttonState == HIGH && state == 0) { //if button is pressed && song is playing
    pause(); //pause && change state to paused
        state = 1;

  } else if (buttonState == HIGH && state == 1) { //if button is pressed && song is paused
    state = 0;
    song(); //play song and change to play


  }

  stopButton = digitalRead(4);
  
  if( stopButton == HIGH) { 
    state = 2;
  }
return state;
}


//hit is in charge of making servo rotations
int hit() {
  if (pos == 180) {
    pos = 160;
  } else if (pos == 160) {
    pos = 180;
  }
  myservo.write(pos);
}


//Pause method
void pause() {
  noTone(9);
  checkSwitch();
}

unsigned long previousMillis = 0;
const long interval = int(random(400, 800));

void wait() {
  while (6 > 5) {
    checkSwitch();
    unsigned long currentMillis = millis();
    Serial.println(state);
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      break;
    }
  }
}


//Play Despacito
void song () {
  tone(tonePin, 587, 710);
  hit();
  wait();
  tone(tonePin, 554, 710);
  hit();
  wait();
  tone(tonePin, 493, 274);
  hit();
  wait();
  tone(tonePin, 369, 274);
  hit();
  wait();
  tone(tonePin, 369, 135);
  hit();
  wait();
  tone(tonePin, 369, 135);
  hit();
  wait();
  tone(tonePin, 369, 135);
  hit();
  wait();
  tone(tonePin, 369, 135);
  hit();
  wait();
  tone(tonePin, 369, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 274);
  hit();
  wait();
  tone(tonePin, 440, 135);
  hit();
  wait();
  tone(tonePin, 493, 274);
  hit();
  wait();
  tone(tonePin, 391, 413);
  hit();
  wait();
  tone(tonePin, 391, 135);
  hit();
  wait();
  tone(tonePin, 391, 135);
  hit();
  wait();
  tone(tonePin, 391, 135);
  hit();
  wait();
  tone(tonePin, 391, 135);
  hit();
  wait();
  tone(tonePin, 391, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 135);
  hit();
  wait();
  tone(tonePin, 493, 274);
  hit();
  wait();
  tone(tonePin, 554, 135);
  hit();
  wait();
  tone(tonePin, 587, 274);
  hit();
  wait();
  tone(tonePin, 440, 413);
  hit();
  wait();
}
