
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

const short buttonPin1 = 2;
const short buttonPin2 = 4;
const short buttonPin3 = 7;
const short buttonPin4 = 11;
const short potPin = A0;

short buttonState1 = 0;
short buttonState2 = 0;
short buttonState3 = 0;
short buttonState4 = 0;
short potValue = 0;
short rotationValue = 0;
bool ActiveMovement = false;

void setup(){

  Serial.begin(9600);

  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  pinMode(buttonPin4, INPUT);
  pinMode(potPin, INPUT);
  
  // Transmitter is connected to Arduino Pin #12  
  mySwitch.enableTransmit(12);
  
  // Optional set protocol (default is 1, will work for most outlets)
  // mySwitch.setProtocol(1);

  // Optional set pulse length.
  // mySwitch.setPulseLength(320);
  
  // Optional set number of transmission repetitions.
  // mySwitch.setRepeatTransmit(3);
  
}

void loop() {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  
  Serial.println(analogRead(potPin));

  if (buttonState3 == HIGH){
    mySwitch.send(4000, 24);
  }
  if (buttonState2 == HIGH && buttonState1 == LOW){
    if (ActiveMovement != true){
      mySwitch.send(1000, 24);
    }
    ActiveMovement = true;
  }

  if (buttonState2 == LOW){
    if (ActiveMovement == true){
      mySwitch.send(2000, 24);
    }
    ActiveMovement = false;
  }
  
  if (buttonState1 == HIGH && buttonState2 == LOW){
    mySwitch.send(3000, 24);
    ActiveMovement = false;
  }
  if (buttonState4 == HIGH){
    mySwitch.send(5000, 24);
  }
  
  if (analogRead(potPin) >= 0 && analogRead(potPin) < 150){
    if (rotationValue != 1){
      mySwitch.send(10000, 24);
      rotationValue = 1;
    }
  }
  else if (analogRead(potPin) >= 150 && analogRead(potPin) < 300){
    if (rotationValue != 2){
      mySwitch.send(11000, 24);
      rotationValue = 2;
    }
  }
  else if (analogRead(potPin) >= 300 && analogRead(potPin) < 450){
    if (rotationValue != 3){
      mySwitch.send(12000, 24);
      rotationValue = 3;
    }
  }
  else if (analogRead(potPin) >= 450 && analogRead(potPin) < 600){
    if (rotationValue != 4){
      mySwitch.send(13000, 24);
      rotationValue = 4;
    }
  }
  else if (analogRead(potPin) >= 600 && analogRead(potPin) < 750){
    if (rotationValue != 5){
      mySwitch.send(14000, 24);
      rotationValue = 5;
    }
  }
  else if (analogRead(potPin) >= 750 && analogRead(potPin) < 900){
    if (rotationValue != 6){
      mySwitch.send(15000, 24);
      rotationValue = 6;
    }
  }
  else if (analogRead(potPin) >= 900 && analogRead(potPin) < 1024){
    if (rotationValue != 7){
      mySwitch.send(16000, 24);
      rotationValue = 7;
    }
  }
  
}
