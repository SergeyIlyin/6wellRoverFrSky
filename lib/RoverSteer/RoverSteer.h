#ifndef RoverSteer_h
#define RoverSteer_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVOMIN 125  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 625  // this is the 'maximum' pulse length count (out of 4096)

class RoverSteer {
  public:
    RoverSteer();
    RoverSteer(Adafruit_PWMServoDriver* pwm, int pin);
    void begin();
    void steer(int angle);
  private:
    Adafruit_PWMServoDriver* _pwm;
    int _pin;
    int angleToPulse(int ang);
}; 

#endif