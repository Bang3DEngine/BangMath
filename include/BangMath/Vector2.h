#pragma once

#include <cstddef>

#include "BangMath/Axis.h"
#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector3G;

template <typename T>
class Vector2G
{
public:
    static const Vector2G &Up();
    static const Vector2G &Down();
    static const Vector2G &Right();
    static const Vector2G &Left();
    static const Vector2G &Zero();
    static const Vector2G &One();
    static const Vector2G &Infinity();
    static const Vector2G &NInfinity();

    T x, y;

    Vector2G();
    explicit Vector2G(const T &a);
    template <typename OtherT1, class OtherT2>
    explicit Vector2G(const OtherT1 &_x, const OtherT2 &_y);

    template <typename OtherT>
    explicit Vector2G(const Vector2G<OtherT> &v);

    T Length() const;
    T SqLength() const;
    void Normalize();

    Vector2G NormalizedSafe() const;
    Vector2G Normalized() const;

    Vector2G ToDegrees() const;
    Vector2G ToRadians() const;

    T Distance(const Vector2G<T> &p) const;
    T SqDistance(const Vector2G<T> &p) const;

    Vector2G<T> Perpendicular() const;
    Vector2G<T> Abs() const;

    T &At(int i);
    const T &At(int i) const;

    T *Data();
    const T *Data() const;

    static T Dot(const Vector2G<T> &v1, const Vector2G<T> &v2);

    static T Distance(const Vector2G<T> &v1, const Vector2G<T> &v2);
    static T SqDistance(const Vector2G<T> &v1, const Vector2G<T> &v2);

    static Vector2G<T> Abs(const Vector2G<T> &v);
    static Vector2G<T> Max(const Vector2G<T> &v1, const Vector2G<T> &v2);
    static Vector2G<T> Min(const Vector2G<T> &v1, const Vector2G<T> &v2);

    static Vector2G<T> Floor(const Vector2G<T> &v1);
    static Vector2G<T> Ceil(const Vector2G<T> &v1);
    static Vector2G<T> Round(const Vector2G<T> &v1);
    static Vector2G<T> Clamp(const Vector2G<T> &v,
                             const Vector2G<T> &min,
                             const Vector2G<T> &max);
    static Vector2G<T> Clamp2(const Vector2G<T> &v,
                              const Vector2G<T> &bound1,
                              const Vector2G<T> &bound2);

    template <typename Real>
    static Vector2G<T> Lerp(const Vector2G<T> &v1,
                            const Vector2G<T> &v2,
                            Real t);

    Vector2G<T> yx() const;
    Vector3G<T> x0y() const;
    Vector3G<T> x1y() const;
    Vector3G<T> xy0() const;
    Vector3G<T> xy1() const;

    T GetMin() const;
    T GetMax() const;
    Axis GetAxis() const;
    const T &GetAxis(Axis axis) const;
    static Vector2G<T> FromAxis(Axis axis);

    T &operator[](std::size_t i);
    const T &operator[](std::size_t i) const;
    T &operator[](const Axis &axis);
    const T &operator[](const Axis &axis) const;

    static T Cross(const Vector2G<T> &v1, const Vector2G<T> &v2);
};

template <typename T>
T &Vector2G<T>::operator[](const Axis &axis)
{
    return (reinterpret_cast<T *>(this))[axis == Axis::HORIZONTAL ? 0 : 1];
}

template <typename T>
const T &Vector2G<T>::operator[](const Axis &axis) const
{
    return (
        reinterpret_cast<const T *>(this))[axis == Axis::HORIZONTAL ? 0 : 1];
}

template <typename T>
bool operator==(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
bool operator!=(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
bool operator<(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
bool operator<=(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
bool operator>(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
bool operator>=(const Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
Vector2G<T> operator+(const Vector2G<T> &v1, const Vector2G<T> &v2);

template <typename T>
Vector2G<T> operator*(const Vector2G<T> &v1, const Vector2G<T> &v2);

template <typename T>
Vector2G<T> operator*(const T &a, const Vector2G<T> &v);

template <typename T>
Vector2G<T> operator*(const Vector2G<T> &v, const T &a);

template <typename T>
Vector2G<T> operator/(const T &a, const Vector2G<T> &v);

template <typename T>
Vector2G<T> operator/(const Vector2G<T> &v, const T &a);

template <typename T>
Vector2G<T> operator/(const Vector2G<T> &v1, const Vector2G<T> &v2);

template <typename T>
Vector2G<T> &operator+=(Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
Vector2G<T> &operator-=(Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
Vector2G<T> &operator*=(Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
Vector2G<T> &operator/=(Vector2G<T> &lhs, const Vector2G<T> &rhs);

template <typename T>
Vector2G<T> operator+(const T &a, const Vector2G<T> &v);

template <typename T>
Vector2G<T> operator+(const Vector2G<T> &v, const T &a);

template <typename T>
Vector2G<T> operator-(const Vector2G<T> &v1, const Vector2G<T> &v2);

template <typename T>
Vector2G<T> operator-(const T &a, const Vector2G<T> &v);

template <typename T>
Vector2G<T> operator-(const Vector2G<T> &v, const T &a);

template <typename T>
Vector2G<T> &operator+=(Vector2G<T> &lhs, const T &a);

template <typename T>
Vector2G<T> &operator-=(Vector2G<T> &lhs, const T &a);

template <typename T>
Vector2G<T> &operator*=(Vector2G<T> &lhs, const T &a);

template <typename T>
Vector2G<T> &operator/=(Vector2G<T> &lhs, const T &a);

template <typename T>
Vector2G<T> operator-(const Vector2G<T> &v);

BANG_MATH_DEFINE_USINGS(Vector2)

}  // namespace Bang


#include "BangMath/Vector2.tcc"
