/*
  This program will run the motor forward for two seconds,
  turn left for 2 seconds, turn right for two seconds,
  backwards for two seconds, then stop for two seconds
*/
#include <Motor.h>

#define FAST 125
#define SLOW (FAST*3/4)
#define TURNSPEED (FAST/2)

int LED = 17;
Motor motor;

int motorSpeed = FAST; //127 max 
int counter = 0;
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
void loop(){
        digitalWrite(LED,HIGH);
        motor.forward(SLOW, 2000);
        digitalWrite(LED,LOW);
        motor.turnLeft(TURNSPEED, 2000);
        digitalWrite(LED,LOW);
        motor.turnRight(TURNSPEED, 2000);
        digitalWrite(LED,HIGH);
        motor.backward(SLOW, 2000);
        digitalWrite(LED,LOW);
        motor.stop();
        delay(2000);
}
