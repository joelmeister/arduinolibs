#include <Average.h>
#include <NewPing.h>
#include <Motor.h>

#define FORWARD_DIST 800
#define TURN_90_DIST_LEFT 1110
#define TURN_90_DIST_RIGHT 1110

NewPing sonar;//(7, 8, 200);
Motor motorTest;//(6,9,20);

void setup() {
	Serial.begin(115200);
}

void loop() {
   new_maze();
}

void new_maze(){
    motorTest.forwardDistance(FORWARD_DIST);
    motorTest.turnRightDistance(TURN_90_DIST_RIGHT);
    if(sonar.ping_in() < 3){
      motorTest.turnLeftDistance(TURN_90_DIST_LEFT);
      
      if(sonar.ping_in() < 3){           
        motorTest.turnLeftDistance(TURN_90_DIST_LEFT);
        if(sonar.ping_in() < 3){           
          motorTest.turnLeftDistance(TURN_90_DIST_LEFT);
        }
      }
    }
}
