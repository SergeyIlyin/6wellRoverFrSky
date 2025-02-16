#include "Rover.h"

Rover::Rover()
{
}

void Rover::begin()
{
  pwm.begin();
  pwm.setPWMFreq(60);
  steer_LF.begin();
}

void Rover::sleep()
{
  pwm.sleep();
  delay(500);
}

void Rover::wakeup()
{
  pwm.wakeup();
  delay(500);
}

void Rover::steer(int angle)
{
  steer_LF.steer(angle);
  steer_LM.steer(angle);
  steer_LR.steer(angle);

  steer_RF.steer(angle);
  steer_RM.steer(angle);
  steer_RR.steer(angle);
}

void Rover::move(int speed)
{
  well_LF.rotate(speed);
  well_LR.rotate(speed);
  well_RM.rotate(speed);
}


