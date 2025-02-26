#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>
#include <Pilot.h>

void PilotRol();
void TestServo();
void TestMotor();
void printPilotData(PilotData data);
Rover rover = Rover();
Pilot pilot = Pilot();
int kX;
int dX = 2;
void setup()
{
  Serial.begin(100000);
  pilot.begin();
  rover.begin();
  rover.wakeup();
  Serial.println("Setup COMPLINED");
}

void loop()
{
  // PilotRol();
  //TestServo();
  // TestMotor();

  kX += dX;
  if (kX >= 100)
  {
    dX = -2;
  }
  if (kX <= -100)
  {
    dX = 2;
  }
  rover.steer(kX, 0);
  Serial.println("");
  delay(200);
}

void PilotRol()
{
  if (pilot.Read())
  {
    PilotData data = pilot.data();
    printPilotData(data);
    rover.steer(data.x, data.y);
    rover.move(data.trottle);
  }
  else
  {
    // Serial.println("NO PILOT!");
    delay(10);
  }
}
void TestServo()
{

  delay(100);
  rover.steer(50, 20);
  Serial.println("");
  delay(500);
  rover.steer(0, 20);
  Serial.println("");
  delay(500);
  rover.steer(-50, 20);
  Serial.println("");
  delay(500);
}

void TestMotor()
{
  delay(100);
  rover.move(50);
  delay(100);
  rover.move(100);
}

void printPilotData(PilotData data)
{
  Serial.print("\tt/x/y=");
  Serial.print(data.trottle);
  Serial.print("/");
  Serial.print(data.x);
  Serial.print("/");
  Serial.print(data.y);
  Serial.print("\t");
}