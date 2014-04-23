#include <IR.h>
#include <IRremote.h>
IR ir;
int LED = 17;
int b0 = 16;
int b1 = 10;
int b2 = 7;
int b3 = 8;
int b4 = 4;

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
    ir.sendMessage(0); Serial.print("s0");
    //has delay at the end 
  }
  else if(s1 == HIGH){
    ir.sendMessage(1); Serial.print("s1");
  }
  else if(s2 == HIGH){
    ir.sendMessage(3); Serial.print("s2");
  }
  else if(s3 == HIGH){
    ir.sendMessage(5); Serial.print("s3");
  }
  else if(s4 == HIGH){
    ir.sendMessage(7); Serial.print("s4");
  }
  else{
    ir.sendMessage(8); 
  }
  digitalWrite(LED,LOW);
  delay(100);
}

