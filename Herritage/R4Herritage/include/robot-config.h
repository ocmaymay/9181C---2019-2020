using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftMotor;
extern motor LeftMotor2;
extern motor RightMotor;
extern motor RightMotor2;
extern motor RightPusher;
extern motor IntakeR;
extern motor IntakeL;
extern motor Arm;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );