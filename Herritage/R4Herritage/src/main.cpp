/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftMotor            motor         12              
// LeftMotor2           motor         16              
// RightMotor           motor         10              
// RightMotor2          motor         8               
// RightPusher          motor         6               
// IntakeR              motor         15              
// IntakeL              motor         3               
// Arm                  motor         1               
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include  <string>

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
  RightPusher.setStopping(vex::brakeType::brake);
  IntakeL.setStopping(brake);
  IntakeR.setStopping(brake);
  Arm.setStopping(hold);
  IntakeL.setMaxTorque(95, percent);
  IntakeR.setMaxTorque(95, percent);
  RightPusher.setMaxTorque(95, percent);
  Arm.setMaxTorque(95, percent);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}


static void stopAllDrive(void){
  LeftMotor.stop();
  LeftMotor2.stop();
  RightMotor.stop();
  RightMotor2.stop();
}

static void stopIntake(void){
  IntakeL.stop();
  IntakeR.stop();
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
    x=65;
  }
  else if (Controller1.ButtonL1.pressing()) {
    x=-80;
  }
  else {
  x=0;
  }
     return x; 
};

int upDwn(void){
  int x;
    if(Controller1.ButtonX.pressing()){
    x=30;
  }
  else if (Controller1.ButtonB.pressing()) {
    x=-50;
  }
  else {
  x=0;
  }
     return x; 
}

int armFunc(void){
  int x;
    if(Controller1.ButtonR2.pressing()){
    x=90;
  }
  else if (Controller1.ButtonL2.pressing()) {
    x=-90;
  }
  else {
  x=0;
  }
     return x; 
}

static void moveWithSeconds(int velR, int velL, int msecs){
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

static void moveWithRotations(int velR, int velL, int degsR, int degsL){
  LeftMotor.setVelocity(velL,percent);
  LeftMotor2.setVelocity(velL,percent);
  RightMotor.setVelocity(velR,percent);
  RightMotor2.setVelocity(velR,percent);
  LeftMotor.startRotateFor(degsL,degrees);
  LeftMotor2.startRotateFor(degsL,degrees);
  RightMotor.startRotateFor(degsR,degrees);
  RightMotor2.startRotateFor(degsR,degrees);
  waitUntil(LeftMotor.isDone()&&RightMotor.isDone());
  stopAllDrive();
}


static void deployCubeHalf(void){
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  stopAllDrive();
  IntakeL.setVelocity(30, percent);
  IntakeR.setVelocity(30, percent);
  IntakeL.spin(forward);
  IntakeR.spin(forward);
  RightPusher.setVelocity(60,pct);
  RightPusher.rotateFor(250,deg);
  RightPusher.setVelocity(15,pct);
  RightPusher.spinFor(2.3,seconds);
  RightPusher.stop();
  wait(300,msec);
  IntakeL.stop();
  IntakeR.stop();
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
}

static void deployCubes(void){
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  RightPusher.setStopping(coast);
  stopAllDrive();
  RightPusher.setVelocity(35,pct);
  RightPusher.spinFor(2.5,seconds);
  RightPusher.setStopping(hold);
  RightPusher.stop();
  wait(300,msec);
  moveWithSeconds(7,7,600);
  wait(300,msec);
  moveWithSeconds(-30,-30,700);
  RightPusher.setVelocity(-70,pct);
  RightPusher.spinFor(1,seconds);
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
  }
//legacy code
/*static void deployCubes(void){
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  RightPusher.setStopping(coast);
  stopAllDrive();
  RightPusher.setVelocity(60,pct);
  RightPusher.rotateFor(200,deg);
  RightPusher.setVelocity(45,pct);
  RightPusher.rotateFor(80,deg);
  RightPusher.setVelocity(20,pct);
  RightPusher.spinFor(1.5,seconds);
  RightPusher.setStopping(hold);
  RightPusher.stop();
  wait(300,msec);
  moveWithSeconds(7,7,600);
  wait(300,msec);
  moveWithSeconds(-30,-30,700);
  RightPusher.setVelocity(-70,pct);
  RightPusher.spinFor(1,seconds);
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
  }*/

  static void driveStraight(void){
      LeftMotor.spin(vex::directionType::fwd,
                     (Controller1.Axis3.position()/1.2),
                     vex::velocityUnits::pct);
      LeftMotor2.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/1.2),
                      vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/1.2),
                      vex::velocityUnits::pct);
      RightMotor2.spin(vex::directionType::fwd,
                       (Controller1.Axis3.position()/1.2),
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


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void){
  
}
/*void autonomous(void) {
pre_auton();
Arm.setVelocity(80, percent);
Arm.spin(fwd);
intakeSpdChange(100,0);
wait(300, msec);
Arm.spin(reverse);
wait(400, msec);
intakeSpdChange(65, 1);
moveWithRotations(30,30,480,480);
wait(200,msec);
moveWithRotations(20,20,-280,280);
wait(200,msec);
moveWithRotations(40,40,200,200);
moveWithRotations(30,30,-300,-300);
wait(200,msec);
moveWithRotations(25,25,-530,530);
wait(300,msec);
moveWithRotations(60,60,300,300);
moveWithRotations(30,30,200,200);
wait(300,msec);
moveWithRotations(30,30,100,-100);
wait(300,msec);
moveWithRotations(50,50,280,280);
intakeSpdChange(100, 0);
wait(300,msec);
deployCubes();
}
*/
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    short yee = abs(Controller1.Axis4.position());
    intakeSpdChange(onoff(), 1);
    if (yee <= 15) {
      driveStraight();
    }
    else {
      driving(1.4);
    }
    if (Controller1.ButtonA.pressing()){
      deployCubes();
    }

  //Pusher
    if(Controller1.ButtonX.pressing()||Controller1.ButtonB.pressing()){
      RightPusher.setVelocity(upDwn(), percent);
      RightPusher.spin(fwd);
    }
    else {
      RightPusher.stop();
    }
    //Arm
    if (Controller1.ButtonA.pressing()){
      deployCubes();
    }
    Arm.setVelocity(Controller1.Axis2.position()/1.3, percent);
    Arm.spin(fwd);

    /*if(Controller1.ButtonR2.pressing()||Controller1.ButtonL2.pressing()){
      Arm.setVelocity(armFunc(), percent);
      Arm.spin(fwd);
    }
    else {
      Arm.stop();
    }
    */
    vex::task::sleep(5); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
