#pragma config(Sensor, in1,    gyro,           sensorGyro)
#pragma config(Sensor, in2,    inLauncher,     sensorReflection)
#pragma config(Sensor, in3,    lightLeft,      sensorReflection)
#pragma config(Sensor, in4,    lightRight,     sensorReflection)
#pragma config(Sensor, dgtl1,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  launcherReady,  sensorTouch)
#pragma config(Motor,  port2,           LD,            tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RD,            tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LL1,           tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           liftWall,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           LR1,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LR2,           tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           lift,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/**
 * @file functions.c
 * @brief This file contains all functions to be used by
 * the competition code.
 *
 * @warning DO NOT compile this file
 * by itself, it will not work. Instead, save it
 * and compile main.c
 *
 * Also, you must include your motor and sensor setup somewhere in this file.
 *
 * @author	 Sean Kelley      sgtkode01@gmail.com
 * @author   Bernard Suwirjo  bsuwirjo@gmail.com
 * @author	 Josh Asari				josh.asari@gmail.com
 *
 */

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 CONSTANTS
//
/////////////////////////////////////////////////////////////////////////////////////////

#define TIMEOUT_CNT_PER_SEC    10   /*!< amount of timeout counts per second */
#define MOTOR_SPEED        		 118  /*!< default motor speed */




/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 DRIVETRAIN
//
/////////////////////////////////////////////////////////////////////////////////////////

/**
* Clears all the motors
*
* @author  Bernard Suwirjo  bsuwirjo@gmail.com
* @author	 Sean Kelley      sgtkode01@gmail.com
*/
void clearMotors(){
	//Set all motor values to 0
	motor[RD]  = 0;
}

/**
* Sets all motors to a certain value
*
* @author Sean Kelley      sgtkode01@gmail.com
*
* @param  speed   the speed of the motors
*/
void setMotors(int power){
	//Set all motor values to power value
	motor[LD]  = power;
	motor[RD]   = power;
}

/**
* Sets the left motors to a given speed
*
* @author Spencer Couture  spence.couture@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param  speed   the speed that the left motors will be set to
*
*/
void setMotorsLeft(int speed){
	motor[LD] = speed;
}

/**
* Sets the right motors to a given speed
*
* @author Spencer Couture  spence.couture@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param  speed   the speed that the right motors will be set to
*
*/
void setMotorsRight(int speed){
	motor[RD] = speed;
}

/**
* Runs each motor for 1.5 seconds
* @warning everything is commented
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*/
void testMotors()
{/*
	motor[frontr]=118;//Set individual motor
	wait1Msec(1500); //Wait 1.5 seconds
	clearMotors(); //clear motor(s)
	motor[backr]=118;
	wait1Msec(1500);
	clearMotors();
	motor[frontl]=118;
	wait1Msec(1500);
	clearMotors();
	motor[backl]=118;
	wait1Msec(1500);
	clearMotors();*/
}

/**
* Moves bot forward for a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param  seconds  amount of seconds to move forward
*	@param  speed    speed of motors
*
*/
void forwardSeconds(float seconds, int speed=MOTOR_SPEED)
{
	//Set all motors to target value
	setMotors(speed);
	wait1Msec(seconds * 1000);//Wait given amount of time
	clearMotors();
}

/**
* Moves bot backward for a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param  seconds  amount of seconds to move backward
*	@param  speed    speed of motors
*
*/
void backwardSeconds(float seconds, int speed=MOTOR_SPEED)
{
	//Set all motors to negative target value
	setMotors(-speed);
	wait1Msec(seconds * 1000);//Wait given amount of time
	clearMotors();
}

/**
* Drive until an encoder value is reached
*
* @author Sean Kelley		sgtkode01@gmail.com
*
* @param  encoder_count         encoder ticks to drive forward
*	@param  timeout_in_seconds    timeout for motors if encoder value is surpassed
* @param  speed									speed of motors
*
*/
int driveByEncoder( int encoder_count, int timeout_in_seconds = 5 , int speed=MOTOR_SPEED){
	int  timeout;

	// Drive motor until encoder has moved a number counts or
	// timeout_in_seconds seconds have passed

	// Zero the encoder
	SensorValue[ encoder ] = 0;

	// Run the motor forwards or backwards
	if( encoder_count > 0 ){
		setMotors(speed);
	} else {
		setMotors(-speed);
	}

	// run loop until encoder hits encoder_count counts or timeout reached

	for( timeout=(timeout_in_seconds*TIMEOUT_CNT_PER_SEC); timeout > 0; timeout-- ){
		// check encoder
		if( encoder_count > 0 ){
			// going forwards
			if( SensorValue[ encoder ] >= encoder_count ){
				break;
			} else {
			// going backwards
				if( SensorValue[ encoder ] <= encoder_count ){
					break;
				}
			}
		}

		// wait 1/10 second
		wait1Msec( 100 );
	}

	// Stop the motor
	clearMotors();

	// See if we sucessfully found the right encoder value
	if( timeout <= 0 ){
		// there was an error - perhaps do something
		// return error
		return (-1);
	} else {
		// return success
		return 0;
	}
}

/**
*
* Locks left side motors with PI loop
*
* @warning function does not work
*
* @author Sean Kelley  sgtkode01@gmail.com
*
*/
task lockLeftSide()
{
	//float target = 0;
	//float pGain = .3;
	//float iGain = .02;
	//float error = target-SensorValue[encoderLeft];
	//float errorSum=0;
	while(true){
/*		error=target-SensorValue[encoderLeft];
		errorSum+=error;
		motor[FL] = error*pGain+errorSum*iGain;
		  motor[BL] = error*pGain+errorSum*iGain;*/
	}
}

/**
*
* Locks right side motors with PI loop
*
* @warning function does not work
*
* @author Sean Kelley  sgtkode01@gmail.com
*
*/
task lockRightSide()
{
	//float target = 0;
	//float pGain = .3;
	//float iGain = .02;
	//float error = target-SensorValue[encoderRight];
	//float errorSum=0;
	while(true){
	/*error=target-SensorValue[encoderRight];
		errorSum+=error;
		motor[FR] = error*pGain+errorSum*iGain;
	  motor[BR] = error*pGain+errorSum*iGain;*/
	}
}

/**
* Turns bot right only using left side motors
*
* @warning requires gyro
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param   degrees   amount of degrees to turn right
* @param   forward   boolean if bot is turning forward or backward
* @param   speed     speed of motors
*
*/
void fancyTurnRightDegrees(int degrees, bool forward=true, int speed = MOTOR_SPEED){

	// reset encoders
	degrees=degrees*10;
	// reset gyro
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	SensorValue[gyro]=0;
	// turn forwards or backwards based on forward boolean
	if(forward){
		while(abs(SensorValue[gyro]) < degrees){ //While the gyro value is less than the target perform code below
			//Set only the left side motors to the target value
			motor[RD] = speed;
		}
		// stop motors
		clearMotors();
	} else {
		while(abs(SensorValue[gyro]) < degrees){
			//Set only the left side motors to the negative target value
			motor[LD] = -speed;
		}
		// stop motors
		clearMotors();
	}
}

/**
* Turns bot left only using left side motors
*
* @warning requires gyro
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param   degrees   amount of degrees to turn left
* @param   forward   boolean if bot is turning forward or backward
* @param   speed     speed of motors
*
*/
void fancyTurnLeftDegrees(int degrees, bool forward=true, int speed = MOTOR_SPEED){
	// reset encoders
	degrees=degrees*10;
	// reset gyro
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	SensorValue[gyro]=0;
	// turn forwards or backwards based on forward boolean
	if(forward){
		while(abs(SensorValue[gyro]) < degrees){ //While the gyro value is less than the target perform code below
			//Set only the left side motors to the target value
			motor[RD] = speed;
		}
		// stop motors
		clearMotors();
	} else {
		while(abs(SensorValue[gyro]) < degrees){
			//Set only the left side motors to the negative target value
			motor[RD] = -speed;
		}
		// stop motors
		clearMotors();
	}
}

/**
* Turns bot right a given amount of degrees
*
* @warning requires gyro
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param  degree  amount of degrees to turn right
*	@param	 speed       speed of motors
*
*/
void turnRightDegrees(float degree, float speed=90)
{
	//Reset gyro
	SensorValue[gyro]=0;
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	degree=degree*10;
	//We want to slow down when we approach the target, so we calculate a first turn segment as 60% of the total
	float first=degree*.6;

	while(abs(SensorValue[gyro]) < first){ //Turn the first 60%
			//Since it's turn right, we want to set right motors backwards and left motors forward.
    	motor[RD] = speed;
    	motor[LD] = speed;
  }
	while(abs(SensorValue[gyro]) < degree){ //Turn the remainin amount.
		//We don't want the motors to run too slow, so we set a a safety net. The motor can't have a power less than 40.
		if(speed*.35<40)//If 35% of the motor power is less than 40, set the power to 40.
		{
			motor[RD] = 40;
    	motor[LD] = 40;
		} else { //If not set it to 35%
				motor[LD] = speed*.35;
	    	motor[RD] = -speed*.35;
    }
	}
	clearMotors();
}

/**
* Turns bot left a given amount of degrees
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
* @author Sean Kelley  sgtkode01@gmail.com
*
* @param  degree  amount of degrees to turn left
*	@param	speed   speed of motors
*
*/
void turnLeftDegrees(float degree, float speed=90)
{
	//Reset gyro
	SensorValue[gyro]=0;
	//gyro takes degrees from 0-3600, so we multiply by 10 to get a gyro processable number
	degree=degree*10;
	//We want to slow down when we approach the target, so we calculate a first turn segment as 60% of the total
	float first=degree*.6;
	while(abs(SensorValue[gyro]) < first){
			//Since it's turn left, we want to set right motors forwards and left motors backwards.
				motor[LD] = speed;
  	    motor[RD] = speed;
	}
	while(abs(SensorValue[gyro]) < degree){
		//We don't want the motors to run too slow, so we set a a safety net. The motor can't have a power less than 40.
		if(speed*.35<40)//If 35% of the motor power is less than 40, set the power to 40.
		{
				motor[LD] = 40;
		    motor[RD] = 40;
		} else { //If not set it to 35%
				motor[LD] = speed*.35;
  	    motor[RD] = speed*.35;
    }
	}
	while(abs(SensorValue[gyro]) > degree){
			motor[LD] = 30;
	    motor[RD] = 30;
	}
	clearMotors();
}


/**
* Turns bot right a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param   seconds   amount of seconds to turn right
* @param	 speed     speed of motors
*
*/
void turnRightSeconds(float seconds, float speed=118)
{
	//Since turn right, we want to set left motors forwards and right motors backwards.
	motor[LD]=speed;
	motor[RD]=-speed;
	wait1Msec(seconds*1000); //Wait desired amount of time
	clearMotors(); //Stop
}

/**
* Turns bot left a given amount of seconds
*
* @author Bernard Suwirjo  bsuwirjo@gmail.com
*
* @param  seconds   amount of seconds to turn left
* @param	speed    speed of motors
*
*/
void turnLeftSeconds(float seconds, float speed=118)
{
	//Since turn left, we want to set the right motors forward and the left motors backwards
	motor[LD] = -speed;
	motor[RD] = speed;
	wait1Msec(seconds*1000); //Wait desired amount of time
	clearMotors(); //Stop
}
/**
* Activates Launcher
* @author Adam Grabowski 122003@pinkertonacademy.org
* @param		speed		speed of motors
*/
void activateLauncher(float speed){
		motor[LL1] = speed;
		motor[LR1] = speed;
		motor[LR2] = speed;
}
/**
* Deactivates Launcher
* @author Adam Grabowski 122003@pinkertonacademy.org
*/
void deactivateLauncher(){
	motor[LL1] = 0;
	motor[LR1] = 0;
	motor[LR2] = 0;
}

/**
* Get the launcher in the ready to fire position.
* @author Kyle Moran		Kyle@llamachair.com
*/
void readyLauncher(){
	while(SensorValue[launcherReady] == 0){
		activateLauncher(90);
	}

	wait1Msec(100);

	while(SensorValue[launcherReady] == 0){
		activateLauncher(90);
	}
	deactivateLauncher();
}



/**
*	Set the motors to the current values
* @warning Code is commented
* @author Sean Kelley  sgtkode01@gmail.com
*
*/
task runMotors(){
	/*while(true){
		motor[motor[backr]]  = motor[frontl];
		motor[motor[backr]]  = motor[backl];
		motor[motor[frontl]] = motor[frontr];
		motor[motor[frontr]] = motor[backr];
	}*/
}

/**
* Allow the user to controll the bot in a thread
* @warning This task currently does nothing
*
* @author Kyle Moran kyle@llamachair.com
*
*/


task userControlls(){


}
