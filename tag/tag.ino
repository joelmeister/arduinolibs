/*
tag
*/
#include <IRremote.h>
#include <NewPing.h>
#define SEND 0
#define RECEIVE 1
#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     9  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define WHEEL0 6
#define WHEEL1 9
#define MOTORENA 20
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3

int LED=3;
int RECV_PIN1 = 10;
int RECV_PIN2 = 16;
int RECV_PIN3 = 14;
int RECV_PIN4 = 15;
int MODE = SEND; //0 for send
int IT = 0;

IRrecv irrecv1(RECV_PIN1); //front
IRrecv irrecv2(RECV_PIN2); //left
IRrecv irrecv3(RECV_PIN3); //right
IRrecv irrecv4(RECV_PIN4); //back
IRsend irsend; //send on pin 5
decode_results results;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Motor motor(6,9,20);

unsigned int not_it_buf[9]	= {500,500,500,500,500,500,500,500};
unsigned int tag_buf[9]		= {500,500,500,500,500,500,500,1000}; //not sure if we should use
unsigned int ack_buf[9]		= {500,500,500,500,500,500,1000,1000};
unsigned int ack2_buf[9]	= {500,500,500,500,500,1000,1000,1000}; //not sure if we should use

void setup()
{
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  enableAll();//start the receivers
}
void loop() {
  getIRMessage();
  digitalWrite(LED,HIGH);
  delay(50);
  if (!IT){
    moveSomewhere();
  }
}
void moveSomewhere(){
  if(!IT){
    irsend.sendRaw(not_it_buf,9,38);
    resumeAll();
  }
  //INSERT MOVE ALGO HERE
  motor.
}
void tagBot(){
   irsend.sendRaw(tag_buf, 9, 38);
   resumeAll();
}
void parseResult(int res, int dir){
  if(res > 118 && res < 125 && IT){
    //got ack message
    IT=0;
   irsend.sendRaw(ack2_buf, 9, 38);//NEW IT -> OLD IT
   resumeAll();
   //run away ?
  }
  else if(res > 138 && res < 145 && !IT){
    //got ack2 message
  }
  else if(res > 78 && res < 85 && IT){
     //8x500 us message - sees a robot that isn't it
     if(dir==FRONT){
       if( sonar.ping() / US_ROUNDTRIP_CM  < 10){
        // < 10 cm
         tagBot();
       }else{
         //moveForward();
       }
     } else if(dir==LEFT){
       //moveLeft();
     } else if(dir==RIGHT){
       //moveRight();
     } else{
       //moveLeft();
     }
   }
  else if(res > 158 && res < 165 && !IT)
  {
    //8x1000 us message - receives tagged message
    irsend.sendRaw(ack_buf, 9, 38);
    IT=1;
    resumeAll();
  }
}
void getIRMessage(){
  if (irrecv1.decode(&results)) {
    int res = getResult(irrecv1);
    parseResult(res, FRONT);
  }
  else if (irrecv2.decode(&results)) {
    int res = getResult(irrecv2);
    parseResult(res, LEFT);
  }
  else if (irrecv3.decode(&results)) {
    int res = getResult(irrecv3);
    parseResult(res, RIGHT);
  }
  else if (irrecv4.decode(&results)) {
    int res = getResult(irrecv4);
    parseResult(res, BACK);
  }else{
   //moveLeft();//? 
  }
}
void resumeAll(){
	enableAll();
    irrecv1.resume(); // Start the receiver
    irrecv2.resume(); // Start the receiver
    irrecv3.resume(); // Start the receiver
    irrecv4.resume(); // Start the receiver
}
void enableAll(){
    irrecv1.enableIRIn(); // Start the receiver
    irrecv2.enableIRIn(); // Start the receiver
    irrecv3.enableIRIn(); // Start the receiver
    irrecv4.enableIRIn(); // Start the receiver
}
int getResult(IRrecv &irrecv){
    digitalWrite(LED,LOW);
    delay(50);
    int sum=0;
    for(int i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
#ifdef DEBUG
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" ");
#endif
    }
#ifdef DEBUG
    Serial.println(sum-results.rawbuf[0]);
#endif
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0] ; //-results.rawbuf[results.rawlen-1];
}
