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
  Adafruit_PWMServoDriver pwmServo = Adafruit_PWMServoDriver(0x40);
  Adafruit_PWMServoDriver pwmMotor = Adafruit_PWMServoDriver(0x41);  
  RoverSteer steer_LF = RoverSteer(&pwmServo, 0x00);  
  RoverSteer steer_LM = RoverSteer(&pwmServo, 0x01);  
  RoverSteer steer_LR = RoverSteer(&pwmServo, 0x02);  
  RoverSteer steer_RF = RoverSteer(&pwmServo, 0x03);  
  RoverSteer steer_RM = RoverSteer(&pwmServo, 0x04);  
  RoverSteer steer_RR = RoverSteer(&pwmServo, 0x05);  
};

#endif