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
// LeftMotor            motor         11
// LeftMotor2           motor         13
// RightMotor           motor         20
// RightMotor2          motor         9
// RightPusher          motor         17
// IntakeR              motor         3
// IntakeL              motor         7
// Controller1          controller
// Arm                  motor         15
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <string>

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
  LeftMotor.setStopping(brake);
  LeftMotor2.setStopping(brake);
  RightMotor.setStopping(brake);
  RightMotor2.setStopping(brake);
  RightPusher.setStopping(brake);
  IntakeL.setStopping(brake);
  IntakeR.setStopping(brake);
  Arm.setStopping(brake);
  IntakeL.setMaxTorque(95, percent);
  IntakeR.setMaxTorque(95, percent);
  RightPusher.setMaxTorque(95, percent);
  Arm.setMaxTorque(95, percent);

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

static void stopAllDrive(void) {
  LeftMotor.stop();
  LeftMotor2.stop();
  RightMotor.stop();
  RightMotor2.stop();
}

static void stopIntake(void) {
  IntakeL.stop();
  IntakeR.stop();
}

static void intakeSpdChange(int spd, int fB) {
  IntakeL.setVelocity(spd, percent);
  IntakeR.setVelocity(spd, percent);
  if (fB == 1) {
    IntakeL.spin(forward);
    IntakeR.spin(forward);
  } else {
    IntakeL.spin(reverse);
    IntakeR.spin(reverse);
  }
}

int onoff(void) {
  int x;
  if (Controller1.ButtonR1.pressing()) {
    // intake speed
    x = 85;
  } else if (Controller1.ButtonL1.pressing()) {
    /// outtake speed
    x = -15;
  } else {
    x = 0;
  }
  return x;
};

int upDwn(void) {
  int x;
  if (Controller1.ButtonX.pressing()) {
    x = 55;
  } else if (Controller1.ButtonB.pressing()) {
    x = -80;
  } else {
    x = 0;
  }
  return x;
}

int armFunc(void) {
  int x;
  if (Controller1.ButtonR2.pressing()) {
    x = 80;
  } else if (Controller1.ButtonL2.pressing()) {
    x = -75;
  }
  /*else if (Controller1.ButtonX.pressing()) {
    x=1400;
  }
  else if (Controller1.ButtonB.pressing()) {
    x=850;
  }*/
  else {
    x = 0;
  }
  return x;
}

void moveWithSeconds(int velR, int velL, int msecs) {
  LeftMotor.setVelocity(velL, percent);
  LeftMotor2.setVelocity(velL, percent);
  RightMotor.setVelocity(velR, percent);
  RightMotor2.setVelocity(velR, percent);
  LeftMotor.spin(fwd);
  LeftMotor2.spin(fwd);
  RightMotor.spin(fwd);
  RightMotor2.spin(fwd);
  wait(msecs, msec);
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

static void deployCubes(void) {
  LeftMotor.setStopping(hold);
  LeftMotor2.setStopping(hold);
  RightMotor.setStopping(hold);
  RightMotor2.setStopping(hold);
  RightPusher.setStopping(coast);
  stopAllDrive();
  stopIntake();
  RightPusher.setVelocity(80, pct);
  RightPusher.spinFor(1.5, seconds);
  RightPusher.setVelocity(15, pct);
  RightPusher.spinFor(0.5, seconds);
  RightPusher.setStopping(hold);
  RightPusher.stop();
  moveWithSeconds(-30, -30, 700);
  RightPusher.setVelocity(-70, pct);
  RightPusher.spinFor(1, seconds);
  LeftMotor.setStopping(brake);
  LeftMotor2.setStopping(brake);
  RightMotor.setStopping(brake);
  RightMotor2.setStopping(brake);
  RightPusher.setStopping(brake);
}

static void trayFlipout(void) {
  Arm.setVelocity(100, percent);
  Arm.spin(fwd);
  wait(900, msec);
  Arm.spin(reverse);
  wait(1400, msec);
}

static void driveStraight(double div) {
  LeftMotor.spin(fwd, (Controller1.Axis3.position() / div), pct);
  LeftMotor2.spin(fwd, (Controller1.Axis3.position() / div), pct);
  RightMotor.spin(fwd, (Controller1.Axis3.position() / div), pct);
  RightMotor2.spin(fwd, (Controller1.Axis3.position() / div), pct);
}

static void driving(double div) {
  LeftMotor.spin(
      fwd,
      ((Controller1.Axis3.position() + Controller1.Axis4.position()) / div),
      pct);
  LeftMotor2.spin(
      fwd,
      ((Controller1.Axis3.position() + Controller1.Axis4.position()) / div),
      pct);
  RightMotor.spin(
      fwd,
      ((Controller1.Axis3.position() - Controller1.Axis4.position()) / div),
      pct);
  RightMotor2.spin(
      fwd,
      ((Controller1.Axis3.position() - Controller1.Axis4.position()) / div),
      pct);
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
void autonomous(void) {
  trayFlipout();
  intakeSpdChange(85, 1);
  moveWithRotations(70, 70, 600, 600);
  wait(100, msec);
  moveWithRotations(20, 20, -300, 300);
  wait(200, msec);
  moveWithRotations(70, 70, 400, 400);
  wait(100, msec);
  moveWithRotations(50, 50, -500, -500);
  wait(200, msec);
  moveWithRotations(35, 35, -600, 600);
  wait(200, msec);
  moveWithRotations(70, 70, 750, 750);
  wait(200, msec);
  moveWithRotations(20, 20, 180, -180);
  wait(200, msec);
  intakeSpdChange(20, 0);
  LeftMotor.setStopping(coast);
  LeftMotor2.setStopping(coast);
  RightMotor.setStopping(coast);
  RightMotor2.setStopping(coast);
  moveWithRotations(30, 30, 270, 270);
  wait(300, msec);
  stopIntake();
  deployCubes();
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
  while (1) {
    short yee = abs(Controller1.Axis4.position());
    if (Controller1.ButtonY.pressing()) {
      intakeSpdChange(-70, 1);
    } else {
      intakeSpdChange(onoff(), 1);
    }

    if (yee <= 21) {
      driveStraight(1);
    } else if (yee <= 70) {
      driving(1.2);
    } else {
      driving(2);
    }
    if (Controller1.ButtonA.pressing()) {
      deployCubes();
    }

    // Pusher
    RightPusher.setVelocity(Controller1.Axis2.position() / 1.4, percent);
    RightPusher.spin(fwd);

    // Arm
    if (Controller1.ButtonR2.pressing() || Controller1.ButtonL2.pressing()) {
      Arm.setVelocity(armFunc(), percent);
      Arm.spin(fwd);
    } else {
      Arm.stop();
    }
    wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
