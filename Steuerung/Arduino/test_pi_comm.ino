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

  Serial.begin(9600);
  
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1_1, OUTPUT);
  pinMode(in1_2, OUTPUT);
  pinMode(in2_1, OUTPUT);
  pinMode(in2_2, OUTPUT);

  servo1.attach(10);
}

void loop() {

  while (!Serial.available()){}
  byte nr = Serial.read();
  nr = char(nr);
  Serial.println(nr, DEC);
  
  switch(nr){
  case 'w':
    digitalWrite(in1_1, HIGH);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_1, HIGH);
    digitalWrite(in2_2, LOW);

    analogWrite(enA, 200);
    analogWrite(enB, 200);
    break;

  case 's':
    digitalWrite(in1_1, LOW);
    digitalWrite(in1_2, HIGH);
    digitalWrite(in2_1, LOW);
    digitalWrite(in2_2, HIGH);

    analogWrite(enA, 200);
    analogWrite(enB, 200);
    break;

  case 'a':
    servo1.write(300);
    break;
  
  case 'd':
    servo1.write(400);
    break;
    
  case 'c':
    digitalWrite(in1_1, LOW);
    digitalWrite(in1_2, LOW);
    digitalWrite(in2_1, LOW);
    digitalWrite(in2_2, LOW);

    servo1.write(350);
    
    break;
  }
}
