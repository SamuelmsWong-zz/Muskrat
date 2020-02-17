//#include <Adafruit_MotorShield.h>

void fine_tuning()		//rotate for 1 second with a given speed and move forwards for 2 seconds with a gives speed
{
	int tuned=0;
	while(tuned==0)
	{
		vect_target_x = 100.00;
		vect_target_y = -5.00;
		vect_grabber_x = (float)(grabber_x - robot_x);
		vect_grabber_y = (float)(grabber_y - robot_y);

		// distance_robot = sqrt(sq(vect_target_x) + sq(vect_target_y));
		// distance_grabber = sqrt(sq(vect_grabber_x) + sq(vect_grabber_y));
		if ((vect_target_x*vect_grabber_x + vect_target_y*vect_grabber_y) < 0)
		// if (distance_grabber > distance_robot && distance_grabber > length_robot + 30)
		{
			rotation(3.14);
		}
		if (vect_grabber_x!=0)	tan_theta = vect_grabber_y / vect_grabber_x;
		else tan_theta = vect_grabber_y / (0.00001);
		theta = atan(tan_theta);
		if (vect_target_x!=0)	tan_phi = vect_target_y / vect_target_x;
		else tan_phi = vect_target_y / (0.00001);
		phi = atan(tan_phi);
		target_angle = phi - theta;
		if (target_angle < 0.04 && target_angle > -0.04)
		{
			turning_point_rotation_flag = 1;
		}
		else
		{
			

			Serial.print("TARGET angle");	
			Serial.print(target_angle);
			Serial.print(" rotation:");
			Serial.print(abs(target_angle));
			if (target_angle < 0)
			{
				rotation(-0.07);
			}
			else
			{
				rotation(0.07);
			}
			
		}
		// rotation(target_angle);
		requestUpdate("Fine rotating:", target_angle, "Moving:", 0, "fine hello");
		wifi_loop();
		assign_coordinates();
	}
	move_forward(3000,50);	// creep forward, to be calibrated experientally----------------------------------------------	
}