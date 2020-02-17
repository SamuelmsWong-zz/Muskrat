//This file contains the sub-function reach_victim(), which controls the rescue sequence (move, grabbing, return to position)

void reach_victim(int time_reach)
{
	int time_victim=0;
	int velocity=250;         //set speed moving forwards
	  
	bool sensor = 0;
//	int counter=0;
//	Serial.print(" moving forwards(");Serial.print(velocity);Serial.print(")");
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors

	myMotor1->setSpeed(velocity);
	myMotor2->setSpeed(velocity);


	ramp(0);                 //re-rise ramp just for redundancy
	grabber(0);              //re-open grabber just for redundancy
	
	//move forwards
	myMotor1->run(FORWARD);
	myMotor2->run(FORWARD);
	unsigned int time_marker = millis();
	while(sensor==0 && millis() < (time_marker + time_reach))      //until measured distance is covered
	{
		if (ultrasound()==1) sensor=1;                 //stop is victim is sensed 5 cm closer or less
//		time_victim+=200;
//		counter+=200;
		if ((int)((millis() - time_marker)/500)%2)     //blink amber LED
		{
			digitalWrite(7, HIGH);
		}
		else
		{
			digitalWrite(7, LOW);
		}
	}
	unsigned int run_time = millis() - time_marker;      //store moving time for return
//	delay(5000);

	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);


	delay(5000);
	crawl_forward();                //move until the grabber 'surrounds' the victim
	grabber(1);                     //close grabber to catch victim
	ramp(1);                        //tilt ramp backwards
	victim_grabbed=1;
	crawl_backward();
	move_backward(run_time, velocity);  //follow path back
	
	
}
