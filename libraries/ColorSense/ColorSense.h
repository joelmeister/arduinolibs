#ifndef ColorSense_h
#define ColorSense_h

#include "Arduino.h"

class ColorSense
{
  public:
    ColorSense(int pin1, int pin2, int pin3, int pin4);
	int GetColor();
  void CalibrateRoom();
	void NoFilter();
	void RedFilter();
	void GreenFilter();
	void BlueFilter();
  private:
    int S2;
    int S3;
    int LED;
    int OUT;
    int Red0;
    int Green0;
    int Blue0;
};

#endif