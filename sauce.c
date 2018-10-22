#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    leftLineFollower, sensorLineFollower)
#pragma config(Sensor, in2,    centerLineFollower, sensorLineFollower)
#pragma config(Sensor, in3,    rightLineFollower, sensorLineFollower)
#pragma config(Sensor, in6,    gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  touchSensor,    sensorTouch)
#pragma config(Sensor, dgtl12, led,            sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  rightIME,       sensorNone)
#pragma config(Sensor, I2C_2,  leftIME,        sensorNone)
#pragma config(Sensor, I2C_3,  armIME,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	repeat(forever);
	{
		if (vexRT[touchSensor] == 0)
			armControl(armMotor, Btn7U, Btn7D, 25);
	}
}