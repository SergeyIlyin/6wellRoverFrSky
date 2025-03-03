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
void Rover::lostSingal()
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
void Rover::sleep()
{
  pwmServo.sleep();
  pwmMotor.sleep();
  if (armed)
  {
    armed = false;
    Serial.print(" CALL MUSIC ");
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
    Serial.print(" CALL MUSIC ");
    player.PlayArm();
    delay(500);
  }
}

void Rover::steer(int x, int y)
{
  // WellPosition p = CalcWellPosion(x, y);
  //  char strBuf[50];
  //  sprintf(strBuf, "x/y=%d/%d W=%d.%02d | %d.%02d  | %d.%02d  | %d.%02d  | %d.%02d | %d.%02d  ", x, y, p.LF, abs(p.LF * 100), p.LM, abs(p.LM * 100), p.LR, abs(p.LR * 100), p.RF, abs(p.RF * 100), p.RM, abs(p.RM * 100), p.RR, abs(p.RR * 100));
  //  Serial.print(strBuf);
  int a = map(x, -100, 100, -90, 90);
  steer_LF.steer(a);
  steer_LM.steer(a);
  steer_LR.steer(a);
  steer_RF.steer(a);
  steer_RM.steer(a);
  steer_RR.steer(a);
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