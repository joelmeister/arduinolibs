#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H
#include <NewPing.h>
#include <arduino.h>
class Ultrasonic{
public:
	Ultrasonic();
	virtual ~Ultrasonic();
	unsigned int getDistance();
private:
	unsigned int distance;
	NewPing sonar;
};
#endif
