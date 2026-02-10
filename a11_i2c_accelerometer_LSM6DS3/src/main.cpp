	/**
	 * Reading values from LSM6DS3
	 * Connect the sensor as follows
	 * VCC <-> 5V
	 * GND <-> GND
	 * SDA <-> 23
	 * SCL <-> 2
	 */

	#include <Arduino.h>
	#include <Wire.h>
	#include "LSM6DS3.h"
	LSM6DS3 imu(I2C_MODE, 0x6A);

	#define WIRE Wire

	#define I2C_SDA 23
	#define I2C_SCL 2

	void setup() {
	Serial.begin(115200);


	Wire.begin(I2C_SDA, I2C_SCL);

	if (imu.begin() != 0) {
		Serial.println("ERROR: LSM6DS3 initialisering feilet!");
		while (1) {
			delay(500);
		}
	}

	Serial.println("LSM6DS3 initialisert!");

	}

void loop() {
	float accelX = imu.readFloatAccelX();
	float accelY = imu.readFloatAccelY();
	float accelZ = imu.readFloatAccelZ();

	Serial.print("accelX = ");
	Serial.println(accelX);
	Serial.print("accelY = ");
	Serial.println(accelY);
	Serial.print("accelZ = ");
	Serial.println(accelZ);

	delay(100); // Oppdater 10 ganger per sekund
}