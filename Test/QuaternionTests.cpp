#include "gtest/gtest.h"
#include "Maths/Quaternion.hpp"

using namespace Maths;

TEST(Quaternion, Addition)
{
  Quaternion q1{2.0f,4.0f,5.0f,8.0f};
  Quaternion q2{2.0f,4.0f,5.0f,8.0f};
  Quaternion res = q1 + q2;
  Quaternion goodRes{4.0f,8.0f,10.0f,16.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i],goodRes.e[i]);
}

TEST(Quaternion, Substraction)
{
  Quaternion q1{2.0f,4.0f,5.0f,8.0f};
  Quaternion q2{2.0f,4.0f,5.0f,8.0f};
  Quaternion res = q1 - q2;
  Quaternion goodRes{0.0f,0.0f,0.0f,0.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i],goodRes.e[i]);
}

TEST(Quaternion, Multiplication)
{
  Quaternion q1{2.0f,4.0f,5.0f,8.0f};
  Quaternion q2{2.0f,4.0f,5.0f,8.0f};
  Quaternion res = q1 * q2;
  Quaternion goodRes{-101.0f, 16.0f, 20.0f, 32.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i],goodRes.e[i]);
}

TEST(Quaternion, MultiplicationByVector)
{
  Quaternion q{.5f,5.0f,4.0f,8.0f};
  q.Normalize();
  Vector3f   v {2.0f,4.0f,5.0f};
  Vector3f res = q * v;

  Vector3f goodRes{4.16f, 0.95f, 5.17f};

  for(int i = 0; i < 3; i++)
    EXPECT_NEAR(res.e[i],goodRes.e[i], 0.01f);
}

TEST(Quaternion, MultiplicationByScalar)
{
  Quaternion q1{1.0f,1.0f,1.0f,1.0f};
  Quaternion res = q1 * 10.0f;
  Quaternion goodRes{10.0f, 10.0f, 10.0f, 10.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i],goodRes.e[i]);
}

TEST(Quaternion, DivisionByScalar)
{
  Quaternion q1{10.0f,10.0f,10.0f,10.0f};
  Quaternion res = q1 / 2.0f;
  Quaternion goodRes{5.0f, 5.0f, 5.0f, 5.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i],goodRes.e[i]);
}

TEST(Quaternion, Normalize)
{
  Quaternion q1{2.0f,4.0f,5.0f,8.0f};
  Quaternion q2{2.0f,4.0f,5.0f,8.0f};
  Quaternion::Normalized(q2);

  Quaternion res = q1.GetNormalized();
  q1.Normalize();
  Quaternion goodRes {2.0f/10.44, 4.0f/10.44, 5.0f/10.44,8.0f/10.44};

  for(int i = 0; i < 4; i++)
  {
    EXPECT_NEAR(res.e[i], goodRes.e[i], 0.01);
    EXPECT_NEAR(q1.e[i], goodRes.e[i], 0.01);
    EXPECT_NEAR(q2.e[i], goodRes.e[i], 0.01);
  }
}

TEST(Quaternion, Magnitude)
{
  Quaternion q{2.0f,4.0f,5.0f,8.0f};

  float res = q.GetMagnitude();
  float goodRes = 10.44f;

  EXPECT_NEAR(res, goodRes, 0.01);
}

TEST(Quaternion, DotProduct)
{
  Quaternion q1{2.0f, 4.0f,2.0f,0.1f};
  Quaternion q2{1.0f, 3.0f,2.0f,6.f};

  float res = Quaternion::DotProduct(q1, q2);

  float goodRes = 18.6f;

  EXPECT_NEAR(res, goodRes, 0.01);
}

TEST(Quaternion, QuaternionToMatrix)
{
  Quaternion q({1.0f,0.0f,0.0f}, 3.14/3.f);
  q.Normalize();
  Matrix4 mat = q.QuaternionToMatrix();
  Matrix4 goodRes = Matrix4::RotateX(3.14/3.f);
  for (int i = 0; i < 16; i++)
    EXPECT_NEAR(mat.e[i], goodRes.e[i], 0.01);
}

int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
