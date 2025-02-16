#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <RoverSteer.h>


class Rover {
public:
  Rover();
  void begin();
  void sleep();
  void wakeup();
  void steer(int angle);
  void move(int speed);
private:
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
  RoverSteer steer_LF = RoverSteer(&pwm, 0x00);  

};

#endif