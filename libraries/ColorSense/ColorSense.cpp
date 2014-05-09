#include "Arduino.h"
#include "ColorSense.h"
#include <Average.h>
#define PIND	2
#define PINE	3
#define PINF	21
#define PINOUT	4

ColorSense::ColorSense()
{
	ColorSense(PIND,PINE,PINF, PINOUT);
}
ColorSense::ColorSense(int pin1, int pin2, int pin3, int pin4)
{
	S2 = pin1;
	S3 = pin2;
	LED = pin3;
	OUT = pin4;
	//initialize pins
	pinMode(pin3,OUTPUT); //LED pinD
	//color mode selection
	pinMode(pin1,OUTPUT); //S2 pinE
	pinMode(pin2,OUTPUT); //S3 pinF
	//output pin
	pinMode(pin4,INPUT); 
}

void ColorSense::NoFilter() { //Select no filter
  digitalWrite(S2,HIGH); 
  digitalWrite(S3,LOW);
  delay(50);
}
void ColorSense::RedFilter() { //Select red filter
  digitalWrite(S2,LOW); 
  digitalWrite(S3,LOW);
  delay(50);
}
void ColorSense::GreenFilter() { //Select green filter
  digitalWrite(S2,HIGH); 
  digitalWrite(S3,HIGH);
  delay(50);
}
void ColorSense::BlueFilter() { //Select blue filter
  digitalWrite(S2,LOW); 
  digitalWrite(S3,HIGH);
  delay(50);
}

int ColorSense::GetColor() { //0=white, 1=orange, 2=yellow, 3=red, 4=green, 5=blue, 6=object out of range

	float FrequencyClear,FrequencyRed,FrequencyGreen,FrequencyBlue;
	int PercentageRed,PercentageGreen,PercentageBlue;

	String color;

	digitalWrite(LED, HIGH);

	ColorSense::NoFilter();
	FrequencyClear=pulseIn(OUT,LOW,80000); // Frequency in kHz
	ColorSense::RedFilter();
	FrequencyRed=pulseIn(OUT,LOW,80000)/FrequencyClear; // Frequency in kHz
	ColorSense::GreenFilter();
	FrequencyGreen=pulseIn(OUT,LOW,80000)/FrequencyClear; // Frequency in kHz
	ColorSense::BlueFilter();
	FrequencyBlue=pulseIn(OUT,LOW,80000)/FrequencyClear; // Frequency in kHz

	//digitalWrite(LED, LOW);



	  //Output frequency blue, green, red percentage represents the ratio of the 
	  //respective color to the Clear channel absolute value:
	/*PercentageRed=int((FrequencyRed/FrequencyClear)*390.0);
	PercentageGreen=int((FrequencyGreen/FrequencyClear)*500.0);
	PercentageBlue=int((FrequencyBlue/FrequencyClear)*440.0);*/


	PercentageRed=int((FrequencyRed*432.2) - 60.51);
	PercentageGreen=int((FrequencyGreen*1416.67) - 340);
	PercentageBlue=int((FrequencyBlue*671.05) - 134.21);

	/*PercentageRed = PercentageRed - Red0;
	PercentageGreen = PercentageGreen - Green0;
	PercentageBlue = PercentageBlue - Blue0;*/


	if (PercentageRed < 0 ) {
	    PercentageRed = 0;
	}
	else if (PercentageRed > 255) {
	    PercentageRed = 255;
	}

	if (PercentageGreen < 0 ) {
	    PercentageGreen = 0;
	}
	else if (PercentageGreen > 255) {
	    PercentageGreen = 255;
	}

	if (PercentageBlue < 0 ) {
	    PercentageBlue = 0;
	}
	else if (PercentageBlue > 255) {
	    PercentageBlue = 255;
	}

	Serial.print("red ");
	Serial.println(FrequencyRed);
	Serial.print("green ");
	Serial.println(FrequencyGreen);
	Serial.print("blue ");
	Serial.println(FrequencyBlue);

	int ClosestColor;
	if(FrequencyRed < 1.6){
		ClosestColor = 0;
	}
	else if(FrequencyGreen < 3.4){
		ClosestColor = 2;
	}
	else if(FrequencyBlue < 3.4){
		ClosestColor = 1;
	}
	else{
		ClosestColor = 3;
	}

	/*if((PercentageRed > PercentageGreen) && (PercentageRed > PercentageBlue)){
		ClosestColor = 0;
	}
	else if((PercentageGreen > PercentageRed) && (PercentageGreen > PercentageBlue)){
		ClosestColor = 1;
	}
	else if((PercentageBlue > PercentageRed) && (PercentageBlue > PercentageGreen)){
		ClosestColor = 2;
	}
	else{
		ClosestColor = 3;
	}*/

/*
	 //Learned blue, green, red percentage values of different colors
	  int SavedColorRed[] = {56,38,39}; 
	  int SavedColorGreen[] = {22,31,26};
	  int SavedColorBlue[] = {27,29,35};
	  int ColorArray[3];
	  int ColorArrayDiff[3];
	  int i_color; 
	  int ClosestColor;
	  int MaxDiff;
	  int MinDiff=300;
	  if(FrequencyClear<.85)ClosestColor=4; // Object out of range
	  else {
	    for (i_color=0; i_color<3; i_color++) { //Find closest color
	      ColorArray[0]=abs(SavedColorRed[i_color]-PercentageRed);
	      ColorArray[1]=abs(SavedColorGreen[i_color]-PercentageGreen);
	      ColorArray[2]=abs(SavedColorBlue[i_color]-PercentageBlue);
	      MaxDiff=maximum(ColorArray,3);
	      ColorArrayDiff[i_color] = MaxDiff;
	      /*if (MaxDiff<4) {
	      //if (MaxDiff<MinDiff) {
	        //MinDiff=MaxDiff;
	        ClosestColor=i_color;
	       }
	       else{
	        ClosestColor=3;
	       }
	     }

	       if (ColorArrayDiff[0] < 4) {
	        ClosestColor=0;
	       }
	       else if (ColorArrayDiff[1] < 4) {
	        ClosestColor=1;
	       }
	       else if (ColorArrayDiff[2] < 4) {
	        ClosestColor=2;
	       }
	       else{
	        ClosestColor=3;
	       }
	   } 
	   	 if(ClosestColor==0) color = "red"; // red 
	     if(ClosestColor==1) color = "green"; // green
	     if(ClosestColor==2) color = "blue"; // blue
	     if(ClosestColor==3) color = "neither"; // not rgb
	     if(ClosestColor==4) color = "nothing in front"; // switch RGB LED off
*/

  	Serial.print("\n");

  	return ClosestColor;
} 

void ColorSense::CalibrateRoom() { //0=white, 1=orange, 2=yellow, 3=red, 4=green, 5=blue, 6=object out of range

	float FrequencyClear,FrequencyRed,FrequencyGreen,FrequencyBlue;
	int PercentageRed,PercentageGreen,PercentageBlue;

	String color;

	digitalWrite(LED, HIGH);

	ColorSense::NoFilter();
	FrequencyClear=500.0/pulseIn(OUT,LOW,10000); // Frequency in kHz
	ColorSense::RedFilter();
	FrequencyRed=500.0/pulseIn(OUT,LOW,10000); // Frequency in kHz
	ColorSense::GreenFilter();
	FrequencyGreen=500.0/pulseIn(OUT,LOW,10000); // Frequency in kHz
	ColorSense::BlueFilter();
	FrequencyBlue=500.0/pulseIn(OUT,LOW,10000); // Frequency in kHz

	Red0=int((FrequencyRed/FrequencyClear)*100.0);
	Green0=int((FrequencyGreen/FrequencyClear)*100.0);
	Blue0=int((FrequencyBlue/FrequencyClear)*100.0);


} 