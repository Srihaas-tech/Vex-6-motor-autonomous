#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
// AI Classification Competition Element IDs
enum gameElements {
  mobileGoal,
  redRing,
  blueRing,
};

digital_out pn = digital_out(Brain.ThreeWirePort.H);
// AI Vision Color Descriptions
aivision::colordesc eyes__bring(1, 70, 154, 198, 10, 0.2);
aivision::colordesc eyes__rring(2, 230, 78, 122, 10, 0.2);
aivision::colordesc eyes__mogo(3, 160, 182, 115, 10, 0.2);
// AI Vision Code Descriptions
aivision::codedesc eyes__ccode(1, eyes__bring, eyes__rring, eyes__mogo);
vex::aivision eyes(PORT7, eyes__bring, eyes__rring, eyes__mogo, eyes__ccode, aivision::ALL_AIOBJS);



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//                                                                            
//    Project:  R- and +                                             
//    Author: 8025B
//    Created:1/25/25
//    Configuration: Competition Template       
//                                                                            
// ----------------------------------------------------------------------------

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

motor lf = motor(PORT13, ratio6_1, true);
motor lb = motor(PORT10, ratio6_1, true);
motor lt = motor(PORT8, ratio6_1, false);
motor_group leftmtrs= motor_group(lf,lb);
motor rb = motor(PORT18, ratio6_1, false);
motor rf = motor(PORT17, ratio6_1, false);
motor rt = motor(PORT16, ratio6_1, true);
motor_group rightmtrs = motor_group(rf,rb);
drivetrain Drivetrain = drivetrain(leftmtrs, rightmtrs, 299.24, 295, 40, mm, 0.6);
motor_group r = motor_group(lt, lb,lf);
motor_group l = motor_group(rt, rb,rf);
motor hook = motor(PORT9, ratio6_1);
motor intake1 = motor(PORT19, ratio18_1);
motor intake2 = motor(PORT15, ratio18_1,false);
controller Controller1 = controller();


void BX(){
  pn.set(false);
}
void BB(){
  pn.set(true);
}
void R1(){
  hook.spin(forward);
}
void R2(){
  hook.spin(reverse);
}
void L1(){
  intake1.spin(forward);
  intake2.spin(reverse);
}
void L2(){
  intake1.spin(reverse);
  intake2.spin(forward);
}
void stopintake(){
  intake1.stop();
  intake2.stop();
}
void stophook(){
  hook.stop();
}

// Begin project code

void preAutonomous(void) {
vexcodeInit();
  Drivetrain.setDriveVelocity(100,percent);
  Drivetrain.setTurnVelocity(100,percent);
  hook.setVelocity(50, percent);
  hook.setMaxTorque(100,percent);
  intake1.setVelocity(100, percent);
  intake2.setVelocity(100, percent);
  pn.set(false);
  Controller1.ButtonX.pressed(BX);
  Controller1.ButtonB.pressed(BB);
  Controller1.ButtonR1.pressed(R1);
  Controller1.ButtonR2.pressed(R2);
  Controller1.ButtonL1.pressed(L1);
  Controller1.ButtonL2.pressed(L2);
 Controller1.ButtonL1.released(stophook);
 Controller1.ButtonL2.released(stophook);
 Controller1.ButtonR1.released(stopintake);
 Controller1.ButtonR2.released(stopintake);
 while(1){
    l.spin(forward,(Controller1.Axis3.position(percent) - Controller1.Axis1.position(percent))*12/100, volt);
    r.spin(forward,(Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent))*12/100, volt);
    wait(20, msec);
 }

  
}

void autonomous(void) {
Drivetrain.setDriveVelocity(100, percent);
leftmtrs.setVelocity(100,percent);
rightmtrs.setVelocity(100,percent);

  Drivetrain.setTurnVelocity(100,percent);
  hook.setVelocity(55,percent);
  pn.set(true);
  intake1.spin(reverse);
  intake2.spin(forward);
  //Going for MoGO
  leftmtrs.spin(reverse);
  rightmtrs.spin(reverse);
  wait(1.1,seconds);
  pn.set(false);
  //Clamps
  wait(0.30,seconds);
  leftmtrs.stop();
  rightmtrs.stop();
  //Stops with the MoGo
  //Turns
  leftmtrs.spin(forward);
  rightmtrs.spin(reverse);
  wait(0.65,seconds);
  leftmtrs.stop();
  rightmtrs.stop();
  //Goes for 1st donut

  //hook.spin(forward);
  intake1.spin(reverse);
  intake2.spin(forward);
leftmtrs.spin(forward);
  rightmtrs.spin(forward);

  wait(1.5,seconds);
leftmtrs.stop();
  rightmtrs.stop();

  //Goes to ladder
leftmtrs.spin(forward);
  rightmtrs.spin(reverse);

  wait(1.6,seconds);
leftmtrs.stop();
  rightmtrs.stop();
  
  Drivetrain.driveFor(forward,55,inches);
  hook.stop();
  intake1.stop();
  intake2.stop();
  //Done*/

  wait(5, msec);
}

void userControl(void) {
  Brain.Screen.clearScreen();
  // place driver control in this while loop
  while (true) {
    wait(20, msec);
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(userControl);

  
  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
