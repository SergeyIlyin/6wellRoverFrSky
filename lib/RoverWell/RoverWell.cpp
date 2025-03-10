#include "RoverWell.h"

RoverWell::RoverWell(Adafruit_PWMServoDriver *pwm, int pin1, int pin2)
{
  this->pwm = pwm;
  this->pin1 = pin1;
  this->pin2 = pin2;
}



void RoverWell::rotate(int trottle)
{
  if (trottle == 0 || (abs(trottle) < TROTTLEMIN))
  {
    release();
  }
  else if (trottle > 0)
  {
    int pulse = trottleToPulse(trottle);
    pwm->setPWM(pin2, 0, 0);
    pwm->setPWM(pin1, 0, pulse);
  }
  else
  {

    int pulse = trottleToPulse(trottle * -1);
    pwm->setPWM(pin1, 0, 0);
    pwm->setPWM(pin2, 0, pulse);
  }
}

void RoverWell::breake()
{
  pwm->setPWM(pin1, 0, DRIVEMAX);
  pwm->setPWM(pin2, 0, DRIVEMAX);
}

void RoverWell::release()
{
  pwm->setPWM(pin1, 0, 0);
  pwm->setPWM(pin2, 0, 0);
}

int RoverWell::trottleToPulse(int trottle)
{
  int pulse = map(trottle, 0, 100, DRIVEMIN, DRIVEMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}
