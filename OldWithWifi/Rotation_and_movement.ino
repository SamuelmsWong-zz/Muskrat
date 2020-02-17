//#include <Adafruit_MotorShield.h>

void rotation(float angle)		//rotate for 1 second with a given speed and move forwards for 2 seconds with a gives speed
{
	Serial.print("rotating(");Serial.print(angle);Serial.print(")");
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors
	myMotor1->setSpeed(rotation_speed);
	myMotor2->setSpeed(rotation_speed);
	if (angle < 0) // ------------------------------------------check------------------
	{
		myMotor1->run(BACKWARD);
		myMotor2->run(FORWARD);
	}
	else
	{
		myMotor1->run(FORWARD);
		myMotor2->run(BACKWARD);
	}
	int ratio=150/rotation_speed;
	delay((int)abs(4300*ratio*angle/3.14));
	myMotor1->run(RELEASE); //stop motors
	myMotor2->run(RELEASE);
}

void move_forward(int duration, int velocity)
{
	
	Serial.print(" moving forwards(");Serial.print(duration);Serial.print(", ");Serial.print(velocity);Serial.print(")");
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors

	myMotor1->setSpeed(velocity);
	myMotor2->setSpeed(velocity);


//	myMotor1->run(BACKWARD);
//	myMotor2->run(BACKWARD);
	myMotor1->run(FORWARD);
	myMotor2->run(FORWARD);

	delay(duration);

	myMotor1->run(RELEASE);
	myMotor2->run(RELEASE);
}

// void crawl()
// {
// 	Serial.print("crawling forwards");
// 	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// 	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
// 	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors

// 	myMotor1->setSpeed(40);
// 	myMotor2->setSpeed(40);


// 	myMotor1->run(FORWARD);
// 	myMotor2->run(FORWARD);

// 	delay(3000);

// 	myMotor1->run(RELEASE);
// 	myMotor2->run(RELEASE);
// }

// void traverse_tunnel()
// {
	
// 	Serial.print("moving forwards");
// 	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// 	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
// 	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); //start motors

// 	myMotor1->setSpeed(forward_speed);
// 	myMotor2->setSpeed(forward_speed);


// 	myMotor1->run(FORWARD);
// 	myMotor2->run(FORWARD);

// 	unsigned long tunnel_timeout + 

// 	myMotor1->run(RELEASE);
// 	myMotor2->run(RELEASE);
// }
