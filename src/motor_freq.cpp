#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "std_srvs/Trigger.h"
#include "yehuh_mouse/MotorFreqs.h"
#include "yehuh_mouse/TimedMotion.h"
#include "Motor.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define QUEUE_SIZE 100

int main(int argc, char **argv)
{
 ros::init(argc, argv,"motors");
 ros::NodeHandle nh;
 ros::Rate rate(10);
 Motor m(nh);
 while(ros::ok())
 {
  if(m.using_cmd_vel && ros::Time::now().toSec() - m.last_time.toSec()>1.0)
  {
   m.set_raw_freq(0,0);
   m.using_cmd_vel = false;
  }
  ros::spinOnce();
  rate.sleep();
 }
 return 0;
}
