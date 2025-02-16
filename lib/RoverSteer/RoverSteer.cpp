
#include "RoverSteer.h"
RoverSteer::RoverSteer(Adafruit_PWMServoDriver *pwm, int pin)
{
  this->pwm = pwm;
  this->pin = pin;
}

void RoverSteer::begin()
{
}

void RoverSteer::steer(int angle)
{
  int pulse = angleToPulse(angle);
  pwm->setPWM(pin, 0, pulse);
  
}

int RoverSteer::angleToPulse(int ang)
{
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}