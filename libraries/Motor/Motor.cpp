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

void Motor::turnLeft() //01H
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, HIGH);
  digitalWrite(motorENA, HIGH);   
}

void Motor::turnRight() //10H
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

void Motor::forward(int speed) //00H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, speed);   
  analogWrite(wheel1, speed);
  digitalWrite(motorENA, HIGH);  
}
void Motor::turnLeft(int speed) //01H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, speed);   
  analogWrite(wheel1, -speed);
  digitalWrite(motorENA, HIGH);   
}

void Motor::turnRight(int speed) //10H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, -speed);   
  analogWrite(wheel1, speed);
  digitalWrite(motorENA, HIGH); 
}

void Motor::backward(int speed) //11H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, -speed);   
  analogWrite(wheel1, -speed);
  digitalWrite(motorENA, HIGH);   
}

void Motor::forward(int speed, int time) //00H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, speed);   
  analogWrite(wheel1, speed);
  digitalWrite(motorENA, HIGH);
  delay(time);
}
void Motor::turnLeft(int speed, int time) //01H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, speed);   
  analogWrite(wheel1, -speed);
  digitalWrite(motorENA, HIGH);   
  delay(time);
}

void Motor::turnRight(int speed, int time) //10H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, -speed);   
  analogWrite(wheel1, speed);
  digitalWrite(motorENA, HIGH); 
  delay(time);
}

void Motor::backward(int speed, int time) //11H
{
  speed = -((speed % 127) - 126);
  analogWrite(wheel0, -speed);   
  analogWrite(wheel1, -speed);
  digitalWrite(motorENA, HIGH);   
  delay(time);
}

void Motor::forwardDistance(int time) //go forward for time then stop
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, HIGH);  

  delay(time);

  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, LOW);  

  
  delay(100);
}

void Motor::turnRightDistance(int time) //turn right for time then stop
{
  digitalWrite(wheel0, HIGH);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, HIGH);  

  delay(time);

  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, LOW);  

  delay(100);
}

void Motor::turnLeftDistance(int time) //turn left for time then stop
{
  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, HIGH);
  digitalWrite(motorENA, HIGH);  

  delay(time);

  digitalWrite(wheel0, LOW);   
  digitalWrite(wheel1, LOW);
  digitalWrite(motorENA, LOW);  

  delay(100);
}

/*void Motor::turnLeft90() //10H
{
  turnLeft();

}*/


