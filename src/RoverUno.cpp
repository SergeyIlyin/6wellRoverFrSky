#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>
#include <Pilot.h>

Rover rover = Rover();
Pilot pilot = Pilot();

void setup()
{
  Serial.begin(100000);
  Serial.println("setup");
  pilot.begin();
  rover.begin();
  Serial.println("exitsetop");
}

void loop()
{
  delay(10);

  if (pilot.Read())
  {
    PilotData data = pilot.data();
    //rover.wakeup();
    Serial.print("roll\t");
    Serial.print(data.roll);
    Serial.print("\ttrottle\t");
    Serial.println (data.trottle);
    rover.steer(data.roll);
    rover.move(data.trottle);
  }
  else
  {
    Serial.println("no data");
   // rover.sleep();
  }
}
