#include <IR.h>
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define RECEIVER 0
#define SENDER 1
#define ERROR 2
#define R0 10 //front
#define R1 16
#define R2 14
#define R3 15
#define SENDPIN 5

#define DEBUG
IR::IR()
	: irSend(),irRecv0(R0),irRecv1(R1),
		irRecv2(R2),irRecv3(R3),
		send_pin(SENDPIN), recv_pin0(R0), recv_pin1(R1),
		recv_pin2(R2), recv_pin3(R3)
{
	setup();
/*these might change*/
	m0_l = 38; m0_u = 42;
	m1_l = 43; m1_u = 47;
	m2_l = 48; m2_u = 52;
	m3_l = 53; m3_u = 57;
	m4_l = 58; m4_u = 62;
	m5_l = 63; m5_u = 67;
	m6_l = 68; m6_u = 72;
	m7_l = 73; m7_u = 77;
	m8_l = 78; m8_u = 82;
	enableAll();
}

IR::~IR(){}

void IR::setup(){ }
/*
	sends a message from a list of preset messages
*/
#define SMALL 5000
#define LARGE 10000
void IR::sendMessage(int msg){
#ifdef DEBUG
	Serial.print("sending: ");
	Serial.println(msg);
#endif

	if(msg == 0){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 1){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 2){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 3){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 4){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if( msg == 5){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if( msg == 6){
		unsigned int msg[8] = {SMALL,SMALL,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else if( msg == 7){
		unsigned int msg[8] = {SMALL,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}
	else{
		unsigned int msg[8] = {LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
	}

	this->enableAll();
	delay(50);
}

/*
	return direction with priority:
		front>left>right>back
*/
bool IR::front(){ return fr;}
bool IR::left(){ return le;}
bool IR::right(){ return ri;}
bool IR::back(){ return ba;}

void IR::enableAll(){
	irRecv0.enableIRIn();
	irRecv1.enableIRIn();
	irRecv2.enableIRIn();
	irRecv3.enableIRIn();
}
void IR::resumeAll(){
	irRecv0.resume();
	irRecv1.resume();
	irRecv2.resume();
	irRecv3.resume();
}
int IR::getMessage(){
	fr = le = ba = ri = false;
	if (irRecv0.decode(&results)) {
		fr = true;
		int res = getResult(irRecv0);
		return parseResult(res, FRONT);
	}
	
	else if (irRecv2.decode(&results)) {
		le = true;
		int res = getResult(irRecv2);
		return parseResult(res, LEFT);
	}
	else if (irRecv3.decode(&results)) {
		ri = true;
	    int res = getResult(irRecv3);
	    return parseResult(res, RIGHT);
	}
	else if (irRecv1.decode(&results)) {
		ba = true;
		int res = getResult(irRecv1);
		return parseResult(res, BACK);
	}
	else{
		return -1;
	}
	return -1;
}
int IR::getResult(IRrecv &irrecv){
    delay(50);
	
    int sum=0;
    for(int i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
#ifdef DEBUG
     Serial.print(results.rawbuf[i],DEC);
     Serial.print(" ");
#endif
    }
#ifdef DEBUG
	Serial.print(" | Sum: ");
    Serial.print(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
	Serial.print(" Rawlen: ");
    Serial.println(results.rawlen);
#endif
    resumeAll(); // Receive the next value
	if(results.rawlen != 10){
#ifdef DEBUG
		Serial.println("bad message size: ");
		Serial.println(results.rawlen);
#endif
		//return -1;
	}
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]; 
}
int IR::parseResult(int res, int dir){
#ifdef DEBUG
	Serial.print("Direction: ");
	Serial.println(dir);
#endif
	if(m0_l < res && res <= m0_u){
		return 0;
	}
	if(m1_l < res && res <= m1_u){
		return 1;
	}
	if(m2_l < res && res <= m2_u){
		return 2;
	}
	if(m3_l < res && res <= m3_u){
		return 3;
	}
	if(m4_l < res && res <= m4_u){
		return 4;
	}
	if(m5_l < res && res <= m5_u){
		return 5;
	}
	if(m6_l < res && res <= m6_u){
		return 6;
	}
	if(m7_l < res && res <= m7_u){
		return 7;
	}
	if(m8_l < res && res <= m8_u){
		return 8;
	}

	if(res > 750 && res < 770) return 0; //1337 h4x
	if(res > 560 && res < 580) return 1; //and 2 lol
	if(res > 370 && res < 390) return 3; 

	return -1;
}
void IR::setMode(int m){
	this->mode = m;
	if(this->mode == RECEIVER){
		this->enableAll();
	}
	else if(this->mode == SENDER){
	}
}
int IR::getMode(){return this->mode;}
