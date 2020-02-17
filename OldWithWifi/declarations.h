// Network name and password
char ssid[] = "Muskrat";				// your network SSID (name)
char pass[] = "Submarine";		// your network password (use for WPA, or use as key for WEP)

#define DATAQUANTITY 12
#define CHARQUANTITY 15

float theta;					// angle of robot orientation to the horizontal
float phi;						// angle of victim-grabber line to the horizontal
float grabber_x;				// grabber coordinates
float grabber_y;
float robot_x;					// robot coordinates
float robot_y;
int victim[4][2];		 // victim coordinates
int i, minimum_grabber, minimum_robot, closest_victim;
float distance_robot, distance_grabber;
float vect_target_x, vect_target_y, vect_grabber_x, vect_grabber_y;
float turning_point1_x, turning_point1_y,turning_point2_x, turning_point2_y;  
float tunnel1_x, tunnel1_y, tunnel2_x, tunnel2_y;
float tan_theta, tan_phi;
float target_distance, target_angle;
int moving_speed;
float K1, K2, K3; // K1 for rotation, K2 for straight moment, K3 for straight movement through tunnel
bool length_flag = 0;
bool tunnel_flag = 0, turning_point_flag = 0;
bool turning_point_rotation_flag = 0;
int turning_time;
int coordinates[DATAQUANTITY] = {0};		// array of coordinates received via wi-fi
int forward_time;
int forward_speed=255; // ---------------------------------------exper
float length_robot=150;
int rotation_speed=150;
float angle;
int grabber_closer_speed=50;
int grabber_closer_time=1000;
int ramp_speed=100;
int ramp_time=1000;
float closest_victim_x;
float closest_victim_y;
float triage_x;
float triage_y;
float finish_x;
float finish_y;
int servoramp;
int servograbber;

// int keyIndex = 0;						// your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiServer server(23); // This is the specified port number for telnet communications


// uint16_t coordinates[DATAQUANTITY]; // (1, 1) for blue centre, (1, 1) for yellow centre, (1, 1) for each of the 4 green centres
uint8_t coordinatespointer = 0;
bool validcoordinates = false;

bool alreadyConnected = false; // whether or not the client was connected previously
bool acceptingdata = false; // needs to first see a start flag before accepting data
uint32_t databuffer = 0;
uint8_t databufferpointer = 0;
uint8_t charactercount = 0;
uint8_t thisChar;

// functions
void assign_coordinates();
void setup_wifi();
void wifi_loop();
bool wifi_step();
void requestUpdate(char* text1, float num1, char* text2, float num2, char* text3);
void printWifiStatus();
void turn(float angle, unsigned int duration);
void turn_180();
void rotation(float target_angle);
void move_forward(int forward_time);
void fine_tuning();
void operate_grabber(bool command);
void ramp(bool command);
void reach_triage();
void operate_grabber(bool command);
void operate_ramp(bool command);

char rottext[] = "rotating hello";
char fortext[] = "fowarding hello";
// initialize motors
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *myMotor1;
Adafruit_DCMotor *myMotor2;
//Adafruit_DCMotor *myMotor3;
//Adafruit_DCMotor *myMotor4;
Servo myservo_grabber;  // create servo object to control a servo
Servo myservo_ramp;  // create servo object to control a servo
