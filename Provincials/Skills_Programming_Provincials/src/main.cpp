
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
  Arm.setStopping(hold);
  LeftMotor.setMaxTorque(75, percent);
  LeftMotor2.setMaxTorque(75, percent);
  RightMotor.setMaxTorque(75, percent);
  RightMotor2.setMaxTorque(75, percent);
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

int armFuncAuto(int wat){
  int x;
    if(wat==1){
    x=80;
  }
  else if (wat==2) {
    x=-75;
  }
  else if (wat==3) {
    x=1400;
  }
  else if (wat==4) {
    x=850;
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

static void moveWithP(int velR, int velL, int degsR, int degsL){
//drives the robot with rotation-base
//set velocity with input velL and velR
  LeftMotor.setVelocity(velL, percent);
  LeftMotor2.setVelocity(velL, percent);
  RightMotor.setVelocity(velR, percent);
  RightMotor2.setVelocity(velR, percent);
//startRotateFor input degsR and degsL
  LeftMotor.startRotateFor(degsL, degrees);
  LeftMotor2.startRotateFor(degsL, degrees);
  RightMotor.startRotateFor(degsR, degrees);
  RightMotor2.rotateFor(degsR,vex::rotationUnits::deg);
//waitUntil(); is unavailable so instead
//if(one of the left && right motor is done), stopAllDrive();, break while loop.
  stopAllDrive();
    LeftMotor.setStopping(vex::brakeType::coast);
    LeftMotor2.setStopping(vex::brakeType::coast);
    RightMotor.setStopping(vex::brakeType::coast);
    RightMotor2.setStopping(vex::brakeType::coast);
  //calculates errors and corrects(p control)
  while (true){

    int x = degsL - LeftMotor.rotation(vex::rotationUnits::deg);//Error L
    int y = degsR - RightMotor.rotation(vex::rotationUnits::deg);//Error R
    Brain.Screen.print(x);
    Brain.Screen.print(y);
  if(LeftMotor.rotation(vex::rotationUnits::deg)!=degsL||RightMotor.rotation(vex::rotationUnits::deg)!=degsR)
  {
    LeftMotor.setVelocity(7,vex::velocityUnits::pct);
    LeftMotor2.setVelocity(7,vex::velocityUnits::pct);
    RightMotor.setVelocity(7,vex::velocityUnits::pct);
    RightMotor2.setVelocity(7,vex::velocityUnits::pct);
    LeftMotor.startRotateFor(x,vex::rotationUnits::deg);
    LeftMotor2.startRotateFor(x,vex::rotationUnits::deg);
    RightMotor.startRotateFor(y,vex::rotationUnits::deg); 
    RightMotor2.startRotateFor(y,vex::rotationUnits::deg);     
  }
    wait(220,msec);
    //if no errors detected
  if (x==0&&y==0){
      //brake and wait
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
    wait(550, msec);
    //if no errors again
        if (x==0&&y==0){
        stopAllDrive();
        break;  
        }

  }
  }
  }


static void deployCubes(void){
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  Lift.setStopping(brake);
  stopAllDrive();
  Lift.setVelocity(65,pct);
  Lift.spin(fwd);
  wait(1300, msec);
  Lift.setVelocity(35,pct);
  wait(1500, msec);
  Lift.setStopping(hold);
  Lift.stop();
  moveWithSeconds(7, 7, 600);
  wait(400,msec);
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
  static void trayFlipout(void){
  Arm.setVelocity(100, percent);
  Arm.spin(fwd);
  wait(1200, msec);
  Arm.spin(reverse);
  wait(500, msec);
  Arm.stop();
  Arm.setStopping(coast);
  wait(1000,msec);
  Arm.setStopping(hold);
  }

void autonomous(void) {

//wait(500, sec);

  trayFlipout();
  intakeSpdChange(35, 1);
  moveWithRotations(40, 40, 200,200);
  //intake and goes beside the tower
  wait(400, msec);
  intakeSpdChange(0, 0);
  Arm.startRotateFor(fwd, 1150, deg);
  moveWithRotations(20, 20, -100,-100);
  wait(600, msec);
  moveWithRotations(30, 30, 450,450);
  //outtakes the cube
  intakeSpdChange(50, 0);
  wait(500, msec);
  //moveWithRotations(30, 30, -400,-400);    old line when we pick the cube under the 1st tower
  moveWithRotations(30, 30, -240, -240);
  Arm.setVelocity(80, pct);
  Arm.spin(reverse);
  intakeSpdChange(45, 1);
  wait(1000,msec);
/*  //back up, lower the arm, intake on
  moveWithRotations(20, 20, -70, 70);
  wait(300, msec);
  moveWithRotations(20, 20, 350, 350);
  intakeSpdChange(65, 1);
  wait(600, msec);
  //backs up to align with the row
  moveWithRotations(20, 20, -200, -200);
  wait(400, msec);*/
 // moveWithRotations(20, 20, -155, 155); old line
  moveWithRotations(20, 20, -190, 190);
  wait(300, msec);
  moveWithSeconds(-50, -50, 700);
  wait(700, msec);
  intakeSpdChange(85, 1);
  //forward
   moveWithRotations(75,75, 4000,4000);
  Arm.stop();
  moveWithRotations(15, 15, -150, 150);
  wait(200, msec);
  //move to the wall
  moveWithRotations(50, 50, 650, 650);
  wait(200, msec);
  //align tail of the robot
  moveWithRotations(0, 70, 0, 190);
  //go stack
  moveWithRotations(50, 50, 630, 630);
  wait(300, msec);
  intakeSpdChange(35, 0);
  wait(550, msec);
  intakeSpdChange(0, 0);
  deployCubes();
  moveWithRotations(0, 30, 0,-120);
  wait(200, msec);
  moveWithRotations(20, 20, -320, -320);  
  Lift.setVelocity(-100,pct);
  Lift.spin(fwd);
  moveWithRotations(30, 30, -270, 270);
  moveWithRotations(20,20,120,120);
  moveWithRotations(30, 30, -110, 110);
  wait(300, msec);
  intakeSpdChange(85, 1);
  Arm.spin(reverse);
  moveWithSeconds(-50, -50, 700);
  wait(500, msec);
  moveWithRotations(85, 85, 1650,1650);
  wait(700, msec);
  Lift.stop();
  intakeSpdChange(50, 0);
  wait(400, msec);
  intakeSpdChange(0, 0);
  moveWithRotations(20, 20, -110, 110);
  wait(200, msec);
  Arm.setVelocity(100, percent);
  Arm.startRotateFor(fwd, 900, deg);
  moveWithRotations(20, 20, -100,-100);
  wait(600, msec);
  moveWithRotations(30, 30, 100,100);
  //outtakes the cube
  intakeSpdChange(70, 0);
  wait(500, msec);
  moveWithRotations(30, 30, -400, -400);
  Arm.setVelocity(80, pct);
  Arm.spin(reverse);
  intakeSpdChange(65, 1);
  wait(800,msec);
  moveWithRotations(30, 30, 350,350);
  wait(300,msec);
  moveWithRotations(30, 30, -110,-110);
  wait(500,msec);
  LeftMotor.resetRotation();
  RightMotor.resetRotation();
  wait(100, msec);
  moveWithRotations(30, 30, -205, 205);
  wait(300, msec);
  moveWithSeconds(-100, -100, 600);
  moveWithSeconds(-30, -30, 700);
  wait(500, msec);
  intakeSpdChange(85, 1);
  moveWithRotations(75, 76, 4000,4000);
  wait(400, msec);
  moveWithRotations(20, 20, -180, 180);
  wait(200, msec);
  //move to the wall
  moveWithRotations(70, 70, 1100, 1100);
  wait(200, msec);
  //go stack
  wait(500, msec);
  intakeSpdChange(35, 0);
  wait(550, msec);
  intakeSpdChange(0, 0);
  LeftMotor.setStopping(vex::brakeType::hold);
  LeftMotor2.setStopping(vex::brakeType::hold);
  RightMotor.setStopping(vex::brakeType::hold);
  RightMotor2.setStopping(vex::brakeType::hold);
  Lift.setStopping(brake);
  stopAllDrive();
  Lift.setVelocity(100,pct);
  Lift.spin(fwd);
  wait(800, msec);
  Lift.setVelocity(70,pct);
  wait(400, msec);
  Lift.setVelocity(40, percent);
  wait(1000, msec);
  Lift.setStopping(hold);
  Lift.stop();
  moveWithSeconds(7, 7, 600);
  wait(400,msec);
  LeftMotor.setStopping(vex::brakeType::brake);
  LeftMotor2.setStopping(vex::brakeType::brake);
  RightMotor.setStopping(vex::brakeType::brake);
  RightMotor2.setStopping(vex::brakeType::brake);
    Lift.setStopping(brake);
  //tower
  moveWithRotations(80, 80, -700, -700);  
  Lift.setVelocity(-100,pct);
  Lift.spin(fwd);
  wait(300, msec);
  moveWithRotations(40, 40, 600, -600);
  wait(300, msec);
  Lift.stop();
  intakeSpdChange(65, 1);
  moveWithRotations(50, 50, 500,500);
  //intake and goes beside the tower
  wait(300, msec);
  intakeSpdChange(0, 0);
  Arm.startRotateFor(fwd, 900, deg);
  moveWithRotations(20, 20, -100,-100);
  wait(600, msec);
  moveWithRotations(30, 30, 200,200);
  //outtakes the cube
  intakeSpdChange(40, 0);
  wait(500, msec); 

 /* //flipout
  trayFlipout();
  //intake and goes beside the tower
  intakeSpdChange(95, 1);
  moveWithSeconds(-10,-10,700);
  wait(200, msec);
  moveWithRotations(50, 50, 700, 700);
  wait(100, msec);
  //outtake
  intakeSpdChange(10, 0);
  //turn
  moveWithRotations(15, 15, 290, -290);
  wait(200, msec);
  //stops intake, raises arm to the high tower
  intakeSpdChange(0,0);
  Arm.startRotateFor(fwd, 1300, deg);
  wait(500, msec);
  //forawrd
  moveWithRotations(50, 50, 5
  oo00, 400);
  wait(100, msec);
  //outtakes the cube
  intakeSpdChange(50, 0);
  wait(800, msec);
  //back up, lower the arm, intake on
  moveWithRotations(70, 70, -400, -400);
  Arm.spin(reverse);
  intakeSpdChange(85, 1);
  wait(600, msec);
  //forward to intake
  moveWithRotations(50, 50, 300, 300);
  wait(400, msec);
  Arm.stop();
  //backs up and rotate to align with the cubes 
  moveWithRotations(50, 50, -200, -200);
  wait(200, msec);
  moveWithRotations(15, 15, -300, 300);
  wait(200, msec);
  //picks cube
  moveWithRotations(50, 50, 1700, 1700);
  wait(200, msec);
  //face towards offset right to the blue small zone
  moveWithRotations(15, 15, 150, -150);
  wait(200, msec);
  //move to the wall
  moveWithRotations(35, 35, 500, 500);
  wait(200, msec);
  moveWithRotations(35, 35, -100, -100);
  //align tail of the robot
  moveWithRotations(0, 20, 0, 100);
  //go stack
  moveWithRotations(30, 30, 150, 150);

*/
  
}


void usercontrol(void) {
}


int main() {
  pre_auton();
  Competition.autonomous(autonomous);
  while (true) {
    wait(100, msec);
  }
}


