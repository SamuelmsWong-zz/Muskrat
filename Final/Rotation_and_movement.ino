/*This file contains the general function for moving forward, taking duration and velocity as parameters, and a function rotating by 90 degrees,
as well as variations of these, including different directions and small increment movements*/

void move_forward(int duration, int velocity)
{
	
	//Serial.print("\n moving forwards(");Serial.print(duration);Serial.print(", ");Serial.print(velocity);Serial.print(")");
//	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //assign motors
	AFMS.begin();

	myMotor1->setSpeed(abs(velocity));
	myMotor2->setSpeed(abs(velocity)-4);
	myMotor1->run(FORWARD);
	myMotor2->run(FORWARD);
	
	int k;   
	for (k=0;k<duration-500;k+=500)
	{
		if (victim_grabbed==0)     //blink amber LED when moving withou victim
		{
			if (victim_LED) digitalWrite(7, LOW);     
			else digitalWrite(7, HIGH);
			victim_LED = !victim_LED;
		}
		else digitalWrite(7,HIGH);   //keep amber LED on when moving with a victim
		delay(500);
	}
	delay(duration - k);    //delay between changing LED status

	myMotor1->run(RELEASE);  //finish motion
	myMotor2->run(RELEASE);
}

void move_backward(int duration, int velocity)    //same as moving_forwards(), except the direction
{
	
	//Serial.print("\nmoving backwards(");Serial.print(duration);Serial.print(", ");Serial.print(velocity);Serial.print(")");
//	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	AFMS.begin();

	myMotor1->setSpeed(abs(velocity));
	myMotor2->setSpeed(abs(velocity)-4);
	myMotor1->run(BACKWARD);
	myMotor2->run(BACKWARD);

	int k=0;
	for (k=0;k<duration-500;k+=500)
	{
		if (victim_grabbed==0) 
		{
			if (victim_LED) digitalWrite(7, LOW);
			else digitalWrite(7, HIGH);
			victim_LED = !victim_LED;
		}
		else digitalWrite(7,HIGH);
		delay(500);
	}
	delay(duration - k);

	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}


void rotate_right90()
{
	//Serial.print("rotatingright90(");
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	AFMS.begin();

	myMotor1->setSpeed(rotation_speed);
	myMotor2->setSpeed(rotation_speed);
	myMotor1->run(FORWARD);
	myMotor2->run(BACKWARD);
	int delaytime = 2100;          //calibrated time for rotation with set_speed rotation_speed=150

	int k;
	for (k=0;k<delaytime-500;k+=500)
	{
		if (victim_grabbed==0) 
		{
			if (victim_LED) digitalWrite(7, LOW);
			else digitalWrite(7, HIGH);
			victim_LED = !victim_LED;
		}
		else digitalWrite(7,HIGH);
		delay(500);	
	}
	delay(delaytime - k);
	digitalWrite(7, LOW);
	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}

void rotate_left90()
{
	//Serial.print("rotatingleft90(");
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	AFMS.begin();

	myMotor1->setSpeed(rotation_speed);
	myMotor2->setSpeed(rotation_speed);
	myMotor1->run(BACKWARD);
	myMotor2->run(FORWARD);
	int delaytime = 2300;          //slightly different fro rotate_right90() because of assymetry of chassis 

	int k;
	for (k=0;k<delaytime-500;k+=500)
	{
		if (victim_grabbed==0) 
		{
			if (victim_LED) digitalWrite(7, LOW);
			else digitalWrite(7, HIGH);
			victim_LED = !victim_LED;
		}
		else digitalWrite(7,HIGH);
		delay(500);	
	}
	delay(delaytime - k);
	digitalWrite(7, LOW);
	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}

void crawl_forward()                  //slow move forwards for a short period of time
{
	move_forward(2000, 50);
	

}

void crawl_backward()
{
	move_backward(2000, 50);
 

}

void crawl_right()        //slowly rotate for a short period of time
{
	//Serial.print("rotatingleft90("));
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	AFMS.begin();

	myMotor1->setSpeed(slow_turn);
	myMotor2->setSpeed(slow_turn);
	myMotor1->run(FORWARD);
	myMotor2->run(BACKWARD);
	int delaytime = 500;
	delay(delaytime);
	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}

void crawl_left()
{
	//Serial.print("rotatingleft90("));
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	AFMS.begin();

	myMotor1->setSpeed(slow_turn);
	myMotor2->setSpeed(slow_turn);
	myMotor1->run(BACKWARD);
	myMotor2->run(FORWARD);
	int delaytime = 500;
	delay(delaytime);
	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}
