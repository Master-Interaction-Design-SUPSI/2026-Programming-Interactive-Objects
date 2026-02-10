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

	Serial.begin(9600);

	Wire.begin(I2C_SDA, I2C_SCL);

	if (imu.begin() != 0) {
		while (1) {
			Serial.println("ERROR initializing LSM6DS3.");
			delay(1000);
		}
	}

	Serial.println("LSM6DS3 initialized.");

}

void loop() {

	float gyroX = imu.readFloatGyroX();
	float gyroY = imu.readFloatGyroY();
	float gyroZ = imu.readFloatGyroZ();

	float accelX = imu.readFloatAccelX();
	float accelY = imu.readFloatAccelY();
	float accelZ = imu.readFloatAccelZ();

	Serial.print("gyroX = ");
	Serial.println(gyroX);
	Serial.print("gyroY = ");
	Serial.println(gyroY);
	Serial.print("gyroZ = ");
	Serial.println(gyroZ);

	Serial.print("accelX = ");
	Serial.println(accelX);
	Serial.print("accelY = ");
	Serial.println(accelY);
	Serial.print("accelZ = ");
	Serial.println(accelZ);

	delay(100); // Oppdater 10 ganger per sekund
}