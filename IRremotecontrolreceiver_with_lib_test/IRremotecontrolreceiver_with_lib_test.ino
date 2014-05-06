
#define DEBUG

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

int LED = 17;
int LED0= A0;
int LED2= A2;
int LED1= A1;
int LED3= A3;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;

void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
	pinMode(LED0,OUTPUT);
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
}
void loop(){
          digitalWrite(LED,HIGH);
	int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
          delay(50);
        }
	if(res == MSG_FWD){
		motor.forward();
                LEDOn(LED0);
	}else if(res == MSG_BACK){
		motor.backward();
                LEDOn(LED1);
	}else if(res == MSG_LEFT){
		motor.turnLeft();
                LEDOn(LED2);
	}else if(res == MSG_RIGHT){
		motor.turnRight();
                LEDOn(LED3);
	}else{
                LEDOn(-1);//all off
        }
	delay(50);
}
void LEDOn(int p){
 digitalWrite(LED0,LOW);
 digitalWrite(LED1,LOW);
 digitalWrite(LED2,LOW);
 digitalWrite(LED3,LOW);
 digitalWrite(p,HIGH); 
}
