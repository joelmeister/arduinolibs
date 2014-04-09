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

IRrecv irrecv1(10);
IRrecv irrecv2(16);
IRrecv irrecv3(14);
IRrecv irrecv4(15);

IRsend irsend;

decode_results results1;
decode_results results2;
decode_results results3;
decode_results results4;
unsigned int buf[10] = {1000,500,1000,500,1000,500,1000,500};

void setup()
{
  Serial.begin(9600);
  irrecv1.enableIRIn(); // Start the receiver
  irrecv2.enableIRIn(); // Start the receiver
  irrecv3.enableIRIn(); // Start the receiver
  irrecv4.enableIRIn(); // Start the receiver
  pinMode(LED,OUTPUT);
}
void loop() {
  boolean flag = false;
  if (irrecv1.decode(&results1)) {
    parseResult(results1, 1);
    flag = true;
  }
  if (irrecv2.decode(&results2)) {
    parseResult(results2, 2);
    flag = true;
  }
  if (irrecv3.decode(&results3)) {
    parseResult(results3, 3);
    flag = true;
  }
  if (irrecv4.decode(&results4)) {
    parseResult(results4, 4);
    flag = true;
  }
  digitalWrite(LED,HIGH);
  delay(50);
  
  irsend.sendRaw(buf,10,38);
  delay(100);
  
  if (flag){
    irrecv1.resume();
  }
}
void parseResult(decode_results results , int r){
    digitalWrite(LED,LOW);
    delay(50);
    //Serial.println(results.value, HEX);
    int i=0;
    int sum=0;

    Serial.print(r);
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
}