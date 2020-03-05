#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "yehuh_mouse/MotorFreqs.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#define QUEUE_SIZE 100
class Motor
{
 public:
 bool is_on;
 bool using_cmd_vel;
 ros::NodeHandle node_handle;
 ros::Subscriber sub_raw;
 ros::Subscriber sub_cmd_vel;
 ros::Time last_time;
 
  bool set_power(const bool motor_en)
  {
   std::ofstream motor_en_file;
   try
   {motor_en_file.open("/dev/rtmotoren0");}
   catch(...)
   {
    std::cout << "motor switch ero"<<std::endl;
    return false;
   }
   motor_en_file << motor_en<<std::endl;
   motor_en_file.close();
   return true;
  }
  
  void set_raw_freq(const int left_wheel, const int right_wheel)
  {
   if(!is_on)
   {
    std::cout<<"motor power is off"<<std::endl;
    return;
   }
    
   std::ofstream mt_file;
   mt_file.open("/dev/rtmotor_raw_l0");
   mt_file << left_wheel << std::endl;
   mt_file.close();
   mt_file.open("/dev/rtmotor_raw_r0");
   mt_file << right_wheel << std::endl;
   mt_file.close();
  }
  
  void callback_raw_massage(const yehuh_mouse::MotorFreqs freq_msg)
  {set_raw_freq(freq_msg.left, freq_msg.right);}
  
  void callback_cmd_vel(const geometry_msgs::Twist twist_msg)
  {
   int forward_hz = 80000.0*twist_msg.linear.x/(9*M_PI);
   int rot_hz = 400.0*twist_msg.angular.z/M_PI;
   set_raw_freq (forward_hz - rot_hz, forward_hz+rot_hz);
   using_cmd_vel =true;
   last_time = ros::Time::now();
  }

  Motor(const ros::NodeHandle nh)
  :node_handle(nh)
  {
   if(set_power(true)){is_on = true;}
   else{is_on = false;}
   sub_raw = node_handle.subscribe("motor_raw", QUEUE_SIZE,
              &Motor::callback_raw_massage,this);
   sub_cmd_vel = node_handle.subscribe("cmd_vel", QUEUE_SIZE,
               &Motor::callback_cmd_vel,this);
   last_time = ros::Time::now();
   using_cmd_vel = false;
  } 
  
  ~Motor(){}
  
};

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
