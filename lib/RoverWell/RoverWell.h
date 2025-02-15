#ifndef RoverWell_h
#define RoverWell_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class RoverWell {
  public:
    RoverWell(Adafruit_PWMServoDriver pwm, int pin1, int pin2);
    void rotate(int speed);
    void breake();
    void release();
  private:
    Adafruit_PWMServoDriver _pwm;
    int _pin1;
    int _pin2;
}; 

#endif