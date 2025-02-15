#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <RoverSteer.h>

#define SERVOMIN 125  // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 625  // this is the 'maximum' pulse length count (out of 4096)

class Rover {
public:
  Rover();
  void begin();
  void sleep();
  void wakeup();
  void steer(int angle);
  void setMoveDirection(int direction);
  void move(int speed);
private:
  Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
  RoverSteer steer_LF = RoverSteer(&pwm, 0x00);  
};

#endif