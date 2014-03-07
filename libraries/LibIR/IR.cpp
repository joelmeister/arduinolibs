#include <IR.h>

#define RECEIVER 1
#define SENDER 2
#define ERROR 3

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
		Serial.print("ERROR SELECTING IR PIN");
	}
}

void IR::sendMessage(int msg){
	if(this->mode == RECEIVER) return;
	switch (msg){
		case 0:
			this->irSend.sendRaw((unsigned int *)msg0,5,38/*kHz*/);
			break;
		case 1:break;
		case 2:break;
		case 3:break;
		case 4:break;
		default:break;
	}
}
int IR::getMessage(){
	if(this->mode == SENDER) return;
    this->irRecv.resume(); // Receive the next value
    unsigned long max_time = millis() + 30000;
    // Wait for decode or timeout
    while (!this->irRecv.decode(&this->results)) {
      if (millis() > max_time) {
        Serial.println("Timeout receiving data");
        this->mode = ERROR;
        return -1;
      }
    }
	return this->parseResult();
}
int IR::parseResult(){
	switch(this->results.value){
		case 0xFF: /*put a signal here*/
			break;
		default:break;
	}

	return -1;
}
void IR::setMode(int m){
	this->mode = m;
	if(this->mode == RECEIVER){
		this.irRecv.enableIRIn(38);//kHz
	}
	else if(this->mode == SENDER){
		this.irSend.enableIROut(38);
	}
}
int IR::getMode(){return this->mode;}
