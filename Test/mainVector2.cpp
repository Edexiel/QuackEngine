#include "gtest/gtest.h"
#include "Maths/Vector2.hpp"

using namespace Maths;

TEST(Vector2, Addition)
{
  Vector2f v1{5.0f, 8.0f};
  Vector2f v2{5.0f, 2.0f};

  Vector2f res = v1 + v2;
  Vector2f goodRes{10.f,10.f};

  for(int i = 0; i < 2; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector2, Substaction)
{
  Vector2f v1{5.0f, 8.0f};
  Vector2f v2{5.0f, 2.0f};

  Vector2f res = v1 - v2;
  Vector2f goodRes{0.f,6.f};

  for(int i = 0; i < 2; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector2, MultiplicationByFloat)
{
  Vector2f v1{1.0f, 1.0f};


  Vector2f res = v1 * 10;
  Vector2f goodRes{10.f,10.f};

  for(int i = 0; i < 2; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector2, CrossProduct)
{
  Vector2f v1{2.0f, 4.0f};
  Vector2f v2{1.0f, 3.0f};

  float res = Vector2f::DotProduct(v1, v2);
  float goodRes = 14;

  EXPECT_EQ(res, goodRes);
}

TEST(Vector2, Length)
{
  Vector2f v1{5.0f, 5.0f};


  float res = v1.Length();
  float goodRes = 7.07f;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector2, SqrLength)
{
  Vector2f v1{5.0f, 5.0f};


  float res = v1.SqrLength();
  float goodRes = 50;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector2, Normalize)
{
  Vector2f v1{5.0f, 5.0f};
  Vector2f v2{5.0f, 5.0f};
  v2 = Vector2f::Normalized(v2);

  Vector2f res = v1.GetNormalized();
  v1.Normalize();
  Vector2f goodRes {0.707, 0.707};

  for(int i = 0; i < 2; i++)
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
