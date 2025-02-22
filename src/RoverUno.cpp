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

void setup()
{
  Serial.begin(100000);
  pilot.begin();
  rover.begin();
  Serial.println("Setup COMPLINED");
}

void loop()
{
  // PilotRol();
  // TestServo();
  TestMotor();
  Serial.println("");
}

void PilotRol()
{
  if (pilot.Read())
  {
    PilotData data = pilot.data();
    printPilotData(data);
    rover.steer(data.x, data.y);
    rover.move(data.trottle);
    Serial.println("");
  }
  else
  {
    // Serial.println("NO PILOT!");
    delay(10);
  }
}
void TestServo()
{
  delay(1000);
  rover.steer(20, 100);
  delay(1000);
  rover.steer(20, 0);
  delay(1000);
  rover.steer(20, -100);
  delay(1000);
  rover.steer(0, 0);
  delay(1000);
  rover.steer(-20, 100);
  delay(1000);
  rover.steer(-20, 0);
  delay(1000);
  rover.steer(20, -100);
  delay(1000);
  rover.steer(0, 0);
  Serial.println("");
}

void TestMotor()
{
  delay(1000);
  rover.move(0);
  delay(1000);
  rover.move(25);
  delay(1000);
  rover.move(50);
  delay(1000);
  rover.move(75);
  delay(1000);
  rover.move(50);
  delay(1000);
  rover.move(25);
  delay(1000);
  rover.move(0);
  Serial.println("");
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