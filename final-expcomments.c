#pragma config(Sensor, in8,    liftStop,       sensorReflection)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  liftEnc,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  liftGo,         sensorTouch)
#pragma config(Sensor, dgtl12, led,            sensorLEDtoVCC)
#pragma config(Sensor, I2C_1,  rightIME,       sensorNone)
#pragma config(Sensor, I2C_2,  leftIME,        sensorNone)
#pragma config(Sensor, I2C_3,  armIME,         sensorNone)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, driveLeft, encoderPort, dgtl3)
#pragma config(Motor,  port6,           liftMotor,     tmotorVex393_MC29, openLoop, encoderPort, dgtl5)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop, reversed, driveRight, encoderPort, dgtl1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//There are too many comments.

//int & char values.
//int can store -2,147,483,648 to 2,147,483,647. This is a massive amout of numbers.
//char can only store -128 to 127. This is ideal for things we know the value of, and
//will not exceed a certain value, we might as well save a few bytes of RAM and use a
//char instead of an int.
char speed = 127;
char leftc = 60;
char rightc = 60;
char turnspeed = 70;
int safetydis;
int sdm;
int sdm2;
// char ctrlinuse;
// char lrctrlinuse;
char spdmul = 1;
int rnd;

//void
//Allows us to lift the lift up.
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

//Allows us to lift the lift down.
void liftdown()
{
	if(vexRT[Btn5D] == 1)
	{
		setMotor(liftMotor, -speed);
		wait1Msec(10);
		if(vexRT[Btn5D] == 0)
		{
			setMotor(liftMotor, speed);
			wait1Msec(30);
			stopMotor(liftMotor);
		}
	}
}

//We are now using joystick controls. This is only here incase they don't work
//all too well.
//They didn't work well at all. Mostly screaming.
//Allows for left point turns.
void leftCTRL()
{
	setMotor(leftMotor, turnspeed);
	setMotor(rightMotor, -turnspeed);
	wait1Msec(10);
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
	wait1Msec(10);
	if(vexRT[Btn7R] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Allows for manual forwards.
void forwardCTRL()
{
	setMotor(rightMotor, rightc * spdmul);
	setMotor(leftMotor, leftc * spdmul);
	wait1Msec(10);
	if(vexRT[Btn7U] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Allows for manual backwards.
void backwardsCTRL()
{
	setMotor(rightMotor, -rightc * spdmul);
	setMotor(leftMotor, -leftc * spdmul);
	wait1Msec(10);
	if(vexRT[Btn7D] == 0)
	{
		stopMultipleMotors(leftMotor, rightMotor);
	}
}
//Automatic part of the program, called later.
//Initally, we had another void to save some space. Accidentally copied a little
//too much. A little bit of thought later, we realized it was actually completely
//useless, as the space used by it was about the same as us just putting the things
//in. So it doesn't exist anymore.
void autoctrl()
{
	waitUntil(vexRT[Btn6D] == 1);
	setMotor(liftMotor, -speed);
	waitUntil(SensorValue[liftStop] >= 500);
	stopMotor(liftMotor);
	waitUntil(SensorValue[liftGo] == 1);
	setMotor(liftMotor, speed);
	waitUntil(SensorValue[liftEnc] >= 800);
	stopMotor(liftMotor);
	setMotor(leftMotor, leftc);
	setMotor(rightMotor, rightc);
	wait1Msec(2000);
	stopMultipleMotors(leftMotor, rightMotor);
	setMotor(liftMotor, -speed);
	waitUntil(SensorValue[liftStop] >= 500);
	stopMotor(liftMotor);
}

//joystick controls. They're here for archival purposes, and should only be used
//if you're curious. Generally though, this is to be considered depreciated.
// void ctrl()
// {
// 	if(vexRT[Ch3] >= 10 || vexRT[Ch3] <= -10)
// 	{
// 		++ctrlinuse;
// 		setMultipleMotors(vexRT[Ch3] / 1.5 , leftMotor, rightMotor);
// 	}
// 	if(vexRT[Ch3] <=9 && vexRT[Ch3] >= -9 && lrctrlinuse == 0)
// 	{
// 		ctrlinuse = 0;
// 		stopMultipleMotors(leftMotor, rightMotor);
// 	}
// }

// void lrctrl()
// {
// 	if(vexRT[Ch1] >=10 || vexRT[Ch1] <= -10)
// 	{
// 		++lrctrlinuse;
// 		setMotor(leftMotor, -vexRT[Ch1]);
// 		setMotor(rightMotor, vexRT[Ch1]);
// 	}
// 	if(vexRT[Ch1] <=9 && vexRT[Ch1] >= -9 && ctrlinuse == 0)
// 	{
// 		lrctrlinuse = 0;
// 		stopMultipleMotors(leftMotor, rightMotor);
// 	}
// }

//task(s)

/*math or something. We're taking the button presses and dividing it by the CPU's
fequency (10MHz, 10,000 Hz) to get how many seconds we are pressing the button for.
Please note however, this task is more or less unused and exists soley as a "proof
of concept." There is a way to use this, however! You have to hold 8U down for at
least 1 second for it to work, which is also the reason it isn't used. See the part
of the code commented out, under the header "//SEE". It's near the bottom of the
code, by the way. All you need to do is uncomment the sdm2 part, and comment out the
safetydis part to avoid conflicts*/
//UPDATE: Used for the led to flicker, but slightly modified.
task mth()
{
	while(true)
	{
		if(rnd % 8 == 0)
		{
			turnLEDOn(led);
			wait1Msec(30);
			turnLEDOff(led);
			rnd = rand();
		}else{
			rnd = rand();
			wait1Msec(10);
		}
		/*We "copy" the value of safetydis to sdm, so we are not doing anything destructive
		to safety dis, in the event that we need the raw value.*/
		sdm = safetydis;
		wait1Msec(100);
		/*We devide sdm by 10,000 to get approximately how many seconds we have pressed the
		button for, then "copy" it to sdm2 for future use.*/
		sdm2 = sdm/10000;
	}
}

//Emergency lift stops.
task liftstops()
{
	while(true)
	{
		/*We wait for either the lift encoder (liftEnc) to detect that the lift has gotten too far
		up, or for the light sensor (liftStop) to detect that we are near the bottom.*/
		if(SensorValue[liftStop] >= 500 || SensorValue[liftEnc] >= 825)
		{
			//Stops the motor regardless of state.
			stopMotor(liftMotor);
			//If the lifttSop is tripped.
			if(SensorValue[liftStop] >= 500)
			{
				setMotor(liftMotor, speed);
				wait1Msec(15);
				stopMotor(liftMotor);
				//If this isn't met, to prevent the task from hogging CPU time, we tell it to wait
				//before trying again.
				}else{
				wait1Msec(10);
			}
			//If liftEnc is tripped.
			if(SensorValue[liftEnc] >= 825)
			{
				setMotor(liftMotor, -speed);
				wait1Msec(15);
				stopMotor(liftMotor);
				//If this isn't met, to prevent the task from hogging CPU time, we tell it to wait
				//before trying again.
				}else{
				wait1Msec(10);
			}
		}
		//Just turn off all the motors, when the Ch2 joystick has been sufficently pressed.
		//Use when "things" go south.
		if(vexRT[Ch2] >= 100)
		{
			stopAllMotors();
		}
	}
}

//main task
task main()
{
	//Generates a random seed based off the current system time (time since boot).
	srand(nSysTime);
	//Start the mth task
	startTask(mth);
	/*We do the following for calibration, and to have a contstant 0 value for liftEnc
	for ease of programming.*/
	//Send the lift motor down
	setMotor(liftMotor, -speed);
	/*Wait until liftStop is tripped. We use this as it's analog, and thus keeps a value
	between power states.*/
	waitUntil(SensorValue[liftStop] >= 500);
	//Stop the motor, we've reached our goal.
	stopMotor(liftMotor);
	//Set liftEnc to 0 here.
	resetSensor(liftEnc);
	//Start the safety "liftstops" task.
	startTask(liftstops);
	//loop
	repeat(forever)
	{
		/*The following are all looking for certain actions, like us pressing a button, which
		triggers a certain void function to run.*/
		if(vexRT[Btn5D] == 1)
		{
			liftdown();
		}
		if(vexRT[Btn5U] == 1)
		{
			liftup();
		}
		//We are using joystick controls. These are only here if they don't work.
		//They didn't. Use these.
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
		//Speed multipliers. Sets spdmul to different values, which are them multiplied by
		//their respective values when we go forwards or backwards.
		if(vexRT[Btn8R] == 1)
		{
			spdmul = 2;
		}
		if(vexRT[Btn8L] == 1)
		{
			spdmul = 1;
		}
		if(vexRT[Btn6U] == 1)
		{
			stopTask(liftstops);
			autoctrl();
			startTask(liftstops);
		}
		//Joysick controls for forwards & backwards.
		//Broken.
		// if(vexRT[Ch3] >= 10 || vexRT[Ch3] <= -10)
		// {
		// 	ctrl();
		// }
		// //Joystick controls for left & right.
		// if(vexRT[Ch1] >= 10 || vexRT[Ch1] <= -10)
		// {
		// 	lrctrl();
		// }
		//Button to disable the "safety". Only reason to use this is when adding something onto
		//the lift, and going all the way UP.
		if(vexRT[Btn8U] == 1)
		{
			stopTask(liftstops);
			//We add 1 to safety dis as long as we are pressng 8U. This is added 10,000 times per second,
			//which is the clockspeed for the controller/VEXnet wireless... thing.
			++safetydis;
		}
		//Allows us to re-enable the safety, as long as we have pressed 8U for at least some time, approx
		//0.01 seconds.
		//SEE
		if(vexRT[Btn8D] == 1 && safetydis >= 100 /*sdm2 >= 1*/)
		{
			startTask(liftstops);
			//Also we reset safetydis so we don't start the task again by accident. Don't set sdm or sdm2
			//to 0 individually, as next CPU cycle they'll be set to 0 anyways.
			safetydis = 0;
		}
	}
}
//There's nothing here.
