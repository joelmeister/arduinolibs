/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include <IRremote.h>
#include <Motor.h>

int LED = A0;
int RECV_PIN1 = 10;
int RECV_PIN2 = 16;
int RECV_PIN3 = 14;
int RECV_PIN4 = 15;
IRrecv irrecv1(RECV_PIN1);
IRrecv irrecv2(RECV_PIN2);
IRrecv irrecv3(RECV_PIN3);
IRrecv irrecv4(RECV_PIN4);
decode_results results;

Motor motor(6,9,20);

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
  int res = 0;
  if (irrecv1.decode(&results)) {
    movement();
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
    irrecv1.resume(); // Receive the next value
  }
  if (irrecv2.decode(&results)) {
    movement();
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
    irrecv2.resume(); // Receive the next value
  }
  if (irrecv3.decode(&results)) {
    movement();
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
    irrecv3.resume(); // Receive the next value
  }
  if (irrecv4.decode(&results)) {
    movement();
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
    irrecv4.resume(); // Receive the next value
  }
  else{
    movement();
  }
  digitalWrite(LED,HIGH);
  delay(50);
}
int last = 4; // fwd,back,left,right,stop
void parseResult(int res){
   if(res > 149 && res <= 155){
    last = 0;
   }
  else if(res > 168 && res < 174){
    last = 1;
  }
  else if(res > 187 && res < 193){
    last = 2;
  }
  else if(res > 204 && res < 212){
    last = 3;
  }
  else if(res > 225 && res < 230){
    last = 4;
  } else {
    idle(); 
  }
}
void movement(){
  Serial.print("movement: ");
  Serial.println(last);
  switch (last){
   case 0:
     fwd();
     break;
   case 1:
     back();
     break;
   case 2:
     left();
     break;
   case 3:
     right();
     break;
   case 4:
     idle();
     break;
  }
}1
void fwd(){
  motor.forward();
}
void back(){
  motor.backward();
}
void left(){
  motor.turnLeft();
}
void right(){
  motor.turnRight();
}
void idle(){
  motor.stop();
}
int getResult(){
    delay(50);
    int i=0;
    int sum=0;
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1];
}
