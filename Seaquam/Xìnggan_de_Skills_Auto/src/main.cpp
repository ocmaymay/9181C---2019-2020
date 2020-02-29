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
  Arm.setStopping(brake);
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
    //intake speed
    x=85;
  }
  else if (Controller1.ButtonL1.pressing()) {
    ///outtake speed
    x=-15;
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
    x=-75;
  }
  else if (Controller1.ButtonL2.pressing()) {
    x=75;
  }
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
    RightPusher.setStopping(brake);
  }

  static void trayFlipout(void){
  Arm.setVelocity(80, percent);
  Arm.spin(fwd);
  intakeSpdChange(100,0);
  wait(300, msec);
  Arm.spin(reverse);
  wait(400, msec);
  }

  static void driveStraight(void){
      LeftMotor.spin(vex::directionType::fwd,
                     (Controller1.Axis3.position()/1),
                     vex::velocityUnits::pct);
      LeftMotor2.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/1),
                      vex::velocityUnits::pct);
      RightMotor.spin(vex::directionType::fwd,
                      (Controller1.Axis3.position()/1),
                      vex::velocityUnits::pct);
      RightMotor2.spin(vex::directionType::fwd,
                       (Controller1.Axis3.position()/1),
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
void autonomous(void) {
  trayFlipout();
  intakeSpdChange(85, 1);
  moveWithRotations(50, 50, 1000, 1000);
  intakeSpdChange(20,0);
  Arm.setVelocity(80, pct);
  Arm.rotateFor(fwd, 900, deg);
  wait(700, msec);
  moveWithRotations(50, 50, -1000, -1000);


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
 //RightPusher.resetRotation();
 //int i = 0;
 //int j = RightPusher.rotation(deg);
 //int duration = 0;
 // int loops = 0;
  while (1) {


  /*  loops++;
   i = RightPusher.rotation(deg);
   if(loops%5==0){
   Controller1.Screen.clearLine();
   Controller1.Screen.print(RightPusher.rotation(deg));
    if(j==i&&RightPusher.rotation(deg)<=30) {
          duration++;
          if (duration>15){
            RightPusher.resetRotation();
            duration = 0;
          }
    }
    }
    j = RightPusher.rotation(deg);



    i = RightPusher.rotation(deg);
    Controller1.Screen.clearLine();
    Controller1.Screen.print(RightPusher.rotation(deg));
    if(j!=i){
     Brain.Screen.print(duration);
    }
    else if(RightPusher.rotation(deg)<=15) {
          duration++;
          if (duration>20){
            RightPusher.resetRotation();
            duration = 0;
          }
    }
    j = RightPusher.rotation(deg);

*/







    short yee = abs(Controller1.Axis4.position());
    intakeSpdChange(onoff(), 1);
    if (yee <= 15) {
      driveStraight();
    }
    else {
      driving(1.2);
    }
    if (Controller1.ButtonA.pressing()){
      deployCubes();
    }



    /*if(Controller1.ButtonX.pressing()||Controller1.ButtonB.pressing()){
        if(Controller1.ButtonB.pressing()){
          
        }
      RightPusher.setVelocity(upDwn(), percent);
      RightPusher.spin(fwd);
    }
    else {
      RightPusher.stop();
    }*/

      //Pusher

    if (Controller1.ButtonA.pressing()){
      deployCubes();
    }

    //if(Controller1.Axis2.position()>=3){
    //  RightPusher.setVelocity(traySpeedChanger(j), percent);
    //}
   // else {
    RightPusher.setVelocity(Controller1.Axis2.position()/1.4, percent);
    RightPusher.spin(fwd);
   // }

        //Arm
    if(Controller1.ButtonR2.pressing()||Controller1.ButtonL2.pressing()){
      Arm.setVelocity(armFunc(), percent);
      Arm.spin(fwd);
    }
    else {
      Arm.stop();
    }
    
    vex::task::sleep(20); // Sleep the task for a short amount of time to
                          // prevent wasted resources.
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


