/*
  This code has programs for both the remote control
  and follow the leader.  The program can be switched
  by sending IR code 6 for remote control, and IR
  code 7 for follow the leader
*/
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
#define TRIG 7
#define ECHO 8
#define MAXDISTANCE 500
#define FAST 125
#define SLOW (FAST*3/4)
#define TURNSPEED (FAST/2)
#define BIG 200 //delay
#define LITTLE 20 //delay
int LED = 17;
IR ir;
Motor motor(WHEEL0, WHEEL1, MOTORENA);
NewPing sonar(TRIG, ECHO, MEXDISTANCE);


int IT=0;
int motorSpeed = FAST; //127 max 
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
int program=0;
void loop(){
  int res = ir.getMessage(); 
  digitalWrite(LED,HIGH);
  if(res != -1){
    digitalWrite(LED,LOW);
  }
  if(res == 6) program = 0;
  else if(res==7) program =1;
  if (program == 0){
    remoteControl(res);
  } else if (program == 1){
    followTheLeader(res); 
  } 
}
void followTheLeader(int res){
        int distance = sonar.ping_in();
	}else if(ir.front()){
            if(!distance || distance > 5)
	      motor.forward(motorSpeed);
            else
               motor.stop();
	}else if(ir.left()){
	    motor.turnLeft(TURNSPEED);
	}else if(ir.right()){
	    motor.turnRight(TURNSPEED);
	}else if(ir.back()){
	    motor.turnRight(TURNSPEED);
	} else if(res == MSG_SLOW){
            motorSpeed = SLOW;
        }else if (res == MSG_FAST){
            motorSpeed = FAST;
        } else if (distance && distance < 5)){
            motor.stop();
        }
	delay(BIG);
}
void remoteControl(int res){
        int distance = sonar.ping_in();
	if(res == MSG_FWD ){
            if(distance || distance > MAXDIST)
	      motor.forward(motorSpeed);
            else
               motor.stop();
	}else if(res == MSG_BACK){
	    motor.backward(motorSpeed);
	}else if(res == MSG_LEFT){
	    motor.turnLeft(TURNSPEED);
	}else if(res == MSG_RIGHT){
	    motor.turnRight(TURNSPEED);
	} else if(res == MSG_SLOW){
            motorSpeed = SLOW;
        }else if (res == MSG_FAST){
            motorSpeed = FAST;
        } else if (res == 8 || (distance && distance < MAXDIST) ){
            motor.stop();
        }
	delay(BIG);
}
