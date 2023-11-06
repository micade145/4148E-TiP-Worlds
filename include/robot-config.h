using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern motor LFront;
extern motor LMid;
extern motor LBack;
extern motor RFront;
extern motor RMid;
extern motor RBack;
extern motor Conveyor;
extern motor Lift;
extern rotation LiftRotation;
extern inertial Inertial;
extern digital_out Back;
extern digital_out Stick;
extern digital_out Claw;
extern signature Vision__F_YELLOW_MOGO;
extern signature Vision__F_RED_MOGO;
extern signature Vision__F_BLUE_MOGO;
extern signature Vision__SIG_4;
extern signature Vision__SIG_5;
extern signature Vision__SIG_6;
extern signature Vision__SIG_7;
extern vision Vision;
extern signature BackVision__B_BLUE_MOGO;
extern signature BackVision__B_RED_MOGO;
extern signature BackVision__SIG_3;
extern signature BackVision__SIG_4;
extern signature BackVision__SIG_5;
extern signature BackVision__SIG_6;
extern signature BackVision__SIG_7;
extern vision BackVision;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );