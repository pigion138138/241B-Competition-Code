#pragma config(Sensor, dgtl1,  frontSonic,     sensorSONAR_mm)
#pragma config(Sensor, dgtl3,  sideSonicF,     sensorSONAR_mm)
#pragma config(Sensor, dgtl5,  sideSonicB,     sensorSONAR_mm)
#pragma config(Motor,  port1,           leftDrive,     tmotorVex393HighSpeed_HBridge, openLoop)
#pragma config(Motor,  port2,           rightDrive,    tmotorVex393HighSpeed_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// amount of millimeters away from the far wall we want to stop at
int target = 100; // 10 centimeters

#define PID_DRIVE_MAX       127.0
#define PID_DRIVE_MIN     (-127.0)

#define PID_INTEGRAL_LIMIT  500.0

float  frontSonic_Val;
float  sideSonicF_Val;
float  sideSonicB_Val;

float  targetError;
float  targetLastError;
float  targetIntegral;
float  targetDerivative;
float  targetDrive;

float  perpError;
float  perpLastError;
float  perpIntegral;
float  perpDerivative;
float  perpDrive;

/*
 * These are the contants for the parts of the PID loop.
 * Edit these in the live debugger each test. At its most
 * basic, Kp and Ki will allow the robot to reach
 * the target faster but will create more over shooting.
 * Kd slows the robot down but prevents over shooting.
 *
*/
float  target_Kp = 0.5;
float  target_Ki = 0.1;
float  target_Kd = 0.005;

float  perp_Kp = 0.5;
float  perp_Ki = 0.1;
float  perp_Kd = 0.005;


task main()
{
	// actual PID loop
  while( true ) {
    // Read the ultrasonic values
    frontSonic_Val = SensorValue[frontSonic];
    sideSonicF_Val = SensorValue[sideSonicF];
    sideSonicB_Val = SensorValue[sideSonicB];

    // calculate error
		targetError = target - frontSonic_Val;
    perpError = sideSonicF_Val - sideSonicB_Val;

    // integral - if Ki is not 0
    if( target_Ki != 0 && perp_Ki != 0 ){
        // If we are inside controlable window then integrate the error
        if( abs(targetError) < PID_INTEGRAL_LIMIT ){
           targetIntegral = targetIntegral + targetError;
      	} else {
           targetIntegral = 0;
        }
        if( abs(perpError) < PID_INTEGRAL_LIMIT ){
            perpIntegral = perpIntegral + perpError;
        } else {
            perpIntegral = 0;
        }
  	} else {
        targetIntegral = 0;
        perpIntegral = 0;
  	}

    // calculate the derivative
    targetDerivative = targetError - targetLastError;
    targetLastError  = targetError;

    perpDerivative = perpError - perpLastError;
    perpLastError  = perpError;

    // calculate drive
    targetDrive = (target_Kp * targetError) + (target_Ki * targetIntegral) + (target_Kd * targetDerivative);
    perpDrive = (perp_Kp * perpError) + (perp_Ki * perpIntegral) + (perp_Kd * perpDerivative);

    // limit drive
    if( (abs(targetDrive) + abs(perpDrive)) > PID_DRIVE_MAX ){
			targetDrive = (targetDrive/(targetDrive + perpDrive)) * PID_DRIVE_MAX;
			perpDrive = (perpDrive/(targetDrive + perpDrive)) * PID_DRIVE_MAX;
  	} else if( (abs(targetDrive) - abs(perpDrive)) < PID_DRIVE_MIN ){
      targetDrive = (targetDrive/(targetDrive + perpDrive)) * PID_DRIVE_MIN;
			perpDrive = (perpDrive/(targetDrive + perpDrive)) * PID_DRIVE_MIN;
    }

    // send to drivetrain
    motor[leftDrive] = targetDrive - perpDrive;
    motor[rightDrive] = targetDrive + perpDrive;
	  wait1Msec(10);
	}
}
