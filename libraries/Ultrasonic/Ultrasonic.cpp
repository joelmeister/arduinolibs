#include <Ultrasonic.h>

Ultrasonic::Ultrasonic()
	:distance(0),sonar(7,8,200)
{
}
Ultrasonic::~Ultrasonic()
{
}

unsigned int Ultrasonic::getDistance()
{
	this->distance = this->sonar.ping_in();
	return this->distance;
}
