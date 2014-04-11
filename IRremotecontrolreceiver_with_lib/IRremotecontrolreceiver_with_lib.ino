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

int LED = 3;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;

void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
void loop(){
	int res = ir.getMessage(); 
	if(res == MSG_FWD){
		motor.forward();
	}else if(res == MSG_BACK){
		motor.backward();
	}else if(res == MSG_LEFT){
		motor.turnLeft();
	}else if(res == MSG_RIGHT){
		motor.turnRight();
	}
	delay(50);
}
