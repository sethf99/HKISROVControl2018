int ledPin1 = 7;
int ledPin2 = 8;
byte currentValue = 0;
byte values[] = {0,0,0,0,0,0,0,0};

#include <Servo.h>
byte MotorPinList[]={9,10,11};
Servo mtr1;
Servo mtr2;
Servo mtr3;
Servo srv1;

int scale;
int openAngle = 1900;
int closedAngle = 1400;

void setup() {
  scale = 200;
  // put your setup code here, to run once:
  pinMode(ledPin1, OUTPUT); //sets up the lights
  pinMode(ledPin2, OUTPUT); //sets up the other light
  Serial.begin(115200);
  mtr1.attach(MotorPinList[0]);
  mtr2.attach(MotorPinList[1]);
  mtr3.attach(MotorPinList[2]);
  srv1.attach(6); // attach claw servo
  mtr1.writeMicroseconds(1500);
  mtr2.writeMicroseconds(1500);
  mtr3.writeMicroseconds(1500);
  srv1.writeMicroseconds(1900); // opens claw
  delay(3000);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    byte incomingValue = Serial.read(); // gets each value for the array and add its to the values array pretty OP if say so myself
    values[currentValue] = incomingValue; //voodoo magic
    currentValue++; //add so that the array index moves
    if(currentValue > 7){ // since their are only 8 numbers we need, if it exceeds 7, throw out the old values and use the new ones. 
      currentValue = 0; //reset
    }
  }
  Serial.flush();
  updateMotors();

 /*  
 float X=map(values[2],0,126,-1,1);
 float Y=map(values[3],0,126,-1,1);
  // int(values[1])
  
  if(int(values[5])>7){ // some yum code
      digitalWrite(ledPin2, LOW);
  } else{ // some more yum code
      digitalWrite(ledPin2, HIGH);
  }
  if(int(values[6])==1){ // some yum code
      digitalWrite(ledPin1, LOW);
  }else{ // some more yum code
      digitalWrite(ledPin1, HIGH);
}*/
//digitalWrite(2, HIGH);
//digitalWrite(3, LOW);
//digitalWrite(4, LOW);
//digitalWrite(5, HIGH);
//digitalWrite(7, LOW);
//digitalWrite(8, HIGH);
//digitalWrite(9, LOW);

}

void updateMotors(){
  mtr2.writeMicroseconds(byteToPWM(values[3])); // Writes veritcal motor speed
  
  if(byteToPWM(values[1]) != 1500 && byteToPWM(values[0] == 1500)){ // if yleft is not zero, forward or back
    mtr1.writeMicroseconds(byteToPWM(values[1]));
    mtr3.writeMicroseconds(byteToPWM(values[1]));
    digitalWrite(ledPin2, LOW);
  }
  else if(byteToPWM(values[0]) < 1500){ // xleft is left, go left
    mtr1.writeMicroseconds(byteToPWM(values[0])-scale);
    mtr3.writeMicroseconds(byteToPWM(values[0]));
    digitalWrite(ledPin1, LOW);
  }
  else if(byteToPWM(values[0]) > 1500){ // xleft is right, go right
    mtr1.writeMicroseconds(byteToPWM(values[0]));
    mtr3.writeMicroseconds(byteToPWM(values[0])-scale);
    digitalWrite(ledPin2, HIGH);
  }
  else if(byteToPWM(values[0]) == 1500){ // xleft is zero, stop
    mtr1.writeMicroseconds(byteToPWM(1500));
    mtr3.writeMicroseconds(byteToPWM(1500));
  }
}

int byteToPWM(byte bt){
  int temp = int(bt);
  return int(map(temp, 0, 126, 1500-scale, 1500+scale));
  //return temp*(scale/126)+1500;
}


