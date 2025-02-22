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
  Serial.print("\t Rorate=");
  Serial.print(angle);
  steer_LF.steer(angle);  
  steer_LM.steer(angle);
  steer_LR.steer(angle); 
  steer_RF.steer(angle);
  steer_RM.steer(angle);
  steer_RR.steer(angle);
}


void Rover::move(int speed) {
  Serial.print("\t LF");
  well_LF.rotate(speed);
  //delay(1000);
  Serial.print("\t LM");
  well_LM.rotate(speed);
  //delay(1000);
  Serial.print("\t LR");
  well_LR.rotate(speed);
  //delay(1000);
  Serial.print("\t RF");
  well_RF.rotate(speed);
  //delay(1000);
  Serial.print("\t RM");
  well_RM.rotate(speed);
  //delay(1000);
  Serial.print("\t RR");
  well_RR.rotate(speed);
}

