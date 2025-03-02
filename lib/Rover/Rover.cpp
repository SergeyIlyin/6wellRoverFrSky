#include "Rover.h"

Rover::Rover()
{
}

void Rover::begin()
{
  pwmServo.setPWMFreq(60);
  pwmMotor.setPWMFreq(100);
  pwmServo.begin();
  pwmMotor.begin();
  steer_LF.begin();
  steer_LM.begin();
  steer_LR.begin();
  steer_RF.begin();
  steer_RM.begin();
  steer_RR.begin();
  well_LF.begin();
  well_LM.begin();
  well_LR.begin();
  well_RF.begin();
  well_RM.begin();
  well_RR.begin();
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
  //WellPosition p = CalcWellPosion(x, y);
  // char strBuf[50];
  // sprintf(strBuf, "x/y=%d/%d W=%d.%02d | %d.%02d  | %d.%02d  | %d.%02d  | %d.%02d | %d.%02d  ", x, y, p.LF, abs(p.LF * 100), p.LM, abs(p.LM * 100), p.LR, abs(p.LR * 100), p.RF, abs(p.RF * 100), p.RM, abs(p.RM * 100), p.RR, abs(p.RR * 100));
  // Serial.print(strBuf);

  steer_LF.steer(x);
  steer_LM.steer(x);
  steer_LR.steer(x);
  steer_RF.steer(x);
  steer_RM.steer(x);
  steer_RR.steer(x);
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

  // вычисляем угол поворота от процентов
  double a_grad = 90;
  if (_x > 0)
    a_grad = map(_x, 0, 100, 90, 0);
  if (_x < 0)
    a_grad = map(_x, 0, -100, 90, 180);
  Serial.print(" a=");
  Serial.print(a_grad);

  double a_rad = a_grad * PI / 180;

  // вычисляем радиус поворота
  if (abs(a_grad - 90) > 1)
  {

    double tng = tan(a_rad);
    double r = tng * ROVER_LENGTH;
    if (abs(r) - ROVER_WIDTH / 2 < 0)
    {
      r = ROVER_WIDTH / 2 * (r / sqrt(r * r));
    }
    Serial.print(" r=");
    Serial.print(r);

    double LF = wellAngle(-ROVER_WIDTH / 2, ROVER_LENGTH / 2, r, 0);
    Serial.print(" LF=");
    Serial.print(LF);
  }
}

// WellPosition Rover::CalcWellPosion(int _x, int _y)
//{
//   WellPosition p = WellPosition();
//   double x = 0;
//
//   if (_x > 0)
//     x = map(_x, 0, 100, MAX_RADIUS, MIN_RADIUS);
//
//   if (_x < 0)
//     x = map(_x, 0, -100, -MAX_RADIUS, -MIN_RADIUS);
//
//   double y = map(_y, -100, 100, -MAX_RADIUS, MAX_RADIUS);
//
//   p.LF = wellAngle(-ROVER_WIDTH / 2, ROVER_LENGTH / 2, x, y);
//   p.LM = wellAngle(-ROVER_WIDTH / 2, 0, x, y);
//   p.LR = wellAngle(-ROVER_WIDTH / 2, -ROVER_LENGTH / 2, x, y);
//   p.RF = wellAngle(ROVER_WIDTH / 2, ROVER_LENGTH / 2, x, y);
//   p.RM = wellAngle(ROVER_WIDTH / 2, 0, x, y);
//   p.RR = wellAngle(ROVER_WIDTH / 2, -ROVER_LENGTH / 2, x, y);
//
//   return p;
// }

double Rover::wellAngle(double well_x, double well_y, double r_x, double r_y)
{

  double d_x = well_x - r_x;
  double d_y = well_y - r_y;
  double w_tan = d_x / d_y;
  double rad = atan(w_tan);
  double gr = rad * 180 / PI;
  return gr;
}