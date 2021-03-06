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
// IntakeR              motor         14              
// IntakeL              motor         11              
// Controller1          controller                    
// Arm                  motor         1               
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

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

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
  stopAllDrive();
  RightPusher.setVelocity(60,pct);
  RightPusher.rotateFor(160,deg);
  RightPusher.setVelocity(45,pct);
  RightPusher.rotateFor(100,deg);
  RightPusher.setVelocity(20,pct);
  RightPusher.spinFor(1.1,seconds);
  RightPusher.stop();
  wait(300,msec);
  moveWithSeconds(10,10,500);
  wait(500,msec);
  moveWithSeconds(-30,-30,700);
  RightPusher.setVelocity(-70,pct);
  RightPusher.spinFor(1,seconds);
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
}




void autonomous(void) {
pre_auton();
intakeSpdChange(70, 1);
moveWithRotations(30,30,550,550);
wait(200,msec);
moveWithRotations(20,20,280,-280);
wait(200,msec);
moveWithRotations(40,40,350,350);
moveWithRotations(30,30,-300,-300);
wait(200,msec);
moveWithRotations(40,40,510,-510);
wait(300,msec);
moveWithRotations(60,60,350,350);
moveWithRotations(30,30,200,200);
moveWithRotations(30,30,-100,100);
wait(300,msec);
intakeSpdChange(20, 0);
moveWithRotations(50,50,350,350);
stopIntake();
wait(200,msec);
//hardcode deploycubes to prevent tipping stack, changing pshing value
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  stopAllDrive();
  IntakeL.spin(forward);
  IntakeR.spin(forward);
  RightPusher.setVelocity(60,pct);
  RightPusher.rotateFor(160,deg);
  RightPusher.setVelocity(40,pct);
  RightPusher.rotateFor(100,deg);
  RightPusher.setVelocity(20,pct);
  RightPusher.spinFor(1.1,seconds);
  RightPusher.stop();
  wait(300,msec);
  IntakeL.setVelocity(-50, percent);
  IntakeR.setVelocity(-50, percent);
  moveWithSeconds(10,10,500);
  wait(500,msec);
  IntakeL.setVelocity(-25, percent);
  IntakeR.setVelocity(-25, percent);
  RightPusher.setVelocity(-70,pct);
  RightPusher.spinFor(1,seconds);
  moveWithSeconds(-30,-30,700);
  IntakeL.stop();
  IntakeR.stop();
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
}

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

  int i = 0;
  while (1) {
    i++;
    short yee = abs(Controller1.Axis4.position());
    Controller1.Screen.clearLine();
    Controller1.Screen.print(RightPusher.position(deg));

    if(Controller1.ButtonL2.pressing()){
            LeftMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 5),
          vex::velocityUnits::pct);
      LeftMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 5),
          vex::velocityUnits::pct);
      RightMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 5),
          vex::velocityUnits::pct);
      RightMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 5),
          vex::velocityUnits::pct);
    }
    else if (yee >= 18) {
      LeftMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 2),
          vex::velocityUnits::pct);
      LeftMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 2),
          vex::velocityUnits::pct);
      RightMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 2),
          vex::velocityUnits::pct);
      RightMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 2),
          vex::velocityUnits::pct);
      yee = abs(Controller1.Axis4.position());
    }
    else if(yee<=18&&yee>=50){
      LeftMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 1.4),
          vex::velocityUnits::pct);
      LeftMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() + Controller1.Axis4.position()) / 1.4),
          vex::velocityUnits::pct);
      RightMotor.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 1.4),
          vex::velocityUnits::pct);
      RightMotor2.spin(
          vex::directionType::fwd,
          ((Controller1.Axis3.position() - Controller1.Axis4.position()) / 1.4),
          vex::velocityUnits::pct);
      yee = abs(Controller1.Axis4.position());
    }
    else {
      LeftMotor.spin(vex::directionType::fwd,
                     (Controller1.Axis3.position()),
                     vex::velocityUnits::pct);
      LeftMotor2.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()),
                      vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()),
                      vex::velocityUnits::pct);
      RightMotor2.spin(vex::directionType::fwd,
                       (Controller1.Axis3.position()),
                       vex::velocityUnits::pct);
      yee = abs(Controller1.Axis4.position());
    }
    if (Controller1.ButtonR1.pressing()) {
      // intake
      IntakeL.setVelocity(70, percent);
      IntakeR.setVelocity(70, percent);
      IntakeL.spin(forward);
      IntakeR.spin(forward);
    }
    if (Controller1.ButtonL1.pressing()) {
      // outtake
      IntakeL.setVelocity(80, percent);
      IntakeR.setVelocity(80, percent);
      IntakeL.spin(reverse);
      IntakeR.spin(reverse);
    }
    if (!Controller1.ButtonL1.pressing() && !Controller1.ButtonR1.pressing()) {
      // stopping the intake after running
      IntakeL.stop();
      IntakeR.stop();
    }
    if (Controller1.ButtonA.pressing()){
      deployCubes();
    }
    if (Controller1.ButtonX.pressing()) {
      RightPusher.setVelocity(45, percent);
      RightPusher.spin(forward);
    }
    if (Controller1.ButtonB.pressing()) {
      RightPusher.setVelocity(50, percent);
      RightPusher.spin(reverse);
    }
    if (!Controller1.ButtonX.pressing() && !Controller1.ButtonB.pressing()) {
      RightPusher.stop();
    }
       Arm.setVelocity(Controller1.Axis2.position()/2, percent);
       Arm.spin(fwd);


    vex::task::sleep(20); // Sleep the task for a short amount of time to
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
