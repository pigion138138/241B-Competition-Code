#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl12, inLauncher,     sensorTouch)
#pragma config(Motor,  port2,           LD,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RD,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LL1,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           LL2,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LR1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LR2,           tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * @file    main.c
 * @brief   This file contains the base for competiton code.
 * @details The three sections include Pre-Auton, Auton, and User
 *          Control.
 *
 * @author		Sean Kelley      sgtkode01@gmail.com
 * @author		Bernard Suwirjo  bsuwirjo@gmail.com
 * @author 		Spencer Couture  spence.couture@gmail.com
 * @author		Kyle Moran			 kyle@llamachair.com
 */


#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"

// all functions for competition code
#include "functions.c"



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Pre-Autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * Period before autonomous when bot cannot move, but minimal code can run
 */
void pre_auton(){
	bStopTasksBetweenModes = true;




}



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * Period of match when bot is using only code to operate.
 */
task autonomous(){




}




/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * Period of match when driver controls the bot
 */
task usercontrol(){
	startTask(userControlls);
	bool isIntakeOn = false;
	bool isLauncherOn = false;
	bool isIntakeButton = false;
	bool isLauncherButton = false;
  while (true)
	{
    if(bVEXNETActive){
				/////////////////////////////////////////////////////////////////////////////////////////
      //
      //                                      Drive
      //
      /////////////////////////////////////////////////////////////////////////////////////////
  		motor[RD] = vexRT[Ch2]*.9;
  		motor[LD] = vexRT[Ch3]*.9;


			if(vexRT[Btn6D] == 1){
				if(isLauncherButton == false){
					if(isLauncherOn){
						deactivateLauncher();
						isLauncherOn = false;
					}else{
						activateLauncher(90);
						isLauncherOn = true;
					}
					isLauncherButton = true;
				}
			}
			if(vexRT[Btn5D] == 1 && sensorValue[inLauncher] == 0){
				if(isIntakeButton == false){
					if(isIntakeOn){
						motor[intake] = 0;
						isIntakeOn = false;
					}else{
						motor[intake] = 90;
						isIntakeOn = true;
					}
					isIntakeButton = true;
				}
			}

			if(vexRT[Btn6D] == 0){
				isLauncherButton = false;
			}

			if(vexRT[Btn5D] == 0){
				isIntakeButton = false;
			}

      wait1Msec(10);
    }
	}
}
