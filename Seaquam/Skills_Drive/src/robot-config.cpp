#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftMotor = motor(PORT11, ratio18_1, false);
motor LeftMotor2 = motor(PORT13, ratio18_1, false);
motor RightMotor = motor(PORT20, ratio18_1, true);
motor RightMotor2 = motor(PORT9, ratio18_1, true);
motor RightPusher = motor(PORT17, ratio36_1, false);
motor IntakeR = motor(PORT2, ratio18_1, true);
motor IntakeL = motor(PORT7, ratio18_1, false);
controller Controller1 = controller(primary);
motor Arm = motor(PORT15, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}