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
  //rover.wakeup();
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
  
  delay(100);

  Serial.print("move 0");
  rover.move(0);
  Serial.println();

  Serial.print("move 50");
  rover.move(50);
  Serial.println();

  Serial.print("move 0");
  rover.move(0);
  Serial.println();
 
  Serial.println(" move -50"); 
  rover.move(-50);
  Serial.println();
  
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