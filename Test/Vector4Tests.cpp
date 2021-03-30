#include "gtest/gtest.h"
#include "Maths/Vector4.hpp"

using namespace Maths;

TEST(Vector4, Addition)
{
  Vector4f v1{5.0f, 8.0f, 5.f, 1.0f};
  Vector4f v2{5.0f, 2.0f, 5.f, 1.0f};

  Vector4f res = v1 + v2;
  Vector4f goodRes{10.f,10.f, 10.0f, 2.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector4, Substaction)
{
  Vector4f v1{5.0f, 8.0f, 2.0f,1.0f};
  Vector4f v2{5.0f, 2.0f,2.0f, 1.0f};

  Vector4f res = v1 - v2;
  Vector4f goodRes{0.f,6.f, 0.0f,0.0f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector4, MultiplicationByFloat)
{
  Vector4f v1{1.0f, 1.0f, 1.0f, 1.0f};


  Vector4f res = v1 * 10;
  Vector4f goodRes{10.f,10.f, 10.f, 10.f};

  for(int i = 0; i < 4; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector4, DotProduct)
{
  Vector4f v1{2.0f, 4.0f,2.0f,0.1f};
  Vector4f v2{1.0f, 3.0f,2.0f,6.f};

  float res = Vector4f::DotProduct(v1, v2);
  float goodRes = 18.6;

  EXPECT_NEAR(res, goodRes,0.01);
}


TEST(Vector4, Length)
{
  Vector4f v1{5.0f, 5.0f, 5.0f, 5.0f};


  float res = v1.Length();
  float goodRes = 10.0f;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector4, SqrLength)
{
  Vector4f v1{5.0f, 5.0f,5.0f ,5.0f};


  float res = v1.SqrLength();
  float goodRes = 100.0f;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector4, Homogenize)
{
  Vector4f v1{5.0f, 5.0f,5.0f, 0.25f};
  Vector4f v2{5.0f, 5.0f,5.0f, 0.25f};
  Vector4f::Homogenized(v2);

  Vector3f res = v1.GetHomogenized();
  v1.Homogenize();

  Vector4f goodRes {20.0f, 20.0f, 20.0f, 0.25f};

  for(int i = 0; i < 3; i++)
  {
    EXPECT_NEAR(res.e[i], goodRes.e[i], 0.01);
    EXPECT_NEAR(v1.e[i], goodRes.e[i], 0.01);
    EXPECT_NEAR(v2.e[i], goodRes.e[i], 0.01);
  }
}



int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
