#include <IR.h>
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3
#define RECEIVER 0
#define SENDER 1
#define ERROR 2

const unsigned int IR::msg0[8] 
    = {500,500,500,500,500,500,500,500};                                                
const unsigned int IR::msg1[8]
    = {500,500,500,500,500,500,500,1000};                                               
const unsigned int IR::msg2[8]
    = {500,500,500,500,500,500,1000,1000};                                              
const unsigned int IR::msg3[8]
    = {500,500,500,500,500,1000,1000,1000};                                             
const unsigned int IR::msg4[8]
    = {500,500,500,500,1000,1000,1000,1000};                                            
const unsigned int IR::msg5[8]
    = {500,500,500,1000,1000,1000,1000,1000}; 
const unsigned int IR::msg6[8]
    = {500,500,1000,1000,1000,1000,1000,1000}; 
const unsigned int IR::msg7[8]
    = {500,1000,1000,1000,1000,1000,1000,1000}; 
const unsigned int IR::msg8[8]
    = {1000,1000,1000,1000,1000,1000,1000,1000}; 

IR::IR()
	: irSend(),irRecv0(10),irRecv1(16),
		irRecv2(14),irRecv3(15),
		send_pin(5), recv_pin0(10), recv_pin1(16),
		recv_pin2(14), recv_pin3(15)
{
	setup();
/*these might change*/
	m0_l = 72; m0_u = 86;
	m1_l = 87; m1_u = 96;
	m2_l = 97; m2_u = 106;
	m3_l = 107; m3_u = 116;
	m4_l = 117; m4_u = 126;
	m5_l = 127; m5_u = 136;
	m6_l = 137; m6_u = 146;
	m7_l = 147; m7_u = 156;
	m8_l = 157; m8_u = 166;
	enableAll();
}

IR::~IR(){}

void IR::setup(){ }
/*
	sends a message from a list of preset messages
*/
void IR::sendMessage(int msg){
	if(this->mode == RECEIVER) {
		Serial.println("You are receiver...don't send");
		return;
	}
	switch (msg){
		case 0:
			this->irSend.sendRaw((unsigned int*)IR::msg0,8,38);
			break;
		case 1:
			this->irSend.sendRaw((unsigned int*)IR::msg1,8,38);
			break;
		case 2:
			this->irSend.sendRaw((unsigned int*)IR::msg2,8,38);
			break;
		case 3:
			this->irSend.sendRaw((unsigned int*)IR::msg3,8,38);
			break;
		case 4:
			this->irSend.sendRaw((unsigned int*)IR::msg4,8,38);
			break;
		case 5:
			this->irSend.sendRaw((unsigned int*)IR::msg5,8,38);
			break;
		default:
			this->irSend.sendRaw((unsigned int*)IR::msg8,8,38);
			break;
	}
	this->resumeAll();
	delay(100);
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
	else if (irRecv1.decode(&results)) {
		le = true;
		int res = getResult(irRecv1);
		return parseResult(res, LEFT);
	}
	else if (irRecv2.decode(&results)) {
		ri = true;
		int res = getResult(irRecv2);
		return parseResult(res, RIGHT);
	}
	else if (irRecv3.decode(&results)) {
		ba = true;
	    int res = getResult(irRecv3);
	    return parseResult(res, BACK);
	}
	return -1;
}
int IR::getResult(IRrecv &irrecv){
    //digitalWrite(LED,LOW);
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
    Serial.println(sum-results.rawbuf[0]);
#endif
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0] ; //-results.rawbuf[results.rawlen-1];
}
int IR::parseResult(int res, int dir){
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
