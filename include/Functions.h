#include "vex.h"
#include "robot-config.h"
#include <cmath>


// // //////// General Functions ////////
void BackOpen() {
  Back.set(true);
}
void BackClosed() {
  Back.set(false);
}
void ClawOpen() {
  Claw.set(true);
}
void ClawCLosed() {
  Claw.set(false);
}
void StickDown() {
  Stick.set(false);
}
void StickUp() {
  Stick.set(true);
}
int DelayedStick(int stickWait) {
  wait(stickWait, msec);
  StickDown();
  return 1;
}
int DelayedLift(double liftTarget, int liftWait) {
  wait(liftWait, msec);
  Lift.spinTo(liftTarget, rev, true);
  return 1;
}

// /////////// Toggles ///////////
// Credit to Hudson Robotics - VexForum
// // Conveyor Toggle
double ConSpeed = 0; 
bool ConLast = false;
double ConPosition = 0;
double LastConPosition = 0;

int ConveyorControl() {
  while(true) {
  ConPosition = Conveyor.position(degrees);
  // double DeltaPosition = ConPosition - LastConPosition;
	if(Controller1.ButtonRight.pressing()) {
		if(!ConLast)
		{
			//If not going forward
			if(ConSpeed != 95) 
			{
				//Go forward
				ConSpeed = 95; 
			}
			else {
				//Else stop
				ConSpeed = 0; 
			}
			ConLast = true;
		}
	} else if(Controller1.ButtonLeft.pressing()) {
		if(!ConLast)
		{
			//If not going reverse
			if(ConSpeed != -75) 
			{
				//Go reverse
				ConSpeed = -75;
			}
			else {
				//Else stop
				ConSpeed = 0;
			}
			ConLast = true;
		}
	}
	//when button is released, let go of latch.
	else {
		ConLast = false;
	}

  Conveyor.spin(forward, ConSpeed, pct);

  if (Lift.position(rev) < .3) {
    Conveyor.stop();
  }

  // if (std::abs(ConSpeed) > 0) {
  //   if (DeltaPosition < 0 ){
  //     Conveyor.spin(reverse, 75, pct);
  //     wait(500, msec);
  //     Conveyor.spin(forward, ConSpeed, pct); 
  //   }
  // }

  // LastConPosition = ConPosition;
  wait(20, msec);
  }
  return(1);
}

// // Non Working Conveyor Toggles
// void FwdRingToggle() {
//   bool FRState = Conveyor.isSpinning();
//   FRState = !FRState;

//   if (FRState) {
//     Conveyor.spin(forward, 100, pct);
//   }
//   else (Conveyor.stop());
// }

// void RevRingToggle() {
//   bool RRState = Conveyor.isSpinning();
//   RRState = !RRState;

//   if (RRState) {
//     Conveyor.spin(reverse, 75, pct);
//   }
//   else (Conveyor.stop());
// }

// // Pneumatic Toggles
void ClawToggle() {
  bool ClawState = Claw.value();
  ClawState = !ClawState;
  Claw.set(ClawState);
}
void BackToggle() {
  bool BackState = Back.value();
  BackState = !BackState;
  Back.set(BackState);
}
void StickToggle() {
  bool StickState = Stick.value();
  StickState = !StickState;
  Stick.set(StickState);
}
