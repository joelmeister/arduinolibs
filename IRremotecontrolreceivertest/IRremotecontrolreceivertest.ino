/*
 * arduino to resistor to +led to ground
*/
#include <IRremote.h>
#include <Motor.h>

int LED = 3;
int LED1 = A0;
int LED2 = A2;
int LED3 = A1;
int LED4 = A0;
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

Motor motor(6,9,20);

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  int res = 0;
  if (irrecv.decode(&results)) {
    digitalWrite(LED,LOW);
    res = getResult();
    parseResult(res);
  }
  digitalWrite(LED,HIGH);
  delay(50);
}
void fwd(){
  motor.forward();
  LEDOn(LED1);
}
void back(){
  motor.backward();
  LEDOn(LED2);
}
void left(){
  motor.turnLeft();
  LEDOn(LED3);
}
void right(){
  motor.turnRight();
  LEDOn(LED4);
}
void idle(){
  motor.stop();
  LEDOn(-1);
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
void LEDOn(int pin){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
       if(pin != -1){
          digitalWrite(pin, HIGH); //overwrite previous 
       }
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
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1];
}
