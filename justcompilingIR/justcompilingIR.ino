
#include <IR.h>
#include <IRremote.h>
#include <IRremoteInt.h>

#define FWD 0x1
#define BACK 0x2
#define LEFT 0x4
#define RIGHT 0x8

const int led = 9;
const int recPin = 10;
IR ir(recPin);

void setup(){
  Serial.begin(9600);
  ir.setup();//default OUTPUT
  pinMode(led, OUTPUT);
}

void loop(){
   digitalWrite(led,LOW);
  ir.sendMessage(FWD);//sends and delays 100
   digitalWrite(led,HIGH);
  delay(100);
}

