#include <iostream>
#include "gtest/gtest.h"

TEST(Bonsoir, CeciEstUnTest)
{
  EXPECT_EQ(1,1);
//  ASSERT_EQ(1,2);
}

TEST(Bonsoir, CeciEstUnAutreTest)
{
  EXPECT_EQ(1,2);
  EXPECT_EQ(1,1);
}

int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
