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
  //delay(100);

  if (pilot.Read())
  {   
    PilotData data = pilot.data();
    Serial.print("Recived Roll=");Serial.print(data.roll);
    rover.steer(data.roll);
    rover.move(data.trottle);
    Serial.println("");
  }
  else
  {
    //rover.sleep();
  }
}
