#include <ros.h>
#include <std_msgs/Int16.h>
#include <geometry_msgs/Twist.h>

#CODE HAS NOT BE TESTED NOR DEBUGGED
#CODE HAS NOT BE TESTED NOR DEBUGGED
#CODE HAS NOT BE TESTED NOR DEBUGGED

ros::NodeHandle nh;

#define ENC_IN_LEFT_A 2
#define ENC_IN_RIGHT_A 3
#define ENC_IN_LEFT_B 4
#define ENC_IN_RIGHT_B 11

boolean Direction_left = true;
boolean Direction_right = true;

std_msgs::Int16 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);

std_msgs::Int16 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

const int interval = 30;
long previousMillis = 0;
long currentMillis = 0;

const int enA = 9;
const int in1 = 5;
const int in2 = 6;
const int enB = 10; 
const int in3 = 7;
const int in4 = 8;

void right_wheel_tick() {
 int val = digitalRead(ENC_IN_RIGHT_B);
 Direction_right = (val == LOW) ? false : true;
 if (Direction_right) {
   right_wheel_tick_count.data++; 
 }
 else {
   right_wheel_tick_count.data--; 
 }
}

void left_wheel_tick() {
 int val = digitalRead(ENC_IN_LEFT_B);
 Direction_left = (val == LOW) ? true : false;
 if (Direction_left) {
   left_wheel_tick_count.data++; 
 }
 else {
   left_wheel_tick_count.data--; 
 }
}

ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &calc_pwm_values );

void setup() {
 pinMode(ENC_IN_LEFT_A , INPUT_PULLUP);
 pinMode(ENC_IN_LEFT_B , INPUT);
 pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
 pinMode(ENC_IN_RIGHT_B , INPUT);
 attachInterrupt(digitalPinToInterrupt(ENC_IN_LEFT_A), left_wheel_tick, RISING);
 attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_tick, RISING);
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
 digitalWrite(in1, LOW);
 digitalWrite(in2, LOW);
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW);
 analogWrite(enA, 0); 
 analogWrite(enB, 0);
 nh.getHardware()->setBaud(115200);
 nh.initNode();
 nh.advertise(rightPub);
 nh.advertise(leftPub);
 nh.subscribe(subCmdVel);
}

void loop() {
 nh.spinOnce();
 currentMillis = millis();
 if (currentMillis - previousMillis > interval) {
   previousMillis = currentMillis;
   leftPub.publish( &left_wheel_tick_count );
   rightPub.publish( &right_wheel_tick_count );
 }
}

#CODE HAS NOT BE TESTED NOR DEBUGGED
#CODE HAS NOT BE TESTED NOR DEBUGGED
#CODE HAS NOT BE TESTED NOR DEBUGGED
