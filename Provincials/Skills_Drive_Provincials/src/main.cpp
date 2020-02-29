
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         16              
// LeftMotor2           motor         6               
// RightMotor           motor         7               
// RightMotor2          motor         5               
// Lift                 motor         19              
// IntakeR              motor         8               
// IntakeL              motor         10              
// Controller1          controller                    
// Arm                  motor         15              
// ---- END VEXCODE CONFIGURED DEVICES ----
#include  <string>

using namespace vex;
competition Competition;
void pre_auton(void) {
  vexcodeInit();
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
  Lift.setStopping(vex::brakeType::brake);
  IntakeL.setStopping(brake);
  IntakeR.setStopping(brake);
  Arm.setStopping(brake);
  IntakeL.setMaxTorque(95, percent);
  IntakeR.setMaxTorque(95, percent);
  Lift.setMaxTorque(95, percent);
  Arm.setMaxTorque(95, percent);
}


static void stopAllDrive(void){
  LeftMotor.stop();
  LeftMotor2.stop();
  RightMotor.stop();
  RightMotor2.stop();
}

static void intakeSpdChange(int spd, int fB)
{
 IntakeL.setVelocity(spd,percent);
 IntakeR.setVelocity(spd,percent); 
 if(fB == 1){
 IntakeL.spin(forward);
 IntakeR.spin(forward);
 } 
 else{
 IntakeL.spin(reverse);
 IntakeR.spin(reverse);
 }
}

int onoff(void){
  int x;
  if(Controller1.ButtonR1.pressing()){
    //intake speed
    x=95;
  }
  else if (Controller1.ButtonL1.pressing()) {
    ///outtake speed
    x=-60;
  }
  else {
  x=0;
  }
     return x; 
};

int upDwn(void){
  int x;
    if(Controller1.ButtonX.pressing()){
    x=55;
  }
  else if (Controller1.ButtonB.pressing()) {
    x=-80;
  }
  else {
  x=0;
  }
     return x; 
}

int armFunc(void){
  int x;
    if(Controller1.ButtonR2.pressing()){
    x=80;
  }
  else if (Controller1.ButtonL2.pressing()) {
    x=-75;
  }
  /*else if (Controller1.ButtonX.pressing()) {
    x=1400;
  }
  else if (Controller1.ButtonB.pressing()) {
    x=850;
  }*/
  else {
  x=0;
  }
     return x; 
}

int traySpeedChanger(int degsTray){
int x;
if(degsTray<=300){
  x=60;
}
else if (degsTray<=650) {
  x=40;
}
else {
  x=15;
}
return x;
}

void moveWithSeconds(int velR, int velL, int msecs){
  LeftMotor.setVelocity(velL,percent);
  LeftMotor2.setVelocity(velL,percent);
  RightMotor.setVelocity(velR,percent);
  RightMotor2.setVelocity(velR,percent);
  LeftMotor.spin(fwd);
  LeftMotor2.spin(fwd);
  RightMotor.spin(fwd);
  RightMotor2.spin(fwd);
  wait(msecs,msec);
  stopAllDrive();
}
static void moveWithRotations(int velR, int velL, int degsR, int degsL) {
  LeftMotor.setVelocity(velL, percent);
  LeftMotor2.setVelocity(velL, percent);
  RightMotor.setVelocity(velR, percent);
  RightMotor2.setVelocity(velR, percent);
  LeftMotor.startRotateFor(degsL, degrees);
  LeftMotor2.startRotateFor(degsL, degrees);
  RightMotor.startRotateFor(degsR, degrees);
  RightMotor2.startRotateFor(degsR, degrees);
  waitUntil(LeftMotor.isDone() && RightMotor.isDone());
  stopAllDrive();
}



static void deployCubes(void){
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  Lift.setStopping(coast);
  stopAllDrive();
  Lift.setVelocity(35,pct);
  Lift.spinFor(2.5,seconds);
  Lift.setStopping(hold);
  Lift.stop();
  wait(300,msec);
  moveWithSeconds(7,7,600);
  wait(300,msec);
  moveWithSeconds(-30,-30,700);
  Lift.setVelocity(-70,pct);
  Lift.spinFor(1,seconds);
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
    Lift.setStopping(brake);
  }

  static void driveStraight(double div){
      LeftMotor.spin(vex::directionType::fwd,
                     (Controller1.Axis3.position()/div),
                     vex::velocityUnits::pct);
      LeftMotor2.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/div),
                      vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/div),
                      vex::velocityUnits::pct);
      RightMotor2.spin(vex::directionType::fwd,
                       (Controller1.Axis3.position()/div),
                       vex::velocityUnits::pct);
  }


  static void driving(double div){
      LeftMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / div),
          vex::velocityUnits::pct);
      LeftMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / div),
          vex::velocityUnits::pct);
      RightMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / div),
          vex::velocityUnits::pct);
      RightMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / div),
          vex::velocityUnits::pct);
  }

void autonomous(void) {
}


void usercontrol(void) {
 // int o=0;
  while (1) {
    short yee = abs(Controller1.Axis4.position());
    short bee = abs(Controller1.Axis3.position());
    if (Controller1.ButtonY.pressing()){
      intakeSpdChange(-70, 1);
    }
    else{
    intakeSpdChange(onoff(), 1);
    }
    if(yee+bee<=4){
      stopAllDrive();
    }
    else if(abs(Controller1.Axis3.position()) <= 20 ||yee >= 22){
      driving(2);
    }
    else if (yee <= 21) {
      driveStraight(1.3);
    }




    Lift.setVelocity(Controller1.Axis2.position()/1.4, percent);
    Lift.spin(fwd);
    
    /*if(Arm.rotation(deg)>=800){
      o=0;
    }
    if((Controller1.ButtonX.pressing()||Controller1.ButtonB.pressing())&&o==0){
      Arm.setVelocity(100, pct);
      Arm.spin(fwd);
      o=1;
    }*/
    if(Controller1.ButtonR2.pressing()||Controller1.ButtonL2.pressing()){
      Arm.setVelocity(armFunc(), percent);
      Arm.spin(fwd);
    } else {
     Arm.stop();
    }


    vex::task::sleep(20); 
  }
}


int main() {
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  while (true) {
    wait(100, msec);
  }
}


