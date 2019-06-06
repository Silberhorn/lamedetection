#include <Servo.h>

//Motor 1
int enA = 3;
int in1_1 = 11;
int in1_2 = 8;

//Motor 2
int enB = 5;
int in2_1 = 7;
int in2_2 = 6;

//Servo
Servo servo1;
//int motorspeed = 0;
int steeringangle = 90;

void setup() {

  Serial.begin(57600);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1_1, OUTPUT);
  pinMode(in1_2, OUTPUT);
  pinMode(in2_1, OUTPUT);
  pinMode(in2_2, OUTPUT);

  servo1.attach(10);
  servo1.write(90);
  // middle 90
}

void loop() {

  while (!Serial.available()){}

  digitalWrite(in1_1, HIGH);
  digitalWrite(in1_2, LOW);
  digitalWrite(in2_1, HIGH);
  digitalWrite(in2_2, LOW);
  //analogWrite(enA, 0);
  //analogWrite(enB, 0);

  int serialTemp = Serial.read();
  // 200 = Stop
  if(serialTemp == 200){
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    delay(5000);
  }
  
  if(serialTemp > 200){
    analogWrite(enA, 200);
    analogWrite(enB, 200);
  }
  
  if(serialTemp >= 0 && serialTemp <= 180){
    servo1.write(serialTemp);
  }

}
