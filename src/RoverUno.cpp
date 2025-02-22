#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>
#include <Pilot.h>

void PilotRol();
void TestServo();
void TestMotor();
Rover rover = Rover();
Pilot pilot = Pilot();

void setup()
{
  Serial.begin(100000);
  Serial.print("Recived Roll=");
  pilot.begin();
  rover.begin();
  Serial.print("Setup COMPLINED");
}

void loop()
{
   //PilotRol();
   //TestServo();
   TestMotor();
   Serial.println("");
}

void PilotRol()
{
  if (pilot.Read())
  {

    PilotData data = pilot.data();
    Serial.print("Recived Roll=");
    Serial.print(data.roll);
    rover.steer(data.roll);
    rover.move(data.trottle);
    Serial.println("");
  }
  else
  {
    //Serial.println("NO PILOT!");
    delay(10);
  }
}
void TestServo()
{
  delay(1000);
  rover.steer(10);
  delay(1000);
  rover.steer(0);
  delay(1000);
  rover.steer(-10);
  delay(1000);
  rover.steer(0);
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
