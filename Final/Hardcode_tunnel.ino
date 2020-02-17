//This file contains all hard-coded navigation functions


void tunnel_from_start()    //enter tunnel from starting area
{
	//set moving times with constant velocities
	int time_reverse=2000;
	int time_turning_point=8300;
	
	move_backward(time_reverse,150);      //move backwards until hitting wall to calibrate position
	move_forward(time_turning_point, 255);   //move until reaching a point on the middle line of the tunnel
	rotate_right90();                       //orientates towards tunnel
	move_forward(time_tunnel,255);          //enter tunnel
	//Serial.print("\nFINISHED TUNNEL FROM START\n");
	
}


void triage_from_cave()       //exit tunnel and reach triage area
{
	
	move_backward(time_tunnel-400,255);     
	rotate_left90();
	move_forward(time_triage,255);
	ramp(0);                    //raise ramp
	grabber(0);                 //open grabber to drop victim
	victim_grabbed=0;           //reset victim collection status
	//Serial.print("\nFINISHED TUNNEL FROM CAVE\n");
}



void tunnel_from_triage()       //enter tunnel from triage area
{
	
	move_backward(time_triage+200,255);
	rotate_right90();
	move_forward(time_tunnel,255);
	//Serial.print("\nFINISHED TUNNEL FROM TRIAGE\n");
}

void finish()       //reach finish area from the triage area after dropping the last victim
{

	int time_reverse_finish=15500;
	move_backward(time_reverse_finish,255);
	move_forward(600,255);
	//Serial.print("\nFINISHED FINISH\n");
	while (1)
	{
		delay(72000);
	}

	
}
