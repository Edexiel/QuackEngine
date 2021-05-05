using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2i = Vector2<int>;

template<typename T>
Vector2<T>::Vector2(T _x, T _y): x{_x}, y{_y}
{}

template<typename T>
T Vector2<T>::Length() const
{
    return sqrtf(x * x + y * y);
}

template<typename T>
T Vector2<T>::SqrLength() const
{
    return x * x + y * y;
}

template<typename T>
Vector2 <T> &Vector2<T>::Normalize()
{
    T length = Length();
    if (length > 0)
    {
        x /= length;
        y /= length;
    }

    return *this;
}

template<typename T>
Vector2 <T> Vector2<T>::GetNormalized() const
{
    T length = Length();
    if (length > 0)
        return {x / length, y / length};
    else
        return *this;
}

template<typename T>
void Vector2<T>::Normalize(Vector2 <T> &v)
{
    T length = v.Length();

    v.x /= length;
    v.y /= length;
}

template<typename T>
T Vector2<T>::DotProduct(const Vector2 <T> &v1, const Vector2 <T> &v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}


template<typename T>
Vector2 <T> Vector2<T>::Up()
{
    return {0, 1};
}

template<typename T>
Vector2 <T> Vector2<T>::Down()
{
    return {0, -1};
}

template<typename T>
Vector2 <T> Vector2<T>::Right()
{
    return {1, 0};
}

template<typename T>
Vector2 <T> Vector2<T>::Left()
{
    return {-1, 0};
}

template<typename T>
Vector2 <T> Vector2<T>::Zero()
{
    return {0, 0};
}

template<typename T>
Vector2 <T> Vector2<T>::operator+(const Vector2 <T> &v2) const
{
    return {this->x + v2.x, this->y + v2.y};
}

template<typename T>
Vector2 <T> Vector2<T>::operator-(const Vector2 <T> &v2) const
{
    return {this->x - v2.x, this->y - v2.y};
}

template<typename T>
Vector2 <T> Vector2<T>::operator*(const T &f) const
{
    return {this->x * f, this->y * f};
}