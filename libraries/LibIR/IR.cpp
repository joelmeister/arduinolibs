#include <IR.h>

#define RECEIVER 0
#define SENDER 1
#define ERROR 2
const unsigned int msg0[] = {0x1,0x2,0x3,0x4,0x5};//replace with message name and real bytecode
IR::IR(int p)
	: pin(p),irRecv(p)
{}

IR::~IR(){}

int IR::getPin(){ return this->pin; }
void IR::setup(int m){ 
	this->mode = m;
	if(m==RECEIVER){
		irRecv.enableIRIn();
    	Serial.println("Receiver mode");
	}else if(m==SENDER){
		//sender mode?
	}else{
		Serial.println("ERROR SELECTING IR PIN");
	}
}
/*
	sends a custom message, up to 8 bits in length (<256)
*/
void IR::sendCustomMessage(int data, int len){
	if(this->mode == RECEIVER) {
		Serial.println("You are receiver...don't send");
		return;
	}
	this->irSend.sendNEC(data,len);
}
/*
	sends a message from a list of preset messages
	the message is 1 shifted left by the input value
*/
void IR::sendMessage(int msg){
	if(this->mode == RECEIVER) {
		Serial.println("You are receiver...don't send");
		return;
	}
	switch (msg){
		case 0:
			this->irSend.sendNEC(0x1,8);
			break;
		case 1:
			this->irSend.sendNEC(0x2,8);
			break;
		case 2:
			this->irSend.sendNEC(0x4,8);
			break;
		case 3:
			this->irSend.sendNEC(0x8,8);
			break;
		case 4:
			this->irSend.sendNEC(0x10,8);
			break;
		case 5:
			this->irSend.sendNEC(0x20,8);
			break;
		default:
			Serial.println("unknown message..sending 0x40");
			this->irSend.sendNEC(0x40,8);
			break;
	}
	delay(100);
}
int IR::getMessage(){
	if(this->mode == SENDER) {
		Serial.println("You are sender..don't receive");
		return -1;
	}
	if(this->irRecv.decode(&this->results)){
		Serial.print("Data: ");
		Serial.println(this->results.value, HEX);
    	this->irRecv.resume(); // Receive the next value
	}

	return this->parseResult();//could just return results.value?
}
/*might not need this function*/
int IR::parseResult(){
	switch(this->results.value){
		case 0x1: /*put a signal here*/
			break;
		case 0x2: /*put a signal here*/
			break;
		case 0x4: /*put a signal here*/
			break;
		case 0x8: /*put a signal here*/
			break;
		case 0x10: /*put a signal here*/
			break;
		case 0x20: /*put a signal here*/
			break;
		default:
			break;
	}

	return this->results.value;
}
void IR::setMode(int m){
	this->mode = m;
	if(this->mode == RECEIVER){
		this->irRecv.enableIRIn();
	}
	else if(this->mode == SENDER){
		this->irSend.enableIROut(38);//kHz
	}
}
int IR::getMode(){return this->mode;}
