#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(int pin1, int pin2, int pin3);
    void stop();
    void forward();
    void backward();
    void turnLeft();
    void turnRight();
    void setForwardSpeed(int speed);
    //void turnLeft90();
  private:
    int wheel0;
    int wheel1;
    int motorENA;
};

#endif