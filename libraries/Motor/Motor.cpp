#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int pin1, int pin2, int pin3)
{
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  wheel0 = pin1;
  wheel1 = pin2;
  motorENA = pin3;
}

void Motor::stop() //--L
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, LOW);  
}

void Motor::forward() //00H
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, HIGH);  
}

void Motor::turnRight() //01H
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, HIGH);
  digitalWrite(motorENA, HIGH);   
}

void Motor::turnLeft() //10H
{
  digitalWrite(wheel0, HIGH);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, HIGH); 
}

void Motor::backward() //11H
{
  digitalWrite(wheel0, HIGH);   
  digitalWrite(wheel1, HIGH);
  digitalWrite(motorENA, HIGH);   
}

/*void Motor::turnLeft90() //10H
{
  turnLeft();

}*/


