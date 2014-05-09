#include <NewPing.h>

#include <IRremote.h>
#include <CppList.h>
#include <IRremoteInt.h>

#include <Motor.h>

#include <IR.h>

#define WHEEL0 6
#define WHEEL1 9
#define MOTORENA 20
#define MSG_FWD 0
#define MSG_BACK 1
#define MSG_LEFT 2
#define MSG_RIGHT 3
#define MSG_SLOW 4
#define MSG_FAST 5
#define SLOW 75
#define FAST 125
#define MAXDIST 8
#define TURNSPEED 40
int LED = 17;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);
NewPing sonar(7, 8, 500);


int IT=0;
int motorSpeed = FAST; //75 slow, 125 fast (127 max) 
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
#define BIG 200
#define LITTLE 20
int counter = 0;
void loop(){
        digitalWrite(LED,HIGH);
        TIMER_DISABLE_INTR;
        unsigned int yo = sonar.ping_in();
        TIMER_ENABLE_INTR;
        Serial.println(yo);
        if(yo && yo < 5){
          motor.turnRight(TURNSPEED); 
        }else{
          counter++;
          if ( counter < 25)
           motor.forward(SLOW);
          else if( counter < 30)
            motor.turnLeft(TURNSPEED);
          else
            counter = 0;
        }
        ir.sendMessage(8);
        delay(100);
}
