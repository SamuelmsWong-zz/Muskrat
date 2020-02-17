//#include "Arduino.h"

void enter_tunnel(int turning_point_x, int turning_point_y, int tunnel_x, int tunnel_y)				 //entering tunnel from the starting point or the traige area
{
	digitalWrite(9, LOW);
	bool finish = 0;
	turning_point_rotation_flag = 0;
	turning_point_flag = 0;
	while (finish == 0)			//check if action was completed----------------------------------------loop
	{
		Serial.println("Traversing tunnel");
		Serial.print(turning_point_flag == 0);
		Serial.write("coordinates: ");
		Serial.print(robot_x);
		Serial.write(", ");
		Serial.print(robot_y);
		Serial.write(", ");
		Serial.print(grabber_x);
		Serial.write(", ");
		Serial.print(grabber_y);
		Serial.write(", ");
		Serial.print(turning_point_x);
		Serial.write(", ");
		Serial.print(turning_point_y);
		Serial.write(", ");
		Serial.print(sq((turning_point_x - robot_x)));
		Serial.write(", ");
		Serial.print(sq((turning_point_y - robot_y)));
		Serial.write(", ");
		Serial.print(sq((turning_point_y - robot_y)) + sq((turning_point_x - robot_x)));
		Serial.write(".\n");
//		delay(1000);
//		turning_point_flag = 1;
		if (turning_point_flag == 0)	//check if the turning point has been reached
		{
//			distance_robot = sqrt(sq((float)(turning_point_y - robot_y)) + sq((float)(turning_point_x - robot_x)));
//			distance_grabber = sqrt(sq((float)(turning_point_y - grabber_y)) + sq((float)(turning_point_x - grabber_x)));

//			Serial.write("Distances: (");
//	 		Serial.print(distance_robot); Serial.write(", ");
//	 		Serial.print(distance_grabber);Serial.write(")");
		
			vect_target_x = (float)(turning_point_x - robot_x);
			vect_target_y = (float)(turning_point_y - robot_y);
			vect_grabber_x = (float)(grabber_x - robot_x);
			vect_grabber_y = (float)(grabber_y - robot_y);

			// distance_robot = sqrt(sq(vect_target_x) + sq(vect_target_y));
			// distance_grabber = sqrt(sq(vect_grabber_x) + sq(vect_grabber_y));
			if ((vect_target_x*vect_grabber_x + vect_target_y*vect_grabber_y) < 0)
//			if (distance_grabber > distance_robot && distance_grabber > length_robot + 15)								//if robot is facing the wrong way turn 180 degrees
			{
				Serial.print("Turning 179");
				rotation(3.14);
				delay(1000);
			}

			if ((grabber_x - robot_x)!=0)	tan_theta = vect_grabber_y / vect_grabber_x;
			else tan_theta = (grabber_y - robot_y) / (0.00001);
			theta = atan(tan_theta);

			if ((turning_point_x - robot_x)!=0)	tan_phi = vect_target_y / vect_target_x;
			else tan_phi = (turning_point_y - robot_y)/ (0.00001);
			phi = atan(tan_phi);



			target_distance = distance_robot;
			target_angle = phi - theta;
			//forward_time = (int)((target_distance/forward_speed)*1500+250);
			forward_time = (int)(sq(target_distance/forward_speed)*10000+500);
			// rotation_speed = (10+K1 * 235 * target_angle/1.57); // pi/2
			// moving_speed = (50+ K2 * 205 * target_distance/640);

			 	Serial.print(grabber_y - robot_y); Serial.print(", ");
			 	Serial.print(grabber_x - robot_x); Serial.print(", ");
			 	Serial.print(tan_theta); Serial.print(", ");
			 	Serial.print(theta); Serial.print(", ");
			 	Serial.print(phi); Serial.print(", ");
			 	Serial.print(target_angle); Serial.print(", ");
			 	Serial.print(target_distance); Serial.print(", ");

			// Serial.print("movement: (");
			// 	Serial.print(rotation_speed); Serial.print(", ");
			// 	Serial.print(moving_speed);Serial.print(")");
			// delay(1000);
			digitalWrite(9, HIGH);
			rotation(target_angle);
			move_forward(forward_time, forward_speed);
			digitalWrite(9, LOW);

			if (turning_point_x - 15 < robot_x && robot_x < turning_point_x + 15 && turning_point_y - 15 < robot_y && robot_y < turning_point_y + 15)
			{
				turning_point_flag = 1;
			}
		}
		else if (turning_point_rotation_flag == 0)				//if turning point is reached, rotate to be perpendicular on the tunnel entry
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
		}
		else																					//quickly move through the tunnel in a straight line
		{
			move_forward(9000, forward_speed);
			finish = 1;
		}
		Serial.println("Asking for Traversing data");
		requestUpdate("Rotating:", target_angle, "Moving:", forward_time, "tunnel hello");
		wifi_loop();
		assign_coordinates();
	}
}
