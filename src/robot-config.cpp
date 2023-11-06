#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LFront = motor(PORT1, ratio18_1, true);
motor LMid = motor(PORT2, ratio18_1, true);
motor LBack = motor(PORT3, ratio18_1, true);
motor RFront = motor(PORT4, ratio18_1, false);
motor RMid = motor(PORT5, ratio18_1, false);
motor RBack = motor(PORT6, ratio18_1, false);
motor Conveyor = motor(PORT16, ratio6_1, true);
motor Lift = motor(PORT17, ratio36_1, true);
rotation LiftRotation = rotation(PORT18, false);
inertial Inertial = inertial(PORT19);
digital_out Back = digital_out(Brain.ThreeWirePort.A);
digital_out Stick = digital_out(Brain.ThreeWirePort.B);
digital_out Claw = digital_out(Brain.ThreeWirePort.C);
/*vex-vision-config:begin*/
signature Vision__F_YELLOW_MOGO = signature (1, 881, 2725, 1803, -3695, -3431, -3563, 2.7, 0);
signature Vision__F_RED_MOGO = signature (2, 4157, 9671, 6914, -1207, -677, -942, 1.3, 0);
signature Vision__F_BLUE_MOGO = signature (3, -2417, -1593, -2005, 8191, 11763, 9977, 2.7, 0);
signature Vision__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision = vision (PORT10, 50, Vision__F_YELLOW_MOGO, Vision__F_RED_MOGO, Vision__F_BLUE_MOGO, Vision__SIG_4);
/*vex-vision-config:end*/
/*vex-vision-config:begin*/
signature BackVision__B_BLUE_MOGO = signature (1, -2633, -1927, -2280, 3011, 13107, 8059, 1.6, 0);
signature BackVision__B_RED_MOGO = signature (2, 7807, 10621, 9214, -1191, -655, -923, 3, 0);
vision BackVision = vision (PORT15, 50, BackVision__B_BLUE_MOGO, BackVision__B_RED_MOGO);
/*vex-vision-config:end*/

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}