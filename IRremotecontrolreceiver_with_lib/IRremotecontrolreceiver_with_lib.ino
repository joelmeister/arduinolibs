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
#define MSG_LEFT 3
#define MSG_RIGHT 5

int LED = 17;
int LED0= A0;
int LED1= A1;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;

void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
	pinMode(LED0,OUTPUT);//shit code
	pinMode(LED1,OUTPUT);//shit code
}
#define BIG 200
#define LITTLE 20
void loop(){
        digitalWrite(LED,HIGH);
	int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
        }
	if(res == MSG_FWD){
	    motor.forward();
            delay(BIG);
	}else if(res == MSG_BACK){
	    motor.backward();
            delay(BIG);
	}else if(res == MSG_LEFT){
	    motor.turnLeft();
            delay(BIG);
	}else if(res == MSG_RIGHT){
	    motor.turnRight();
            delay(BIG);
	}else{
            motor.stop();
	    delay(LITTLE);
        }
}
