/** @file functions.c
 * @brief General functions to be used in the rest of the code
 *
 *
 *  Created on: Dec 17, 2015
 *      Author: Spencer Couture
 *			Author: Jahn Martin
 **/

#include "main.h"

void clearMotors(){
	motorSet(RD, 0);
	motorSet(LD, 0);
}


void setMotors(int power){
	motorSet(RD, power);
	motorSet(LD, -power);
}

void setMotorsLeft(int speed){
	motorSet(LD, -speed);
}

void setMotorsRight(int speed){
	motorSet(RD, speed);
}

void forwardSeconds(float seconds, int speed=MOTOR_SPEED){
	setMotors(speed);
	delay(seconds * 1000);
	clearMotors();
}

void backwardSeconds(float seconds, int speed=MOTOR_SPEED){
	setMotors(-speed);
	delay(seconds * 1000);
	clearMotors();
}

void turnRightDegrees(float degree, float speed = 90){
	gyroReset();
	float first = degree*.6;

	while(abs(gyroGet(gyro) < first)){
		motorSet(RD, -speed);
		motorSet(LD, -speed);
	}

	while(abs(gyroGet(gyro) < degree)){
		if(speed*.35<40){
			setMotors(RD, -40);
			setMotors(LD, -40);
		}
		else{
			setMotors(LD, -.35*speed);
			setMotors(RD, -.35*speed);
		}
	}
	clearMotors();
}


void turnRightSeconds(float seconds, float speed=118){
	setMotors(LD, -speed);
	setMotors(RD, -speed);
	delay(1000*seconds);
	clearMotors();
}


void turnLeftSeconds(float seconds, float speed=118){
	setMotors(LD, speed);
	setMotors(RD, speed);
	delay(1000*seconds);
	clearMotors();
}


void activateLauncher(float speed){
	motorSet(LL1, -speed);
	motorSet(LL2, -speed);
	motorSet(LR1, speed);
	motorSet(LR2, speed);
}

void deactivateLauncher(float speed){
	motorSet(LL1, 0);
	motorSet(LL2, 0);
	motorSet(LR1, 0);
	motorSet(LR2, 0);
}













////
