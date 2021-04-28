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

TEST(Matrix4, MultiplicationWithVector4)
{
  Matrix4 mat1 = Matrix4::Translate({0.f,0.f,1.f});
  Vector4f vec{2,5,4,1};

  Vector4f result = mat1 * vec;
  Vector4f goodResult{2,5,4,5};

  for (int i = 0; i < 4; i++)
  {
    EXPECT_EQ(result.e[i], goodResult.e[i]);
  }
}

TEST(Matrix4, Transpose)
{
  Matrix4 mat4
      {
          0,2,3,2,
          9,12,15,46,
          0,0,0,2,
          7,8,5,1
      };

  Matrix4 res = mat4.GetTranspose();
  Matrix4 goodRes
      {
          0,9,0,7,
          2,12,0,8,
          3,15,0,5,
          2,46,2,1
      };
  for (int i = 0; i < 16; i++)
  {
    EXPECT_EQ(res.e[i], goodRes.e[i]);
  }
}

TEST(Matrix4, Determinant)
{
    Matrix4 mat
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        10,2,3,1
    };
    float res = mat.GetDeterminant();
    EXPECT_EQ(res, 1);
}

TEST(Matrix4, Invert)
{
    Matrix4 mat
    {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            10, 2, 3, 1
    };

    Matrix4 goodRes
    {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        -10, -2, -3, 1
    };
    Matrix4 res = mat.GetInvert();
    for (int i = 0; i < 16; i++)
    {
        EXPECT_EQ(res.e[i], goodRes.e[i]);
    }
}