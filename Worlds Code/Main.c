#pragma config(Sensor, in1,    AutoPot,        sensorPotentiometer)
#pragma config(Sensor, in2,    RightClawPot,   sensorPotentiometer)
#pragma config(Sensor, in3,    Gyro1,          sensorGyro)
#pragma config(Sensor, in7,    LeftClawPot,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  Drive_Encoder,  sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  Climb_Switch,   sensorTouch)
#pragma config(Sensor, dgtl6,  Lift_Encoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl10, Lift_Switch,    sensorTouch)
#pragma config(Motor,  port1,           RightClaw,     tmotorVex393HighSpeed_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           Lift_C,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           Lift_B,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           RightDriveA,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           LeftDriveA,    tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port6,           RightDriveB,   tmotorVex393TurboSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           LeftDriveB,    tmotorVex393TurboSpeed_MC29, openLoop)
#pragma config(Motor,  port8,           Lift_A,        tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Lift_D,        tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          LeftClaw,      tmotorVex393HighSpeed_HBridge, openLoop, reversed)

#pragma platform(VEX2)

#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"   //Main competition background code


task liftcontrol();
volatile int Lift_Position = 0;
int Lift_PositionCount = 1;
volatile int Lift_Power;
#define Lift_UpperLimit 2100
#define Lift_Pos1 -15
#define Lift_Pos2 682
#define Lift_Pos3 2000
#define Lift_PosAuto 400
#define Lift_PosRelease 1700

task Lclawcontrol();
task Rclawcontrol();
volatile int LeftClaw_Position = 0;
volatile int LeftClaw_Power;

#define RightClaw_Cross 24
#define RightClaw_Open 1850
#define RightClaw_Closed 500
#define RightClaw_Mid 1120

volatile int RightClaw_Position = 0;
volatile int RightClaw_Power;

#define LeftClaw_Cross 4000
#define LeftClaw_Open 2000 //(150)
#define LeftClaw_Closed 3550 //(2310)
#define LeftClaw_Mid 2700

#define Mid 2
#define Closed 1
#define Open 3
#define ClawThreshold 25

volatile int ClawPos = 0;

#include "Functions.c"
#include "Autos.c"

void Auto(){
	if(SensorValue(AutoPot) < 600){
		StandardAuto(L);
	}
	else if(SensorValue(AutoPot) < 1200){
		Elims_FrontAuto(L)

	}
	else if(SensorValue(AutoPot) < 1800){
		Skills(R);

	}
	else if(SensorValue(AutoPot) < 2400){
		SpicyBlock();
	}
	else if(SensorValue(AutoPot) < 3000){
		NewSpicyAuto(R);
	}
	else if(SensorValue(AutoPot) < 3600){
		Elims_FrontAuto(R);
	}
	else{
		StandardAuto(R);
	}
}

string sLStandard = "Standard Left";
string sLElims_Front = "Elims Front Left";
string sRSkills = "Skills";
string sLSpicy = "Spicy";
string sNone = "Block";
string sRSpicy = "Spicy Right";
string sRElims_Front = "Elims Front Right";
string sRStandard = "Standard Right";
string SelectedAuton;

void DisplayAuto(){
	if(SensorValue(AutoPot) < 600){
		SelectedAuton = sLStandard;
	}
	else if(SensorValue(AutoPot) < 1200){
		SelectedAuton = sLElims_Front;
	}
	else if(SensorValue(AutoPot) < 1800){
		SelectedAuton = sRSkills;
	}
	else if(SensorValue(AutoPot) < 2400){
		SelectedAuton = sNone;
	}
	else if(SensorValue(AutoPot) < 3000){
		SelectedAuton = sRSpicy;
	}
	else if(SensorValue(AutoPot) < 3600){
		SelectedAuton = sRElims_Front;
	}
	else{
		SelectedAuton = sRStandard;
	}

	bLCDBacklight = true;
	clearLCDLine(0); clearLCDLine(1);
	displayLCDString(0, 0, SelectedAuton);
}

void pre_auton(){

	bStopTasksBetweenModes = true;
	SensorValue(Drive_Encoder) = 0;
	SensorValue(Lift_Encoder) = 0;

	SensorType[in3] = sensorNone;
	wait1Msec(3000);
	SensorType[in3] = sensorGyro;
	wait1Msec(1000);


	while (bIfiRobotDisabled) {
		DisplayAuto();
	}
}



task autonomous(){
	startTask(liftcontrol); startTask(Lclawcontrol); startTask(Rclawcontrol);startTask(DriveControl);
	Auto();
	DisplayAuto();
}

task usercontrol(){
	 startTask(liftcontrol); startTask(Lclawcontrol); startTask(Rclawcontrol);
	 bool Lift_Toggle2 = false;
 	 bool Claw_Toggle = false;
	 int LeftDrive; int RightDrive;
	 while (true){
	 DisplayAuto();
	 LeftDrive = abs(vexRT(Ch3)) > 20 ? vexRT(Ch3) : 0;
	 RightDrive = abs(vexRT(Ch2)) > 20 ? vexRT(Ch2) : 0;
	 SetDrive(LeftDrive, RightDrive);

		if(vexRT(Btn5U) == 1){
			Lift_PositionCount = -1;
		}
		else {
			if(Lift_PositionCount == -1){
			Lift_PositionCount = 0;
		}
	}
	


		if(vexRT(Btn6U) == 1){
			if(Claw_Toggle == false){
				ClawPos--;
				ClawPos = (ClawPos < 1) ? 3 : ClawPos;
				Claw_Toggle = true;
			}
		}
		else{
			Claw_Toggle = false;
		}

		if(vexRT(Btn5D) == 1){
			Lift_PositionCount = -4;
	}
			else{
			if(Lift_PositionCount == -4){
				Lift_PositionCount = 0;
		}
		}

		if(vexRT(Btn8U) == 1){
            Lift_PositionCount = -5;
        }
        else{
            if(Lift_PositionCount == -5)
            {
                Lift_PositionCount = -3;
            }
        }

		if(vexRT(Btn6D) == 1){
			if(Lift_Toggle2 == false){
				Lift_PositionCount++;

				if(Lift_PositionCount > 3){
					Lift_PositionCount = 3;
				}

			}
			Lift_Toggle2 = true;
		}
		else{
			Lift_Toggle2 = false;
		}

		if(vexRT(Btn8D) == 1){
			startTask(DriveControl);
			Auto();
			stopTask(DriveControl);
		}
	}
}

task Lclawcontrol(){
	int LeftClaw_Current;
	int LeftClawP;
	float LeftClaw_kP = .3;
	while(true){

			switch(ClawPos){
			case 1:
			LeftClaw_Position = LeftClaw_Closed;
			break;
			case 2:
			LeftClaw_Position = LeftClaw_Mid;
			break;
			case 3:
			LeftClaw_Position = LeftClaw_Open;
			break;
			}

			LeftClaw_Current = SensorValue(LeftClawPot); //Current Error
			LeftClawP = LeftClaw_Position - LeftClaw_Current;
			LeftClaw_Power = LeftClawP * LeftClaw_kP;

			//System Limits
			if(SensorValue(LeftClawPot) > LeftClaw_Closed){
				LeftClaw_Power = LeftClaw_Power > 0 ? 0 : LeftClaw_Power;
			}

			if(SensorValue(LeftClawPot) < LeftClaw_Open){
				LeftClaw_Power = LeftClaw_Power < 0 ? 0 : LeftClaw_Power;
			}
			motor[LeftClaw] = LeftClaw_Power;
			wait1Msec(20);
		}
}

task Rclawcontrol(){
	int RightClaw_Current;
	int RightClawP;
	float RightClaw_kP = .3;
	while(true){
			switch(ClawPos){
			case 1:
			RightClaw_Position = RightClaw_Closed;
			break;
			case 2:
			RightClaw_Position = RightClaw_Mid;
			break;
			case 3:
			RightClaw_Position = RightClaw_Open;
			break;
			}

			RightClaw_Current = (SensorValue(RightClawPot)); //Current Error
			RightClawP = RightClaw_Position - RightClaw_Current;
			RightClaw_Power = RightClawP * RightClaw_kP;
			//System Limits
			if(SensorValue(RightClawPot) > RightClaw_Closed){
				RightClaw_Power = RightClaw_Power;
			}

			if(SensorValue(RightClawPot) < RightClaw_Open){
				RightClaw_Power = RightClaw_Power;
			}
			motor[RightClaw] = RightClaw_Power;
			wait1Msec(20);
	}
}

task liftcontrol(){
	int Lift_Current; float LkP = 0.3; int Lift_Hold = 0; int LP;
	while (true){
		Lift_Current = abs(SensorValue(Lift_Encoder));
		LP = Lift_Position - Lift_Current;
		switch(Lift_PositionCount){
	  case -5:
    if(SensorValue(Climb_Switch) == 0)
    {
    Lift_Power = 127;
    }
    else{
    Lift_Power = 0;
    }

    break;
		case -4:
		if(SensorValue(Lift_Switch) == 1){
		    Lift_Power = -15;
				SensorValue(Lift_Encoder) = 0;
			}
		    Lift_Power = -127;
		break;
		case -3:
		Lift_Power = 0;
		break;
		case -2:
		Lift_Power = 127;
		break;
		case -1:
			SetLiftPosition(Lift_UpperLimit);
			Lift_Power = (LP*2.5 - 30);
			if(Lift_Current > Lift_PosRelease){
			ClawPos = Open;
			}
			break;
		case 0:
			Lift_Power = (Lift_Current < Lift_UpperLimit) ? 0 : (LP * LkP - 20);
				if(SensorValue(Lift_Switch) == 1){
				Lift_Power = -30;
				SensorValue(Lift_Encoder) = 0;
			}
			break;
		case 1:
			SetLiftPosition(Lift_Pos1);
			if(SensorValue(Lift_Switch) == 1){
				Lift_Power = -10;
				SensorValue(Lift_Encoder) = 0;
			}
			else{
				Lift_Power = (LP * LkP + Lift_Hold);
			}
			break;

		case 2:
			SetLiftPosition(Lift_Pos2);
			Lift_Power = (LP * LkP + Lift_Hold);
			break;

		case 3:
			SetLiftPosition(Lift_Pos3);
			Lift_Power = (LP * LkP + Lift_Hold);
			break;
		case 4:
		SetLiftPosition(Lift_PosAuto);
			Lift_Power = (LP * LkP + Lift_Hold);
		break;
	}
		SetLiftMotors(Lift_Power);
		wait1Msec(20);
	}
}

task DriveControl(){

	int DrivePower; int DriveDirection; float CurrentDriveValue; float DkP;
	int LockingThreshold = 15;
	int BrakingPower; int BrakingTime; short BatteryLvl;
	int P;
	while(true){
		if(DriveActive){
			CurrentDriveValue = DriveMode == Line ? -SensorValue(Drive_Encoder) : SensorValue(Gyro1);
			DriveDirection = sgn(DrivePower);
			DkP = DriveMode == Line ? LinekP : .2;
			if(DriveMode == Rotation){
				DkP = DesiredDriveValue > (75 * TurnConst) ? .13 : .13;
			}
			BrakingPower = DriveMode == Line ? 20 : 80;

			BrakingTime = 120;
			P = (DesiredDriveValue - CurrentDriveValue);
			if(abs(P) > LockingThreshold){
				DrivePower = P * DkP;
			}
			if(abs(P) < LockingThreshold){
				DrivePower = -DriveDirection*BrakingPower;
				FirstLockCheck = true;
			}
			BatteryLvl = nImmediateBatteryLevel/1000;
			DrivePower = (DrivePower * pow(8.4/BatteryLvl, 2));
			switch(DriveMode){
			case Line: SetDrive(DrivePower, DrivePower);	break;
			case Rotation: SetDrive(-DrivePower, DrivePower); break;
			case Off: SetDrive(0,0); break;
			}
			if(FirstLockCheck == true){
				wait1Msec(BrakingTime);
				SetDrive(0,0);
				wait1Msec(0);
				if(abs(P) < LockingThreshold){
					BreakLoop = true;
				}
				else{
					FirstLockCheck = false;
				}
			}
			wait1Msec(5);
		}
		else{
			wait1Msec(5);
		}
	}
}
