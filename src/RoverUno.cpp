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
  Serial.println("Setup START");  
  //pilot.begin();
  rover.begin();
  rover.move(0);
  rover.wakeup();
  Serial.println("Setup COMPLINED");
}

void loop()
{ 
 // PilotRol();
  Serial.println("строка");
  rover.move(0);
  TestServo(); 
  rover.move(50);
  TestServo(); 
  rover.move(0);
  delay(500);
  rover.move(-50);
  TestServo(); 
  delay(100);
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
    Serial.println("NO PILOT!");
    delay(10);
  }
}
void TestServo()
{
  delay(100);
  rover.steer(0, 20);
  delay(500);
  rover.steer(-60, 20);
  delay(500);
  rover.steer(0, 20);
  delay(500);
  rover.steer(60, 20);
  delay(500);
  rover.steer(0, 20);
}

void TestMotor()
{
  int s=0;
  for (s=0; s<=100; s+=10)
  {
    rover.move(s);
    delay(1000);
  }

  for (s=100; s>=-100; s-=10)
  {
    rover.move(s);
    delay(1000);
  }

  for (s=-100; s<=0; s+=10)
  {
    rover.move(s);
    delay(1000);
  }
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