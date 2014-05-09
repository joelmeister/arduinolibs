#include <Average.h>
#include <ColorSense.h>
#include <NewPing.h>
#include <Motor.h>
#include <IRremote.h>

#define FORWARD_DIST 800
#define TURN_90_DIST_LEFT 1110
#define TURN_90_DIST_RIGHT 1110
//#include <Ultrasonic.h>


//int S2 = 2;//pinE
//int S3 = 3;//pinF
//int out = 4;//pinC
int maze_done;
//int LED = 15;//pinD

//Ultrasonic us;
NewPing sonar(7, 8, 200);
Motor motorTest(6,9,20);
//ColorSensor sensor(2, 3, 21);
ColorSense sensor(2, 3, 21, 4);

/*int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend irsend;*/

void setup() {
	//TCS3200setup();
	Serial.begin(115200);
        //sensor.CalibrateRoom();
        //maze_done = 0;
        
  //pinMode(A0, OUTPUT);
        //irrecv.enableIRIn(); // Start the receiver
	//Serial.print("\n\n\nready\n\n\n");
	//delay(100);
}
unsigned int buf[10] = {1000,500,1000,500,1000,500,1000,500};

void loop() {
  RedGreenLight();
}

void RedGreenLight(){
  int color;
  color = sensor.GetColor();

  
  if(color == 0){
    motorTest.stop();
  }
  else if(color == 1){
    motorTest.forward();
  }
  else if(color == 2){
    motorTest.turnRight();
  }
  Serial.print(color);
}

