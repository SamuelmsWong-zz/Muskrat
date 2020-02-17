//#include "Arduino.h"

void reach_triage()
{
  
	bool triage_reached = 0;
	while (triage_reached == 0)														//check if a victim has been reached
	{
		wifi_loop();
		assign_coordinates();

    distance_grabber = sqrt(sq((float)(triage_x - grabber_x))  + sq((float)(triage_y - grabber_y)));
    distance_robot = sqrt(sq((float)(triage_x - robot_x)) + sq((float)(triage_y - robot_y)));

		tan_theta = (grabber_y - robot_y) / (grabber_x - robot_x);
		theta = atan(tan_theta);
		//minimum=0;
		
		if (distance_grabber > distance_robot && distance_grabber>length_robot)											//if the robot orientation si wrong, turn 180 degrees
		{
			rotation(3.14);
		}
		tan_phi = (triage_y - grabber_y) / (triage_x - grabber_x);
		phi = atan(tan_phi);
		target_distance = (distance_grabber / length_robot);
		target_angle = phi - theta;
		//rotation_speed = (K1 * 255 * target_angle);
		//moving_speed = (K2 * 255 * target_distance);
		
			forward_time = (int)((target_distance/forward_speed)*600+500);
		
		rotation(target_angle);
		move_forward(forward_time, forward_speed);   //move to the victim
		
		if (triage_x - 10 < robot_x && robot_x < triage_x + 10 && triage_y - 10 < robot_y && robot_y < triage_y + 10)
		{
      rotation(3.14);
			triage_reached = 1;													//mark that victim has been reached
      ramp(1);                                 //unload ramp
			operate_grabber(1);                     //open grabber
      
		}
	}
}
