// declare variables and initiate some to calibrated values
int rotation_speed=150;
bool victim_LED;
bool victim_grabbed=0;
int time_tunnel=9300;
int time_triage=4500;
int trigPin;
int echoPin;
int slow_turn = 50;


// low-level functions
void move_forward(int duration, int velocity);
void move_backward(int duration, int velocity);
void crawl_left();
void crawl_right();
void crawl_forward();
void crawl_backward();
void rotate_right90();
void rotate_left90();
void grabber(bool command);
void ramp(bool command);
bool ultrasound();
int get_us();

// control functions
void tunnel_from_start();
void triage_from_cave();
void tunnel_from_triage();
void finish();
void reach_victim(int time_reach);
void choose_victim();

// initialize motors and servos
Adafruit_MotorShield AFMS;
Adafruit_DCMotor *myMotor1;
Adafruit_DCMotor *myMotor2;
Servo myservo_grabber;
Servo myservo_ramp;
