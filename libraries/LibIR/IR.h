#ifndef IRLIB_H
#define IRLIB_H

#include <Arduino.h>
#include <IRremote.h>
#include <IRremoteInt.h>
class IR{
public:
	IR();
	~IR();
	IRsend irSend;
	IRrecv irRecv0;//change for irPin
	IRrecv irRecv1;//change for irPin
	IRrecv irRecv2;//change for irPin
	IRrecv irRecv3;//change for irPin
	decode_results results;
	void setup();
	void sendMessage(int msg);
	int getMessage();
	int getResult(IRrecv &irrecv);
	int parseResult(int res,int dir);
	void setMode(int mode);
	int getMode();
	void enableAll();
	void resumeAll();
	bool front(), left(), right(), back();
	static const unsigned int msg0[8];
	static const unsigned int msg1[8];
	static const unsigned int msg2[8];
	static const unsigned int msg3[8];
	static const unsigned int msg4[8];
	static const unsigned int msg5[8];
	static const unsigned int msg6[8];
	static const unsigned int msg7[8];
	static const unsigned int msg8[8];
private:
	int send_pin;
	int recv_pin0;
	int recv_pin1;
	int recv_pin2;
	int recv_pin3;
	int mode;
	bool fr, le, ba, ri;
	short int 
		m0_l, m0_u, m1_l, m1_u,
		m2_l, m2_u,	m3_l, m3_u,
		m4_l, m4_u,	m5_l, m5_u,
		m6_l, m6_u,	m7_l, m7_u,
		m8_l, m8_u; /*lower and upper bounds*/
};

#endif //#ifndef IRLIB_H
