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
NewPing sonar(7, 8, 200);


int IT=0;
int motorSpeed = FAST; //75 slow, 125 fast (127 max) 
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
#define BIG 200
#define LITTLE 20
void loop(){
        digitalWrite(LED,HIGH);
	int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
        }
        int waddupson = sonar.ping_in();
	if(res == MSG_FWD ){
	      motor.forward(motorSpeed);
              Serial.println("forwards");
	}else if(res == MSG_BACK){
	    motor.backward(motorSpeed);
            Serial.println("backwards");
	}else if(res == MSG_LEFT){
	    motor.turnLeft(TURNSPEED);
            Serial.println("left");
	}else if(res == MSG_RIGHT){
	    motor.turnRight(TURNSPEED);
            Serial.println("right"); 
        } else if (res != -1 || (waddupson < MAXDIST && waddupson)){
            motor.stop();
        }
	delay(200);
}
