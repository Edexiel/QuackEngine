//
// Created by a.figueiredo on 25/01/2021.
//

#ifndef QUACKENGINE_MATRIX4_HPP
#define QUACKENGINE_MATRIX4_HPP

struct Matrix4
{
  union
  {
    Vec4 v[4];
    float e[16];
    //float aa[4][4];
  };

  static Matrix4 Identity();
  static Matrix4 Scale(float s);
  static Matrix4 Scale(Vec3 v);
  static Matrix4 Translate(Vec3 v);
  static Matrix4 RotateX(float angle);
  static Matrix4 RotateY(float angle);
  static Matrix4 RotateZ(float angle);
  static Matrix4 Rotation(const Vector3 &rotation)
  static Matrix4 frustum(float left, float right, float bottom, float top, float znear, float zfar);
  static Matrix4 Perspective(float fov, float aspectRatio, float znear, float zfar);
  static Matrix4 OrthoMatrix(float left, float right, float bottom, float top, float near, float far);
};

inline Matrix4 Matrix4::Identity()
{
  return
    {
      1.f, 0.f, 0.f, 0.f,
      0.f, 1.f, 0.f, 0.f,
      0.f, 0.f, 1.f, 0.f,
      0.f, 0.f, 0.f, 1.f
    };
}


inline Matrix4 Matrix4::Scale(float s)
{
  return
    {
      s, 0.f, 0.f, 0.f,
      0.f, s, 0.f, 0.f,
      0.f, 0.f, s, 0.f,
      0.f, 0.f, 0.f, 1.f
    };
}

inline Matrix4 Matrix4::Scale(Vec3 v)
{
  return
    {
      v.x, 0.f, 0.f, 0.f,
      0.f, v.y, 0.f, 0.f,
      0.f, 0.f, v.z, 0.f,
      0.f, 0.f, 0.f, 1.f
    };
}

inline Matrix4 Matrix4::Translate(Vec3 v)
{
  return
    {
      1.f, 0.f, 0.f, v.x,
      0.f, 1.f, 0.f, v.y,
      0.f, 0.f, 1.f, v.z,
      0.f, 0.f, 0.f, 1.f
    };
}

inline Matrix4 Matrix4::RotateX(float angle)
{
  float c, s;
  c = cosf(angle);
  s = sinf(angle);

  return
    {
      1, 0, 0, 0,
      0, c, s, 0,
      0, -s, c, 0,
      0, 0, 0, 1
    };
}
inline Matrix4 Matrix4::RotateY(float angle)
{
  float c, s;
  c = cosf(angle);
  s = sinf(angle);

  return
    {
      c, 0, -s, 0,
      0, 1, 0, 0,
      s, 0, c, 0,
      0, 0, 0, 1
    };
}
inline Matrix4 Matrix4::RotateZ(float angle)
{
  return
    {
      c, s, 0, 0,
      -s, c, 0, 0,
      0, 0, 1, 0,
      0, 0, 0, 1
    };
}

inline Matrix4 Matrix4::Rotation(const Vec3 &rotation)
{
  return RotateY(rotation.y) * RotateX(rotation.x) * RotateZ(rotation.z);
}

inline Matrix4 Matrix4::CreateAxisRotationMatrix(const float angle, const Vector3 &axis)
{
  float tsin, tcos;
  tsin = sinf(angle);
  tcos = cosf(angle);

  return
    {
      (axis.x * axis.x + (1 - tcos) + tcos), axis.x * axis.y * (1 - tcos) + axis.z * tsin, axis.x * axis.z * (1 - tcos) - axis.y * tsin, 0,
      axis.x * axis.y * (1 - tcos) - axis.z * tsin, axis.y * axis.y + (1 - tcos) + tcos, axis.y * axis.z * (1 - tcos) + axis.x * tsin, 0,
      axis.x * axis.z * (1 - tcos) + axis.y * tsin, axis.y * axis.z + (1 - tcos) - axis.x * tsin, axis.z * axis.z * (1 - tcos) + tcos, 0,
      0, 0, 0, 1
    };
}

inline Matrix4 Matrix4::frustum(float left, float right, float bottom, float top, float znear, float zfar)
{
  float nn, rl, tb, fn;
  nn = 2.0f * znear;
  rl = right - left;
  tb = top - bottom;
  fn = zfar - znear;

  return
    {
      nn / rl, 0.f, 0.f, 0.f,
      0.f, nn / tb, 0.f, 0.f,
      (right + left) / rl, (top + bottom) / tb, -(zfar + znear) / fn, -1.0,
      0, 0, -(nn * zfar) / fn, 0.f
    };
}

inline Matrix4 Matrix4::Perspective(float fov, float aspectRatio, float znear, float zfar)
{
  float ymax, xmax;
  ymax = znear * tanf(fov * (float)(float)M_PI / 360.0f);
  xmax = ymax * aspectRatio;
  return frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}

inline Matrix4 Matrix4::OrthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
  return
    {
      2.f / (right - left), 0.f, 0.f, 0.f,
      0.f, 2.f / (top - bottom), 0.f, 0.f,
      0.f, 0.f, -2.f / (far - near), 0.f,
      -((right + left) / (right - left)), -((top + bottom) / (top - bottom)), -((far + near) / (far - near)), 1.f
    };
}


inline Matrix4 operator*(const Matrix4& a, const Matrix4& b)
{
  Matrix4 res = {};
  for (int c = 0; c < 4; ++c)
    for (int r = 0; r < 4; ++r)
      for (int k = 0; k < 4; ++k)
        res.v[r].e[c] += a.v[r].e[k] * b.v[k].e[c];
  return res;
}

inline Matrix4& operator*=(Matrix4& a, const Matrix4& b) { a = a * b; return a; }

#endif // QUACKENGINE_MATRIX4_HPP
