/*
 * Magr.cpp
 *
 * Created: 2020-11-19 오후 2:15:37
 *  Author: English
 */ 

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <Arduino.h>
#include "Magr.h"
#include "Magr_cfg.h"
#include "MotorDriver/MotorDriver.h"
#include "UltraSonic/UltraSonic.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

UltraSonic ultraSonic_FL(ULTRASONIC_FL_TRIG, ULTRASONIC_FL_ECHO);
UltraSonic ultraSonic_F(ULTRASONIC_F_TRIG, ULTRASONIC_F_ECHO);
UltraSonic ultraSonic_FR(ULTRASONIC_FR_TRIG, ULTRASONIC_FR_ECHO);
UltraSonic ultraSonic_L(ULTRASONIC_L_TRIG, ULTRASONIC_L_ECHO);
UltraSonic ultraSonic_R(ULTRASONIC_R_TRIG, ULTRASONIC_R_ECHO);
UltraSonic ultraSonic_B(ULTRASONIC_B_TRIG, ULTRASONIC_B_ECHO);
UltraSonic ultraSonic_BL(ULTRASONIC_BL_TRIG, ULTRASONIC_BL_ECHO);
UltraSonic ultraSonic_BR(ULTRASONIC_BR_TRIG, ULTRASONIC_BR_ECHO);

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

Magr::Magr(){
	safety_factor_ = {};
	obstacle_distance_ = {};
	x_ = 0;
	y_ = 0;
}

void Magr::measure_obstacle_distance(){
	obstacle_distance_.front		= ultraSonic_F.measureDistance();
	obstacle_distance_.front_left	= ultraSonic_FL.measureDistance();
	obstacle_distance_.front_right	= ultraSonic_FR.measureDistance();
	obstacle_distance_.left			= ultraSonic_L.measureDistance();
	obstacle_distance_.right		= ultraSonic_R.measureDistance();
	obstacle_distance_.back			= ultraSonic_B.measureDistance();
	obstacle_distance_.back_left	= ultraSonic_BL.measureDistance();
	obstacle_distance_.back_right	= ultraSonic_BR.measureDistance();
}

void Magr::set_safety_factor(int& safety_factor, int distance){
	if(distance < SAFETY_DISTANCE_LOW2MID)
		safety_factor =	SAFETY_FACTOR_LOW;
	else if(distance < SAFETY_DISTANCE_MID2HIGH)
		safety_factor = SAFETY_FACTOR_MID;
	else
		safety_factor = SAFETY_FACTOR_HIGH;
}

void Magr::set_magr_orientation(){
	measure_obstacle_distance();
	
	set_safety_factor(safety_factor_.front, obstacle_distance_.front);
	set_safety_factor(safety_factor_.front_left, obstacle_distance_.front_left);
	set_safety_factor(safety_factor_.front_right, obstacle_distance_.front_right);
	set_safety_factor(safety_factor_.left, obstacle_distance_.left);
	set_safety_factor(safety_factor_.right, obstacle_distance_.right);
	set_safety_factor(safety_factor_.back, obstacle_distance_.back);
	set_safety_factor(safety_factor_.back_left, obstacle_distance_.back_left);
	set_safety_factor(safety_factor_.back_right, obstacle_distance_.back_right);
	
	x_ = -safety_factor_.front_left + safety_factor_.front_right -safety_factor_.back_left + safety_factor_.back_right -safety_factor_.left + safety_factor_.right;
	y_ = 2*safety_factor_.front + (safety_factor_.front_left + safety_factor_.front_right) - (safety_factor_.back + safety_factor_.back_left + safety_factor_.back_right);
	
	//boolean sideObstacles = (safety_factor_.left == SAFETY_FACTOR_LOW) ||
							//(safety_factor_.right == SAFETY_FACTOR_LOW);
	//if(sideObstacles){
		//x_ = -safety_factor_.left + safety_factor_.right;
		//
	//if(safety_factor_.back == SAFETY_FACTOR_LOW)
		//y_ = safety_factor_.front - safety_factor_.back;
	//}
}

void Magr::move(){
	if(y_ > 0){
		if(x_ == 0)
			motor_driver.setOrientation(MagrOrientation::kForward);
		
		else if(x_ > 0)
			motor_driver.setOrientation(MagrOrientation::kForwardRight);
		
		else // (x_ < 0)
			motor_driver.setOrientation(MagrOrientation::kForwardLeft);
	}
	
	else if(y_ < 0){
		if(x_ == 0)
			motor_driver.setOrientation(MagrOrientation::kBackward);
		
		else if(x_ > 0)
			motor_driver.setOrientation(MagrOrientation::kBackwardRight);
		
		else //(x_ < 0)
			motor_driver.setOrientation(MagrOrientation::kBackwardLeft);
	}
	
	else{	// (y_ == 0)
		if(x_ == 0){
			//motor_driver.setOrientation(MagrOrientation::kRelease);
			if(obstacle_distance_.front_left >= obstacle_distance_.front_right){
				if(obstacle_distance_.back_left >= obstacle_distance_.back_right){
					motor_driver.setOrientation(MagrOrientation::kLeft);
				}
				else{ //(obstacle_distance_.back_left <= obstacle_distance_.back_right)
					motor_driver.setOrientation(MagrOrientation::kCounterClockwise);
					delay(500);
				}
			}
			else{ //(obstacle_distance_.front_left < obstacle_distance_.front_right)
				if(obstacle_distance_.back_left <= obstacle_distance_.back_right){
					motor_driver.setOrientation(MagrOrientation::kRight);
				}
				else{ //obstacle_distance_.back_left > obstacle_distance_.back_right
					motor_driver.setOrientation(MagrOrientation::kClockwise);	
					delay(500);
				}
			}
		}
		
		else if(x_ > 0)
			motor_driver.setOrientation(MagrOrientation::kRight);
		
		else //(x_ < 0)
			motor_driver.setOrientation(MagrOrientation::kLeft);
	}
	
	//if(x_==0 && y_>=-4 && y_< 0){
	if(y_>=-4 && y_< 0){
		if(obstacle_distance_.front_left >= obstacle_distance_.front_right){
			if(obstacle_distance_.back_left >= obstacle_distance_.back_right){
				motor_driver.setOrientation(MagrOrientation::kLeft);
			}
			else{ //(obstacle_distance_.back_left <= obstacle_distance_.back_right)
				motor_driver.setOrientation(MagrOrientation::kCounterClockwise);
				delay(500);
			}
		}
		else{ //(obstacle_distance_.front_left < obstacle_distance_.front_right)
			if(obstacle_distance_.back_left <= obstacle_distance_.back_right){
				motor_driver.setOrientation(MagrOrientation::kRight);
			}
			else{ //obstacle_distance_.back_left > obstacle_distance_.back_right
				motor_driver.setOrientation(MagrOrientation::kClockwise);
				delay(500);
			}
		}
	}
}