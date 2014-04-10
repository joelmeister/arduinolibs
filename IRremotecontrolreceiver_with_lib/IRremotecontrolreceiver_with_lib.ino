#include <IR.h>
#include <NewPing.h>

#define TRIG 8
#define ECHO 9
#define DIST 400
#define WHEEL0 6
#define WHEEL1 9
#define MOTORENA 20
#define MSG_NOT_IT 0
#define MSG_TAG 1
#define MSG_ACK 2

int LED = 3;
IR ir;
NewPing sonar(TRIG,ECHO,DIST);
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;

void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
void loop(){
	if(IT){
		lookForBot();
	} else{
		runFromBot();
	}
	delay(50);
}

void lookForBot(){
	int msg = ir.getMessage();
	if(msg == MSG_ACK){
		IT = 0;
		//turn around and move forward
	}else if (msg == MSG_NOT_IT){
		if(distance() < 10 && ir.front()){
			ir.sendMessage(MSG_TAG);
			motor.stop();
			delay(50);
		}else if(ir.front()){
			move();
		} else if(ir.left()){
			motor.turnLeft();
		} else if(ir.right()){
			motor.turnRight();
		} else if(ir.back()){
			motor.turnLeft();
		} else{
			move();
		}
	} else{
		move();
	}
}
/*
	broadcast NOT_IT and wait to be tagged
	while moving, if tagged send ACK
*/
void runFromBot(){
	int msg = ir.getMessage();
	if(msg == MSG_TAG){
		IT = 1;
		//send ack three times
		for (int i = 0 ; i < 3; i++){
			ir.sendMessage(MSG_ACK);
			delay(50);
		}
	}
	else {
		ir.sendMessage(MSG_NOT_IT);
		move();
	}
}
/*
	move but dont run into anything
*/
void move(){
	//if wall turn left
	motor.turnLeft();
	//else go forward
	motor.forward();
}
