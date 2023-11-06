#include "vex.h"
#include "pid.h"
#include <cmath>
#pragma once

///// Drive Configuration ////
motor_group LeftDrive(LFront, LMid, LBack);
motor_group RightDrive(RFront, RMid, RBack);
drivetrain RobotDrive(LeftDrive, RightDrive, 10., 15, 12, inches);

// //// Drive Functions
void ResetEncoders() {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
}
void SetDriveVoltage(double leftvolt, double rightvolt) {
  LeftDrive.spin(forward, leftvolt, volt);
  RightDrive.spin(forward, rightvolt, volt);
}
// enum DriveStopMode{Brake, Hold, Coast};
// void DriveBrake(enum DriveStopMode) {
//   switch(DriveStopMode) {
//     case Brake: LeftDrive.stop(brake);
//   }
//   LeftDrive.stop(brake);
//   RightDrive.stop(brake);
// }
void DriveHold() {
  LeftDrive.stop(hold);
  RightDrive.stop(hold);
}
void DriveCoast() {
  LeftDrive.stop(coast);
  RightDrive.stop(coast);
}

// ///////////////////// PID /////////////////////
// //// Drive and Turn PID Constants ////

// // PID drivePID(.07, 0.2);
PID drivePID(.073, 0.2);
PID turnPID(.16, 0.2);

// //// Ideal parameters ////
// // Turn: 10    With Goal: 7
// // Move: 10    Prog Skills: 6;
void Move(double target, double maxPower, double lineAssist, 
double maxlA = 12, double maxTime = 3000) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  timer DriveTimer;
  DriveTimer.reset();
  DriveTimer.time(msec);
  while (true){
    double DrivePosition = (LeftDrive.position(degrees) 
    + RightDrive.position(degrees)) / 2;
    // double DrivePosition = DriveAVG*(3/5);
    double DriveHeading = Inertial.rotation();

    double DriveError = target - DrivePosition;
    double TurnError = lineAssist - DriveHeading;
    
    if (TurnError > 180) {
      TurnError -=360;
    }

    if (TurnError < -180) {
      TurnError += 360;
    }

    double DrivePower = drivePID.calculateErr(DriveError);
    double TurnPower = turnPID.calculateErr(TurnError);

    // Power Bounds
    if (TurnPower > maxlA) {
      TurnPower = maxlA;
    }
    if (TurnPower < -maxlA) {
      TurnPower = -maxlA;
    }

    if (DrivePower > maxPower) {
      DrivePower = maxPower;
    }
    if (DrivePower < -maxPower) {
      DrivePower = -maxPower;
    }

    // Exit Condition
    // double combinedErr = std::abs(err) + std::abs(terr);
    if ( (std::abs(DriveError) < 5 && std::abs(TurnError) < 5) || DriveTimer >= maxTime )  {
      LeftDrive.stop(coast);
      RightDrive.stop(coast);
      DrivePower = 0;
      TurnPower = 0;
      break;
    }

    // Print Debug Info
    Brain.Screen.clearScreen(black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print( "Drive Error: %4.0f  Drive Power: %4.0f", 
    DriveError, DrivePower );
    Brain.Screen.newLine();
    Brain.Screen.print( "Turn Error: %4.0f  Turn Power: %4.0f", 
    TurnError, TurnPower );

    // Output To Motors
    LeftDrive.spin(forward, DrivePower + TurnPower, voltageUnits::volt);
    RightDrive.spin(forward, DrivePower - TurnPower, voltageUnits::volt);
    wait(20, msec);

  }
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  drivePID.reset();
}

//// Vision Algorithms
PID visionPID(.14, 0);
void FrontToMogo(double FrontTarget, double maxFrontPower, double maxFrontTurn = 12, 
double maxFrontTime = 3000) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  timer FrontTimer;
  FrontTimer.reset();
  FrontTimer.time(msec);

  while (true){
    double FDrivePosition = (LeftDrive.position(degrees) 
    + RightDrive.position(degrees)) / 2;
    double FDriveError = FrontTarget - FDrivePosition;

    double FCenterError;
    double FCenterPower;

    Vision.takeSnapshot(Vision__F_YELLOW_MOGO);
    if (Vision.largestObject.exists) {
      FCenterError = 158 - Vision.largestObject.centerX;
      FCenterPower = visionPID.calculateErr(FCenterError);

      if(FCenterPower > maxFrontTurn) {
        FCenterPower = maxFrontTurn;
      }
      if(FCenterPower < -maxFrontTurn) {
        FCenterPower = -maxFrontTurn;
      }

      wait(20, msec);
    }


    double FDrivePower = drivePID.calculateErr(FDriveError);

    if (FDrivePower > maxFrontPower) {
      FDrivePower = maxFrontPower;
    }
    if (FDrivePower < -maxFrontPower) {
      FDrivePower = -maxFrontPower;
    }

    // Exit Condition
    // double combinedErr = std::abs(err) + std::abs(terr);
    if (FrontTimer >= maxFrontTime )  {
      LeftDrive.stop(brake);
      RightDrive.stop(brake);
      FDrivePower = 0;
      break;
    }

    // Print Debug Info
    Brain.Screen.clearScreen(black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print( "Drive Error: %4.0f  Drive Power: %4.0f", 
    FDriveError, FDrivePower );

    // Output To Motors
    LeftDrive.spin(forward, FDrivePower - FCenterPower, voltageUnits::volt);
    RightDrive.spin(forward, FDrivePower + FCenterPower, voltageUnits::volt);
    wait(20, msec);

  }
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  visionPID.reset();
}
enum BackColor {BackRed, BackBlue};
void BackToMogo(BackColor BackColorVar, double BackTarget, double BackMax, double BtMax= 12, 
double BMaxTime = 3000) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  timer BackTimer;
  BackTimer.reset();
  BackTimer.time(msec);
  while (true){
    double BDrivePosition = (LeftDrive.position(degrees) 
    + RightDrive.position(degrees)) / 2;
    double BDriveError = BackTarget - BDrivePosition;

    double BCenterError;
    double BCenterPower;

    if (BackColorVar == BackRed) {
    BackVision.takeSnapshot(BackVision__B_RED_MOGO);
    }
    else if (BackColorVar == BackBlue) {
    BackVision.takeSnapshot(BackVision__B_BLUE_MOGO);  
    }

    if (BackVision.largestObject.exists) {
      BCenterError = 158 - BackVision.largestObject.centerX;
      BCenterPower = turnPID.calculateErr(BCenterError);

      if(BCenterPower > BtMax) {
        BCenterPower = BtMax;
      }
      if(BCenterPower < -BtMax) {
        BCenterPower = -BtMax;
      }

      wait(20, msec);
    }


    double BDrivePower = drivePID.calculateErr(BDriveError);

    if (BDrivePower > BackMax) {
      BDrivePower = BackMax;
    }
    if (BDrivePower < -BackMax) {
      BDrivePower = -BackMax;
    }

    // Exit Condition
    // double combinedErr = std::abs(err) + std::abs(terr);
    if (BackTimer >= BMaxTime)  {
      LeftDrive.stop(brake);
      RightDrive.stop(brake);
      BDrivePower = 0;
      break;
    }

    // Print Debug Info
    Brain.Screen.clearScreen(black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print( "Drive Error: %4.0f  Drive Power: %4.0f", 
    BDriveError, BDrivePower );

    // Output To Motors
    LeftDrive.spin(forward, BDrivePower - BCenterPower, voltageUnits::volt);
    RightDrive.spin(forward, BDrivePower + BCenterPower, voltageUnits::volt);
    wait(20, msec);

  }
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  drivePID.reset();
}

void BackToBlueMogo(double BackTarget, double BackMax, double BtMax= 12, 
double BMaxTime = 3000) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  timer BackTimer;
  BackTimer.reset();
  BackTimer.time(msec);
  while (true){
    double BDrivePosition = (LeftDrive.position(degrees) 
    + RightDrive.position(degrees)) / 2;
    double BDriveError = BackTarget - BDrivePosition;

    double BCenterError;
    double BCenterPower;

    BackVision.takeSnapshot(BackVision__B_BLUE_MOGO);  
    if (BackVision.largestObject.exists) {
      BCenterError = 158 - BackVision.largestObject.centerX;
      BCenterPower = turnPID.calculateErr(BCenterError);

      if(BCenterPower > BtMax) {
        BCenterPower = BtMax;
      }
      if(BCenterPower < -BtMax) {
        BCenterPower = -BtMax;
      }

      wait(20, msec);
    }


    double BDrivePower = drivePID.calculateErr(BDriveError);

    if (BDrivePower > BackMax) {
      BDrivePower = BackMax;
    }
    if (BDrivePower < -BackMax) {
      BDrivePower = -BackMax;
    }

    // Exit Condition
    // double combinedErr = std::abs(err) + std::abs(terr);
    if (BackTimer >= BMaxTime)  {
      LeftDrive.stop(brake);
      RightDrive.stop(brake);
      BDrivePower = 0;
      break;
    }

    // Print Debug Info
    Brain.Screen.clearScreen(black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print( "Drive Error: %4.0f  Drive Power: %4.0f", 
    BDriveError, BDrivePower );

    // Output To Motors
    LeftDrive.spin(forward, BDrivePower - BCenterPower, voltageUnits::volt);
    RightDrive.spin(forward, BDrivePower + BCenterPower, voltageUnits::volt);
    wait(20, msec);

  }
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  drivePID.reset();
}

void BackToRedMogo(double BackTarget, double BackMax, double BtMax= 12, 
double BMaxTime = 3000) {
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  timer BackTimer;
  BackTimer.reset();
  BackTimer.time(msec);
  while (true){
    double BDrivePosition = (LeftDrive.position(degrees) 
    + RightDrive.position(degrees)) / 2;
    double BDriveError = BackTarget - BDrivePosition;

    double BCenterError;
    double BCenterPower;

    BackVision.takeSnapshot(BackVision__B_RED_MOGO);  
    if (BackVision.largestObject.exists) {
      BCenterError = 158 - BackVision.largestObject.centerX;
      BCenterPower = turnPID.calculateErr(BCenterError);

      if(BCenterPower > BtMax) {
        BCenterPower = BtMax;
      }
      if(BCenterPower < -BtMax) {
        BCenterPower = -BtMax;
      }

      wait(20, msec);
    }


    double BDrivePower = drivePID.calculateErr(BDriveError);

    if (BDrivePower > BackMax) {
      BDrivePower = BackMax;
    }
    if (BDrivePower < -BackMax) {
      BDrivePower = -BackMax;
    }

    // Exit Condition
    // double combinedErr = std::abs(err) + std::abs(terr);
    if (BackTimer >= BMaxTime)  {
      LeftDrive.stop(brake);
      RightDrive.stop(brake);
      BDrivePower = 0;
      break;
    }

    // Print Debug Info
    Brain.Screen.clearScreen(black);
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print( "Drive Error: %4.0f  Drive Power: %4.0f", 
    BDriveError, BDrivePower );

    // Output To Motors
    LeftDrive.spin(forward, BDrivePower - BCenterPower, voltageUnits::volt);
    RightDrive.spin(forward, BDrivePower + BCenterPower, voltageUnits::volt);
    wait(20, msec);

  }
  LeftDrive.resetPosition();
  RightDrive.resetPosition();
  drivePID.reset();
}

void VisionToMogo(double MaxCenterPower, double maxVisionTime) {
  timer VisionTimer;
  VisionTimer.reset();
  VisionTimer.time(msec);
  while (true) {
    Vision.takeSnapshot(Vision__F_YELLOW_MOGO);
    if (Vision.largestObject.exists) {
      // Vision.takeSnapshot(Vision__YELLOW_MOGO);
      
      double CenterError = 158 - Vision.largestObject.centerX;

      double CenterPower = turnPID.calculateErr(CenterError);

      if(CenterPower > MaxCenterPower) {
        CenterPower = MaxCenterPower;
      }
      if(CenterPower < -MaxCenterPower) {
        CenterPower = -MaxCenterPower;
      }

      LeftDrive.spin(forward, -CenterPower, volt);
      RightDrive.spin(forward, CenterPower, volt);
      // std::abs(CenterError) < 10 ||
      if (VisionTimer >= maxVisionTime) {
        RobotDrive.stop(brake);
        break;
      }
      wait(20, msec);
    }
    // else {
      // LeftDrive.spin(forward, 4, volt);
      // RightDrive.spin(reverse, 4, volt);
    // }

    wait(20, msec);
  }
}

//// Lift PID
PID LiftPID(.7, 0);
void LiftTo(double ltarget, double maxlpower = 12, double maxltime = 2000) {
  timer LTimer;
  LTimer.reset();
  LTimer.time(msec);
  while(true) {
      double lposition = LiftRotation.position(rotationUnits::rev);
      double lerror = ltarget - lposition;
      
      // Turning Bounds
      // if(lerror > 130) {
      //   lerror -=360;
      // }
      // if (lerror < -130) {
      //   lerror +=360;
      // }

      double LiftPower = LiftPID.calculateErr(lerror);

      // Power Bounds
      if (LiftPower > maxlpower) {
        LiftPower = maxlpower;
      }
      if (LiftPower < -maxlpower) {
        LiftPower = - maxlpower;
      }

      // Exit Condition
      // if (std::abs(lerror) < 5 || LTimer > maxltime) {
      //   Lift.stop(brake);
      //   break;
      // }
      
      // Debug
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print( "  FL Error   : %4.0f   FL Power: %4.0f",
      lerror, LiftPower );

      // Output
      Lift.spin(forward, LiftPower, volt);

      wait(20, msec);
    }
    LiftPID.reset();
  }

