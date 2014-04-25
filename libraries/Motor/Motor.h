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
    void forward(int speed);
    void backward(int);
    void turnLeft(int);
    void turnRight(int);
    void forward(int, int);
    void backward(int, int);
    void turnLeft(int, int);
    void turnRight(int, int);
    void forwardDistance(int time);
    void turnRightDistance(int time);
    void turnLeftDistance(int time);
    //void turnLeft90();
  private:
    int wheel0;
    int wheel1;
    int motorENA;
};

#endif