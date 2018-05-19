//Driver Control
const unsigned int TrueSpeed[128] =
{
	25,  25,  25,  25,  25,  25,  25,  25,  25,  25,
	25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
	25, 25, 26, 26, 26, 27, 28, 28, 28, 29,
	29, 30, 30, 30, 30, 31, 31, 32, 32, 32,
	33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
	37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
	41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
	46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
	52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
	61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
	71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
	80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
	88, 89, 89, 90, 90, 127, 127, 127
};
void SetDrive(int LeftDrivePower, int RightDrivePower){
	LeftDrivePower = LeftDrivePower > 127 ? 127 : LeftDrivePower;
	LeftDrivePower = LeftDrivePower < -127 ? -127 : LeftDrivePower;
	RightDrivePower = RightDrivePower > 127 ? 127 : RightDrivePower;
	RightDrivePower = RightDrivePower < -127 ? -127 : RightDrivePower;
	if(vexRT(Btn7L) == true){
		if(RightDrivePower > 0)
			RightDrivePower = TrueSpeed[RightDrivePower];
		else if(RightDrivePower < 0)
			RightDrivePower = -TrueSpeed[-RightDrivePower];
		else
			RightDrivePower = 0;

		LeftDrivePower = RightDrivePower;
	}
	else{
		if(LeftDrivePower > 0)
			LeftDrivePower = TrueSpeed[LeftDrivePower];
		else if(LeftDrivePower < 0)
			LeftDrivePower = -TrueSpeed[-LeftDrivePower];
		else
			LeftDrivePower = 0;

		// right
		if(RightDrivePower > 0)
			RightDrivePower = TrueSpeed[RightDrivePower];
		else if(RightDrivePower < 0)
			RightDrivePower = -TrueSpeed[-RightDrivePower];
		else
			RightDrivePower = 0;
	}

	motor[RightDriveA] = RightDrivePower;
	motor[RightDriveB] = RightDrivePower;
	motor[LeftDriveA] = LeftDrivePower;
	motor[LeftDriveB] = LeftDrivePower;
}

void SetLiftMotors(int Power){
	motor[Lift_A] = Power;
	motor[Lift_B] = Power;
	motor[Lift_C] = Power;
}

void SetLiftPosition(int Position){
	Lift_Position = Position;
}

task DriveControl();
volatile bool BreakLoop;
volatile int DriveMode;
volatile float DesiredDriveValue;
volatile bool FirstLockCheck = false;
volatile bool DriveActive;
volatile float LinekP = .33;
#define Line 1
#define Rotation 2
#define Off 3
#define F 1
#define B -1
#define R -1
#define L 1
float LeftTurnConst = 7.66;
float RightTurnConst = 7.66;
float TurnConst;
void SetDriveControl(int Mode, int Value, int Time){
	DriveMode = Mode;
	SensorValue(Drive_Encoder) = 0;
	SensorValue(Gyro1) = 0;
	TurnConst = (sgn(Value) == -1) ? RightTurnConst : LeftTurnConst;
	DesiredDriveValue = (Mode == Line) ? (Value*335)/10.205 : (Value * TurnConst);
	clearTimer(T1);
	BreakLoop = false;
	DriveActive = true;
	while(BreakLoop == false && time1[T1] < (Time*1000)){
		wait1Msec(20);
	}
	FirstLockCheck = false;
	BreakLoop = false;
	DriveActive = false;
	SetDrive(0,0);
}

void RampUp(int D){
DriveActive = false;
SetDrive(30*D,30*D);
wait1Msec(375);
DriveActive = true;
}

void Dump(){
Lift_PositionCount = -1;
wait1Msec(2000);
Lift_PositionCount = 1;
}
