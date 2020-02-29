#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

int main (int argc, char **argv)
{
ros::init(argc, argv,"buzzer");
//ros::NodeHandle n;
ros::spin();
return 0;
}
