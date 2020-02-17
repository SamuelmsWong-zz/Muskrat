int get_us() //returns US distance reading
{
	long duration_us; // echo time value used to calc distance
	float distance_us; // return value
	
	// Clears the trigPin
	digitalWrite(trigPin, LOW);
	delayMicroseconds(10);
	
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	
	pinMode(echoPin, INPUT); // Sets the echoPin as an Input
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration_us = pulseIn(echoPin, HIGH);
	// Calculating the distance
	distance_us= duration_us*0.034/2;
	delay(20); // read every 20 milliseconds
	return distance_us;
}
bool ultrasound()
{
	if (get_us()<15) return true;
	else return false; 
}
