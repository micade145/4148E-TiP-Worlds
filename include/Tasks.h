// #include "vex.h"
// #include "pid_Functions.h"

// // ////////////////////////////// Display Task //////////////////////////////
// int displayTask() {
//     while(1) {
//       // display some useful info
//       Brain.Screen.setCursor(2,1);
//       // Brain.Screen.print( " FrontLeft Speed: %4.0f    Position: %6.2f", 
//       // FrontLeft.velocity( percent ), FrontLeft.position( degrees ) );
//       // Brain.Screen.newLine();
//       // Brain.Screen.print( " BackLeft Speed: %4.0f     Position: %6.2f", 
//       // BackLeft.velocity( percent ), BackLeft.position( degrees ));
//       // Brain.Screen.newLine();
//       // Brain.Screen.print( " FrontRight Speed: %4.0f   Position: %6.2f", 
//       // FrontRight.velocity( percent ), FrontRight.position( degrees ));
//       // Brain.Screen.newLine();
//       // Brain.Screen.print( " BackRight Speed: %4.0f    Position: %6.2f", 
//       // BackRight.velocity( percent ), BackRight.position( degrees ));
//       Brain.Screen.newLine();
//       Brain.Screen.newLine();

//       // motor group velocity and position is returned for the first motor in the group
//       Brain.Screen.print( " LeftDrive Speed: %4.0f    Position: %6.2f", 
//       LeftDrive.velocity(percent), LeftDrive.position(degrees));
      
//       Brain.Screen.newLine();
//       Brain.Screen.print( " RightDrive Speed: %4.0f   Position: %6.2f", 
//       RightDrive.velocity(percent), RightDrive.position(degrees));
//       Brain.Screen.newLine();
//       Brain.Screen.newLine();

//       // drivetrain velocity is the average of the motor velocities for left and right
//       Brain.Screen.print( " RobotDrive Speed: %4.0f   Position: %6.2f", 
//       RobotDrive.velocity( percent ), 
//       (LeftDrive.position(deg) + RightDrive.position(deg))/2);
      
//       Brain.Screen.newLine();
//       Brain.Screen.print( " Inertial Heading: %4.0f   Rotation: %4.0f", 
//       Inertial.heading(degrees), Inertial.rotation(degrees) );
//       wait(20, msec);
//     }
// }

// int Display() {
//   while(true) {
//   Brain.Screen.setCursor(1, 1);
//   Brain.Screen.print( "4148E");
// /////////////////////////////// DriveTrain Info /////////////////////////////////
//     Brain.Screen.setCursor(2, 1); //FrontLeft Temp
//     // Brain.Screen.print( "FrontLeft Temp: %4.0f", FrontLeft.temperature(fahrenheit));

//     // Brain.Screen.setCursor(2, 25); //BackLeft Temp
//     // Brain.Screen.print( "BackLeft Temp: %4.0f", BackLeft.temperature(fahrenheit));

//     // Brain.Screen.setCursor(3, 1); //FrontRight Temp
//     // Brain.Screen.print( "FrontRight Temp: %4.0f", FrontRight.temperature(fahrenheit));

//     // Brain.Screen.setCursor(3, 25); //BackRight Temp
//     // Brain.Screen.print( "BackRight Temp: %4.0f", BackRight.temperature(fahrenheit));

//     Brain.Screen.setCursor(5, 1); //Left and Right Drive Position
//     Brain.Screen.print( "LeftDrive: %4.0f", LeftDrive.position(degrees));
//     Brain.Screen.setCursor(5, 25);
//     Brain.Screen.print( "RightDrive: %4.0f", RightDrive.position(degrees));

// /////////////////////////////// Extra Motor Info ///////////////////////////////////
//     Brain.Screen.setCursor(7, 1); //FrontLift Position and Temp
//     Brain.Screen.print( "FrontLift Temp: %4.0f", Lift.temperature(fahrenheit));
//     Brain.Screen.setCursor(7, 25);
//     Brain.Screen.print( "FrontLift Position: %4.0f", LiftRotation.position(degrees));

//     Brain.Screen.setCursor(9, 1); //Conveyor Position and Temp
//     Brain.Screen.print( "Conveyor Temp: %4.0f", Conveyor.temperature(fahrenheit));
//     Brain.Screen.setCursor(9, 25);
//     Brain.Screen.print( "Conveyor Position: %4.0f", Conveyor.position(degrees));

// ///////////////////////// Inertial Heading and Rotation ////////////////////////////
//     Brain.Screen.setCursor(12, 1); //Inertial Heading and Rotation
//     Brain.Screen.print( "Inertial Heading: %4.0f", Inertial.heading());
//     Brain.Screen.setCursor(12, 25);
//     Brain.Screen.print( "Rotation: %4.0f", Inertial.rotation());

//     wait(20, msec);
//     }
// }

// int RingStop() {
//   while (true) {
//   if (LiftRotation.position(rev) < .3) {
//     Conveyor.stop();
//     }
//   }
//   return(1);
// }