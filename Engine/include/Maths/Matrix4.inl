inline Matrix4 Matrix4::Identity()
{
    Matrix4 mat;

    mat.e[0] = 1;
    mat.e[5] = 1;
    mat.e[10] = 1;
    mat.e[15] = 1;

    return mat;
}


inline Matrix4 Matrix4::Scale(float s)
{
    Matrix4 mat;
    mat.e[0] = s;
    mat.e[5] = s;
    mat.e[10] = s;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::Scale(const Maths::Vector3f &v)
{
    Matrix4 mat;
    mat.e[0] = v.x;
    mat.e[5] = v.y;
    mat.e[10] = v.z;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::Translate(const Maths::Vector3f &v)
{
    Matrix4 mat;
    mat.e[12] = v.x;
    mat.e[13] = v.y;
    mat.e[14] = v.z;

    mat.e[0] = 1;
    mat.e[5] = 1;
    mat.e[10] = 1;
    mat.e[15] = 1;

    return mat;
}

inline Matrix4 Matrix4::RotateX(float angle)
{
    Matrix4 rotX;
    rotX.e[0] = 1;
    rotX.e[5] = cosf(angle);
    rotX.e[9] = -sinf(angle);
    rotX.e[6] = sinf(angle);
    rotX.e[10] = cosf(angle);
    rotX.e[15] = 1;

    return rotX;
}

inline Matrix4 Matrix4::RotateY(float angle)
{
    Matrix4 rotY;
    rotY.e[0] = cosf(angle);
    rotY.e[8] = sinf(angle);
    rotY.e[5] = 1;
    rotY.e[2] = -sinf(angle);
    rotY.e[10] = cosf(angle);
    rotY.e[15] = 1;

    return rotY;
}

inline Matrix4 Matrix4::RotateZ(float angle)
{
    Matrix4 rotZ;
    rotZ.e[0] = cosf(angle);
    rotZ.e[4] = -sinf(angle);
    rotZ.e[1] = sinf(angle);
    rotZ.e[5] = cosf(angle);
    rotZ.e[10] = 1;
    rotZ.e[15] = 1;

    return rotZ;
}

inline Matrix4 Matrix4::Rotation(const Vector3f &rotation)
{
    return RotateY(rotation.y) * RotateX(rotation.x) * RotateZ(rotation.z);
}

inline Matrix4 Matrix4::AxisRotation(const float angle, const Vector3f &axis)
{
    Matrix4 first;

    first.e[0] = axis.x * axis.x;
    first.e[1] = axis.y * axis.x;
    first.e[2] = axis.z * axis.x;

    first.e[4] = axis.x * axis.y;
    first.e[5] = axis.y * axis.y;
    first.e[6] = axis.z * axis.y;

    first.e[8] = axis.x * axis.z;
    first.e[9] = axis.y * axis.z;
    first.e[10] = axis.z * axis.z;

    first.e[15] = 1;

    first = first * (1 - cosf(angle));

    Matrix4 second = Identity() * cosf(angle);

    Matrix4 third;

    third.e[1] = axis.z;
    third.e[2] = -axis.y;
    third.e[4] = -axis.z;
    third.e[6] = axis.x;
    third.e[8] = axis.y;
    third.e[9] = -axis.x;

    third = third * sinf(angle);

    return first + second + third;
}

inline Matrix4
Matrix4::Perspective(const int &width, const int &height, float near, float far, float fov)
{
    Matrix4 projection;
    float const a = 1.f / tanf(fov / 2.f);
    float const aspect = (float) width / height;

    projection.e[0] = a / aspect;

    projection.e[5] = a;

    projection.e[10] = -((far + near) / (far - near));
    projection.e[11] = -1.f;

    projection.e[14] = -((2.f * far * near) / (far - near));

    return projection;
}

inline Matrix4 Matrix4::OrthoMatrix(const int &width, const int &height, float near, float far)
{
    Matrix4 ortho;

    ortho.e[0] = (float) height / width;
    ortho.e[5] = 1;
    ortho.e[10] = -2 / (far - near);

    ortho.e[12] = 0;
    ortho.e[13] = 0;
    ortho.e[14] = -(far + near) / (far - near);
    ortho.e[15] = 1;

    return ortho;
}

inline Matrix4 Matrix4::ViewportMatrix(const int &x, const int &y, const int &width, const int &height)
{
    Matrix4 view;

    view.e[0] = (float) width / 2;
    view.e[5] = (float) height / 2;

    view.e[12] = x + (float) width / 2;
    view.e[13] = y + (float) height / 2;

    view.e[10] = 1;

    view.e[15] = 1;

    return view;
}

inline Matrix4 Matrix4::GetTranspose() const
{
    return {
            v[0].e[0], v[1].e[0], v[2].e[0], v[3].e[0],
            v[0].e[1], v[1].e[1], v[2].e[1], v[3].e[1],
            v[0].e[2], v[1].e[2], v[2].e[2], v[3].e[2],
            v[0].e[3], v[1].e[3], v[2].e[3], v[3].e[3],
    };
}

inline float Matrix4::GetDeterminant() const
{
    float a00 = e[0], a01 = e[1], a02 = e[2], a03 = e[3];
    float a10 = e[4], a11 = e[5], a12 = e[6], a13 = e[7];
    float a20 = e[8], a21 = e[9], a22 = e[10], a23 = e[11];
    float a30 = e[12], a31 = e[13], a32 = e[14], a33 = e[15];

    float result = a30 * a21 * a12 * a03 - a20 * a31 * a12 * a03 - a30 * a11 * a22 * a03 + a10 * a31 * a22 * a03 +
                   a20 * a11 * a32 * a03 - a10 * a21 * a32 * a03 - a30 * a21 * a02 * a13 + a20 * a31 * a02 * a13 +
                   a30 * a01 * a22 * a13 - a00 * a31 * a22 * a13 - a20 * a01 * a32 * a13 + a00 * a21 * a32 * a13 +
                   a30 * a11 * a02 * a23 - a10 * a31 * a02 * a23 - a30 * a01 * a12 * a23 + a00 * a31 * a12 * a23 +
                   a10 * a01 * a32 * a23 - a00 * a11 * a32 * a23 - a20 * a11 * a02 * a33 + a10 * a21 * a02 * a33 +
                   a20 * a01 * a12 * a33 - a00 * a21 * a12 * a33 - a10 * a01 * a22 * a33 + a00 * a11 * a22 * a33;

    return result;
}

inline Matrix4 Matrix4::GetInvert() const
{
    Matrix4 result = {0};

    float a00 = e[0], a01 = e[1], a02 = e[2], a03 = e[3];
    float a10 = e[4], a11 = e[5], a12 = e[6], a13 = e[7];
    float a20 = e[8], a21 = e[9], a22 = e[10], a23 = e[11];
    float a30 = e[12], a31 = e[13], a32 = e[14], a33 = e[15];

    float b00 = a00 * a11 - a01 * a10;
    float b01 = a00 * a12 - a02 * a10;
    float b02 = a00 * a13 - a03 * a10;
    float b03 = a01 * a12 - a02 * a11;
    float b04 = a01 * a13 - a03 * a11;
    float b05 = a02 * a13 - a03 * a12;
    float b06 = a20 * a31 - a21 * a30;
    float b07 = a20 * a32 - a22 * a30;
    float b08 = a20 * a33 - a23 * a30;
    float b09 = a21 * a32 - a22 * a31;
    float b10 = a21 * a33 - a23 * a31;
    float b11 = a22 * a33 - a23 * a32;

    float invDet = 1.0f / (b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06);

    result.e[0] = (a11 * b11 - a12 * b10 + a13 * b09) * invDet;
    result.e[1] = (-a01 * b11 + a02 * b10 - a03 * b09) * invDet;
    result.e[2] = (a31 * b05 - a32 * b04 + a33 * b03) * invDet;
    result.e[3] = (-a21 * b05 + a22 * b04 - a23 * b03) * invDet;
    result.e[4] = (-a10 * b11 + a12 * b08 - a13 * b07) * invDet;
    result.e[5] = (a00 * b11 - a02 * b08 + a03 * b07) * invDet;
    result.e[6] = (-a30 * b05 + a32 * b02 - a33 * b01) * invDet;
    result.e[7] = (a20 * b05 - a22 * b02 + a23 * b01) * invDet;
    result.e[8] = (a10 * b10 - a11 * b08 + a13 * b06) * invDet;
    result.e[9] = (-a00 * b10 + a01 * b08 - a03 * b06) * invDet;
    result.e[10] = (a30 * b04 - a31 * b02 + a33 * b00) * invDet;
    result.e[11] = (-a20 * b04 + a21 * b02 - a23 * b00) * invDet;
    result.e[12] = (-a10 * b09 + a11 * b07 - a12 * b06) * invDet;
    result.e[13] = (a00 * b09 - a01 * b07 + a02 * b06) * invDet;
    result.e[14] = (-a30 * b03 + a31 * b01 - a32 * b00) * invDet;
    result.e[15] = (a20 * b03 - a21 * b01 + a22 * b00) * invDet;

    return result;
}

inline Matrix4 Matrix4::operator*(const Matrix4 &m)
{
    Matrix4 result;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.e[i + j * 4] += this->e[i + k * 4] * m.e[k + j * 4];

    return result;
}

inline Matrix4 &Matrix4::operator*=(const Matrix4 &m)
{
    *this = *this * m;
    return *this;
}

inline Matrix4 Matrix4::operator*(float f)
{
    Matrix4 result;

    for (unsigned int i = 0; i < 16; i++)
        result.e[i] = this->e[i] * f;

    return result;
}

inline Vector4f Matrix4::operator*(const Vector4f &v) const
{
    Vector4f result;

    result.x = v.x * e[0] + v.y * e[1] + v.z * e[2] + v.w * e[3];
    result.y = v.x * e[4] + v.y * e[5] + v.z * e[6] + v.w * e[7];
    result.z = v.x * e[8] + v.y * e[9] + v.z * e[10] + v.w * e[11];
    result.w = v.x * e[12] + v.y * e[13] + v.z * e[14] + v.w * e[15];

    return result;
}

inline Matrix4 Matrix4::operator+(const Matrix4 &m2)
{
    Matrix4 result;

    for (unsigned int i = 0; i < 16; i++)
        result.e[i] = this->e[i] + m2.e[i];

    return result;
}



/*std::ostream& operator<<(std::ostream &os, const Matrix4& m)
{
  os << m.e[0] << ", " << m.e[4] << ", " << m.e[8] << ", " << m.e[12] << "\n"
     << m.e[1] << ", " << m.e[5] << ", " << m.e[9] << ", " << m.e[13] << "\n"
     << m.e[2] << ", " << m.e[6] << ", " << m.e[10] << ", " << m.e[14] << "\n"
     << m.e[3] << ", " << m.e[7] << ", " << m.e[11] << ", " << m.e[15] << "\n";

  return os;
}*/