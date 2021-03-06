#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, in1,    armPotent,      sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  frontTouch,     sensorTouch)
#pragma config(Sensor, dgtl6,  sonarSensor,    sensorSONAR_cm)
#pragma config(Sensor, dgtl12, led,            sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  rightIME,       sensorNone)
#pragma config(Sensor, I2C_2,  leftIME,        sensorNone)
#pragma config(Sensor, I2C_3,  armIME,         sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed, encoderPort, I2C_3)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int left = 36;
int right = 30;
int armspeed = 40;
int dist = 15;
int turn = 250;
int turnspeed = 50;
//int fdist = 30;
void goforward()
{
	setMotor(leftMotor, left);
	setMotor(rightMotor, right);
	waitUntil(SensorValue[sonarSensor] <= dist);
	stopMultipleMotors(leftMotor, rightMotor);
}
//void finalforward()
//{
//	setMotor(leftMotor, left);
//	setMotor(rightMotor, right);
//	waitUntil(SensorValue[sonarSensor] <= dist);
//	stopMultipleMotors(leftMotor, rightMotor);
//}

void goleft()
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, turnspeed);
	setMotor(rightMotor, -turnspeed);
	waitUntil(SensorValue[rightEncoder] >= turn && SensorValue[leftEncoder] <= -turn);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}

void goright()
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, -turnspeed);
	setMotor(rightMotor, turnspeed);
	waitUntil(SensorValue[rightEncoder] <= -turn && SensorValue[leftEncoder] >= turn);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}

task main()
{
	//Set some constant values that would be a pain to change one at a time.
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	repeat(forever)
	{
		//Starts everything.
		if(vexRT[Btn7U] == 1)
		{
			turnLEDOn(led);
			//Gets the claw out of the way.
			setMotor(armMotor, armspeed);
			waitUntil(SensorValue[armPotent] <= 1250);
			stopMotor(armMotor);
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns right, 90 degrees.
			goright();
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns left, 90 degrees.
			goleft();
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns left, 90 degrees.
			goleft();
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns right, 90 degrees.
			goright();
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns right, 90 degrees.
			goright();
			//Moves forwards until it is <dist> away from the wall.
			goforward();
			//Turns right, 90 degrees
			goleft();
			//Moves forwards until it is <dist> away from the wall. Will go on forever, in theory.
			goforward();
			//End
			turnLEDOff(led);
		}
		if(vexRT[Btn6U] == 1)
		{
			goforward();
			goleft();
		}
		if(vexRT[Btn6D] == 1)
		{
			goforward();
			goright();
		}
	}
}
