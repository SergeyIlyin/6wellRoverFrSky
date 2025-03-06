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

  double posX = _x / abs(_x);

  double maxX = ROVER_WIDTH / 2 / .017455;
  double minX = (ROVER_WIDTH / 2 + 1);
  double DX=maxX -minX;
  double minY = -ROVER_LENGTH * 2;
  double maxY = ROVER_LENGTH * 2;

  int angle = map(abs(_x), 0, 100, 0, 90);
  double KX = sin(angle * PI / 180);
  double x = (maxX -  DX*KX   + minX) * posX;

  double y = map(_y, -100, 100, minY, maxY);

  Serial.print("\tKX/X/Y=");

  Serial.print(KX);
  Serial.print("/");
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