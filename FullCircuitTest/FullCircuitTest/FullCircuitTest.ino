#include <Average.h>
#include <ColorSense.h>
#include <NewPing.h>
#include <Motor.h>
#include <IRremote.h>

#define FORWARD_DIST 1250
#define TURN_90_DIST 1600
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
        sensor.CalibrateRoom();
        maze_done = 0;
        
  //pinMode(A0, OUTPUT);
        //irrecv.enableIRIn(); // Start the receiver
	//Serial.print("\n\n\nready\n\n\n");
	//delay(100);
}
unsigned int buf[10] = {1000,500,1000,500,1000,500,1000,500};


void loop() {
  //Color Sensor
  /*int color = sensor.GetColor();
  Serial.println(color);
  delay(2000);*/
  
  /*int num = sonar.ping_in();
  Serial.println(num);
  delay(2000);*/
  
  /*motorTest.setForwardSpeed(100);
  delay(1000);
  
  motorTest.setForwardSpeed(50);
  delay(1000);
  
  motorTest.setForwardSpeed(25);
  delay(1000);
  
  motorTest.setForwardSpeed(0);
  delay(1000);*/
  
  new_maze();
  
  
  
  //sensor.detectColor(out);
  //Serial.print(sensor.detectColor(out));
  //Serial.print("\n\n\n");
  //delay(2000);
  
  
  //Red Light Green Light
  //RedGreenLight();

  //delay(1000);
  
  
  
  
        /*Serial.print(sonar.ping_in());
	Serial.print("\n");
        
        if(sonar.ping_in() > 4){
          motorTest.forward();
        }
        else{   
          motorTest.stop();
        }*/
        //if(maze_done = 0){
          //mazeGame();
          //motorTest.turnLeft();
          //delay(340);
          //motorTest.stop();
          //delay(2000);
        //}
          //motorTest.turnRight();
          //delay(1000);          
          //motorTest.turnRight();
          //delay(1000);
//if(maze_done = 0){
          //maze();
          //motorTest.turnLeft();
          //delay(340);
          //motorTest.stop();
          //delay(2000);
        //}
        //delay(1000);
        //motorTest.backward();
        //delay(1000);
        //motorTest.turnRight();
        //delay(1000);
        //motorTest.turnLeft();
        //delay(1000);
        //motorTest.stop();
        //delay(2000);
	//delay(1000);

        /*if (irrecv.decode(&results)) {
          //digitalWrite(LED,LOW);
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
        }
      //digitalWrite(LED,HIGH);
      delay(50);
      irsend.sendRaw(buf,10,38);
      delay(100);*/
}

void mazeGame(){
        if(sonar.ping_in() > 1){
          motorTest.forward();
        }
        else{   
          motorTest.turnRight();
        }
}

int count;

void maze(){
        //int count;
        if(sonar.ping_in() > 5){  
          digitalWrite(A0, LOW); 
          motorTest.forward();
          delay(300);
          motorTest.stop();
          delay(100);
          count = 0;
        }
        else if(count == 0){  
          digitalWrite(A0, LOW); 
          motorTest.turnRight();
          delay(400);
          motorTest.stop();
          delay(500);
          count = 1;
          //maze(count);
        }
        else{        
          digitalWrite(A0, HIGH);   
          motorTest.turnRight();
          delay(400);
          motorTest.stop();
          delay(500);
          motorTest.turnRight();
          delay(400);
          motorTest.stop();
          delay(500);
          count = 0;
          //maze(count);
        }
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
  /*else if(sonar.ping_in() < 5){
    motorTest.turnRightDistance(TURN_90_DIST);
  }*/
  Serial.print(color);
}

void new_maze(){
        //int count;  
        motorTest.forwardDistance(FORWARD_DIST);
        motorTest.turnRightDistance(TURN_90_DIST);
        if(sonar.ping_in() < 2){           
          motorTest.turnLeftDistance(TURN_90_DIST);
          if(sonar.ping_in() < 2){           
            motorTest.turnLeftDistance(TURN_90_DIST);
            if(sonar.ping_in() < 2){           
              motorTest.turnLeftDistance(TURN_90_DIST);
            }
          }
        }
}


