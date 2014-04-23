#include <IR.h>
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define RECEIVER 0
#define SENDER 1
#define ERROR 2

#define DEBUG
IR::IR()
	: irSend(),irRecv0(10),irRecv1(16),
		irRecv2(14),irRecv3(15),
		send_pin(5), recv_pin0(10), recv_pin1(16),
		recv_pin2(14), recv_pin3(15)
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
		//this->irSend.sendRaw((unsigned int*)IR::msg3,9,38);
		Serial.println("sent 0"); 
	}
	else if(msg == 1){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg3,9,38);
		Serial.println("sent 1"); 
	}
	else if(msg == 2){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,SMALL,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg5,9,38);
		Serial.println("sent 2"); 
	}
	else if(msg == 3){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,SMALL,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg3,9,38);
		Serial.println("sent 3"); 
	}
	else if(msg == 4){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,SMALL,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg3,9,38);
		Serial.println("sent 4"); 
	}
	else if( msg == 5){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg5,9,38);
		Serial.println("sent 5"); 
	}
	else{
		unsigned int msg[8] = {LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE};
		this->irSend.sendRaw(msg,9,38);
		//this->irSend.sendRaw((unsigned int*)IR::msg5,9,38);
		Serial.println("sent else"); 
	}
	
	this->resumeAll();
	delay(150);
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
		digitalWrite(A0, 0);//shitty
		digitalWrite(A1, 0);//shitty
		return parseResult(res, FRONT);
	}
	
	else if (irRecv2.decode(&results)) {
		le = true;
		int res = getResult(irRecv2);
		digitalWrite(A0, 1);//shitty
		digitalWrite(A1, 0);
		return parseResult(res, LEFT);
	}
	else if (irRecv3.decode(&results)) {
		ri = true;
	    int res = getResult(irRecv3);
		digitalWrite(A0, 1);//shitty
		digitalWrite(A1, 1);
	    return parseResult(res, RIGHT);
	}
	else if (irRecv1.decode(&results)) {
		ba = true;
		int res = getResult(irRecv1);
		digitalWrite(A0, 0);//shitty
		digitalWrite(A1, 1);//shitty
		return parseResult(res, BACK);
	}
	else{
		return -1;
	}
#ifdef DEBUG
	//Serial.println("Didn't receive a message");
#endif
	return -1;
}
int IR::getResult(IRrecv &irrecv){
    delay(50);
	
	if(results.rawlen != 10){
#ifdef DEBUG
		Serial.println("bad message size: ");
		Serial.println(results.rawlen);
#endif
		resumeAll();
		return -1;
	}
	
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
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]; 
}
int IR::parseResult(int res, int dir){
	Serial.println(dir);
	//Serial.println(" [f,b,l,r]");
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
