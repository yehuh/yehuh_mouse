#include "../include/yehuh_mouse/Motor.h"

int main(int argc, char **argv)
{
 ros::init(argc, argv,"motors");
 //ros::NodeHandle nh;
 Motor m;
 ros::Rate rate(10);

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
