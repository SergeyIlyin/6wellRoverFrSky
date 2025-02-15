#include <Arduino.h>
#include <sbus.h>
#include <Rover.h>

void showSteerMove();

bfs::SbusRx sbus_rx = bfs::SbusRx(&Serial, true);
bfs::SbusData data;

Rover rover = Rover();


void setup() {
  Serial.begin(100000);
  Serial.println("Wait Serial");
  while (!Serial) {}
  Serial.println("Begin sbus_rx");
  sbus_rx.Begin();

  Serial.println("Begin rover");
  rover.begin();
}

void loop() {
   delay(1000);
   Serial.println("chanel");
  if (false && sbus_rx.Read()) {
    data = sbus_rx.data();
    Serial.println("chanel");
    for (int8_t i = 0; i < data.NUM_CH; i++) {
      Serial.println("chanel");
      Serial.print(data.ch[i]);
      Serial.print("\t");
    }

    //Serial.print("\l\n");
    /* Display lost frames and failsafe data */
    //Serial.print(data.lost_frame);
    //Serial.print("\t");
    //Serial.println(data.failsafe);
  }

  if (false) {
    delay(1000);

    rover.wakeup();
    showSteerMove();

    delay(1000);
    rover.sleep();
    Serial.println("Rover sleep");
    showSteerMove();
  }
}

void showSteerMove() {
  rover.steer(60);
  delay(1000);
  rover.steer(150);
}
