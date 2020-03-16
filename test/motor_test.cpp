#include "../include/yehuh_mouse/Motor.h"
#include <gtest/gtest.h>

TEST(MotorFixture, TestCmdVel)
{
 try
 {
  Motor m;
  ros::Rate rate(0.3);
  ros::Publisher pub = m.node_handle.advertise<geometry_msgs::Twist>("cmd_vel", QUEUE_SIZE);
  int spin_count = 0;
  while(ros::ok())
  {
   geometry_msgs::Twist twi_msg;
   spin_count++;
   if(spin_count < 2)
   {
    twi_msg.linear.x =   0.0000000;
    twi_msg.angular.z =  1.57;
    pub.publish(twi_msg);
    ros::spinOnce();
    rate.sleep();
   }
   else
   {
    twi_msg.linear.x =   0.0000;
    twi_msg.angular.z =  0.0000;
    pub.publish(twi_msg);
   
    ros::spinOnce();
    rate.sleep();
    if(spin_count> 2) break;
   }
  }
 }
 catch(...)
 {FAIL()<<"CmdVel Apply Ero";}
}

TEST(MotorFixture, TestRawFreq)
{
 try
 {
  Motor m;
  m.set_raw_freq(250,-250);
  ros::Duration(5.0).sleep();
  m.set_raw_freq(0,0);
 }
 catch(...)
 {FAIL() << "Raw Freg Apply Ero";}
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 ros::init(argc, argv, "motor_test");
 ros::NodeHandle nh;
 return RUN_ALL_TESTS();
}
