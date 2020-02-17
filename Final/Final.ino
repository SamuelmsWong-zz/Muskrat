#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <math.h>
#include <SPI.h>
#include <Servo.h>


#include "declarations.h"

int table_number = 2;
// initialise all the global variables
void initialise()
{
	// Initialize serial and wait for port to open:
	Serial.begin(9600);
	Adafruit_MotorShield AFMS = Adafruit_MotorShield();
	Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1); // Left wheel
	Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2); // Right wheel
	AFMS.begin();

	pinMode(7, OUTPUT);		 // set the LED pin mode
  myservo_grabber.attach(9);  // attaches the servo on pin 10 to the servo object
  myservo_ramp.attach(10);  // attaches the servo on pin 9 to the servo object
  
  trigPin = 5; // ultrasound pins
  echoPin = 6; // ultrasound pins
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
}


void setup()
{
	initialise();
}
// flags to show sub-mission completion
bool start_flag=0;
bool time_flag=0;
unsigned long time_start=millis(); // mission timer

	
void loop()
{


	if (start_flag==0)
	{
		tunnel_from_start();
		start_flag=1;
	}
	else
	{ // Make an attempt to get a victim
		choose_victim();
		triage_from_cave();
		// try again if there is more than a minute left, up to 2 times
		for (int i=0;i<2;i++)
		{
     if (millis()>4000*60+time_start)
			{
				time_flag=1;
			}
			if (time_flag==1) break;
			tunnel_from_triage();
			choose_victim();
			triage_from_cave();
		}
		// Make a final attenpt if more than a minute left
		if (time_flag==0)
		{
			tunnel_from_triage();
			choose_victim();
			finish();	
		}
		else finish();
	}

	// The following code is the one actually run during the competition,
	// as we prioritised getting to the finish area

	// tunnel_from_start();
	// choose_victim();
	// triage_from_cave();
	// finish();
}
