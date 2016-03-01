#pragma config(Motor,  port2,           LF,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           LB,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           RF,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           RB,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           DL,            tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           DR,            tmotorVex393HighSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"


void pre_auton(){
  bStopTasksBetweenModes = true;
}
//Activates all 4 motors to start the launcher
void activateLauncher(int speed=100){
	motor[LF] = speed;
	motor[LB] = speed;
	motor[RF] = speed;
	motor[RB] = speed;
}

task autonomous(){
}


task usercontrol(){

	while (true){
	  UserControlCodePlaceholderForTesting(); // Remove this function call once you have "real" code.
	  motor[DL] = vexRT[Ch3] * .9;
	  motor[DR] = vexRT[Ch1] * .9;
	}
}
