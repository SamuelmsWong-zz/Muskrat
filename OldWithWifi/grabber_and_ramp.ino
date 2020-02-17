//#include <Adafruit_MotorShield.h>
#include <Servo.h>

void operate_grabber(bool command)
{
//  Servo myservo_grabber;  // create servo object to control a servo
//  myservo_grabber.attach(9);  // attaches the servo on pin 10 to the servo object    //which pin????
  
 
  
  if (command==0) // close
  {
  		Serial.print("\nclose grabber");
//  	for (int i=0;i<90;i+=10)
//  	{
//    	myservo_grabber.write(i);              // tell servo to go to position in variable 'pos'
//    	delay(5);                       // waits 15ms for the servo to reach the position
//  	}
    myservo_grabber.write(150);
    delay(200);
  }
  if (command==1) // open
  {
  		Serial.print("\nopen grabber");
//  	for (int i=90;i>0;i-=10)
//  	{
//    	myservo_grabber.write(i);              // tell servo to go to position in variable 'pos'
//    	delay(5);                       // waits 15ms for the servo to reach the position
//  	}
    myservo_grabber.write(0);
    delay(200);
  }
  
  
}

void operate_ramp(bool command)
{
//  Servo myservo_ramp;  // create servo object to control a servo
//  myservo_ramp.attach(9);  // attaches the servo on pin 9 to the servo object    //which pin????
  
 
  
  if (command==0) // up
  {
  	Serial.print("\nramp up");
//    for (int i=110;i>30;i--)
//  	{
//    	myservo_ramp.write(i);              // tell servo to go to position in variable 'pos'
//    	delay(20);                       // waits 15ms for the servo to reach the position
//  	}                   // waits 15ms for the servo to reach the position
    myservo_ramp.write(110);
    delay(200);
  }
  if (command==1) // down
  {
  	Serial.print("\nramp down");
//    for (int i=30;i<110;i++)
//  	{
//    	myservo_ramp.write(i);              // tell servo to go to position in variable 'pos'
//    	delay(20);                       // waits 15ms for the servo to reach the position
//  	}                     // waits 15ms for the servo to reach the position
    myservo_ramp.write(30);
    delay(200);
  }
}
