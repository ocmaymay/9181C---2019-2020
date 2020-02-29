#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT12, ratio18_1, false);
motor LeftMotor2 = motor(PORT16, ratio18_1, false);
motor RightMotor = motor(PORT10, ratio18_1, true);
motor RightMotor2 = motor(PORT8, ratio18_1, true);
motor RightPusher = motor(PORT6, ratio36_1, false);
motor IntakeR = motor(PORT17, ratio18_1, true);
motor IntakeL = motor(PORT2, ratio18_1, false);
controller Controller1 = controller(primary);
motor Arm = motor(PORT1, ratio18_1, false);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}