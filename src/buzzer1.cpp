#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <sstream>
#include <fstream>
#include <iostream>
void int16Callback(const std_msgs::Int16::ConstPtr& msg)
{
 ROS_INFO("I heared: %ld",(int)msg->data);
 int freq = msg->data;
 std::ofstream buzz_file;
 buzz_file.open("/dev/rtbuzzer0");
 buzz_file << freq << std::endl;
 buzz_file.close(); 
}

int main (int argc, char **argv)
{
ros::init(argc, argv,"buzzer");
ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("chatter", 1000, int16Callback);
ros::spin();
return 0;
}
