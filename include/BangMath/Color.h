#pragma once

#include <ostream>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector2G;
template <typename>
class Vector3G;
template <typename>
class Vector4G;

template <typename T>
class ColorG
{
public:
    static const ColorG<T> &Red();
    static const ColorG<T> &Orange();
    static const ColorG<T> &Yellow();
    static const ColorG<T> &Green();
    static const ColorG<T> &Turquoise();
    static const ColorG<T> &VeryLightBlue();
    static const ColorG<T> &LightBlue();
    static const ColorG<T> &Blue();
    static const ColorG<T> &DarkBlue();
    static const ColorG<T> &Purple();
    static const ColorG<T> &Pink();
    static const ColorG<T> &Black();
    static const ColorG<T> &Gray();
    static const ColorG<T> &LightGray();
    static const ColorG<T> &DarkGray();
    static const ColorG<T> &White();
    static const ColorG<T> &Zero();
    static const ColorG<T> &One();

    T r = 0;
    T g = 0;
    T b = 0;
    T a = 0;

    ColorG() = default;
    explicit ColorG(T m);
    explicit ColorG(const Vector2G<T> &v, T b = 0, T a = 1);
    explicit ColorG(const Vector3G<T> &v, T a = 1);
    explicit ColorG(const Vector4G<T> &v);
    explicit ColorG(T r, T g, T b);
    explicit ColorG(T r, T g, T b, T a);
    explicit ColorG(const ColorG<T> &c, T a);

    static ColorG<T> Lerp(const ColorG<T> &v1,
                          const ColorG<T> &v2,
                          T progression);

    ColorG<T> WithAlpha(T alpha) const;
    ColorG<T> WithValue(T value) const;
    ColorG<T> WithSaturation(T saturation) const;

    ColorG<T> ToHSV() const;
    ColorG<T> ToRGB() const;
    Vector3G<T> ToVector3() const;
    Vector4G<T> ToVector4() const;

    static ColorG<T> FromVector3(const Vector3G<T> &v);
    static ColorG<T> FromVector4(const Vector4G<T> &v);

    T &operator[](int i);
    const T &operator[](int i) const;
};

template <typename T>
ColorG<T> operator+(T m, const ColorG<T> &v);

template <typename T>
ColorG<T> operator+(const ColorG<T> &v, T m);

template <typename T>
ColorG<T> operator+(const ColorG<T> &v1, const ColorG<T> &v2);

template <typename T>
ColorG<T> operator-(T m, const ColorG<T> &v);

template <typename T>
ColorG<T> operator-(const ColorG<T> &v, T m);

template <typename T>
ColorG<T> operator-(const ColorG<T> &v1, const ColorG<T> &v2);

template <typename T>
ColorG<T> operator-(const ColorG<T> &v);

template <typename T>
ColorG<T> operator*(T m, const ColorG<T> &v);

template <typename T>
ColorG<T> operator*(const ColorG<T> &v, T m);

template <typename T>
ColorG<T> operator*(const ColorG<T> &v1, const ColorG<T> &v2);

template <typename T>
ColorG<T> operator/(T m, const ColorG<T> &v);

template <typename T>
ColorG<T> operator/(const ColorG<T> &v, T m);

template <typename T>
ColorG<T> operator/(const ColorG<T> &v1, const ColorG<T> &v2);

template <typename T>
bool operator==(const ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
bool operator!=(const ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
ColorG<T> &operator+=(ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
ColorG<T> &operator-=(ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
ColorG<T> &operator*=(ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
ColorG<T> &operator/=(ColorG<T> &lhs, const ColorG<T> &rhs);

template <typename T>
ColorG<T> &operator+=(ColorG<T> &lhs, T m);

template <typename T>
ColorG<T> &operator-=(ColorG<T> &lhs, T m);

template <typename T>
ColorG<T> &operator*=(ColorG<T> &lhs, T m);

template <typename T>
ColorG<T> &operator/=(ColorG<T> &lhs, T m);

template <typename T>
std::ostream &operator<<(std::ostream &log, const ColorG<T> &c)
{
    log << "(" << c.r << ", " << c.g << ", " << c.b << ", " << c.a << ")";
    return log;
}

BANG_MATH_DEFINE_USINGS(Color)
}

#include "BangMath/Color.tcc"
