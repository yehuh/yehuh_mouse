#include "Motor.h"
#include <gtest/gtest.h>


TEST(MotorFixture, TestRawFreq)
{
 try
 {
  Motor m;
  m.set_raw_freq(50,-50);
  //while(ros::Time::now().toSec() - m.last_time.toSec() < 10.0){}
  ros::Duration(10.0).sleep();
  m.set_raw_freq(0,0);
 }
 catch(...)
 {FAIL() << "Raw Freg Apply Ero";}
}

TEST(MotorFixture, TestCmdVel)
{
 try
 {
  Motor m;
  ros::Publisher pub = m.node_handle.advertise<geometry_msgs::Twist>("cmd_vel", QUEUE_SIZE);
  geometry_msgs::Twist twi_msg;
  twi_msg.linear.x = 0.1414;
  twi_msg.angular.z = 1.57;
  pub.publish(twi_msg);
  while(ros::Time::now().toSec() - m.last_time.toSec()<10.0){}
  twi_msg.linear.x = 0;
  twi_msg.angular.z =0;
  pub.publish(twi_msg);
 }
 catch(...)
 {FAIL()<<"CmdVel Apply Ero";}
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 ros::init(argc, argv, "motor_test");
 ros::NodeHandle nh;
 return RUN_ALL_TESTS();
}
