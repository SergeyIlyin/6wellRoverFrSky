#ifndef Rover_h
#define Rover_h

#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <RoverSteer.h>
#include <RoverWell.h>

#define ROWER_WIDTH 300
#define ROVER_LENGTH 300
#define MAX_RADIUS 10000
#define MIN_RADIUS 300

struct WellPosition
{
  int LF;
  int LM;
  int LR;
  int RF;
  int RM;
  int RR;
  /* data */
};


class Rover
{
public:
  Rover();
  void begin();
  void sleep();
  void wakeup();
  void steer(int x, int y);
  void move(int speed);

private:
  Adafruit_PWMServoDriver pwmServo = Adafruit_PWMServoDriver(0x42);
  Adafruit_PWMServoDriver pwmMotor = Adafruit_PWMServoDriver(0x40);
  RoverSteer steer_LF = RoverSteer(&pwmServo, 0x00);
  RoverSteer steer_LM = RoverSteer(&pwmServo, 0x01);
  RoverSteer steer_LR = RoverSteer(&pwmServo, 0x02);
  RoverSteer steer_RF = RoverSteer(&pwmServo, 0x03);
  RoverSteer steer_RM = RoverSteer(&pwmServo, 0x04);
  RoverSteer steer_RR = RoverSteer(&pwmServo, 0x05);

  RoverWell well_LF = RoverWell(&pwmMotor, 0x00, 0x01);
  RoverWell well_LM = RoverWell(&pwmMotor, 0x02, 0x03);
  RoverWell well_LR = RoverWell(&pwmMotor, 0x04, 0x05);
  RoverWell well_RF = RoverWell(&pwmMotor, 0x06, 0x07);
  RoverWell well_RM = RoverWell(&pwmMotor, 0x08, 0x09);
  RoverWell well_RR = RoverWell(&pwmMotor, 0x10, 0x11);

  WellPosition CalcWellPosion(int _x, int _y);
};

#endif