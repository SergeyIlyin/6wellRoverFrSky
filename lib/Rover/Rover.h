#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <RoverSteer.h>
#include <RoverWell.h>
class Rover
{
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
  RoverSteer steer_LM = RoverSteer(&pwm, 0x01);
  RoverSteer steer_LR = RoverSteer(&pwm, 0x02);
  RoverSteer steer_RF = RoverSteer(&pwm, 0x03);
  RoverSteer steer_RM = RoverSteer(&pwm, 0x04);
  RoverSteer steer_RR = RoverSteer(&pwm, 0x05);
  
  RoverWell well_LF = RoverWell(&pwm, 0x10, 0x11);
  //RoverWell well_LM = RoverWell(&pwm, 0x08, 0x09);
  RoverWell well_LR = RoverWell(&pwm, 0x12, 0x13);
  //RoverWell well_RF = RoverWell(&pwm, 0x12, 0x13);
  RoverWell well_RM = RoverWell(&pwm, 0x14, 0x15);
  //RoverWell well_RR = RoverWell(&pwm, 0x16, 0x17);
};

#endif