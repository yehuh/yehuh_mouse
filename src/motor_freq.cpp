#include "Motor.h"

int main(int argc, char **argv)
{
 ros::init(argc, argv,"motors");
 ros::Rate rate(10);
 Motor m;
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
