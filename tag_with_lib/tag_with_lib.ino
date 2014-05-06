#include <Motor.h>

#include <IRremote.h>
#include <CppList.h>
#include <IRremoteInt.h>

#include <IR.h>
#include <NewPing.h>

#define TRIG 7
#define ECHO 8
#define DIST 200
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

int LED = A0;
IR ir;
NewPing sonar(TRIG,ECHO,DIST);
Motor motor(WHEEL0, WHEEL1, MOTORENA);

int IT=0;
int motorspeed  = SLOW;
void setup(){
	Serial.begin(9600);
	pinMode(LED,OUTPUT);
}
void loop(){
	tag();
}

void tag(){
	if(IT){
		motorspeed=FAST;
		digitalWrite(LED,HIGH);
		lookForBot();
		Serial.println("IT");
                //moveIt();
	} else{
		motorspeed=SLOW;
		digitalWrite(LED,LOW);
		runFromBot();
		Serial.println("NOT IT");
                //moveIt();
	}
	delay(50);
}
void lookForBot(){
	int msg = ir.getMessage();
	if(msg == MSG_ACK){
		IT = 0;
		//turn around and move forward
	}else if (msg == MSG_NOT_IT){
		if(sonar.ping_cm() < 10 && ir.front()){
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
			moveIt();
		}
	} else{
		moveIt();
	}
}
/*
   broadcast NOT_IT and wait to be tagged
   while moving, if tagged send ACK
 */
void runFromBot(){
	int msg = ir.getMessage();
	if(msg == MSG_TAG){
		motor.stop();
		IT = 1;
		//send ack three times
		for (int i = 0 ; i < 3; i++){
			ir.sendMessage(MSG_ACK);
		}
	}
	else {
		ir.sendMessage(MSG_NOT_IT);
		moveIt();
	}
        delay(50);
}
/*
   move but dont run into anything
 */
void moveIt(){
	//if wall turn left
        TIMER_DISABLE_INTR;
        unsigned int dist = sonar.ping_in();
        TIMER_ENABLE_INTR;
        Serial.print("distance ");
        Serial.println(dist);
        ///*
	if(dist < 10)
		motor.turnLeft(TURNSPEED);
	//else go forward
	else 
		motor.forward(motorspeed);
        //*/
}
