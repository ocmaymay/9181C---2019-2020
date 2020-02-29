#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT8, ratio18_1, false);
motor LeftMotor2 = motor(PORT9, ratio18_1, false);
motor RightMotor = motor(PORT3, ratio18_1, true);
motor RightMotor2 = motor(PORT2, ratio18_1, true);
motor RightPusher = motor(PORT7, ratio36_1, false);
motor IntakeR = motor(PORT4, ratio18_1, false);
motor IntakeL = motor(PORT10, ratio18_1, true);
controller Controller1 = controller(primary);

// VEXcode generated functions



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}