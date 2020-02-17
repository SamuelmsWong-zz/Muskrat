/*
 *	This function rotates to the left by 90 degrees and starts a slow sweep to look after a victim using the ultrasound sensor. 
 *	When a victim is found, the robot adjusts a bit more to the right to align the centre of the grabber with the victim (rather than it's right extremity)
 *	and reach_victim() is called. After the victim is grabbed, the robot does all the operations in reverse, until reaching the initial point,
 *	at 0 degrees relative to the tunnel.
 */

void choose_victim()
{
	//Serial.print("choose_victim()");		//for testing
	ramp(0);									//raise ramp
	grabber(0);							 //open grabber
	int prev_us = 0;					//previous ultrasound measurement
	int current_us = 0;			 //current ultrasound measurement
	int next_us = 0;				 
	rotate_left90(); 
	bool victim_flag = 0;		//1 if a victim has been detected
	int time_180 = 3000;
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	myMotor1->setSpeed(slow_turn);				 //start turning to the right
	myMotor2->setSpeed(slow_turn);
	myMotor1->run(FORWARD);
	myMotor2->run(BACKWARD);
	unsigned int time_marker = millis();
	while((victim_flag==0) && (millis() < (time_marker + time_180)))				//until a victim is found or a rotation is complete
	{
		//Serial.print("angle loop\n");						 //for testing
		prev_us = current_us;
		next_us = get_us();
		if (next_us < 200 && next_us > 5) current_us = next_us;		 //elminate outlier sensor returns
			if (current_us < prev_us - 30)										//distinguish between victims and walls (search for a sudden drop in distance) 
			{
				
				victim_flag=1;
				break;		
			}
			if ((int)(((time_marker + time_180) - millis())/500)%2)		 //blink amber LED while moving
			{
				digitalWrite(7, HIGH);
			}
			else
			{
				digitalWrite(7, LOW);
			}
	}
	
	unsigned int turn_time = millis() - time_marker;					 //record the time taken for turning in order to later turn equal and opposite 
	digitalWrite(7, LOW);
	myMotor1->run(RELEASE);						
	myMotor2->run(RELEASE);

 
 float t1=((float)current_us/118)*7650;				 // coverting measured distance to victim into moving time
 delay(1000);
 crawl_right();													 //align centro of grabber with victim (short movement)
 Serial.print("reach_victim");
 reach_victim((int)t1);									//begin rescue sequence
 crawl_left();
	
	//reyurn to initial point
	myMotor1->setSpeed(slow_turn);	
	myMotor2->setSpeed(slow_turn);
	myMotor1->run(BACKWARD);
	myMotor2->run(FORWARD);
	delay((int)(turn_time));
	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
	
	rotate_right90();
}
