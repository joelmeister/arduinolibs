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
int button = 4;

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(button,INPUT);
}
unsigned int buf1[10] = {500,500,500,500,500,500,500,500};
unsigned int buf2[10] = {500,500,500,500,500,500,1000,1000};
unsigned int buf3[10] = {500, 500,500,500,1000,1000,1000,1000};
unsigned int buf4[10] = {500, 500,1000,1000,1000,1000,1000,1000};
unsigned int buf5[10] = {1000,1000,1000,1000,1000,1000,1000,1000};
void loop() {
  
  int buttonState = digitalRead(button);
  Serial.println(buttonState);
  delay(100);
  if(buttonState == HIGH){
    irsend.sendRaw(buf1,9,38);
    delay(100);
  }else{
    irsend.sendRaw(buf5,9,38);
    delay(100);
  }
  /*
  irsend.sendRaw(buf1,9,38);
  delay(100);
  irsend.sendRaw(buf2,9,38);
  delay(100);
  irsend.sendRaw(buf3,9,38);
  delay(100);
  irsend.sendRaw(buf4,9,38);
  delay(100);
  irsend.sendRaw(buf5,9,38);
  delay(100);
  */
}

