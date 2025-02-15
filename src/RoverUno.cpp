#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>
#include <Pilot.h>

Rover rover = Rover();
Pilot pilot = Pilot();

void setup()
{

  pilot.begin();
  rover.begin();
}

void loop()
{
  delay(1000);

  if (pilot.Read())
  {
    PilotData data = pilot.data();
    rover.wakeup();
    rover.steer(data.roll);
    rover.move(data.trottle);
  }
  else
  {
    rover.sleep();
  }
}
