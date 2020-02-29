//#include "foo/foo.h"
#include <gtest/gtest.h>

TEST(TestSuite, testCase1)
{
  // <test things here, calling EXPECT_* and/or ASSERT_* macros as needed>
}

int main(int argc, char **argv){
     testing::InitGoogleTest(&argc, argv);
     //ros::init(argc, argv, "tester");
     //ros::NodeHandle nh;
     return RUN_ALL_TESTS();
   }
