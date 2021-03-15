#include <iostream>
#include "gtest/gtest.h"
#include "Maths/Matrix4.hpp"

using namespace Maths;

TEST(Matrix4, Addition)
{
  Matrix4 mat1 = Matrix4::Translate({0.f,0.f,1.f});
  Matrix4 mat2 = Matrix4::Scale(0.5f);

  Matrix4 result = mat1 + mat2;
  Matrix4 goodResult
      {
          1.5f,0,0,0,
          0,1.5f,0,0,
          0,0,1.5f,0,
          0,0,1,2
      };
  for (int i = 0; i < 16; i++)
  {
    EXPECT_EQ(result.e[i], goodResult.e[i]);
  }
}

TEST(Matrix4, Multiplication)
{
  Matrix4 mat1 = Matrix4::Translate({0.f,0.f,1.f});
  Matrix4 mat2 = Matrix4::Scale(0.5f);

  Matrix4 result = mat1 * mat2;
  Matrix4 goodResult
      {
          0.5f,0,0,0,
          0,0.5f,0,0,
          0,0,0.5f,0,
          0,0,1,1
      };
  for (int i = 0; i < 16; i++)
  {
    EXPECT_EQ(result.e[i], goodResult.e[i]);
  }
}

TEST(Matrix4, Scalaire)
{
  Matrix4 mat1 = Matrix4::Translate({0.f,0.f,1.f});

  Matrix4 result = mat1 * 10;
  Matrix4 goodResult
      {
          10.f,0,0,0,
          0,10.f,0,0,
          0,0,10.f,0,
          0,0,10.f,10.f
      };
  for (int i = 0; i < 16; i++)
  {
    EXPECT_EQ(result.e[i], goodResult.e[i]);
  }
}

int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
