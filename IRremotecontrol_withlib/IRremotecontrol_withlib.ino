#include <IR.h>
#include <IRremote.h>
IR ir;
int LED = 17;
int b0 = 2;
int b1 = 3;
int b2 = 4;
int b3 = 6;
int b4 = 7;

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(b0,INPUT);
  pinMode(b1,INPUT);
  pinMode(b2,INPUT);
  pinMode(b3,INPUT);
  pinMode(b4,INPUT);
}
void loop() {
  int s0 = digitalRead(b0);
  int s1 = digitalRead(b1);
  int s2 = digitalRead(b2);
  int s3 = digitalRead(b3);
  int s4 = digitalRead(b4);
  digitalWrite(LED,HIGH);
  delay(100);
  if(s0 == HIGH){
    ir.sendMessage(0);//has delay at the end
  }
  else if(s1 == HIGH){
    ir.sendMessage(1);
  }
  else if(s2 == HIGH){
    ir.sendMessage(2);
  }
  else if(s3 == HIGH){
    ir.sendMessage(3);
  }
  else if(s4 == HIGH){
    ir.sendMessage(4);
  }
  else{
    ir.sendMessage(8);
  }
  digitalWrite(LED,LOW);
  delay(100);
}

