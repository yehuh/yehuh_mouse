#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <sstream>

void int16Callback(const std_msgs::Int16::ConstPtr& msg)
{
 ROS_INFO("I heared: %ld",(int)msg->data);
}

int main (int argc, char **argv)
{
ros::init(argc, argv,"buzzer");
ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("chatter", 1000, int16Callback);
ros::spin();
return 0;
}
