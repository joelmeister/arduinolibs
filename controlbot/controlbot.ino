#include <IR.h>
#include <IRremote.h>

#define REC 1
#define SEND 2
#define ERR 3
//this is from the robot side


//function declarations
IR_t decodeIR();
void handleSend(IR_t sig);

//init some things
const int IRpin = A0;
IR ir(IRpin); //pin ir is connected to

void setup(){
  //setup pins for things and stuff
  ir.setup(REC);  //rec=1,send=2,err=3
}
void loop(){
  delay(50);
  if(ir.getMode() == REC){
    int msg = ir.getMessage();
    handleSend(decoded);
  }
  else if(ir.getMode() == SEND){
    
  }else{}
}

void handleSend(int sig){
  switch(sig){
   case(0):
     motor.forward();
     break;
   case(1):
     motor.backward();
     break;
   case(2):
     motor.left();
     break;
   case(3):
     motor.right();
     break;
   default:
     motor.disable();
     break; 
  }
}
