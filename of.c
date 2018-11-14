//Automatically turns left
void goLeft()
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, turnspeed);
	setMotor(rightMotor, -turnspeed);
	waitUntil(SensorValue[rightEncoder] >= turn && SensorValue[leftEncoder] <= -turn);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}
//Automatically turns right
void goRight()
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, -turnspeed);
	setMotor(rightMotor, turnspeed);
	waitUntil(SensorValue[rightEncoder] <= -turn && SensorValue[leftEncoder] >= turn);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}
/*
Automatically goes forwards. !NOTE! this has a "switch" variable ('sw'). By
default, this value is set to 0 but can be changed by putting a number where X is
in 'goForward(X);' when needed. Please go 'sw = -1;' when done. This will be
cleared and set to 0 shortly after (the default), and stop the motors.
*/
void goForward(int sw, int encval)
{
	setMotor(leftMotor, left);
	setMotor(rightMotor, right);
	//If we set sw to 0, we go forwards until it is dist cm from an object.
	if(sw == 0)
	{
		waitUntil(SensorValue[sonarSensor] <= dist);
		stopMultipleMotors(leftMotor, rightMotor);
	}
	//If we set sw to 1, we set it to go forward for t milliseconds.
	if(sw == 1)
	{
		wait1Msec(t);
		stopMultipleMotors(leftMotor, rightMotor);
	}
	//If we set sw to 2, we just go forwards. You must do the programming to stop it.
	if(sw == 2)
	{
		setMotor(leftMotor, left);
		setMotor(rightMotor, right);
		wait(10, milliseconds);
	}
	if(sw == 3)
	{
		setMotor(leftMotor, left);
		setMotor(rightMotor, right);
		waitUntil(SensorValue[leftEncoder] >=encval && SensorValue[rightEncoder] >=encval);
	}
}
//Allows for manual left point turns.
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
//Automatic left swing turn.
void swingLeft(int multi)
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, 0);
	setMotor(rightMotor, turnspeed);
	waitUntil(SensorValue[leftEncoder] >= sl*multi);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}
//Automatic right swing turn.
void swingRight(int multi)
{
	resetSensor(leftEncoder);
	resetSensor(rightEncoder);
	setMotor(leftMotor, turnspeed);
	setMotor(rightMotor, 0);
	waitUntil(SensorValue[rightEncoder] >= sr*multi);
	stopMultipleMotors(leftMotor, rightMotor);
	wait(20, milliseconds);
}
//Left line follower correction.
void correctionL()
{
	setMotor(leftMotor, -lc);
	setMotor(rightMotor, rightCorr);
	wait(10, milliseconds);
}
//Right line follower correction.
void correctionR()
{
	setMotor(leftMotor, leftCorr);
	setMotor(rightMotor, -rc);
	wait(10, milliseconds);
}
//Moves the arm out of the way automatically.
void afo()
{
	setMotor(armMotor, armspeed);
	waitUntil(SensorValue[armPotent] <= 1250);
	stopMotor(armMotor);
}
