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
// leftFront            motor         1               
// rightFront           motor         2               
// leftBack             motor         3               
// rightBack            motor         4               
// center               motor         5               
// lift                 motor         6               
// intake               motor         7               
// Controller1          controller                    
// lift2                motor         8               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void strafe(){
  //strafe left and right
  center.spin(fwd, (Controller1.Axis1.position()) * 3, pct);
}

void turnRight(){
  rightFront.stop();
  rightBack.stop();
  leftBack.spin(fwd, (Controller1.Axis4.position()) * 0.75, pct);
  leftFront.spin(fwd, (Controller1.Axis4.position()) * 0.75, pct);
}

void turnLeft(){
  leftFront.stop();
  leftBack.stop();
  rightBack.spin(fwd, (Controller1.Axis4.position()) * 0.75, pct);
  rightFront.spin(fwd, (Controller1.Axis4.position()) * 0.75, pct);
}

void YMove(){
  //move forward and backward
  rightFront.spin(reverse, (Controller1.Axis3.position()) * 0.75, pct);
  leftFront.spin(fwd, (Controller1.Axis3.position()) * 0.75, pct);
  rightBack.spin(reverse, (Controller1.Axis3.position()) * 0.75, pct);
  leftBack.spin(fwd, (Controller1.Axis3.position()) * 0.75, pct);
}

void moveStop(){
  rightFront.stop();
  leftFront.stop();
  rightBack.stop();
  leftBack.stop();
  center.stop();
  lift.stop();
  intake.stop();
  lift2.stop();
}
void yellowGoal(){
  leftFront.rotateFor(5, rev, 40, rpm);
  leftBack.rotateFor(5, rev, 40, rpm);
  rightFront.rotateFor(5, rev, -40, rpm);
  rightBack.rotateFor(5, rev, -40, rpm);
}
void raiseGoal(){
  lift.rotateFor(0.3,  rev, -40, rpm);
  lift2.rotateFor(0.3, rev, -40, rpm);
}
void home(){
  leftFront.rotateFor(4, rev, -40, rpm);
  leftBack.rotateFor(4, rev, -40, rpm);
  rightFront.rotateFor(4, rev, 40, rpm);
  rightBack.rotateFor(5, rev, 40, rpm);  
  lift.rotateFor(0.3, rev, 40, rpm);
  lift2.rotateFor(0.3, rev, 40, rpm);
}
void rotate(){
  rightFront.stop();
  rightBack.stop();
  leftFront.rotateFor(1, rev, -40, rpm);
  leftBack.rotateFor(1, rev, -40, rpm);
}
void climb(){
  leftFront.rotateFor(0.5, rev, 40, rpm);
  leftBack.rotateFor(0.5, rev, 40, rpm);
  rightFront.rotateFor(0.5, rev, -40, rpm);
  rightBack.rotateFor(0.5, rev, -40, rpm);
}
void autonomous(void) {
  if(Controller1.ButtonB.pressing()){
    yellowGoal();
    wait(20, msec);
    raiseGoal();
    wait(20, msec);
    home();
    wait(20, msec);
    rotate();
    wait(20, msec);
    climb();
    moveStop();
  }
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
  // User control code here, inside the loop
  while (1) {
    if(Controller1.ButtonA.pressing()){
      moveStop();
    }
    strafe();
    if(Controller1.Axis4.value() > 0){
      turnRight();
    }
    if(Controller1.Axis4.value() < 0){
      turnLeft();
    }
    YMove();
    if(Controller1.ButtonR2.pressing()){
      intake.spin(fwd, 75, pct);
      lift2.spin(fwd, 75, pct);
    }
    if(Controller1.ButtonL2.pressing()){
      intake.spin(reverse, 75, pct);
      lift2.spin(reverse, 75, pct);
    }
    if(Controller1.ButtonR1.pressing()){
      lift.spin(fwd, 100, pct);
    }
    if(Controller1.ButtonL1.pressing()){
      lift.spin(reverse, 100, pct);
    }

    wait(20, msec); 
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
