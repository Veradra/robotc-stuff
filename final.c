#pragma config(Sensor, in8,    liftStop,       sensorReflection)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl12, led,            sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  rightIME,       sensorNone)
#pragma config(Sensor, I2C_2,  leftIME,        sensorNone)
#pragma config(Sensor, I2C_3,  armIME,         sensorNone)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port6,           liftMotor,     tmotorVex393_MC29, openLoop, encoderPort, dgtl5)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//int
int speed = 127;
int leftc = 60;
int rightc = 60;
int turnspeed = 70;


//void
//Allows us to lift the lift up or down.
void liftup()
{
	if(vexRT[Btn5U] == 1)
	{
		setMotor(liftMotor, speed);
		wait1Msec(10);
		if(vexRT[Btn5U] == 0)
		{
			stopMotor(liftMotor);
		}
	}
}
void liftdown()
{
	if(vexRT[Btn5D] == 1)
	{
		setMotor(liftMotor, -speed);
		wait1Msec(10);
		if(vexRT[Btn5D] == 0)
		{
			stopMotor(liftMotor);
		}
	}
}

//Allows for left point turns.
void leftCTRL()
{
	setMotor(leftMotor, turnspeed);
	setMotor(rightMotor, -turnspeed);
	wait1Msec(20);
	if(vexRT[Btn7L] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Allows for manual right point turns.
void rightCTRL()
{
	setMotor(leftMotor, -turnspeed);
	setMotor(rightMotor, turnspeed);
	wait1Msec(20);
	if(vexRT[Btn7R] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Allows for manual forwards.
void forwardCTRL()
{
	setMotor(rightMotor, rightc);
	setMotor(leftMotor, leftc);
	wait1Msec(20);
	if(vexRT[Btn7U] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Allows for manual backwards.
void backwardsCTRL()
{
	setMotor(rightMotor, -rightc);
	setMotor(leftMotor, -leftc);
	wait1Msec(20);
	if(vexRT[Btn7D] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}

//task(s)

//Emergency lift stops.
task liftstops()
{
	while(true)
	{
		if(SensorValue[liftStop] >= 500 || SensorValue[liftEnc] >= 850)
		{
			stopMotor(liftMotor);
			if(SensorValue[liftStop] >= 500)
			{
				setMotor(liftMotor, speed)
				wait1Msec(30);
				stopMotor(liftMotor);
			}
			if(SensorValue[liftEnc] >= 850)
			}else{
			wait1Msec(10)
		}
	}
}

//main task
task main()
{
	setMotor(liftMotor, -speed);
	waitUntil(SensorValue[liftStop] >= 500);
	stopMotor(liftMotor);
	resetMotorEncoder(liftEnc);
	startTask(liftstops);
	repeat(forever)
	{
		if(vexRT[Btn5D] == 1)
		{
			liftdown();
		}
		if(vexRT[Btn5U] == 1)
		{
			liftup();
		}
		if(vexRT[Btn7U] == 1)
		{
			forwardCTRL();
		}
		if(vexRT[Btn7D] == 1)
		{
			backwardsCTRL();
		}
		if(vexRT[Btn7R] == 1)
		{
			rightCTRL();
		}
		if(vexRT[Btn7L] == 1)
		{
			leftCTRL();
		}
	}
}
}
