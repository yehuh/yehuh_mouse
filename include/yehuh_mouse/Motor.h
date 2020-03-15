#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int16.h"
#include "std_srvs/Trigger.h"
#include "yehuh_mouse/MotorFreqs.h"
#include "yehuh_mouse/TimedMotion.h"
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
 ros::ServiceServer srv_on;
 ros::ServiceServer srv_off;
 ros::ServiceServer srv_tm;
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
   is_on = motor_en;
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
  
  std_srvs::TriggerResponse onoff_response(const bool onoff)
  {
   std_srvs::TriggerResponse d;
   d.success = set_power(onoff);
   d.message = is_on?"ON":"OFF";
   return d;
  }

  bool callback_on(std_srvs::TriggerRequest& req, std_srvs::TriggerResponse& resp)
  {
   resp = onoff_response(true);
   return resp.success;
  }
  
  bool callback_off(std_srvs::TriggerRequest& req, std_srvs::TriggerResponse& resp)
  {
   resp = onoff_response(false);
   return resp.success;
  }
  
  bool callback_tm(yehuh_mouse::TimedMotion::Request& req, 
          yehuh_mouse::TimedMotion::Response& resp)
  {
   if(!is_on)
   {
    ROS_INFO("not enpowered");
    return false;
   }
   
   std::ofstream motor_file;
   motor_file.open("/dev/rtmotor0");
   motor_file << req.left_hz<<std::endl<< req.right_hz<<std::endl<< req.duration_ms;
   return true;
  } 
  
  Motor()
  {
   if(set_power(true)){is_on = true;}
   else{is_on = false;}
   sub_raw = node_handle.subscribe("motor_raw", QUEUE_SIZE,
              &Motor::callback_raw_massage,this);
   sub_cmd_vel = node_handle.subscribe("cmd_vel", QUEUE_SIZE,
               &Motor::callback_cmd_vel,this);   

   last_time = ros::Time::now();
   using_cmd_vel = false;
   srv_on = node_handle.advertiseService("motor_on", &Motor::callback_on, this);
   srv_off = node_handle.advertiseService("motor_off", &Motor::callback_off, this);
   
   srv_tm = node_handle.advertiseService("timed_motion", &Motor::callback_tm, this);
  } 
  
  ~Motor(){}
  
};
