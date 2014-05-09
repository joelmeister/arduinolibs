#include <IR.h>
#define FRONT 0
#define BACK 1
#define LEFT 2
#define RIGHT 3
#define R0 10 //front
#define R1 16
#define R2 14
#define R3 15
#define SENDPIN 5

#define SMALL 5000 //mark/space in send message
#define LARGE 10000 //mark/space in send message

#define DEBUG
IR::IR()
	: irSend(),irRecv0(R0),irRecv1(R1),
		irRecv2(R2),irRecv3(R3),
		send_pin(SENDPIN), recv_pin0(R0), recv_pin1(R1),
		recv_pin2(R2), recv_pin3(R3)
{
	setup();
/*these might change*/
/*
	m0_l = (SMALL*8+LARGE*0)/1000-2; m0_u = (SMALL*8+LARGE*0)/1000+2;
	m1_l = (SMALL*7+LARGE*1)/1000-2; m1_u = (SMALL*7+LARGE*1)/1000+2;
	m2_l = (SMALL*6+LARGE*2)/1000-2; m2_u = (SMALL*6+LARGE*2)/1000+2;
	m3_l = (SMALL*5+LARGE*3)/1000-2; m3_u = (SMALL*5+LARGE*3)/1000+2;
	m4_l = (SMALL*4+LARGE*4)/1000-2; m4_u = (SMALL*4+LARGE*4)/1000+2;
	m5_l = (SMALL*3+LARGE*5)/1000-2; m5_u = (SMALL*3+LARGE*5)/1000+2;
	m6_l = (SMALL*2+LARGE*6)/1000-2; m6_u = (SMALL*2+LARGE*6)/1000+2;
	m7_l = (SMALL*1+LARGE*7)/1000-2; m7_u = (SMALL*1+LARGE*7)/1000+2;
	m8_l = (SMALL*0+LARGE*8)/1000-2; m8_u = (SMALL*0+LARGE*8)/1000+2;
*/
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
		unsigned int msg[8] = {SMALL,SMALL,SMALL,LARGE,SMALL,SMALL,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 2){
		unsigned int msg[8] = {SMALL,SMALL,SMALL,LARGE,LARGE,SMALL,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 3){
		unsigned int msg[8] = {SMALL,SMALL,LARGE,LARGE,LARGE,SMALL,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if(msg == 4){
		unsigned int msg[8] = {SMALL,SMALL,LARGE,LARGE,LARGE,LARGE,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if( msg == 5){
		unsigned int msg[8] = {SMALL,LARGE,LARGE,LARGE,LARGE,LARGE,SMALL,SMALL};
		this->irSend.sendRaw(msg,9,38);
	}
	else if( msg == 6){
		unsigned int msg[8] = {SMALL,LARGE,LARGE,LARGE,LARGE,LARGE,LARGE,SMALL};
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
    delay(100);
	
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
	if(results.rawlen < 10){
#ifdef DEBUG
		Serial.println("bad message size: ");
		Serial.println(results.rawlen);
#endif
		return -1;
	}
    return sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]; 
}
int IR::parseResult(int res, int dir){
#ifdef DEBUG
	Serial.print("Direction: ");
	Serial.println(dir);
#endif
	if(m0_l <= res && res <= m0_u){
		Serial.println("received 0");
		return 0;
	}
	if(m1_l <= res && res <= m1_u){
		Serial.println("received 1");
		return 1;
	}
	if(m2_l <= res && res <= m2_u){
		Serial.println("received 2");
		return 2;
	}
	if(m3_l <= res && res <= m3_u){
		Serial.println("received 3");
		return 3;
	}
	if(m4_l <= res && res <= m4_u){
		Serial.println("received 4");
		return 4;
	}
	if(m5_l <= res && res <= m5_u){
		Serial.println("received 5");
		return 5;
	}
	if(m6_l <= res && res <= m6_u){
		Serial.println("received 6");
		return 6;
	}
	if(m7_l <= res && res <= m7_u){
		Serial.println("received 7");
		return 7;
	}
	if(m8_l <= res && res <= m8_u){
		Serial.println("received 8");
		return 8;
	}

	if(res > 750 && res < 770) return 0; //1337 h4x
	if(res > 560 && res < 580) return 1; //1 and 2 lol
	if(res > 370 && res < 390) return 3; 

	return -1;
}
void IR::setMode(int m){
	this->mode = m;
}
int IR::getMode(){return this->mode;}
