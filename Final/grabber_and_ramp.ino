void grabber(bool command)
{
	Servo myservo_grabber;	// create servo object to control a servo
	myservo_grabber.attach(9);	// attaches the servo on pin 10 to the servo object
	if (command==0)				//open grabber
	{
		myservo_grabber.write(150);
		delay(1000); // allow time for servo to settle
	}
	if (command==1)							//close grabber
	{
		myservo_grabber.write(40);
		delay(1000); // allow time for servo to settle
	}
}

void ramp(bool command)
{
	Servo myservo_ramp;	// create servo object to control a servo
	myservo_ramp.attach(10);	// attaches the servo on pin 9 to the servo object

	if (command==0)					// bring up
	{
		myservo_ramp.write(110);
		delay(1000); // allow time for servo to settle
	}
	if (command==1)					// put down
	{
		myservo_ramp.write(40);
		delay(1000); // allow time for servo to settle
	}
}
