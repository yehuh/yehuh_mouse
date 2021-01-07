#include "../include/yehuh_mouse/Motor.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(MotorFixture, TestCmdVel){
	Motor m;
	ros::NodeHandle nh;
  	ros::Rate rate(0.5);
	ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", QUEUE_SIZE);
	ros::Publisher raw_motor_pub = 
		nh.advertise<yehuh_mouse::MotorFreqs>("motor_raw", QUEUE_SIZE);
   	geometry_msgs::Twist twi_msg;
	yehuh_mouse::MotorFreqs msg_mf;
	msg_mf.left = 0;
	msg_mf.right = 0;
	int rev_cnt =0;
	while(ros::ok()){
		if(rev_cnt>3){
			rev_cnt++;
			ROS_INFO("motor is shutting down");
		  	twi_msg.linear.x =   0.0000;
			twi_msg.angular.z =  0.0000;
			pub.publish(twi_msg);

			if(rev_cnt<8){
				ros::spinOnce();
				rate.sleep();
			}else{
				//SUCCEED();
				ros::shutdown();
			}
		}else{
			rev_cnt++;
		  	twi_msg.angular.z = -3.14;
			twi_msg.linear.x =   0.0000;
		  	pub.publish(twi_msg);
			ros::spinOnce();
			rate.sleep();
		}

	}
	EXPECT_EQ(2, 1+1);
}

TEST(MotorFixture, TestTimedMotion)
{/*
 try
 {
  Motor m;
 // ros::Rate rate(0.3);
  ros::ServiceClient clt = m.node_handle.serviceClient<yehuh_mouse::TimedMotion>("timed_motion");
  int spin_count = 0;
 // while(ros::ok())
 // {
   yehuh_mouse::TimedMotion tm_srv;
   spin_count++;
   if(spin_count < 2)
   {
    tm_srv.request.left_hz =  300;
    tm_srv.request.right_hz = -300;
    tm_srv.request.duration_ms = 20000;
    clt.call(tm_srv);
   // {ROS_INFO("Sucess");}
   // else
   // {ROS_ERROR("Time Motion Service Error %c\n",' ');}
   // ros::spinOnce();
   // rate.sleep();
   }
   /*else
   {
    twi_msg.linear.x =   0.0000;
    twi_msg.angular.z =  0.0000;
    pub.publish(twi_msg);
   
    ros::spinOnce();
    rate.sleep();
    if(spin_count> 2) break;
   }*/
 // }
/*
 }
 catch(...)
 {FAIL()<<"CmdVel Apply Ero";}
 */
	EXPECT_EQ(2, 1+1);
}

/*TEST(MotorFixture, TestRawFreq)
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
}*/

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 ros::init(argc, argv, "motor_test");
 // ros::NodeHandle nh;
 return RUN_ALL_TESTS();
}
