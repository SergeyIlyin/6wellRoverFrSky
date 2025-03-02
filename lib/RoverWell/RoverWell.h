#ifndef RoverWell_h
#define RoverWell_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define DRIVEMIN 0
#define DRIVEMAX 4095
#define TROTTLEMIN 5

class RoverWell {
  public:
    RoverWell(Adafruit_PWMServoDriver* pwm, int pin1, int pin2);
    void begin();
    void rotate(int speed);
    void breake();
    void release();
  private:
    Adafruit_PWMServoDriver* pwm;
    int pin1;
    int pin2;
    int trottleToPulse(int trottle);
}; 

#endif