//Autonomous code file


void StandardAuto(int Side){

Lift_PositionCount = 1;
SetDriveControl(Line, 20, 1.5);
ClawPos = Closed;
wait1Msec(1500);
Lift_PositionCount = 4;
SetDriveControl(Rotation, 40*-Side, 1);
//RampUp(B);
//SetDriveControl(Line, 30*B, 1);
SetDriveControl(Rotation, 80*-Side, 1.5);
RampUp(B);
SetDriveControl(Line, 20*B, 1);
Lift_PositionCount = -1;
wait1Msec(1500);
Lift_PositionCount = 1;
}

void Block(){

ClawPos = Open;
wait1Msec(100);
Lift_PositionCount = 2;
SetDriveControl(Line, 54*B, 1.75);
Dump();
}

void NewAuto(int Side){

}

void Elims_FrontAuto(int Side){
}

void None(){
}

void Elims_BackAuto(int Side){

}

void Skills(int side){
//First load
Lift_PositionCount = 1;
SetDriveControl(Line, 20*B, 3);
ClawPos = Open;
wait1Msec(1500);
ClawPos = Closed;
wait1Msec(1000);
Lift_PositionCount = 4;
RampUp(B);
SetDriveControl(Line, 35*B, 1);
wait1Msec(500);
Dump();
wait1Msec(300);

//Second load
SetDriveControl(Line, 2*B, 0.1);
wait1Msec(200);
ClawPos = Mid;
SetDriveControl(Line, 27, 1);
wait1Msec(600);
ClawPos = Closed;
wait1Msec(500);
Lift_PositionCount = 4;
RampUp(B);
SetDriveControl(Line, 34*B, 1);
wait1Msec(500);
Dump();
wait1Msec(300);

//Third load
Lift_PositionCount = 2;
ClawPos = Mid;
wait1Msec(400);
SetDriveControl(Line, 1.5*B, 0.1);
wait1Msec(200);
SetDriveControl(Line, 4, 0.25);
wait1Msec(200);
SetDriveControl(Rotation, 90*-Side, 1);
wait1Msec(500);
Lift_PositionCount = 1;
wait1Msec(300);
SetDriveControl(Line, 7, 0.25);
wait1Msec(200);
ClawPos = Closed;
wait1Msec(200);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Line, 1*B, 0.5);
wait1Msec(200);
SetDriveControl(Rotation, 90*Side, 1);
wait1Msec(500);
Lift_PositionCount = 4;
wait1Msec(300);
ClawPos = Open;
SetDriveControl(Line, 25, 1.75);
wait1Msec(300);
ClawPos = Closed;
wait1Msec(1000);
Lift_PositionCount = 4;
wait1Msec(500);
SetDriveControl(Line, 36*B, 1);
wait1Msec(500);
Dump();
wait1Msec(300);
SetDriveControl(Line, 1.5*B, 0.1);
wait1Msec(300);

//Middle cube
ClawPos = Mid;
SetDriveControl(Line, 20, 1.75);
wait1Msec(300);
SetDriveControl(Rotation, 90*Side, 1);
wait1Msec(500);
SetDriveControl(Line, 28, 2);
wait1Msec(300);
ClawPos = Closed;
wait1Msec(1200);
Lift_PositionCount = 4;
wait1Msec(500);
SetDriveControl(Line, 30*B, 1);
wait1Msec(500);
SetDriveControl(Rotation, 80*-Side, 1);
wait1Msec(500);
SetDriveControl(Line, 20*B, 1);
wait1Msec(500);
Dump();
wait1Msec(300);

//Front 3 stars
ClawPos = Mid;
Lift_PositionCount = 2;
wait1Msec(500);
SetDriveControl(Rotation, 90*Side, 1);
wait1Msec(500);
Lift_PositionCount = 1;
wait1Msec(500);
SetDriveControl(Line, 35, 1.75);
wait1Msec(300);
ClawPos = Closed;
wait1Msec(600);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Rotation, 80*-Side, 1);
wait1Msec(500);
SetDriveControl(Line, 5*B, 1);
wait1Msec(500);
Dump();
wait1Msec(500);

//Back 3 stars
SetDriveControl(Line, 32, 1.75);
wait1Msec(300);
ClawPos = Closed;
wait1Msec(1000);
SetDriveControl(Line, 5*B, 1);
wait1Msec(500);
ClawPos = Open;
SetDriveControl(Line, 5, 1);
wait1Msec(500);
ClawPos = Closed;
wait1Msec(900);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Line, 35*B, 1.75);
wait1Msec(600);
Dump();
wait1Msec(200);

//Last Cube
SetDriveControl(Rotation, 30*Side, 1);
wait1Msec(500);
SetDriveControl(Line, 30, 1.75);
wait1Msec(600);
ClawPos = Closed;
wait1Msec(600);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Rotation, 20*-Side, 1);
wait1Msec(1000);
SetDriveControl(Line, 35*B, 1.75);
wait1Msec(600);
Dump();
wait1Msec(300);


//Corner Star
SetDriveControl(Rotation, 90*Side, 1);
wait1Msec(500);
Lift_PositionCount = 4;
wait1Msec(300);
ClawPos = Mid;
Lift_PositionCount = 1;
wait1Msec(300);
SetDriveControl(Line, 38, 2);
wait1Msec(600);
ClawPos = Closed;
wait1Msec(300);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Rotation, 90*-Side, 1);
wait1Msec(500);
Lift_PositionCount = 1;
wait1Msec(300);
ClawPos = Mid;
SetDriveControl(Line, 38, 2);
wait1Msec(600);
ClawPos = Closed;
wait1Msec(500);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Line, 38*B, 2);
wait1Msec(600);
Dump();
wait1Msec(600);


//Hang
SetDriveControl(Line, 25, 1.75);
wait1Msec(600);
SetDriveControl(Rotation, 180*-Side, 1);
wait1Msec(500);
Lift_PositionCount = 4;
wait1Msec(300);
SetDriveControl(Line, 25*B, 1.75);
wait1Msec(1000);
SetDriveControl(Line, 8, 1);
wait1Msec(600);
SetDriveControl(Rotation, 45*Side, 1);
wait1Msec(500);
SetDriveControl(Line, 8*B, 1);
wait1Msec(600);
Lift_PositionCount = 3;
wait1Msec(300);







}
