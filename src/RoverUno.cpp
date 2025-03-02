#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <sbus.h>

bfs::SbusRx sbus_rx = bfs::SbusRx(&Serial, true);
bfs::SbusData sBusData;

#define AXISMIN 172
#define AXISMAX 1811
#define CH_TROTTLE 0x0
#define CH_X 0x1
#define CH_Y 0x2
struct PilotData
{
  int trottle;
  int x;
  int y;
};
PilotData pilotData;

#define DRIVEMIN 1000
#define DRIVEMAX 4095
#define TROTTLEMIN 5
struct RoverWells
{
  int LF1 = 0x08;
  int LF2 = 0x09;
  int LM1 = 0x06;
  int LM2 = 0x07;
  int LR1 = 0x02;
  int LR2 = 0x03;
  int RF1 = 0x04;
  int RF2 = 0x05;
  int RM1 = 0x0A;
  int RM2 = 0x0B;
  int RR1 = 0x01;
  int RR2 = 0x00;
};
RoverWells rw;

#define SERVOMIN 125
#define SERVOMAX 625
struct RoverStears
{
  int LF = 0x00;
  int LM = 0x01;
  int LR = 0x02;
  int RF = 0x03;
  int RM = 0x04;
  int RR = 0x05;
};
RoverStears rs;


Adafruit_PWMServoDriver pwmServo = Adafruit_PWMServoDriver(0x42);
Adafruit_PWMServoDriver pwmMotor = Adafruit_PWMServoDriver(0x40);

void PilotRol();
void TestServo();
void TestMotor();
bool ReadPilot();
void Steer(int x);
void steer(int pin, int angle);
int angleToPulse(int ang);
void Move(int trottle);
void RotateWell(int pin1, int pin2, int trottle);
void Release(int pin1, int pin2);
void Breake(int pin1, int pin2);
int trottleToPulse(int trottle);
bool usePilot = false;
void setup()
{
  Serial.begin(100000);
  Serial.println("Setup START");

  if (usePilot)
  {
    while (!Serial)
    {
    }
    sbus_rx.Begin();
  }

  pwmServo.setPWMFreq(60);
  pwmMotor.setPWMFreq(100);
  pwmServo.begin();
  pwmMotor.begin(); 
  Serial.println("Setup COMPLINED");
}

void loop()
{
  Serial.println("строка");
  TestMotor();
  delay(200);
}

void PilotRol()
{
  if (ReadPilot())
  {
    PilotData data = pilotData;
    Steer(data.x);
    Move(data.trottle);
  }
  else
  {
    delay(10);
  }
}

bool ReadPilot()
{
  bool readed = sbus_rx.Read();
  if (readed)
  {
    sBusData = sbus_rx.data();
    pilotData = PilotData();
    pilotData.trottle = map(sBusData.ch[CH_TROTTLE], AXISMIN, AXISMAX, 0, 100);
    pilotData.x = map(sBusData.ch[CH_X], AXISMIN, AXISMAX, -100, 100);
    pilotData.y = map(sBusData.ch[CH_Y], AXISMIN, AXISMAX, -100, 100);
  }
  return readed;
};

void Move(int trottle)
{
  RotateWell(rw.LF1, rw.LF2, trottle);
  RotateWell(rw.LM1, rw.LM2, trottle);
  RotateWell(rw.LR1, rw.LR2, trottle);
  RotateWell(rw.RF1, rw.RF2, trottle);
  RotateWell(rw.RM1, rw.RM2, trottle);
  RotateWell(rw.RR1, rw.RR2, trottle);
}

void TestServo()
{
  delay(100);
  Steer(0);
  delay(500);
  Steer(-60);
  delay(500);
  Steer(0);
  delay(500);
  Steer(60);
  delay(500);
  Steer(0);
}

void TestMotor()
{
  int s = 0;
  for (s = 0; s <= 100; s += 10)
  {
    Move(s);
    delay(1000);
  }

  for (s = 100; s >= -100; s -= 10)
  {
    Move(s);
    delay(1000);
  }

  for (s = -100; s <= 0; s += 10)
  {
    Move(s);
    delay(1000);
  }
}
void Steer(int x)
{
  //WellPosition p = CalcWellPosion(x, y);
  // char strBuf[50];
  // sprintf(strBuf, "x/y=%d/%d W=%d.%02d | %d.%02d  | %d.%02d  | %d.%02d  | %d.%02d | %d.%02d  ", x, y, p.LF, abs(p.LF * 100), p.LM, abs(p.LM * 100), p.LR, abs(p.LR * 100), p.RF, abs(p.RF * 100), p.RM, abs(p.RM * 100), p.RR, abs(p.RR * 100));
  // Serial.print(strBuf);

  steer(rs.LF,x);
  steer(rs.LM,x);
  steer(rs.LR,x);
  steer(rs.RF,x);
  steer(rs.RM,x);
  steer(rs.RR,x);
};

void steer(int pin, int angle)
{
  int pulse = angleToPulse(angle+90);
  pwmServo.setPWM(pin, 0, pulse);
}

int angleToPulse(int ang)
{
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
};


void RotateWell(int pin1, int pin2, int trottle)
{
  if (trottle == 0 || (abs(trottle) < TROTTLEMIN))
  {
    Release(pin1, pin2);
  }
  else if (trottle > 0)
  {
    int pulse = trottleToPulse(trottle);
    pwmMotor.setPWM(pin2, 0, 0);
    pwmMotor.setPWM(pin1, 0, pulse);
  }
  else
  {

    int pulse = trottleToPulse(trottle * -1);
    pwmMotor.setPWM(pin1, 0, 0);
    pwmMotor.setPWM(pin2, 0, pulse);
  }
};

void Breake(int pin1, int pin2)
{
  pwmMotor.setPWM(pin1, 0, DRIVEMAX);
  pwmMotor.setPWM(pin2, 0, DRIVEMAX);
};

void Release(int pin1, int pin2)
{
  pwmMotor.setPWM(pin1, 0, 0);
  pwmMotor.setPWM(pin2, 0, 0);
};

int trottleToPulse(int trottle)
{
  int pulse = map(trottle, 0, 100, DRIVEMIN, DRIVEMAX); // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
};