#include <IR.h>
#include <IRremote.h>

IRsend irsend;
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
unsigned int buf1[10] = {500,500,500,500,500,500,500,500}; //82
unsigned int buf2[10] = {500,500,500,500,500,500,500,1000}; //92
unsigned int buf3[10] = {500, 500,500,500,500,500,1000,1000}; //102
unsigned int buf4[10] = {500, 500,500,500,500,1000,1000,1000}; //112
unsigned int buf5[10] = {500, 500,500,500,1000,1000,1000,1000}; //112
unsigned int buf6[10] = {1000,1000,1000,1000,1000,1000,1000,1000};//162
void loop() {
  int s1 = digitalRead(b1);
  int s2 = digitalRead(b2);
  int s3 = digitalRead(b3);
  int s4 = digitalRead(b4);
  int s5 = digitalRead(b5);
  digitalWrite(LED,HIGH);
  delay(100);
  if(s1 == HIGH){
    irsend.sendRaw(buf1,9,38);
  }
  else if(s2 == HIGH){
    irsend.sendRaw(buf2,9,38);
  }
  else if(s3 == HIGH){
    irsend.sendRaw(buf3,9,38);
  }
  else if(s4 == HIGH){
    irsend.sendRaw(buf4,9,38);
  }
  else if(s5 == HIGH){
    irsend.sendRaw(buf5,9,38);
  }
  else{
    irsend.sendRaw(buf6,9,38);
  }
  digitalWrite(LED,LOW);
  delay(100);
}

