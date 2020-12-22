#include <Arduino.h>
#include "Magr.h"
#include "BTController/BTController.h"

Magr magr;

void setup() {
	Serial.begin(9600);
	btController.init();
}

void loop() {
	btController.getInput();
	if(btController.autonomous_mode_ == true){
		magr.set_magr_orientation();
		magr.move();
		Serial.print(magr.safety_factor_.front_left);
		Serial.print("  ");
		Serial.print(magr.safety_factor_.front);
		Serial.print("  ");
		Serial.println(magr.safety_factor_.front_right);
		Serial.print(magr.safety_factor_.left);
		Serial.print("     ");
		Serial.println(magr.safety_factor_.right);
		Serial.print(magr.safety_factor_.back_left);
		Serial.print("  ");
		Serial.print(magr.safety_factor_.back);
		Serial.print("  ");
		Serial.println(magr.safety_factor_.back_right);
		Serial.print(magr.x_);
		Serial.println(magr.y_);
	}
	
	//magr.set_magr_orientation();
	//Serial.print(magr.obstacle_distance_.front_left);
	//Serial.print("cm  ");
	//Serial.print(magr.obstacle_distance_.front);
	//Serial.print("cm  ");
	//Serial.print(magr.obstacle_distance_.front_right);
	//Serial.println("cm");
	//delay(100);
}

