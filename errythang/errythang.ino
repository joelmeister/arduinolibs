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
int program=0;
void loop(){
  int res = ir.getMessage(); 
  if(res == 6) program = 0;
  else if(res==7) program =1;
  if (program == 0){
    remoteControl(res);
  } else if (program == 1){
    followTheLeader(res); 
  } 
}
void followTheLeader(int res){
        digitalWrite(LED,HIGH);
	//int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
        }	
        if(res == MSG_FWD ){
            if(sonar.ping_in() > MAXDIST)
	      motor.forward(motorSpeed);
            else
               motor.stop();
            //delay(BIG);
	}else if(res == MSG_BACK){
	    motor.backward(motorSpeed);
            //delay(BIG);
	}else if(res == MSG_LEFT){
	    motor.turnLeft(TURNSPEED);
            //delay(BIG);
	}else if(res == MSG_RIGHT){
	    motor.turnRight(TURNSPEED);
            //delay(BIG);
	}else if(ir.left()){
	    motor.turnLeft(TURNSPEED);
            //delay(BIG);
	}else if(ir.right()){
	    motor.turnRight(TURNSPEED);
            //delay(BIG);
	}else if(ir.front()){
            if(sonar.ping_in() > MAXDIST)
	      motor.forward(motorSpeed);
            else
               motor.stop();
            //delay(BIG);
	}else if(ir.left()){
	    motor.turnLeft(TURNSPEED);
            //delay(BIG);
	}else if(ir.right()){
	    motor.turnRight(TURNSPEED);
            //delay(BIG);
	}else if(ir.back()){
	    motor.turnRight(TURNSPEED);
            //delay(BIG);
	} else if(res == MSG_SLOW){
            motorSpeed = SLOW;
        }else if (res == MSG_FAST){
            motorSpeed = FAST;
        } else if (sonar.ping_in() < MAXDIST){
            motor.stop();
        }
	delay(BIG);
}
void remoteControl(int res){
        digitalWrite(LED,HIGH);
	//int res = ir.getMessage(); 
        if(res != -1){
          digitalWrite(LED,LOW);
        }
	if(res == MSG_FWD ){
            if(sonar.ping_in() > MAXDIST)
	      motor.forward(motorSpeed);
            else
               motor.stop();
            //delay(BIG);
	}else if(res == MSG_BACK){
	    motor.backward(motorSpeed);
            //delay(BIG);
	}else if(res == MSG_LEFT){
	    motor.turnLeft(TURNSPEED);
            //delay(BIG);
	}else if(res == MSG_RIGHT){
	    motor.turnRight(TURNSPEED);
            //delay(BIG);
	} else if(res == MSG_SLOW){
            motorSpeed = SLOW;
        }else if (res == MSG_FAST){
            motorSpeed = FAST;
        } else if (res == 8 ||  sonar.ping_in() < MAXDIST){
            motor.stop();
        }
	delay(BIG);
}
