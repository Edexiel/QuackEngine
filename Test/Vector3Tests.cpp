#include "gtest/gtest.h"
#include "Maths/Vector3.hpp"

using namespace Maths;

TEST(Vector3, Addition)
{
  Vector3f v1{5.0f, 8.0f, 5.f};
  Vector3f v2{5.0f, 2.0f, 5.f};

  Vector3f res = v1 + v2;
  Vector3f goodRes{10.f,10.f, 5.0f};

  for(int i = 0; i < 2; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector3, Substaction)
{
  Vector3f v1{5.0f, 8.0f, 2.0f};
  Vector3f v2{5.0f, 2.0f,2.0f};

  Vector3f res = v1 - v2;
  Vector3f goodRes{0.f,6.f, 0.f};

  for(int i = 0; i < 3; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector3, MultiplicationByFloat)
{
  Vector3f v1{1.0f, 1.0f, 1.0f};


  Vector3f res = v1 * 10;
  Vector3f goodRes{10.f,10.f, 10.f};

  for(int i = 0; i < 3; i++)
    EXPECT_EQ(res.e[i], goodRes.e[i]);
}

TEST(Vector3, DotProduct)
{
  Vector3f v1{2.0f, 4.0f,2.0f};
  Vector3f v2{1.0f, 3.0f,2.0f};

  float res = Vector3f::DotProduct(v1, v2);
  float goodRes = 18;

  EXPECT_EQ(res, goodRes);
}

TEST(Vector3, CrossProduct)
{
  Vector3f v1{2.0f, 4.0f,2.0f};
  Vector3f v2{1.0f, 3.0f,2.0f};

  Vector3f res = Vector3f::CrossProduct(v1, v2);
  Vector3f goodRes{2.0f, -2.0f, 2.0f};

  for (int i = 0; i < 3; i++)
    EXPECT_NEAR(res.e[i], goodRes.e[i], 0.01f);

}

TEST(Vector3, Length)
{
  Vector3f v1{5.0f, 5.0f, 5.0f};


  float res = v1.Length();
  float goodRes = 8.66f;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector3, SqrLength)
{
  Vector3f v1{5.0f, 5.0f,5.0f};


  float res = v1.SqrLength();
  float goodRes = 75;

  EXPECT_NEAR(res, goodRes,0.01);
}

TEST(Vector3, Normalize)
{
  Vector3f v1{5.0f, 5.0f,5.0f};
  Vector3f v2{5.0f, 5.0f,5.0f};
  Vector3f::Normalized(v2);

  Vector3f res = v1.GetNormalized();
  v1.Normalize();
  Vector3f goodRes {0.577, 0.577, 0.577};

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
