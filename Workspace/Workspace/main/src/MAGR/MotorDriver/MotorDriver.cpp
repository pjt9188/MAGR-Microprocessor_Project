/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "MotorDriver/MotorDriver.h"

/******************************************************************************/
/*------------------------------Global variables------------------------------*/
/******************************************************************************/

AF_DCMotor	motor_1(1);     // 모터 1 객체
AF_DCMotor	motor_2(2);     // 모터 2 객체
AF_DCMotor	motor_3(3);     // 모터 3 객체
AF_DCMotor	motor_4(4);     // 모터 4 객체

MotorDriver motor_driver;

/******************************************************************************/
/*------------------------Private Variables/Constants-------------------------*/
/******************************************************************************/

const byte kMaxSpeed = 255; // 최고속도

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

/* Motor Driver Initialization */
MotorDriver::MotorDriver(){
	magr_orientation_ = MagrOrientation::kRelease;
	motor_1.run(RELEASE);			// 모터 1 돌리지 않는 상태
	motor_2.run(RELEASE);			// 모터 2 돌리지 않는 상태
	motor_3.run(RELEASE);			// 모터 3 돌리지 않는 상태
	motor_4.run(RELEASE);			// 모터 4 돌리지 않는 상태
	motor_1.setSpeed(kMaxSpeed);    // 모터 1 속도 설정
	motor_2.setSpeed(kMaxSpeed);    // 모터 2 속도 설정
	motor_3.setSpeed(kMaxSpeed);    // 모터 3 속도 설정
	motor_4.setSpeed(kMaxSpeed);    // 모터 4 속도 설정
}

/* set rotate speed of all the motors */
void MotorDriver::setSpeed(byte speed_8bit){
	motor_1.setSpeed(speed_8bit);
	motor_2.setSpeed(speed_8bit);
	motor_3.setSpeed(speed_8bit);
	motor_4.setSpeed(speed_8bit);
}

/* set orientation of the movement */
void MotorDriver::setOrientation(MagrOrientation orientation){
	magr_orientation_ = orientation;
	switch(magr_orientation_){
		case MagrOrientation::kRelease:
		motor_1.run(RELEASE);			// 모터 1 돌리지 않는 상태
		motor_2.run(RELEASE);			// 모터 2 돌리지 않는 상태
		motor_3.run(RELEASE);			// 모터 3 돌리지 않는 상태
		motor_4.run(RELEASE);			// 모터 4 돌리지 않는 상태
		Serial.println("RELEASE");
		break;
		
		case MagrOrientation::kForward:
		motor_1.run(FORWARD);
		motor_2.run(FORWARD);
		motor_3.run(FORWARD);
		motor_4.run(FORWARD);
		Serial.println("FORWARD");
		break;
		
		case MagrOrientation::kBackward:
		motor_1.run(BACKWARD);
		motor_2.run(BACKWARD);
		motor_3.run(BACKWARD);
		motor_4.run(BACKWARD);
		Serial.println("BACKWARD");
		break;
		
		case MagrOrientation::kLeft:
		motor_1.run(FORWARD);
		motor_2.run(BACKWARD);
		motor_3.run(FORWARD);
		motor_4.run(BACKWARD);
		Serial.println("LEFT");
		break;
		
		case MagrOrientation::kRight:
		motor_1.run(BACKWARD);
		motor_2.run(FORWARD);
		motor_3.run(BACKWARD);
		motor_4.run(FORWARD);
		Serial.println("RIGHT");
		break;
		
		case MagrOrientation::kForwardLeft:
		motor_1.run(FORWARD);
		motor_2.run(RELEASE);
		motor_3.run(FORWARD);
		motor_4.run(RELEASE);
		Serial.println("FORWARD LEFT");
		break;
		
		case MagrOrientation::kForwardRight:
		motor_1.run(RELEASE);
		motor_2.run(FORWARD);
		motor_3.run(RELEASE);
		motor_4.run(FORWARD);
		Serial.println("FORWARD RIGHT");
		break;
		
		case MagrOrientation::kBackwardLeft:
		motor_1.run(RELEASE);
		motor_2.run(BACKWARD);
		motor_3.run(RELEASE);
		motor_4.run(BACKWARD);
		Serial.println("BACKWARD LEFT");
		break;
		
		case MagrOrientation::kBackwardRight:
		motor_1.run(BACKWARD);
		motor_2.run(RELEASE);
		motor_3.run(BACKWARD);
		motor_4.run(RELEASE);
		Serial.println("BACKWARD RIGHT");
		break;
		
		case MagrOrientation::kCounterClockwise:
		motor_1.run(BACKWARD);
		motor_2.run(FORWARD);
		motor_3.run(FORWARD);
		motor_4.run(BACKWARD);
		Serial.println("ROTATE CCW");
		break;
		
		case MagrOrientation::kClockwise:
		motor_1.run(FORWARD);
		motor_2.run(BACKWARD);
		motor_3.run(BACKWARD);
		motor_4.run(FORWARD);
		Serial.println("ROTATE CW");
		break;
	}
}
