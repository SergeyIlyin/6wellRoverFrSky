
#include "RoverSteer.h"
RoverSteer::RoverSteer(){}
RoverSteer::RoverSteer(Adafruit_PWMServoDriver* pwm, int pin) {
  _pwm = pwm;
  _pin = pin;
}

void RoverSteer::begin(){
  Serial.print("Steer...pwm...begin;");
}

void RoverSteer::steer(int angle) {  
  int pulse = angleToPulse(angle);
  _pwm -> setPWM(_pin, 0, pulse);
}

int RoverSteer::angleToPulse(int ang) {
  int pulse = map(ang, 0, 180, SERVOMIN, SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max
  return pulse;
}