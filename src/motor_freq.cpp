#include "../include/yehuh_mouse/Motor.h"

int main(int argc, char **argv)
{
 ros::init(argc, argv,"motor_freq");
 ros::NodeHandle nh;
 ros::Publisher	 pub_motor_raw;
 Motor m;
 pub_motor_raw = nh.advertise<yehuh_mouse::MotorFreqs>("motor_raw", 1000);
 ros::Rate rate(0.5);
 yehuh_mouse::MotorFreqs msg_mf;
 	while(ros::ok()){
		if(ros::Time::now().toSec() - m.last_time.toSec()>10.0){
			//m.set_raw_freq(0, 0);
			//m.using_cmd_vel = false;
			ROS_INFO("motor is shutting down");
			msg_mf.left = 0;
			msg_mf.right = 0;
			pub_motor_raw.publish(msg_mf);

		//	while(ros::ok()){
		//		ros::shutdown();
		//	}

			//return 0;
  			ros::spinOnce();
			rate.sleep();
  		}else{
			msg_mf.left = -100;
			msg_mf.right = 100;
			pub_motor_raw.publish(msg_mf);
	        	// m.set_raw_freq(-30,30);
			ROS_INFO("motor is acting");

  			ros::spinOnce();
			rate.sleep();
		}
	 }
 return 0;
}
