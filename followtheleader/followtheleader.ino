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
#define BIG 100
#define LITTLE 30
void loop(){
          digitalWrite(LED,HIGH);
	int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
          if(ir.front()){
        	motor.forward();
                delay(BIG);
          }else if(ir.left()){
        	motor.turnRight();
                delay(BIG);
          }else if(ir.right()){
        	motor.turnLeft();
                delay(BIG);
          }else if(ir.back()){
        	motor.turnRight();
                delay(BIG);
          }else{
            motor.stop();
          }
        }
        motor.stop();
	delay(LITTLE);
}
