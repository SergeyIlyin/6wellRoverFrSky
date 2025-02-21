#include "Rover.h"

Rover::Rover() {

}

void Rover::begin() {  
  pwmServo.begin(); 
  pwmMotor.begin(); 
  pwmServo.setPWMFreq(60);
  pwmMotor.setPWMFreq(60);
  steer_LF.begin();
  steer_LM.begin();
  steer_LR.begin(); 
  steer_RF.begin();
  steer_RM.begin();
  steer_RR.begin();
}

void Rover::sleep() {
  pwmServo.sleep();
  pwmMotor.sleep();
  delay(500);
}

void Rover::wakeup() {
  pwmServo.wakeup();
  pwmMotor.wakeup();
  delay(500);
}

void Rover::steer(int angle) {
  steer_LF.steer(angle);  
  steer_LM.steer(angle);
  steer_LR.steer(angle); 
  steer_RF.steer(angle);
  steer_RM.steer(angle);
  steer_RR.steer(angle);
}


void Rover::move(int speed) {
}

