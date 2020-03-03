#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include "yehuh_mouse/LightSensorValues.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>

int main (int argc, char **argv)
{
 ros::init(argc, argv, "light_sensor");
 ros::NodeHandle n;
 ros::Publisher value_trans =
    n.advertise<yehuh_mouse::LightSensorValues>("SensorValues",1000);
 ros::Rate loop_rate(1);
 std::vector<std::string> str_vec;

 while(ros::ok())
 {
  std::fstream light_file;
  std::string str;  
  light_file.open("/dev/rtlightsensor0");
  
   getline(light_file, str);
   //std::cout<<str<<std::endl;
   //std::cout<<"str size"<<str.size()<<std::endl;
   
   int space_pos = 0;
   for(int data_pos=0;data_pos<str.size();data_pos++)
   {
    if(str[data_pos]==' ')
    {
     //std::cout<<"space_pos:"<<space_pos<<std::endl;
     str_vec.push_back(str.substr(space_pos,data_pos - space_pos));
     //std::cout<<"str size: "<<str_vec.size()<<std::endl;

     //std::cout<<"value:"<<str.substr(space_pos,data_pos-space_pos)<<"fin"<<std::endl;
     space_pos = data_pos+1;
    }
   }
   str_vec.push_back(str.substr(space_pos, str.size()));
   //std::cout<<"str size: "<<str_vec.size()<<std::endl;
   //std::cout<<"value: "<<str_vec.back()<<std::endl;
 
  yehuh_mouse::LightSensorValues lsv;
  lsv.right_forward = std::atoi(str_vec[0].c_str());
  lsv.right_side = std::atoi(str_vec[1].c_str());
  lsv.left_side = std::atoi(str_vec[2].c_str());
  lsv.left_forward = std::atoi(str_vec[3].c_str());
  str_vec.clear();
  value_trans.publish(lsv);
  ros::spinOnce();
  loop_rate.sleep();
 }
 return 0;
}
