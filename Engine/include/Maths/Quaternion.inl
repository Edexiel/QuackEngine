
#include "Quaternion.hpp"

inline Quaternion::Quaternion(float _w, float _x, float _y, float _z) : x{_x}, y{_y}, z{_z}, w{_w}
{}

inline Quaternion::Quaternion(float _w, const Vector3f &_axis) : x{_axis.x}, y{_axis.y}, z{_axis.z}, w{_w}
{}

inline Quaternion::Quaternion(const Vector3f &axis, float angle)
{
    w = cosf(angle / 2);

    x = sinf(angle / 2) * axis.x;
    y = sinf(angle / 2) * axis.y;
    z = sinf(angle / 2) * axis.z;
}

inline Quaternion Quaternion::AngleAxis(float angle, Vector3f axis)
{
    return {cosf(angle / 2),
            sinf(angle / 2) * axis.x,
            sinf(angle / 2) * axis.y,
            sinf(angle / 2) * axis.z};
}

inline Quaternion Quaternion::Identity()
{
    return {1, 0, 0, 0};
}

inline float Quaternion::GetMagnitude() const
{
    return sqrtf(w * w + x * x + y * y + z * z);
}

inline Quaternion Quaternion::GetConjugate() const
{
    return {w, -x, -y, -z};
}

inline Quaternion &Quaternion::Normalize()
{
    float size = GetMagnitude();

    w /= size;
    x /= size;
    y /= size;
    z /= size;

    return *this;
}

inline Quaternion Quaternion::GetNormalized() const
{
    float size = GetMagnitude();

    return {w / size, x / size, y / size, z / size};
}

inline void Quaternion::Normalize(Quaternion &q)
{
    float size = q.GetMagnitude();

    q.w /= size;
    q.x /= size;
    q.y /= size;
    q.z /= size;
}

/**
 * @brief clamp angle between pi and -pi
 * @param angle
 * @return clamped angle
 */
inline float Quaternion::NormalizeAxis(float angle)
{
    angle > 1.f ? angle = Pi<float>() : angle = angle;
    angle < -1.f ? angle = - Pi<float>() : angle = angle;
    return angle;
}

inline Maths::Matrix4 Quaternion::ToMatrix() const
{
    Maths::Matrix4 result;

    result.e[0] = 1 - (2 * y * y) - (2 * z * z);
    result.e[1] = (2 * x * y) + (2 * w * z);
    result.e[2] = (2 * x * z) - (2 * w * y);

    result.e[4] = (2 * x * y) - (2 * w * z);
    result.e[5] = 1 - (2 * x * x) - (2 * z * z);
    result.e[6] = (2 * y * z) + (2 * w * x);

    result.e[8] = (2 * x * z) + (2 * w * y);
    result.e[9] = (2 * y * z) - (2 * w * x);
    result.e[10] = 1 - (2 * x * x) - (2 * y * y);

    result.e[15] = 1;

    return result;
}

inline Vector3f Quaternion::ToEuler() const
{
    Vector3f result;

    // roll (x-axis rotation)
    float x0 = 2.0f * (w * x + y * z);
    float x1 = 1.0f - 2.0f * (x * x + y * y);
    result.x = atan2f(x0, x1);

    // pitch (y-axis rotation)
    float y0 = 2.0f * (w * y - z * x);
    y0 = y0 > 1.0f ? 1.0f : y0;
    y0 = y0 < -1.0f ? -1.0f : y0;
    result.y = asinf(y0);

    // yaw (z-axis rotation)
    float z0 = 2.0f * (w * z + x * y);
    float z1 = 1.0f - 2.0f * (y * y + z * z);
    result.z = atan2f(z0, z1);

    return result;
}

inline Quaternion Quaternion::EulerToQuaternion(Vector3f rot)
{
    Quaternion q;

    float x0 = cosf(rot.x * 0.5f);
    float x1 = sinf(rot.x * 0.5f);
    float y0 = cosf(rot.y * 0.5f);
    float y1 = sinf(rot.y * 0.5f);
    float z0 = cosf(rot.z * 0.5f);
    float z1 = sinf(rot.z * 0.5f);

    q.x = x1 * y0 * z0 - x0 * y1 * z1;
    q.y = x0 * y1 * z0 + x1 * y0 * z1;
    q.z = x0 * y0 * z1 - x1 * y1 * z0;
    q.w = x0 * y0 * z0 + x1 * y1 * z1;
    return q;
}

inline float Quaternion::DotProduct(const Quaternion &q1, const Quaternion &q)
{
    return q1.x * q.x + q1.y * q.y + q1.z * q.z + q1.w * q.w;
}

inline Quaternion Quaternion::Slerp(const Quaternion &q1, const Quaternion &q2, float completion)
{
    if (q1 == q2 || completion <= 0.f)
    {
        return q1;
    }
    else if (completion >= 1.0f)
    {
        return q2;
    }


    float dot = DotProduct(q1, q2);

    Quaternion newQ1 = q1;

    if (dot < 0.0f)
    {
        dot = -dot;
        newQ1 = {-newQ1.w, -newQ1.x, -newQ1.y, -newQ1.z};
    }

    float omega = acosf(dot);
    float sin = sinf(omega);

    if (sin == 0 || std::isnan(sin)) // Both Quaternion are equal
    {
        return q1;
    }


    return newQ1 * (sinf((1.0f - completion) * omega) / sin) + q2 * (sinf(completion * omega) / sin);
}

inline Quaternion Quaternion::Lerp(const Quaternion &q1, const Quaternion &q2, float t)
{
    return q1 * (1 - t) + q2 * t;
}

inline Quaternion Quaternion::Nlerp(const Quaternion &q1, const Quaternion &q2, float t)
{
    return Lerp(q1, q2, t).GetNormalized();
}

inline Quaternion Quaternion::LookAt(const Vector3f& origin, const Vector3f& target)
{
    Vector3f forwardVector = (target - origin).Normalize();

    float dot = Vector3f::DotProduct(Vector3f::Forward(), forwardVector);

    if (abs(dot - (-1.0f)) < 0.000001f)
    {
        return Quaternion(Vector3f::Up(), 3.1415926535897932f);
    }
    if (abs(dot - (1.0f)) < 0.000001f)
    {
        return Quaternion::Identity();
    }

    float rotAngle = acosf(dot);
    Vector3f rotAxis = Vector3f::CrossProduct(Vector3f::Forward(), forwardVector).Normalize();
    return AngleAxis(rotAngle, rotAxis);
}

inline Maths::Vector3f Quaternion::XYZVector() const
{
    return {x, y, z};
}

inline Quaternion Quaternion::GetInverse() const
{
    Quaternion q = *this;
    return q / (w * w + x * x + y * y + z * z);
}

inline Quaternion Quaternion::operator+(const Quaternion &q) const
{
    return {this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z};
}

inline Quaternion Quaternion::operator-(const Quaternion &q) const
{
    return {this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z};
}

inline Quaternion Quaternion::operator*(const Quaternion &q) const
{
    return {(this->w * q.w) - Maths::Vector3f::DotProduct(this->XYZVector(), q.XYZVector()),
            (q.XYZVector() * this->w) + (this->XYZVector() * q.w) +
            Maths::Vector3f::CrossProduct(this->XYZVector(), q.XYZVector())};
}

inline Quaternion Quaternion::operator*(float scalar) const
{
    return {this->w * scalar, {this->x * scalar, this->y * scalar, this->z * scalar}};
}

inline Quaternion Quaternion::operator/(float scalar) const
{
    return {this->w / scalar, this->x / scalar, this->y / scalar, this->z / scalar};
}

inline Vector3f Quaternion::operator*(const Vector3f &v) const
{
    Vector3f u = XYZVector();
    return u * 2 * (Vector3f::DotProduct(u, v)) + v * (w * w - Vector3f::DotProduct(u, u)) +
           Vector3f::CrossProduct(u, v) * 2 * w;
}

inline bool Quaternion::operator==(const Quaternion &q) const
{
    return (this->x == q.x && this->y == q.y && this->z == q.z && this->w == q.w);
}