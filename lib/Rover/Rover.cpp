#include "Rover.h"

Rover::Rover()
{
}

void Rover::begin()
{
  pwmServo.begin();
  pwmMotor.begin();
  pwmServo.setPWMFreq(60);
  pwmMotor.setPWMFreq(60);
  steer_LF.begin();
  steer_LM.begin();
  steer_LR.begin();
  steer_RF.begin();
  steer_RM.begin();
  steer_RR.begin();
}

void Rover::sleep()
{
  pwmServo.sleep();
  pwmMotor.sleep();
  delay(500);
}

void Rover::wakeup()
{
  pwmServo.wakeup();
  pwmMotor.wakeup();
  delay(500);
}

void Rover::steer(int x, int y)
{
  WellPosition p = CalcWellPosion(x, y);
  Serial.print("\tx/y=");
  Serial.print(x);
  Serial.print("/");
  Serial.print("\t");
  Serial.print(y);
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

  steer_LF.steer(p.LF);
  steer_LM.steer(p.LM);
  steer_LR.steer(p.LR);
  steer_RF.steer(p.RF);
  steer_RM.steer(p.RM);
  steer_RR.steer(p.RR);
}

void Rover::move(int speed)
{
  Serial.print("\t LF");
  well_LF.rotate(speed);
  // delay(1000);
  Serial.print("\t LM");
  well_LM.rotate(speed);
  // delay(1000);
  Serial.print("\t LR");
  well_LR.rotate(speed);
  // delay(1000);
  Serial.print("\t RF");
  well_RF.rotate(speed);
  // delay(1000);
  Serial.print("\t RM");
  well_RM.rotate(speed);
  // delay(1000);
  Serial.print("\t RR");
  well_RR.rotate(speed);
}

void printWellPosition(WellPosition p)
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

WellPosition CalcWellPosion(int _x, int _y)
{
  WellPosition p = WellPosition();
  long x = 0;
  
  if (_x > 0)
    x = map(_x, 0, 100, MAX_RADIUS, MIN_RADIUS);

  if (_x < 0)
    x = map(_x, 0, -100, -MAX_RADIUS, -MIN_RADIUS);

  long y = map(_y, -100, 100, -MAX_RADIUS, MAX_RADIUS);

  p.LF = wellAngle(-ROVER_WIDTH / 2, ROVER_LENGTH / 2, x, y);
  p.LM = wellAngle(-ROVER_WIDTH / 2, 0, x, y);
  p.LR = wellAngle(-ROVER_WIDTH / 2, -ROVER_LENGTH / 2, x, y);
  p.RF = wellAngle(ROVER_WIDTH / 2, ROVER_LENGTH / 2, x, y);
  p.RM = wellAngle(ROVER_WIDTH / 2, 0, x, y);
  p.RR = wellAngle(ROVER_WIDTH / 2, -ROVER_LENGTH / 2, x, y);

  return p;
}

double wellAngle(double well_x, double well_y, double rotation_x, double rotation_y)
{
  double x = well_x + rotation_x;
  double y = well_y + rotation_y;
  double fl_r = sqrt(x * x + y * y);
  double fl_cos = (x) / fl_r;
  double fl_a = PI / 2 - acos(fl_cos);
}