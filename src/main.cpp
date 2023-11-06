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
// Controller1          controller                    
// LFront               motor         1               
// LMid                 motor         2               
// LBack                motor         3               
// RFront               motor         4               
// RMid                 motor         5               
// RBack                motor         6               
// Conveyor             motor         16              
// Lift                 motor         17              
// LiftRotation         rotation      18              
// Inertial             inertial      19              
// Back                 digital_out   A               
// Stick                digital_out   B               
// Claw                 digital_out   C               
// Vision               vision        10              
// BackVision           vision        15              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <cmath>
#include "AutoSelector.h"
#include "pid_Functions.h"
#include "Functions.h"
// #include "Tasks.h"
// #include "pid.h"

using namespace vex;

// A global instance of competition
competition Competition;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

bool RedAlliance = false;
bool enableSelect = true;
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // Starting States
  // ClawCLosed();
  // BackClosed();
  // StickUp();


  // Auto Selector
//   while(enableSelect) {
//       // Alliance Color Buttons
//       isRed.render();
//       isBlue.render();
//       if (isRed.isClicked()) {
//         RedAlliance = true;
//         isRed.buttonColor = vex::red;
//         isBlue.buttonColor = vex::black;
//       }
//       if (isBlue.isClicked()) {
//         RedAlliance = false;
//         isBlue.buttonColor = vex::blue;
//         isRed.buttonColor = vex::black;
//       }

//       // Iterate through the button array and render buttons
//       for(int i = 0; i < 12; i++){
//         // Render buttons
//         autonButtons[i].render();
//       // If a button is pressed, iterate again and clear all button colors
//         if(autonButtons[i].isClicked()){
//           for(int i = 0; i < 12; i++){
//         // Clear all button colors
//            autonButtons[i].buttonColor = vex::black;
//           }
//       // Then select and highlight the pressed button
//         autonButtons[i].buttonColor = vex::color(255,145,175);
//         autonToRun = i;
//         }
//       }

//       // Print selected button info
//       if (autonToRun == 0) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "RightWP - Neutral and Line of Rings");
//       }
//       if (autonToRun == 1) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "LeftWP - Neutral and Ring Star");
//       }
//       if (autonToRun == 2) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "SoloWP - Tall Neutral");
//       }
//       if (autonToRun == 3) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "SoloWP - Right Neutral");
//       }
//       if (autonToRun == 4) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "SoloWP - Line of Rings");
//       }
//       if (autonToRun == 5) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "SoloWP - Left Neutral");
//       }
//       if (autonToRun == 6) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "Right Mid - Fakeout");
//       }
//       if (autonToRun == 7) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "Right Mid - Straight");
//       }
//       if (autonToRun == 8) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "nothing");
//       }
//       if (autonToRun == 9) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "nothing");
//       }
//       if (autonToRun == 10) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "nothing");
//       }
//       if (autonToRun == 11) {
//       Brain.Screen.clearLine(1);
//       Brain.Screen.setCursor(1 , 1);
//       Brain.Screen.print( "nothing");
//       }
      

//       wait(20, msec);
// }
}

//////// Autos ////////

// Alliance Color
// enum AutoColor {AutoRed, AutoBlue};
void RightWP(int RightWPMode) { // Auto 0, Button 1
  RobotDrive.setDriveVelocity(50, pct);
  RobotDrive.setTurnVelocity(30, pct);

  ResetEncoders(); // Reset Drive Position
  ClawOpen();

  if (RightWPMode == 1) {
    StickDown();
    Move(640, 13, 0, 9, 800); // Grab 
    Move(0, 0, 270, 12, 800);

    StickUp();
    wait(250, msec);
    VisionToMogo(3, 800);
    Move(360, 6, Inertial.angle(), 8, 750);
    wait(250, msec);
    ClawCLosed();

    Move(-550, 7, 330, 9, 1500);
    wait(250, msec);

    Move(-230, 8, 270, 9, 1000);
    BackOpen();
    RobotDrive.setTurnVelocity(30, pct);
    RobotDrive.turn(left);
    // waitUntil(Optical.color() = blue);
    Move(-80, 4, Inertial.angle(), 5, 800);
  }

  else if(RightWPMode == 2) {
    Move(840, 13, 0, 10, 1500);
    ClawCLosed();
    Move(-460, 8, 0, 10, 1500);
    BackOpen();
    Move(-400, 6, 270, 9, 1000);
  }

  else if (RightWPMode == 3) {
    thread RWPstick = thread([] {DelayedStick(300);});
    thread(RWPstick).detach();
    Move(570, 13, 0, 9, 700);
    Move(-500, 13, 0, 8, 1500);
    StickUp();

    RobotDrive.driveFor(forward, 1, inches, false);
    wait(250, msec);
    VisionToMogo(4, 500);
    Move(340, 7, Inertial.angle() + 6, 3, 900);

    ClawCLosed(); // Claw.set(false);
    BackOpen();
    Move(-250, 5, 270, 9, 1000);
    if (RedAlliance == true) {
      BackToRedMogo(-200, 4, 2, 1000);
    }
    else if (RedAlliance == false) {
      BackToBlueMogo(-200, 4, 2, 1000);
    }
    // Move(-200, 4, Inertial.angle(), 2, 1000);
  }

  BackClosed();
  Lift.spinTo(1.3, rev, false);
  wait(500, msec);

  Conveyor.spin(forward, 95, pct);
  wait(250, msec);
  Move(1160, 3, 0, 9, 3000);
  Move(500, 3, 90, 5, 1500);

  thread liftDownRWP = thread([] {DelayedLift(.2, 300);});
  thread(liftDownRWP).detach();
  Conveyor.stop();
  Move(-1040, 10, 0, 11, 2000);
  BackOpen();

  wait(500, msec);
  RobotDrive.setDriveVelocity(20, pct);
  RobotDrive.driveFor(forward, 2, inches, false);
  RobotDrive.setStopping(coast);
  Conveyor.stop();
}

void LeftWP() { // Auto 1, Button 2
  ResetEncoders();
  ClawOpen();

  thread LWPstick = thread([] {DelayedStick(300);});
  thread(LWPstick).detach();

  Move(610, 13, 0, 9, 750);
  Move(-600, 13, 0, 8, 1500);
  StickUp();

  // Move(0, 0, Inertial.angle() - 5, 5, 700);
  RobotDrive.driveFor(reverse, .5, inches, false);
  wait(250, msec);
  
  VisionToMogo(4, 500);
  Move(360, 6, Inertial.angle(), 3, 900);

  wait(150, msec);
  ClawCLosed(); // Claw.set(false);
  BackOpen();

  Move(-280, 8, 270, 3, 1000);
    
  if (RedAlliance == true) {
    BackToRedMogo(-400, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-400, 4, 2, 1000); 
  }

  // BackToMogo(-400, 4, 2, 1000);
  BackClosed();
  Lift.spinTo(1, rev, false);
  

  Move(500, 9, 0, 10, 1100);
  Conveyor.setVelocity(95, pct);
  Conveyor.spin(forward);

  Move(1300, 4, 85, 8, 3000);
  Lift.spinTo(.1, rev, false);

  BackOpen();
  RobotDrive.setDriveVelocity(30, pct);
  RobotDrive.driveFor(forward, 3, inches);
}

void SoloWP(int SoloMode) { // Auto 2, Button 3-6
  ResetEncoders(); //Reset drive position

  Lift.setVelocity(100, pct);  //Deposit first ring
  Lift.spinFor(forward, 360, degrees, false);
  wait(100, msec);
  ClawOpen();
  wait(500, msec);

  Move(-480, 10, 175, 12, 1300);  //Move backwards and lower BackLift
  BackOpen();
  wait(250, msec);

  Move(-1890, 10, 177, 11, 2600); //Grab Alliance

  if (RedAlliance == true) {
    BackToRedMogo(-200, 4, 2, 800);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-200, 4, 2, 800); 
  }

  // BackToMogo(-200, 4, 2, 800);
  // Move(-100, 3, Inertial.angle(), 5, 800);
  // RobotDrive.driveFor(forward, 1, inches);
  BackClosed();
  wait(100, msec);
  Conveyor.spin(forward, 95, pct);
  wait(750, msec);
  

  if(SoloMode == 1) {                   // Tall Neutral, Button 3
  Lift.spinTo(0, rev, false);
  Conveyor.stop();
  wait(500, msec);

  // Move(1040, 9, 218, 8, 3000);  //Grab Tall Neutral
  Move(500, 9, 218, 8.9, 1500);

  // Wack Vision Tracking
  // thread MoveThread = thread([]{Move(650, 7, Inertial.angle(), 0, 1250);});
  // thread(MoveThread).detach();
  // VisionToMogo(3, 1250);

  // FrontToMogo(650, 7, 3, 1250);
  FrontToMogo(0, 0, 3, 300);
  Move(650, 7, Inertial.angle(), 3, 1000);

  ClawCLosed();
  wait(250, msec);
  // Move(-860, 10, 220, 9, 1000);
  Lift.spinTo(1, rev, false);
  Move(0, 0, 148, 10, 1000);
  Conveyor.spin(forward, 95, pct);
  Move(1500, 6, Inertial.angle() -5, 1, 4000);
  BackOpen();

  RobotDrive.driveFor(forward, 1, inches, false);
  Conveyor.stop();
  Lift.spinTo(0, rev);
  }

  if (SoloMode == 2) {               // Right Neutral, Button 4
  Conveyor.stop();
  Lift.spinTo(0, rev, false);
  wait(500, msec);
  // Conveyor.spin(forward, 95, pct);

  Move(410, 9, 270, 7, 700);  //Grab Neutral
  // wait(250, msec);
  FrontToMogo(300, 8, 2, 1000);
  ClawCLosed();

  Lift.spinTo(.5, rev, false);
  Move(-350, 8, 270, 6, 1000);
  Conveyor.spin(forward, 95, pct);
  Move(12000, 4, 180, 10, 5000);
  BackOpen();
  RobotDrive.setDriveVelocity(30, pct);
  RobotDrive.driveFor(forward, 1, inches);

  //// Reverse and Drop Goal ////
  // Move(-850, 10, 260, 9, 1000);
  // BackOpen();
  // RobotDrive.driveFor(forward, 1, inches, false);
  }

  if (SoloMode == 3) {                // Line of Rigns, Button 5
  Lift.spinTo(1.3, rev, false);
  Move(700, 3, 270, 7, 3000);
  Move(500, 3, 0, 5, 1500);

  Conveyor.stop();
  thread SWP3Lift = thread([] {DelayedLift(.1, 300);});
  thread(SWP3Lift).detach();
  Move(-1000, 8, 270, 7, 2000);
  BackOpen();

  RobotDrive.driveFor(forward, 1, inches, false);
  Lift.spinTo(0, rev);
  }
}

void SoloLeftNeutral() { // Auto 5, Button 6
  ResetEncoders();

  Lift.setVelocity(100 ,pct);
  Lift.spinTo(180, degrees);
  ClawOpen();
  wait(250, msec);

  Move(0, 0, 280, 12, 1000);
  Lift.spinTo(0, rev, false);
  // VisionToMogo(4, 500);

  Move(930, 12, Inertial.angle(), 8, 2000);
  wait(150, msec);
  ClawCLosed();
  wait(150, msec);

  Move(-400, 8, 270, 7, 1200);
  BackOpen();
  Move(-1800, 8, 180, 12, 2600);
  
  if (RedAlliance == true) {
    BackToRedMogo(-300, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-300, 4, 2, 1000);
  }

  Lift.spinTo(1.3, rev, false);
  BackClosed();
  Conveyor.spin(forward, 95, pct);
  Move(800, 3, 270, 9, 3000);
  Move(500, 3, 0, 5, 1500);
  
  thread SWP3Lift = thread([] {DelayedLift(.1, 300);});
  thread(SWP3Lift).detach();
  Conveyor.stop();
  Move(-900, 8, 270, 12, 2000);
  BackOpen();

  RobotDrive.driveFor(forward, 1, inches, false);
  Lift.spinTo(0, rev);

  // Move(-1890, 10, 177, 11, 2600);
}

void RightMidFakeout() { //Auton 6, Button 7
  ResetEncoders();
  Lift.setVelocity(100, pct);
  ClawOpen();

  Move(990, 13, 312, 10, 1500);
  
  wait(150, msec);
  ClawCLosed();
  wait(150, msec);

  Move(-700, 12, 270, 1.5, 1500);

  BackOpen();
  Move(-300, 7, 270, 9, 1000);

  if (RedAlliance == true) {
    BackToRedMogo(-300, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-300, 4, 2, 1000);
  }

  BackClosed();

  Lift.spinTo(1.3, rev, false);
  wait(500, msec);

  Conveyor.spin(forward, 95, pct);

  Move(700, 4, 0, 10, 2500);
  Move(500, 3, 90, 5, 1500);

  thread SWP3Lift = thread([] {DelayedLift(.1, 300);});
  thread(SWP3Lift).detach();
  Conveyor.stop();
  Move(-900, 8, 0, 12, 2000);
  BackOpen();

  RobotDrive.driveFor(forward, 1, inches, false);
  Lift.spinTo(0, rev);
}
void RightMidStraight() { // Auto 7, Button 8
  ResetEncoders();
  // Angle Rotated -30 degrees
  // Add 30 degrees to all angles
  // Inertial.setRotation(330, degrees);
  Lift.setVelocity(100, pct);
  ClawOpen();
  
  Move(990, 13, Inertial.angle(), 10, 1500);
  wait(150, msec);
  ClawCLosed();
  wait(150, msec);
  Move(-600, 12, 300, 4, 1500);

  BackOpen();
  Move(-300, 7, 300, 9, 1000);

  if (RedAlliance == true) {
    BackToRedMogo(-300, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-300, 4, 2, 1000);
  }
  
  BackClosed();
  Lift.spinTo(1.3, rev, false);
  wait(500, msec);
  Conveyor.spin(forward, 95, pct);

  Move(700, 4, 30, 10, 2200);
  Move(500, 3, 120, 5, 1500);

  thread SWP3Lift = thread([] {DelayedLift(.1, 400);});
  thread(SWP3Lift).detach();
  Conveyor.stop();
  Move(-900, 8, 30, 12, 2000);
  BackOpen();

  RobotDrive.driveFor(forward, 1, inches, false);
  Lift.spinTo(0, rev);
}

void LeftMid() { // Auto 8, Button 9
  ResetEncoders();
  Lift.setVelocity(100, pct);
  ClawOpen();

  // thread LeftMidStick = thread([] {DelayedStick(800);});
  Lift.spinTo(.5, rev, false);
  // thread(LeftMidStick).detach();
  Conveyor.spin(forward, 12, volt);

  Move(500, 12, 50, 13, 1500);
  FrontToMogo(0, 4, 2, 500);
  Move(500, 12, Inertial.angle(), 13, 1500);
  Lift.spinTo(0, rev, false);
  Conveyor.stop();
  FrontToMogo(400, 4, 3, 800);
  // Move(300, 5, Inertial.angle() + 1, 3, 1000);
  ClawCLosed();

  Move(-1100, 8, 30, 7, 1500);
  Move(0, 0, 270, 8, 1000);
  BackOpen();

  if (RedAlliance == true) {
    BackToRedMogo(-400, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-400, 4, 2, 1000);
  }
  Lift.spinTo(1.3, rev, false);
  BackClosed();
  Conveyor.spin(forward, 12, volt);

  Move(1000, 5, 0, 7, 1500);
  Move(1200, 3, 89, 7, 5000);

  // Move(700, 3, Inertial.angle(), 2.5, 1000);
  // wait(250, msec);
  // Move(-600, 3, Inertial.angle(), 2.5, 1000);
  // wait(250, msec);
  // Move(600, 3, Inertial.angle(), 2.5, 1000);
  // wait(250, msec);
  // Move(-300, 3, Inertial.angle(), 2.5, 1000);

  Lift.spinTo(0, rev, false);
  Conveyor.stop();
  BackOpen();
  RobotDrive.setDriveVelocity(30, pct);
  RobotDrive.driveFor(forward, 2, inches);
}

void DoubleNeutral() { // Auto 9, Button 10
  ResetEncoders();
  ClawOpen();

  thread RWPstick = thread([] {DelayedStick(300);});
  thread(RWPstick).detach();
  Move(570, 13, 0, 9, 700);
  
  Move(-400, 13, 0, 8, 1500);
  StickUp();
  wait(500, msec);

  Move(-200, 3, 330, 8, 1000);
  FrontToMogo(0, 4, 2, 500);

  Move(1000, 8, Inertial.angle(), 5, 1500);
  wait(100, msec);
  ClawCLosed();
  wait(100, msec);

  Move(-1000, 8, Inertial.angle(), 5, 1500);
  BackOpen();
  Move(-360, 3, 270, 9, 1000);

  if (RedAlliance == true) {
    BackToRedMogo(-200, 4, 2, 1000);
  }
  else if (RedAlliance == false) {
    BackToBlueMogo(-200, 4, 2, 1000);
  }

  BackClosed();

  Move(0, 0, 180, 8, 1000);
  ClawOpen();

  Move(0, 0, 330, 8, 800);
  FrontToMogo(300, 4, 2, 1000);
  wait(50, msec);
  ClawCLosed();
  wait(100, msec);
  Move(-500, 4, 0, 9, 1000);

}

void TotallyRealProgSkills() {

}
//////// Test Autons ////////
void BoxTest() {
  while (true) {
  Move(360, 10, 0, 9);
  wait(250, msec);
  Move(0, 10, 270, 10);
  wait(250, msec);
  Move(360, 10, 270, 9);
  wait(250, msec);
  Move(0, 10, 180, 10);
  wait(250, msec);
  Move(360, 10, 180, 9);
  wait(250, msec);
  Move(0, 10, 90, 10);
  wait(250, msec);
  Move(360, 10, 90, 10);
  wait(250, msec);
  Move(0, 10, 0, 10);
  }
}
void Tuning() {
  while(true) {
  Move(400, 10, 0, 9);
  wait(250, msec);
  Move(-400, 10, 0, 9);
  wait(250, msec);
  Move(0, 10, 90, 10);
  wait(250, msec);
  Move(0, 10, 180, 10);
  wait(250, msec);
  Move(0, 10, 0, 10);
  wait(250, msec);
}
}
void TurnTuning() {
  Move(0, 0, 90, 7, 1500);
  wait(250, msec);
  Move(0, 0, 0, 7, 1500);
  wait(250, msec);
  Move(0, 0, 270, 7, 1500);
  wait(250, msec);
  Move(0, 0, 0, 7, 1500);
}
void PneumaticTest() {
  ClawOpen();
  wait(500, msec);
  ClawCLosed();
  wait(500, msec);
  BackOpen();
  wait(500, msec);
  BackClosed();
  wait(500, msec);
  StickDown();
  wait(500, msec);
  StickUp();
}
void FrontVisionTest() {
  ClawOpen();
  FrontToMogo(0, 4, 2, 100000);
}
void BackVisionTest() {
  BackOpen();
  if (RedAlliance == true) {
    BackToRedMogo(0, 4, 2, 100000);
  }
  else if(RedAlliance == false) {
    BackToBlueMogo(0, 4, 2, 100000);
  }

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
  // Reset Sensors
  Inertial.resetRotation();
  // ResetEncoders();

  // Testing Stuff 
 
  // //// Run Selected Auto ////
  if (autonToRun == 0) { // Button 1
    RightWP(3);
  }
  if (autonToRun == 1) { // Button 2
    LeftWP();
    //  LeftWP();
  }  
  if (autonToRun == 2) { // Button 3
    SoloWP(1);
    // Tuning();
  }
  if (autonToRun == 3) { // Button 4
    SoloWP(2);
    //  RightMid();
  }
  if (autonToRun == 4) { // Button 5
    SoloWP(3);
    //  DoubleNeutral();
  }
  if (autonToRun == 5) { // Button 6
    SoloLeftNeutral();
    //  SoloWP(2);
  }
  if (autonToRun == 6) { // Button 7
    RightMidFakeout();
      // LeftMid();
  }
  if (autonToRun == 7) { // Button 8
    RightMidStraight();
    // LeftMid();
    // SoloWP(3);
  }
  if (autonToRun == 8) { // Button 9
    LeftMid();
    //  BetterProgSkills(false);
  }
  if (autonToRun == 9) { // Button 10
    DoubleNeutral();
  }
  if (autonToRun == 10) { // Button 11
    BackVisionTest();
  }
  if (autonToRun == 11) { // Button 12
    FrontVisionTest();
  }
  //// End of Auto Select ////
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
  // Disable Auto Selector and Start Tasks
  // enableSelect = false; 
  Brain.Screen.clearScreen(black); 
  task ConveyorTask = task(ConveyorControl);
  // task RingStopTask = task(RingStop);

  while (1) {
  //////////////// Drivetrain Controls ////////////////
  Brain.Screen.clearLine(1);
  Brain.Screen.setCursor(1,1);
  Brain.Screen.print("Inertial Angle: %4.0f, Inertial Rotation: %4.0f",
  Inertial.angle(), Inertial.rotation());
  //// Arcade 
  //Read Controller inputs
    double DriveSpeed = Controller1.Axis2.position(percent) 
    + Controller1.Axis3.position(percent);
    double TurnSpeed = ( Controller1.Axis1.position(percent) * .75 )
    + ( Controller1.Axis4.position(percent) *.75 );

    double LeftStickPos = ( std::abs( Controller1.Axis3.position(percent) ) + 
    std::abs( Controller1.Axis4.position(percent) ) );
    double RightStickPos = ( std::abs( Controller1.Axis2.position(percent) ) + 
    std::abs( Controller1.Axis1.position(percent) ) );
  
  //Deadband
    if (std::abs(DriveSpeed) < 10) {
     DriveSpeed = 0; 
    }
    if (std::abs(TurnSpeed) < 10) {
      TurnSpeed = 0;
    } 

  //Output to Drivetrain
    LeftDrive.spin(forward, DriveSpeed + TurnSpeed, percent);
    RightDrive.spin(forward, DriveSpeed - TurnSpeed, percent);

    // Change Drive Stopping
    if (LeftStickPos > 1) {
      LeftDrive.setStopping(hold);
      RightDrive.setStopping(hold);
    }
    else if (RightStickPos > 1) {
      LeftDrive.setStopping(brake);
      RightDrive.setStopping(brake);
    }
    
    // //// Exponential Tank Drive ////
    // int LeftSign = Controller1.Axis3.position(percent) /
    //  Controller1.Axis3.position(percent);
    // int RightSign = Controller1.Axis2.position(percent) /
    //  Controller1.Axis2.position(percent);

    // double LeftSqr = Controller1.Axis3.position(percent) *
    // abs(Controller1.Axis3.position(percent)); 
    // double RightSqr = Controller1.Axis2.position(percent) *
    // abs(Controller1.Axis2.position(percent)); 

    // double LeftPower = (LeftSqr*LeftSign) / 100;
    // double RightPower = (RightSqr*RightSign) / 100;;

    // LeftDrive.spin(forward, LeftPower, percent);
    // RightDrive.spin(forward, RightPower, percent);

    // Lift
    if (Controller1.ButtonR1.pressing()) {
      Lift.spin(forward, 100, pct);
    }
    else if(Controller1.ButtonR2.pressing()) {
      Lift.spin(reverse, 100, pct);
    }
    else Lift.stop(hold);

    // Conveyor 
    // Controller1.ButtonRight.pressed(FwdRingToggle);
    // Controller1.ButtonLeft.pressed(RevRingToggle);

    // Claw
    Controller1.ButtonL1.pressed(ClawToggle);
    // Back Clamp
    Controller1.ButtonL2.pressed(BackToggle);
    // Stick
    Controller1.ButtonX.pressed(StickToggle);

    wait(20, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  StickUp();
  ClawCLosed();
  BackClosed();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while(enableSelect) {
      // Alliance Color Buttons
      isRed.render();
      isBlue.render();
      if (isRed.isClicked()) {
        RedAlliance = true;
        isRed.buttonColor = vex::red;
        isBlue.buttonColor = vex::black;
      }
      if (isBlue.isClicked()) {
        RedAlliance = false;
        isBlue.buttonColor = vex::blue;
        isRed.buttonColor = vex::black;
      }

      // Iterate through the button array and render buttons
      for(int i = 0; i < 12; i++){
        // Render buttons
        autonButtons[i].render();
      // If a button is pressed, iterate again and clear all button colors
        if(autonButtons[i].isClicked()){
          for(int i = 0; i < 12; i++){
        // Clear all button colors
           autonButtons[i].buttonColor = vex::black;
          }
      // Then select and highlight the pressed button
        autonButtons[i].buttonColor = vex::color(255,145,175);
        autonToRun = i;
        }
      }

      // Print selected button info
      if (autonToRun == 0) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "RightWP - Neutral and Line of Rings");
      }
      if (autonToRun == 1) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "LeftWP - Neutral and Ring Star");
      }
      if (autonToRun == 2) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "SoloWP - Tall Neutral");
      }
      if (autonToRun == 3) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "SoloWP - Right Neutral");
      }
      if (autonToRun == 4) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "SoloWP - Line of Rings");
      }
      if (autonToRun == 5) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "SoloWP - Left Neutral");
      }
      if (autonToRun == 6) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "Right Mid - Fakeout");
      }
      if (autonToRun == 7) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "Right Mid - Straight");
      }
      if (autonToRun == 8) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "Left Mid + Ring Stars");
      }
      if (autonToRun == 9) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "Double Neutral - Right Side");
      }
      if (autonToRun == 10) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "nothing");
      }
      if (autonToRun == 11) {
      Brain.Screen.clearLine(1);
      Brain.Screen.setCursor(1 , 1);
      Brain.Screen.print( "nothing");
      }
      wait(20, msec);
}

  // Run the pre-autonomous function.
  pre_auton();
  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
