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

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED,OUTPUT);
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
void parseResult(int res){
   if(res > 75 && res < 85){
   
   }
  else if(res > 155 && res < 165){
    
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
