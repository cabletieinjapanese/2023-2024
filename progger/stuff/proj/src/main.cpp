#include <Arduino.h>

//motor driver ports
int ena = 0;
int enb = 5;
int enc = 6;
int end = 11;

int in1 = 1; //driver 1 motor a
int in2 = 2;
int in3 = 3; //driver 1 motor b
int in4 = 4;

int in5 = 7; //driver 2 motor a
int in6 = 8;
int in7 = 9; //driver 2 motor b
int in8 = 10;

int ledPin = 13;

int buffer = 0;
int buildup = 0;

float ball_x = 0;
float ball_y =  0;
float ball_y_old = 0;
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
  pinMode(0,OUTPUT);
  pinMode(1,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT); 


  
  pinMode(20,INPUT);
  pinMode(21,INPUT);

  digitalWrite(1, HIGH);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);





  // Serial.begin(512000);
  // Serial.println("begin");
  // Serial5.begin(100000); //TX5, RX5 (to OpenMV)
  // //baudrate set at 100k to match with OpenMV

}

// void forward() {
  



// }



void loop() {
  // if (Serial5.available()) {
  //   //a packet is 8 bits : ABBCCCCC - where A is a completeness marker, BB is a 2-bit identity_marker and CCCCC is the 5-bit payload.
  //   unsigned char incoming_pkt = Serial5.read();
  //   int completeness_marker = incoming_pkt >> 7;
  //   int identity_marker = (incoming_pkt % 128) >> 5; 
  //   int payload = (incoming_pkt % 32);

  //   buffer = buffer + (payload << buildup * 5);
  //   buildup = buildup + 1;

  //   if (completeness_marker == 1) { //ending packet
  //     ball_y = (buffer % 1000);
  //     ball_x = floor(buffer / 1000);

  //     Serial.println(ball_x);
    for (int speed = 130; speed <= 255; speed++) {
          analogWrite(0, speed);
          analogWrite(5, speed);
          analogWrite(6, speed);
          analogWrite(11,speed);
          delay(100);
        }

  //     Serial.println(ball_y);

        
  // forward();
  //     if (ball_x > 135 and ball_x < 165){
  //       Serial.println("centre");

  //     }
  //     if (ball_x>80 and ball_x<130){
  //       Serial.println("right");
  //     }
  //     if (ball_x>165 and ball_x<300){
  //       Serial.println("left");
  //     }

      
  //     buildup = 0;
  //     buffer = 0;
  //   }
    
  // } 
} 


