#ifndef _COMMON_HPP_
#define _COMMON_HPP_

template <typename T>
constexpr T Pi()
{
    return (T)3.14159265358979323846;
}

template <typename T>
constexpr T RadToDeg()
{
    return (T)180.0 / Pi<T>();
}

template <typename T>
constexpr float DegToRad()
{
    return Pi<T>() / (T)180.0;
}

#endif