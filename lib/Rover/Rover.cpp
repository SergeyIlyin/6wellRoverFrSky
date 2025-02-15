#include "Rover.h"

Rover::Rover() {

}

void Rover::begin() {  
  pwm.begin(); 
  pwm.setPWMFreq(60);
  steer_LF.begin();
}

void Rover::sleep() {
  pwm.sleep();
  delay(500);
}

void Rover::wakeup() {
  pwm.wakeup();
  delay(500);
}

void Rover::steer(int angle) {
  steer_LF.steer(angle);
}

void Rover::setMoveDirection(int direction) {
}

void Rover::move(int speed) {
}

