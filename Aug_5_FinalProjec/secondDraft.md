My project will be a security system that makes use of a microntroller-camera that connects to the Arduino Uno via Serial connection. If a person's face is found by the camera and is detected within a specified range of an ultrasonic sensor, a piezo buzzer will ring to indicate presence and a RED LED light will shine. The person will then be prompted to click 3 switches in a proper combination to disarm the alarm system. A character LCD will indicate these instructions to the person. If after 3 tries the user fails to enter the proper combination, the piezo buzzer will trigger an alarm and the RED LED will turn on and off repeatedly. However, if the user enters the proper combination within the first 3 tries, the RED LED will turn of and a GREEN LED will shine to indicate access. 

I am still unsure if I should create a "Door System" by attaching a board to a motor-wheel device made in class. If the system is disarmed, the wheels would rotate and thus open the door.

In summary, these are the following components to be used:
- OpenMV H7 Camera
- Arduino
- 2 LED Lights
- Piezo Buzzer
- Character LCD
- Ultrasonic Sensor
- 3 Switches
- 2 Breadboards
- 10K Ohm Resistors
- 330 Ohm Resistors
- Wires

The riskiest part of my project at the moment is the establishment of connection between the OpenMV Camera and the Arduino. I have already contacted OpenMV and am currently communicating with their co-founder to discuss the connection process needed to establish connection. Once done, the second riskiest part would be programming aspect of this system's logic.
