void setup_wifi()
{
	while (!Serial)
	{
		; // wait for serial port to connect. Needed for native USB port only
	}

	// check for the WiFi module:
	if (WiFi.status() == WL_NO_MODULE)
	{
		Serial.println("Communication with WiFi module failed!");
		// don't continue
		while (true);
	}

	String fv = WiFi.firmwareVersion();
	if (fv < WIFI_FIRMWARE_LATEST_VERSION)
	{
		Serial.println("Please upgrade the firmware");
	}

	// attempt to connect to Wifi network:
	while (status != WL_CONNECTED)
	{
		Serial.print("Attempting to connect to SSID: ");
		Serial.println(ssid);
		// Connect to WPA/WPA2 network. Change this line if using open or WEP network:
		status = WiFi.begin(ssid, pass);

		// wait 10 seconds for connection:
		Serial.print("Waiting 10 seconds");
		delay(10000);
	}

	// start the server:
	server.begin();
	// you're connected now, so print out the status:
	printWifiStatus();
}

void wifi_loop()
{
	
	Serial.print("wifi_loop");
	bool waiting = true;
	while (waiting) // wait until client detected. Laptop side already has timeout
	{
		waiting = !wifi_step();
	}
	digitalWrite(8, LOW);
	while (!waiting) // wait until no more client
	{
		waiting = !wifi_step();
	}
	Serial.print("finished reading for data");
}

bool wifi_step()
{
	// wait for a new client:
	WiFiClient client = server.available();
	// Serial.println("Got client");
	if (acceptingdata)
	{
		digitalWrite(9, HIGH);
	}
	else {
		digitalWrite(9, LOW);
	}
	if (client)
	{
		if (!alreadyConnected)
		{
			// clead out the input buffer:
			client.flush();
//			Serial.println("We have a new client");
			alreadyConnected = true;
		}

		if (client.available() > 0)
		{
			// read the bytes incoming from the client:
			thisChar = client.read();
			if (acceptingdata == false && thisChar == 255) // start flag is 255
			{
				// start reading
				acceptingdata = true; // accept data now
				coordinatespointer = 0; // starting adding data to the start of the list
				databuffer = 0; // temporary stroage of unformed 10 bit numbers
				databufferpointer = 0; // reset how many bits are in the databuffer
				charactercount = 0; // expecting 12 characters
				Serial.print("\n-----------------New Feed------------\n");
				thisChar = client.read(); // for some reason, the 255 get picked up twice???
//				thisChar = client.read(); // for some reason, the 255 get picked up twice???
				//				thisChar = client.read(); // for some reason, the 255 get picked up twice???
			}
			else if (acceptingdata)
			{
				charactercount += 1;
				databuffer <<= 8; // make space for next 8 bit char
				databuffer |= thisChar; // add next 8 bit char
				databufferpointer += 8; // point to HSB of temporary number
				if (databufferpointer >= 10)
				{
					coordinatesbuffer[coordinatespointer] = ((databuffer >> (databufferpointer - 10)) & 1023); // mask out 10 bit number
					coordinatespointer += 1; // start filling next piece of coordinate data
					databufferpointer -= 10; // point to HSB of temporary number
					if (coordinatespointer == 12) // all 12x10 bit coordinates received
					{
						acceptingdata = false; // stop taking data
						validcoordinates = true; // coordinates are valid
						dumpcoordinates();
						if (!locating_victim) // Allow big changes in victim x,y wheen looking for or moving a victim
						{
							if ( // Catch for bad data by checking for big changes in x and y components
								abs(coordinates[11] - coordinatesbuffer[11]) < 3 &&
								abs(coordinates[10] - coordinatesbuffer[10]) < 3 &&
								abs(coordinates[9] - coordinatesbuffer[9]) < 3 &&
								abs(coordinates[8] - coordinatesbuffer[8]) < 3 &&
								abs(coordinates[7] - coordinatesbuffer[7]) < 3 &&
								abs(coordinates[6] - coordinatesbuffer[6]) < 3 &&
								abs(coordinates[5] - coordinatesbuffer[5]) < 3 &&
								abs(coordinates[4] - coordinatesbuffer[4]) < 3
								)
								{
									for (int i = 0; i < DATAQUANTITY; i++) // update coordinates with collected data
									{
										coordinates[i] = coordinatesbuffer[i];
									}
								}
								else
								{
									requestUpdate("REPEAT:", 0, "REPEAT:", 0, "REPEAT hello");
									wifi_loop();
									assign_coordinates();
								}
						}
						else // if looking for victim, allow large variation in victim location
						{
								for (int i = 0; i < DATAQUANTITY; i++)
								{
									coordinates[i] = coordinatesbuffer[i];
								}
						}
						if (charactercount != 15)
						{
							Serial.println("Did not process 15 characters!!!");
						}
						for (int i = 0; i < 17; i++) // empty the queue
						{
							thisChar = client.read();
						}
						return false;
					}
				}
			}
			// echo the bytes back to the client:
			// server.write(thisChar);
		}
		return true;
	}
	else
	{
//		Serial.println("No client");
		return false;
	}
}

void requestUpdate(char* text1, float num1, char* text2, float num2, char* text3)
{
	// server.print(millis());
	server.write(text1);
	server.print(num1);
	server.write(text2);
	server.print(num2);
	server.write(text3);
//	Serial.write(text);
//	delay(1000);
}

void printWifiStatus()
{
	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print your board's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.print(rssi);
	Serial.println(" dBm");
}
