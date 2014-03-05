#include <IR.h>
#include <IRremote.h>

//this is from the robot side

typedef enum IRSignal {s0, s1, s2, s3} IR_t;

const int IRpin = A0;

IR_t decodeIR(); //func declaration for IR decode

void setup(){
  //setup pins for things and stuff
}
void loop(){
  delay(50);
  IR_t ir = decodeIR();
  switch(ir){
   case(s0):break;
   case(s1):break;
   case(s2):break;
   case(s3):break;
   default:break; 
  }
}

IR_t decodeIR(){
 IR_t decoded = s0;
 //decode the signal
  return decoded; 
}
