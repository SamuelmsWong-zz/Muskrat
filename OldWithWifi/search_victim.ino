//#include "Arduino.h"

void search_victim()
{
	for (i = 0; i < 4; i++)															//find the closest victim
	{
		float minimum_grabber = 1e10;
		if (victim[i][0] > 0 && victim[i][1] > 0)				 //only look at victims not already collected
		{

		// distance_robot = sqrt(sq((float)(closest_victim_y - robot_y)) + sq((float)(closest_victim_x - robot_x)));
		distance_grabber = sqrt(sq((float)(closest_victim_y - grabber_y)) + sq((float)(closest_victim_x - grabber_x)));

			if (distance_grabber < minimum_grabber)
			{
				minimum_grabber = distance_grabber;
			 // minimum_robot = distance_robot;
				closest_victim_x = victim[i][0];
				closest_victim_y = victim[i][1];
		Serial.print("\nclosest_victim_x: ");
		Serial.print(closest_victim_x);
		Serial.print("\nclosest_victim_y: ");
		Serial.print(closest_victim_y);
			}
		}
	}
	bool victim_reached = 0;
	while (victim_reached == 0)														//check if a victim has been reached
	{

		Serial.print("\nclosest_victim_x: ");
		Serial.print(closest_victim_x);
		Serial.print("\nclosest_victim_y: ");
		Serial.print(closest_victim_y);
		Serial.print("\nrobot_x: ");
		Serial.print(robot_x);
		Serial.print("\nrobot_y: ");
		Serial.print(robot_y);
		Serial.print("\ngrabber_x: ");
		Serial.print(grabber_x);
		Serial.print("\ngrabber_y: ");
		Serial.print(grabber_y);
		vect_target_x = (float)(closest_victim_x - robot_x);
		vect_target_y = (float)(closest_victim_y - robot_y);
		vect_grabber_x = (float)(grabber_x - robot_x);
		vect_grabber_y = (float)(grabber_y - robot_y);
		tan_theta = vect_grabber_y / vect_grabber_x;
		theta = atan(tan_theta);
		// distance_robot = sqrt(sq((float)(closest_victim_y - robot_y)) + sq((float)(closest_victim_x - robot_x)));
		//minimum=0;
		// if (distance_grabber > distance_robot && distance_grabber>length_robot)											//if the robot orientation si wrong, turn 180 degrees
		
		Serial.print("\nvect_target_x: ");
		Serial.print(vect_target_x);
		Serial.print("\nvect_grabber_x: ");
		Serial.print(vect_grabber_x);
		Serial.print("\nvect_target_y: ");
		Serial.print(vect_target_y);
		Serial.print("\nvect_grabber_y: ");
		Serial.print(vect_grabber_y);
		if ((vect_target_x*vect_grabber_x + vect_target_y*vect_grabber_y) < 0)
		{
			rotation(3.14);
			delay(1000);
		}
		distance_grabber = sqrt(sq((float)(closest_victim_y - grabber_y)) + sq((float)(closest_victim_x - grabber_x)));
		tan_phi = vect_target_y / vect_target_x;
		phi = atan(tan_phi);
		target_distance = distance_grabber;
		target_angle = phi - theta;
		//rotation_speed = (K1 * 255 * target_angle);
		//moving_speed = (K2 * 255 * target_distance);
		forward_time = (int)(sq(target_distance/forward_speed)*10000+500);
		
		Serial.print("\nforward_time: ");
		Serial.print(forward_time);
		Serial.print("\ntarget_distance: ");
		Serial.print(target_distance);
		rotation(target_angle);
		move_forward(forward_time, forward_speed);	 //move to the victim
		
		if (closest_victim_x - 20 < grabber_x && grabber_x < closest_victim_x + 20 && closest_victim_y - 20 < grabber_y && grabber_y < closest_victim_y + 20)
		{
			fine_tuning();
			victim_reached = 1;													//mark that victim has been reached
			closest_victim_x = -1;							//mark victim taken so it is disregarded in the future
			closest_victim_y = -1;
		}
		requestUpdate("Rotating:", target_angle, "Moving:", forward_time, "search hello");
		wifi_loop();
		assign_coordinates();
	}
}
