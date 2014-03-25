#include <Arduino.h>
#include <IRremote.h>
#include <IRremoteInt.h>

class IR{
public:
	IR(int p=1);
	~IR();
	IRsend irSend;
	IRrecv irRecv;//change for irPin
	decode_results results;
	int getPin();
	void setup(int mode=OUTPUT);
	void sendMessage(int msg);
	int getMessage();
	int parseResult();
	void setMode(int mode);
	int getMode();
private:
	int pin;
	int mode;
};
