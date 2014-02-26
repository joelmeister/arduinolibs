#include <LED.h>
#include <Arduino.h>
LED::LED(int p, int type=OUTPUT)
	:pin(p),io(type)
{
}
LED::~LED()
{}
void LED::LEDinit(){
	pinMode(this->pin, this->io);
}
void LED::turnOn(){
	digitalWrite(this->pin,HIGH);
}
void LED::turnOff(){
	digitalWrite(this->pin,LOW);
}
