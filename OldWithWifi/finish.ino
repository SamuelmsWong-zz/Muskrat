//#include "Arduino.h"

void reach_finish()
{
  
	bool finish_reached = 0;
	while (finish_reached == 0)														//check if a victim has been reached
	{
		wifi_loop();
		assign_coordinates();

		distance_robot = sqrt(sq((float)(finish_y - robot_y)) + sq((float)(finish_x - robot_x)));
		distance_grabber = sqrt(sq((float)(finish_y - grabber_y)) + sq((float)(finish_x - grabber_x)));
		tan_theta = (grabber_y - robot_y) / (grabber_x - robot_x);
		theta = atan(tan_theta);
		//minimum=0;
		
		if (distance_grabber > distance_robot && distance_grabber>length_robot)											//if the robot orientation si wrong, turn 180 degrees
		{
			rotation(3.14);
		}
		tan_phi = (finish_y - grabber_y) / (finish_x - grabber_x);
		phi = atan(tan_phi);
		target_distance = (distance_grabber / length_robot);
		target_angle = phi - theta;
		//rotation_speed = (K1 * 255 * target_angle);
		//moving_speed = (K2 * 255 * target_distance);
		
			forward_time = (int)((target_distance/forward_speed)*600+500);
		
		rotation(target_angle);
		move_forward(forward_time, forward_speed);   //move to the victim
		
		if (finish_x - 10 < grabber_x && grabber_x < finish_x + 10 && finish_y - 10 < grabber_y && grabber_y < finish_y + 10)
		{
			finish_reached = 1;													//mark that victim has been reached
            
		}
	}
}
