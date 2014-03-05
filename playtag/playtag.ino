//demo

#include <Tag.h>//robot is has tag functions

Tag robot(false);//robot is not it
void setup(){
  //todo
}
void loop(){
  delay(50); //50 ms
  if(robot.isIt()){
     //look for other robots
     //if robot is in center IR
       //move forward
     //else if right/left
       //turn right/left
     //else
       //turn right
       //(keep track of time without finding robot)
     //if distance < 10 
       //tell other robot it is it (IR pulse?)
       
  } else {
     //run away from it robot
     //if (IR tagged pulse)
       //robot.tagged()
     //else if obstacle in view
       //turn away
     //else
       //go straight
  }
}
