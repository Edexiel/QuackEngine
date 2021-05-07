using Vector4f = Vector4<float>;
using Color4f = Vector4<float>;
using Vector4d = Vector4<double>;

template<typename T>
Vector4<T>::Vector4(T _x, T _y, T _z, T _w):x{_x}, y{_y}, z{_z}, w{_w}
{}

template<typename T>
Vector4<T>::Vector4(Vector3 <T> v, T _w):x{v.x}, y{v.y}, z{v.z}, w{_w}
{}

template<typename T>
Maths::Vector4<T>::Vector4(T n):x{n}, y{n}, z{n}, w{n}
{}

template<typename T>
T Vector4<T>::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

template<typename T>
T Vector4<T>::SqrLength() const
{
    return x * x + y * y + z * z + w * w;
}

template<typename T>
Vector4 <T> &Vector4<T>::Homogenize()
{
    if (w != 0 && w != 1)
    {
        x /= w;
        y /= w;
        z /= w;
    }

    return *this;
}

template<typename T>
Vector3 <T> Vector4<T>::GetHomogenized() const
{
    if (w == 0 || w == 1)
        return xyz;

    return {x / w, y / w, z / w};
}

template<typename T>
void Vector4<T>::Homogenize(Vector4 <T> &v)
{
    if (v.w != 0 && v.w != 1)
    {
        v.x /= v.w;
        v.y /= v.w;
        v.z /= v.w;
    }
}

template<typename T>
T Vector4<T>::DotProduct(const Vector4 <T> &v1, const Vector4 <T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

template<typename T>
Vector4 <T> Vector4<T>::Zero()
{
    return {0, 0, 0, 0};
}

template<typename T>
Vector4 <T> Vector4<T>::One()
{
    return {1, 1, 1, 1};
}

template<typename T>
Vector4 <T> Vector4<T>::operator+(const Vector4 <T> &v2) const
{
    return {this->x + v2.x, this->y + v2.y, this->z + v2.z, this->w + v2.w};
}

template<typename T>
Vector4 <T> Vector4<T>::operator-(const Vector4 <T> &v2) const
{
    return {this->x - v2.x, this->y - v2.y, this->z - v2.z, this->w - v2.w};
}

template<typename T>
Vector4 <T> Vector4<T>::operator*(const T &f) const
{
    return {this->x * f, this->y * f, this->z * f, this->w * f};
}

