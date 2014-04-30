#include <Motor.h>

#include <IRremote.h>
#include <CppList.h>
#include <IRremoteInt.h>

#include <IR.h>
#include <NewPing.h>

#define TRIG 7
#define ECHO 8
#define DIST 400
#define WHEEL0 6
#define WHEEL1 9
#define MOTORENA 20
#define MSG_NOT_IT 0
#define MSG_TAG 1
#define MSG_ACK 3

#define SLOW 75
#define FAST 125
#define MAXDIST 8
#define TURNSPEED 40

int LED = 17;
int LED0 = A0;
int LED1 = A1;
int LED2 = A2;
int LED3 = A3;


IR ir;
NewPing sonar(TRIG,ECHO,DIST);
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;

void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
	pinMode(LED0,OUTPUT);
	pinMode(LED1,OUTPUT);
	pinMode(LED2,OUTPUT);
	pinMode(LED3,OUTPUT);
        ir.sendMessage(0);
        ir.enableAll();
        ir.resumeAll();
}
void loop(){
  tag();
}

void tag(){
	if(IT){
              digitalWrite(LED,HIGH);
	      lookForBot();
              Serial.println("IT");
	} else{
              digitalWrite(LED,LOW);
	      runFromBot();
              Serial.println("NOT IT");
	}
	delay(50);
}
void lookForBot(){
	int msg = ir.getMessage();
	if(msg == MSG_ACK){
		IT = 0;
		//turn around and move forward
                digitalWrite(LED0,LOW);
                digitalWrite(LED1,LOW);
                digitalWrite(LED2,LOW);
                digitalWrite(LED3,HIGH);
	}else if (msg == MSG_NOT_IT){
		if(sonar.ping_cm() < 10 && ir.front()){
                        digitalWrite(LED0,LOW);
                        digitalWrite(LED1,LOW);
                        digitalWrite(LED2,HIGH);
                        digitalWrite(LED3,LOW);
			ir.sendMessage(MSG_TAG);
			motor.stop();
			delay(50);
		}else if(ir.front()){
			motor.forward();
		} else if(ir.left()){
			motor.turnLeft();
		} else if(ir.right()){
			motor.turnRight();
		} else if(ir.back()){
			motor.turnLeft();
		} else{
			moveIt(FAST);
		}
	} else{
		moveIt(FAST);
	}
}
/*
	broadcast NOT_IT and wait to be tagged
	while moving, if tagged send ACK
*/
int fuck = 0;
void runFromBot(){
	int msg = ir.getMessage();
	if(msg == MSG_TAG){
                digitalWrite(LED0,HIGH);
                digitalWrite(LED1,LOW);
                digitalWrite(LED2,LOW);
                digitalWrite(LED3,LOW);
                motor.stop();
		IT = 1;
		//send ack three times
		for (int i = 0 ; i < 3; i++){
			ir.sendMessage(MSG_ACK);
		}
                ir.enableAll();
                ir.resumeAll();
                //delay(40);
	}
	else {
                digitalWrite(LED0,LOW);
                digitalWrite(LED1, HIGH);
                digitalWrite(LED2,LOW);
                digitalWrite(LED3,LOW);
		if(fuck == 3) {
                  ir.sendMessage(MSG_NOT_IT);
                  ir.enableAll();
                  ir.resumeAll();
                }
                fuck = (fuck + 1) % 4;
                //delay(40);
		moveIt(SLOW);
	}
}
/*
	move but dont run into anything
*/
void moveIt(int sp){
	//if wall turn left
        if(sonar.ping_in() < 10)
	  motor.turnLeft(TURNSPEED);
	//else go forward
	else 
          motor.forward(sp);
}
