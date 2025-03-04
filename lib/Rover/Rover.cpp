#include "Rover.h"

Rover::Rover()
{
}

void Rover::begin()
{
  pwmServo.begin();
  pwmMotor.begin();
  pwmServo.setPWMFreq(60);
  pwmMotor.setPWMFreq(100);
  move(0);
}
void Rover::lostSingal(bool lost)
{
  if (lost)
  {
    lostSignalCount++;
    if (armed)
    {
      player.LostSignal();
    }
    if (lostSignalCount > maxLostSignal)
    {
      sleep();
      lostSignalCount = 0;
    }
  }
  else
  {
    lostSignalCount = 0;
  }
}
void Rover::sleep()
{
  pwmServo.sleep();
  pwmMotor.sleep();
  if (armed)
  {
    armed = false;
    player.PlayDisam();
  }
}

void Rover::wakeup()
{
  if (!armed)
  {
    pwmServo.wakeup();
    pwmMotor.wakeup();
    armed = true;
    player.PlayArm();
    delay(500);
  }
}

void Rover::steer(int x, int y)
{
  WellPosition p = CalcWellPosion(x, y);
  printWellPosition(p);
  steer_LF.steer(p.LF);
  steer_LM.steer(p.LM);
  steer_LR.steer(p.LR);
  steer_RF.steer(p.RF);
  steer_RM.steer(p.RM);
  steer_RR.steer(p.RR);
}

void Rover::printWellPosition(WellPosition p)
{
  Serial.print("\tW=");
  Serial.print(p.LF);
  Serial.print(" | ");
  Serial.print(p.LM);
  Serial.print(" | ");
  Serial.print(p.LR);

  Serial.print(" | ");
  Serial.print(p.RF);
  Serial.print(" | ");
  Serial.print(p.RM);
  Serial.print(" | ");
  Serial.print(p.RR);
}
void Rover::breake()
{
  well_LF.breake();
  well_LM.breake();
  well_LR.breake();
  well_RF.breake();
  well_RM.breake();
  well_RR.breake();
}

void Rover::move(int speed)
{
  well_LF.rotate(speed);
  well_LM.rotate(speed);
  well_LR.rotate(speed);
  well_RF.rotate(speed);
  well_RM.rotate(speed);
  well_RR.rotate(speed);
}

WellPosition Rover::CalcWellPosion(int _x, int _y)
{
  WellPosition p = WellPosition();
  if (_x == 0)
    return p;

  int x = 0;

  double maxDX=ROVER_LENGTH / 2/.017455;
  double minDX=ROVER_WIDTH / 2;
  if (_x > 0)
    x = map(_x, 0, 100, maxDX, minDX );

  if (_x < 0)
    x = map(_x, -100, 0, -maxDX, -minDX);

  double y = map(_y, -100, 100, -MAX_RADIUS, MAX_RADIUS);

  Serial.print("\tX/Y=");
  Serial.print(x);
  Serial.print("/");
  Serial.print(y);
  double dx = ROVER_WIDTH / 2;
  double dy = ROVER_LENGTH / 2;

  p.LF = CalcAngle(x + dx, y - dy);
  p.LM = CalcAngle(x + dx, y);
  p.LR = CalcAngle(x + dx, y + dy);
  p.RF = CalcAngle(x - dx, y - dy);
  p.RM = CalcAngle(x - dx, y);
  p.RR = CalcAngle(x - dx, y + dy);

  return p;
}

double Rover::CalcAngle(double x, double y)
{
  if (y == 0)
    return 0;
  if (x == 0)
    return 0;

  double ctg = y / x;
  double angR = atan(ctg);
  double angD = angR * 180 / PI;
  return angD;
}