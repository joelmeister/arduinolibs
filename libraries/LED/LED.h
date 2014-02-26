#ifndef _LED_H
#define _LED_H
class LED{
public:
	LED(int p, int type);
	virtual ~LED();
	void LEDinit();
	void turnOn();
	void turnOff();
private:
	int pin;
	int io;
};
#endif
