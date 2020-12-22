/*
 * BTController.cpp
 *
 * Created: 2020-11-19 오전 17:19:04
 *  Author: English
 */ 

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include <Arduino.h>
#include "BTController/BTController.h"
#include "MotorDriver/MotorDriver.h"

/******************************************************************************/
/*-----------------------------------Macros-----------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*--------------------------------Enumerations--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-----------------------------Data Structures--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

BTController btController;

/******************************************************************************/
/*-------------------------Function Prototypes--------------------------------*/
/******************************************************************************/

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

BTController::BTController(){
	input_button_ = 0;
	thumb_position_ = 255;
	autonomous_mode_ = false;
}

void BTController::init(){
	Serial1.begin(9600);
	Serial.begin(9600);
	//motor_driver.init();
}

/* AT mode Setup */
void BTController::setATmode() {
	Serial1.begin(38400);	
	Serial.begin(9600);
	Serial.println("Enter AT commands : ");
	
	while(1){
		if (Serial1.available()){
			Serial.write(Serial1.read());
		}
		if (Serial.available()){
			//char temp = Serial.read();
			//Serial.print("Read Char :6 ");
			//Serial.println(temp);
			//Serial1.write(temp);
			Serial1.write(Serial.read());
		}
	}
}

void BTController::getInput() {
	int btValue;
	if (Serial1.available()){
		btValue = Serial1.read();
		//Serial.println(btValue);
		
		if(btValue <= 15 && autonomous_mode_ == false){
			input_button_ = btValue;
			switch(input_button_){
				case 0:
					motor_driver.setOrientation(MagrOrientation::kRelease);
					Serial.println("State: Release");
					break;
				case 1:
					motor_driver.setOrientation(MagrOrientation::kForward);
					Serial.println("State: Forward");
					break;
				case 2:
					motor_driver.setOrientation(MagrOrientation::kBackward);
					Serial.println("State: Backward");
					break;
				case 3:
					motor_driver.setOrientation(MagrOrientation::kLeft);
					Serial.println("State: Left");
					break;
				case 4:
					motor_driver.setOrientation(MagrOrientation::kRight);
					Serial.println("State: Right");
					break;
				case 5:
					motor_driver.setOrientation(MagrOrientation::kForwardLeft);
					Serial.println("State: Forward Left");
					break;
				case 6:
					motor_driver.setOrientation(MagrOrientation::kForwardRight);
					Serial.println("State: Forward Right");
					break;
				case 7:
					motor_driver.setOrientation(MagrOrientation::kBackwardLeft);
					Serial.println("State: Backward Left");
					break;
				case 8:
					motor_driver.setOrientation(MagrOrientation::kBackwardRight);
					Serial.println("State: Backward Right");
					break;
				case 9:
					motor_driver.setOrientation(MagrOrientation::kCounterClockwise);
					Serial.println("State: Counter Clockwise");
					break;
				case 10:
					motor_driver.setOrientation(MagrOrientation::kClockwise);
					Serial.println("State: Clockwise");
					break;
			}
		}
		
		if(btValue >= 11 && btValue <= 15){
			input_button_ = btValue;
			switch(input_button_){
				case 14:
				autonomous_mode_ = false;
				motor_driver.setOrientation(MagrOrientation::kRelease);
				Serial.println("Mode : Manual");
				break;
				case 15:
				autonomous_mode_ = true;
				motor_driver.setOrientation(MagrOrientation::kRelease);
				Serial.println("Mode : Autonomous");
				break;
			}
		}
		
	}
}
