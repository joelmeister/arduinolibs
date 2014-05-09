#include <Average.h>
#include <ColorSense.h>
#include <NewPing.h>
#include <Motor.h>

//Ultrasonic us;
NewPing sonar;//(7, 8, 200);
Motor motorTest;//(6,9,20);
ColorSense sensor;//(2, 3, 21, 4);


void setup() {
	Serial.begin(115200);
}

void loop() {
  RedGreenLight();
}

void RedGreenLight(){
  int color;
  color = sensor.GetColor();
  
  if(color == 0){
    motorTest.stop();
  }
  else if(color == 1){
    motorTest.forward();
  }
  else if(color == 2){
    motorTest.turnRight();
  }
  Serial.print(color);
}

