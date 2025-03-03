#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>
#include <Pilot.h>
#include <Player.h>

void PilotRol();
void TestServo();
void TestMotor();
void printPilotData(PilotData data);
Rover rover = Rover();
Pilot pilot = Pilot();
Player player = Player();
int kX;
int dX = 2;
void setup()
{
  Serial.begin(100000);
  pilot.begin();
  Serial.println("\tSetup START");
  rover.begin();
  rover.sleep();
  player.PowerOn();
  Serial.println("\tSetup COMPLINED");
}

void loop()
{
  PilotRol();
}

void PilotRol()
{
  if (pilot.Read())
  {
    PilotData data = pilot.data();
    //printPilotData(data);

    if (data.arm == false)
    {
      rover.sleep();
    }
    else if (abs(data.trottle) < 5)
    {
      rover.wakeup();
    }

    if (data.handbreak == true)
    {
      rover.breake();
    }
    else
    {
      rover.move(data.trottle);
    }
    rover.steer(data.x, data.y);
    Serial.println("");
  }
  else
  {
    Serial.println("NO PILOT!");
    rover.lostSingal();
    delay(100);
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
  int s = 0;
  for (s = 0; s <= 100; s += 10)
  {
    rover.move(s);
    delay(1000);
  }

  for (s = 100; s >= -100; s -= 10)
  {
    rover.move(s);
    delay(1000);
  }

  for (s = -100; s <= 0; s += 10)
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