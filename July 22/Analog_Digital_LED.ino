void setup() {
  pinMode(13, OUTPUT); //feed digital value to LED in pin 13
  pinMode(A2, INPUT);  //read digital value from switch

  Serial.begin(9600); // initialize serial communication at 9600 bits per second:
  pinMode(A0, INPUT); //analog (use analog read for this pin)
  pinMode(9, OUTPUT); //LED Pin (use analog Write into this pin)
  pinMode(5, OUTPUT); //LEd Pin (use analog Write into this pin)

}

void loop() {


  int switchPosition = digitalRead(A2); //this pin will read values from switch

  if (switchPosition == HIGH) {
    digitalWrite(8, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(13, LOW);


    //I will be creating fading effect for LED on pin 5
      for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
        // sets the value (range from 0 to 255):
        analogWrite(5, fadeValue);
        

        //dimming effect will be captured by photoresistor
        int val = analogRead(A0);
        Serial.println(val);

        //map value from photoresistor and invert it
        val = map(val,150, 765, 255, 0); 

        //feed this inverted value to LED in Pin 9
        analogWrite(9, val);
        delay(30); // wait for 30 milliseconds to see the dimming effect
      }

      //same process below
      // fade out from max to min in increments of 5 points:
      for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
        // sets the value (range from 0 to 255):
        analogWrite(5, fadeValue);
        int val = analogRead(A0);
        val = map(val, 150, 765, 255, 0);
        analogWrite(9, val);
        
        delay(30); // wait for 30 milliseconds to see the dimming effect
      }



  } else  {
    digitalWrite(8, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(13, HIGH);

  }
}
