#include <IR.h>
#include <IRremote.h>
IR ir;
int LED = A0;
int b1 = 2;
int b2 = 3;
int b3 = 4;
int b4 = 6;
int b5 = 7;

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(b4,INPUT);
  pinMode(b5,INPUT);
}
void loop() {
  int s1 = digitalRead(b1);
  int s2 = digitalRead(b2);
  int s3 = digitalRead(b3);
  int s4 = digitalRead(b4);
  int s5 = digitalRead(b5);
  delay(100);
  if(s1 == HIGH){
    ir.sendMessage(0);//has delay at the end
  }
  else if(s2 == HIGH){
    ir.sendMessage(1);
  }
  else if(s3 == HIGH){
    ir.sendMessage(2);
  }
  else if(s4 == HIGH){
    ir.sendMessage(3);
  }
  else if(s5 == HIGH){
    ir.sendMessage(4);
  }
  else{
    ir.sendMessage(8);
  }
  delay(100);
}

