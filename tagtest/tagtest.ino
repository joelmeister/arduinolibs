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
#define FRONT 0
#define LEFT 1
#define RIGHT 2
#define BACK 3

int LED=3;
int LED1 = A3;
int LED2 = A2;
int LED3 = A1;
int LED4 = A0;

int RECV1 = 10;
int RECV2 = 16;
int RECV3 = 14;
int RECV4 = 15;
int MODE = SEND; //0 for send
int IT = 0;

IRrecv irrecv1(RECV1);
IRrecv irrecv2(RECV2);
IRrecv irrecv3(RECV3);
IRrecv irrecv4(RECV4);
IRsend irsend;
decode_results results;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


unsigned int not_it_buf[9] = {500,500,500,500,500,500,500,500}; //82
unsigned int ack_buf[9] = {500,500,500,500,500,500,500,1000}; //92
unsigned int ack2_buf[9] = {500,500,500,500,500,500,1000,1000}; //102- not sure if we should use
unsigned int tag_buf[9] = {500,500,500,500,500,1000,1000,1000}; //112


int use_test_circuit =1;

void setup()
{
  Serial.begin(9600);
  irrecv1.enableIRIn(); // Start the receiver
  irrecv2.enableIRIn(); // Start the receiver
  irrecv3.enableIRIn(); // Start the receiver
  irrecv4.enableIRIn(); // Start the receiver
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}
void loop() {
  getIRMessage();
  if (!IT){
    moveSomewhere(); 
  }
  digitalWrite(LED,HIGH);
  delay(50);
}
void moveSomewhere(){
  if(!IT){
    irsend.sendRaw(not_it_buf,9,38);
    resumeAll();
  }
  //INSERT MOVE ALGO HERE
}
void tagBot(){
   irsend.sendRaw(tag_buf, 9, 38);
   resumeAll();
}
void parseResult(int res, int dir){
  if(res > 87 && res < 96 && IT){
    //got ack message
    IT=0;
   irsend.sendRaw(ack2_buf, 9, 38);//NEW IT -> OLD IT
   resumeAll();
   //run away ?
   LEDOn(LED2);
  }
  else if(res > 97 && res < 106 && !IT){
    //got ack2 message
  }
  else if(res > 77 && res < 86 && IT){
     //8x500 us message - sees a robot that isn't it
     if(dir==FRONT || use_test_circuit == 1){
       if( sonar.ping() / US_ROUNDTRIP_CM  < 10 || use_test_circuit == 1){
        // < 10 cm
         tagBot();
         LEDOn(LED1);
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
  else if(res > 107 && res < 116 && !IT)
  {
    //8x1000 us message - receives tagged message
    irsend.sendRaw(ack_buf, 9, 38);
    IT=1;
    resumeAll();
    LEDOn(LED3);
  }
}
void getIRMessage(){
  if (irrecv1.decode(&results)) {
    digitalWrite(LED,LOW);
    int res = getResult(irrecv1);
    parseResult(res, FRONT);
  }
  else if (irrecv2.decode(&results)) {
    digitalWrite(LED,LOW);
    int res = getResult(irrecv2);
    parseResult(res, LEFT);
  }
  else if (irrecv3.decode(&results)) {
    digitalWrite(LED,LOW);
    int res = getResult(irrecv3);
    parseResult(res, RIGHT);
  }
  else if (irrecv4.decode(&results)) {
    digitalWrite(LED,LOW);
    int res = getResult(irrecv4);
    parseResult(res, BACK);
  }else{
   //moveLeft();//? 
  }
}
void resumeAll(){
    irrecv1.enableIRIn(); // Start the receiver
    irrecv2.enableIRIn(); // Start the receiver
    irrecv3.enableIRIn(); // Start the receiver
    irrecv4.enableIRIn(); // Start the receiver
    irrecv1.resume(); // Start the receiver
    irrecv2.resume(); // Start the receiver
    irrecv3.resume(); // Start the receiver
    irrecv4.resume(); // Start the receiver
}
void LEDOn(int pin){
       digitalWrite(LED1, LOW);
       digitalWrite(LED2, LOW);
       digitalWrite(LED3, LOW);
       digitalWrite(LED4, LOW);
       if(pin != -1){
          digitalWrite(pin, HIGH); //overwrite previous 
       }
}
int getResult(IRrecv &irrecv){
    delay(50);
    //Serial.println(results.value, HEX);
    int i=0;
    int sum=0;
    for(i=0;i<results.rawlen;i++){
     sum+=results.rawbuf[i];
     Serial.print(results.rawbuf[i],DEC); 
     Serial.print(" "); 
    }
    Serial.println(sum-results.rawbuf[0]-results.rawbuf[results.rawlen-1]);
    irrecv.resume(); // Receive the next value
    return sum-results.rawbuf[0] ; //-results.rawbuf[results.rawlen-1];
}
