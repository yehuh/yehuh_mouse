#include "Motor.h"
#include <gtest/gtest.h>

class MotorFixture
:public ::testing::Test
{
  MotorTester(){}
}

TEST_F(MotorFixture, TestAdder)
{
 
}

int main(int argc, char **argv)
{
 testing::InitGoogleTest(&argc, argv);
 ros::init(argc, argv, "motor_tester");
 ros::NodeHandle nh;
 return RUN_ALL_TESTS();
}
