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

void setup() {

  Serial.begin(115200);
  
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

  int steeringangle = Serial.read();
  
  digitalWrite(in1_1, HIGH);
  digitalWrite(in1_2, LOW);
  digitalWrite(in2_1, HIGH);
  digitalWrite(in2_2, LOW);
  analogWrite(enA, 180);
  analogWrite(enB, 180);
  
  servo1.write(steeringangle);
}
