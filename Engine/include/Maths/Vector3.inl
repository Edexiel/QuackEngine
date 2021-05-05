
typedef Vector3<float> Vector3f;
typedef Vector3<double> Vector3d;
typedef Vector3<int> Vector3i;
typedef Vector3<unsigned char> Color3;
typedef Vector3<float> Color3f;

template<typename T>
Vector3<T>::Vector3(T _x, T _y, T _z) : x{_x}, y{_y}, z{_z}
{}

template<typename T>
Vector3<T>::Vector3(Vector2 <T> v, T _z) : x{v.x}, y{v.y}, z{_z}
{}

template<typename T>
T Vector3<T>::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

template<typename T>
T Vector3<T>::SqrLength() const
{
    return x * x + y * y + z * z;
}

template<typename T>
Vector3 <T> &Vector3<T>::Normalize()
{
    T length = Length();
    if (length > 0)
    {
        x /= length;
        y /= length;
        z /= length;
    }

    return *this;
}

template<typename T>
Vector3 <T> Vector3<T>::GetNormalized() const
{
    T length = Length();
    if (length > 0)
        return {x / length, y / length, z / length};
    else
        return *this;
}

template<typename T>
void Vector3<T>::Normalize(Vector3 <T> &v)
{
    T length = v.Length();

    v.x /= length;
    v.y /= length;
    v.z /= length;
}

template<typename T>
T Vector3<T>::DotProduct(const Vector3 <T> &v1, const Vector3 <T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
Vector3 <T> Vector3<T>::CrossProduct(const Vector3 <T> &v1,
                                     const Vector3 <T> &v2)
{
    return {(v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z),
            (v1.x * v2.y) - (v1.y * v2.x)};
}

template<typename T>
Vector3 <T> Vector3<T>::Up()
{ return {0, 1, 0}; }

template<typename T>
Vector3 <T> Vector3<T>::Down()
{
    return {0, -1, 0};
}

template<typename T>
Vector3 <T> Vector3<T>::Right()
{
    return {1, 0, 0};
}

template<typename T>
Vector3 <T> Vector3<T>::Left()
{
    return {-1, 0, 0};
}

template<typename T>
Vector3 <T> Vector3<T>::Forward()
{
    return {0, 0, 1};
}

template<typename T>
Vector3 <T> Vector3<T>::Backward()
{
    return {0, 0, -1};
}

template<typename T>
Vector3 <T> Vector3<T>::Zero()
{ return {0, 0, 0}; }

template<typename T>
Vector3 <T> Vector3<T>::One()
{ return {1, 1, 1}; }

template<typename T>
Vector3 <T> Vector3<T>::operator+(const Vector3 <T> &v2) const
{
    return {this->x + v2.x, this->y + v2.y, this->z + v2.z};
}

template<typename T>
Vector3 <T> Vector3<T>::operator-(const Vector3 <T> &v2) const
{
    return {this->x - v2.x, this->y - v2.y, this->z - v2.z};
}

template<typename T>
Vector3 <T> Vector3<T>::operator*(const T &f) const
{
    return {this->x * f, this->y * f, this->z * f};
}

template<typename T>
bool Vector3<T>::operator==(const Vector3 <T> &v2) const
{
    for (unsigned int i = 0; i < 3; i++)
    {
        if (e[i] != v2.e[i])
            return false;
    }
    return true;
}

template<typename T>
bool Vector3<T>::operator!=(const Vector3 <T> &v2) const
{
    for (unsigned int i = 0; i < 3; i++)
    {
        if (e[i] != v2.e[i])
            return true;
    }
    return false;
}

