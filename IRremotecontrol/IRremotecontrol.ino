/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

IRsend irsend;
int LED = A0;
int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 6;

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(b4,INPUT);
}
unsigned int buf1[10] = {500,500,500,500,500,500,500,500}; //82
unsigned int buf2[10] = {500,500,500,500,500,500,500,1000}; //92
unsigned int buf3[10] = {500, 500,500,500,500,500,1000,1000}; //102
unsigned int buf4[10] = {500, 500,500,500,500,1000,1000,1000}; //112
unsigned int buf5[10] = {1000,1000,1000,1000,1000,1000,1000,1000};
void loop() {
  int s1 = digitalRead(b1);
  int s2 = digitalRead(b2);
  int s3 = digitalRead(b3);
  int s4 = digitalRead(b4);
  digitalWrite(LED,HIGH);
  delay(100);
  if(s1 == HIGH){
    irsend.sendRaw(buf1,9,38);
  }
  else if(s2 == HIGH){
    irsend.sendRaw(buf2,9,38);
  }
  else if(s3 == HIGH){
    irsend.sendRaw(buf3,9,38);
  }
  else if(s4 == HIGH){
    irsend.sendRaw(buf4,9,38);
  }
  else{
    irsend.sendRaw(buf5,9,38);
  }
  digitalWrite(LED,LOW);
  delay(100);
}
