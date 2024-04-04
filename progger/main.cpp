#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <Arduino.h>
#include <SPI.h>

//motor driver ports
int ena = 0;
int enb = 5;
int enc = 6;
int end = 12;

int in1 = 1; //driver 1 motor a
int in2 = 2;
int in3 = 3; //driver 1 motor b
int in4 = 4;

int in5 = 7; //driver 2 motor a
int in6 = 8;
int in7 = 9; //driver 2 motor b
int in8 = 10;

int switchpin = 18;

int ledPin = 13;

int buffer = 0;
int buildup = 0;

float ball_x = 0;
float ball_y =  0;
float ball_y_old = 0;

float wheel1 = 0;
float wheel2 = 0;
float wheel3 = 0;
float wheel4 = 0;


void motor(float motor1, float motor2, float motor3, float motor4) {

}



void setup() {
  // put your setup code here, to run once:
  pinMode(ena,OUTPUT);
  pinMode(enb,OUTPUT);
  pinMode(enc,OUTPUT);
  pinMode(end,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  pinMode(in5,OUTPUT);
  pinMode(in6,OUTPUT);
  pinMode(in7,OUTPUT);
  pinMode(in8,OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(switchpin,INPUT);


  
  pinMode(20,INPUT);
  pinMode(21,INPUT);

  


  Serial.begin(512000);
  Serial5.begin(100000);
  // Serial.println("begin");
  // Serial5.begin(100000); //TX5, RX5 (to OpenMV)
  // //baudrate set at 100k to match with OpenMV

}

// void forward() {
  



// }



void loop() {

  if (analogRead(switchpin) > 800) {
    digitalWrite(ledPin,HIGH);
    uint8_t speed = 255;
    analogWrite(ena, speed);
    analogWrite(enb, speed);
    analogWrite(enc, speed);
    analogWrite(end,speed);
   

    if (Serial5.available()) {
      //a packet is 8 bits : ABBCCCCC - where A is a completeness marker, BB is a 2-bit identity_marker and CCCCC is the 5-bit payload.
      unsigned char incoming_pkt = Serial5.read();
      int completeness_marker = incoming_pkt >> 7;
      int identity_marker = (incoming_pkt % 128) >> 5; 
      int payload = (incoming_pkt % 32);

      buffer = buffer + (payload << buildup * 5);

      buildup = buildup + 1;

      if (completeness_marker == 1) { //ending packet
        wheel1 = 0;
        wheel2 = 0;
        wheel3 = 0;
        wheel4 = 0;
        ball_x = floor(buffer / 1000); //x
        ball_y = (buffer % 1000); //y
        
        float ball_y_offset =  (120 - ball_y) / 120;
        wheel1 = (wheel1 + ball_y_offset) * 2;
        wheel2 = (wheel2 - ball_y_offset) * 2;
        wheel3 = (wheel3 - ball_y_offset) * 2;
        wheel4 = (wheel4 + ball_y_offset) * 2;
        buffer = 0;
        buildup = 0;
      }
    }
    analogWrite(ena, int (abs(wheel1) * 200));
    analogWrite(enb, int (abs(wheel2) * 200));
    analogWrite(enc, int (abs(wheel3) * 200));
    analogWrite(end, int (abs(wheel4) * 200));

    if (wheel1 > 0) {digitalWrite(in1,HIGH); digitalWrite(in2,LOW);} else {digitalWrite(in2,HIGH); digitalWrite(in1,LOW);}
    if (wheel2 > 0) {digitalWrite(in3,HIGH); digitalWrite(in4,LOW);} else {digitalWrite(in4,HIGH); digitalWrite(in3,LOW);}
    if (wheel3 > 0) {digitalWrite(in5,HIGH); digitalWrite(in6,LOW);} else {digitalWrite(in6,HIGH); digitalWrite(in5,LOW);}
    if (wheel4 > 0) {digitalWrite(in7,HIGH); digitalWrite(in8,LOW);} else {digitalWrite(in8,HIGH); digitalWrite(in7,LOW);}

    Serial.println(wheel1);
    Serial.println(wheel2);
    Serial.println(wheel3);
    Serial.println(wheel4);
  }
  else {
    digitalWrite(ledPin,LOW);
    uint8_t speed = 0;
    analogWrite(ena, speed);
    analogWrite(enb, speed);
    analogWrite(enc, speed);
    analogWrite(end,speed);
  }
}
