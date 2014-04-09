/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>

int RECV_PIN = 10;
int LED=3;
int LED1=16;
int LED2=14;
int LED3=15;
int LED4=A0;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED,OUTPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
}

void loop() {
  int res = 0;
  if (irrecv.decode(&results)) {
    res = getResult();
    parseResult(res);
  }
    digitalWrite(LED,HIGH);
  delay(50);
}
void fwd(){
       digitalWrite(LED1, HIGH);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
}
void back(){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, HIGH);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
}
void left(){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, HIGH);
       digitalWrite(LED4, LOW);
}
void right(){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, HIGH);
}
void idle(){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
}
void parseResult(int res){
   if(res > 79 && res <= 88){
     fwd();
   }
  else if(res > 89 && res < 98){
    back();
  }
  else if(res > 99 && res < 108){
    left();
  }
  else if(res > 109 && res < 118){
    right();
  }
  else{
    idle();
  }
}
int getResult(){
    digitalWrite(LED,LOW);
    delay(50);
    //Serial.println(results.value, HEX);
    int i=0;
    int sum=0;
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1];
}
