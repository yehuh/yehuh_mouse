#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

void callback(const std_msgs::String::ConstPtr& msg)
{
 ROS_INFO("I heared: [%s]",msg->data.c_str());
}

int main (int argc, char **argv)
{
ros::init(argc, argv,"buzzer");
ros::NodeHandle n;
ros::Subscriber sub = n.subscribe("chatter", 1000, callback);
ros::spin();
return 0;
}
