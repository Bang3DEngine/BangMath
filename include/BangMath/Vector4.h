#pragma once

#include "BangMath/Axis.h"
#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector2G;
template <typename>
class Vector3G;

template <typename T>
class Vector4G
{
public:
    static const Vector4G<T> &Up();
    static const Vector4G<T> &Down();
    static const Vector4G<T> &Right();
    static const Vector4G<T> &Left();
    static const Vector4G<T> &Zero();
    static const Vector4G<T> &One();
    static const Vector4G<T> &Forward();
    static const Vector4G<T> &Back();
    static const Vector4G<T> &Infinity();
    static const Vector4G<T> &NInfinity();

    T x, y, z, w;

    Vector4G();
    explicit Vector4G(const T &a);

    template <typename OtherT>
    explicit Vector4G(const Vector4G<OtherT> &v);

    template <typename OtherT1, class OtherT2, class OtherT3, class OtherT4>
    explicit Vector4G(OtherT1 _x, OtherT2 _y, OtherT3 _z, OtherT4 _w);

    template <typename OtherT1, class OtherT2, class OtherT3>
    explicit Vector4G(const Vector2G<OtherT1> &v,
                      const OtherT2 &_z,
                      const OtherT3 &_w);

    template <typename OtherT1, class OtherT2, class OtherT3>
    explicit Vector4G(const OtherT1 &_x,
                      const Vector2G<OtherT2> &v,
                      const OtherT3 &_w);

    template <typename OtherT1, class OtherT2, class OtherT3>
    explicit Vector4G(const OtherT1 &_x,
                      const OtherT2 &_y,
                      const Vector2G<OtherT3> &v);

    template <typename OtherT1, class OtherT2>
    explicit Vector4G(const Vector3G<OtherT1> &v, const OtherT2 &_w);

    template <typename OtherT1, class OtherT2>
    explicit Vector4G(const OtherT1 &_x, const Vector3G<OtherT2> &v);

    T Length() const;
    T SqLength() const;
    void Normalize();

    Vector4G NormalizedSafe() const;
    Vector4G Normalized() const;

    Vector4G ToDegrees() const;
    Vector4G ToRadians() const;

    T Distance(const Vector4G<T> &p) const;
    T SqDistance(const Vector4G<T> &p) const;

    Vector4G<T> Abs() const;

    T &At(int i);
    const T &At(int i) const;

    T *Data();
    const T *Data() const;

    static T Dot(const Vector4G<T> &v1, const Vector4G<T> &v2);

    static T Distance(const Vector4G<T> &v1, const Vector4G<T> &v2);
    static T SqDistance(const Vector4G<T> &v1, const Vector4G<T> &v2);

    static Vector4G<T> Abs(const Vector4G<T> &v);
    static Vector4G<T> Max(const Vector4G<T> &v1, const Vector4G<T> &v2);
    static Vector4G<T> Min(const Vector4G<T> &v1, const Vector4G<T> &v2);

    static Vector4G<T> Floor(const Vector4G<T> &v1);
    static Vector4G<T> Ceil(const Vector4G<T> &v1);
    static Vector4G<T> Round(const Vector4G<T> &v1);
    static Vector4G<T> Clamp(const Vector4G<T> &v,
                             const Vector4G<T> &min,
                             const Vector4G<T> &max);
    static Vector4G<T> Clamp2(const Vector4G<T> &v,
                              const Vector4G<T> &bound1,
                              const Vector4G<T> &bound2);

    template <typename Real>
    static Vector4G<T> Lerp(const Vector4G<T> &v1,
                            const Vector4G<T> &v2,
                            Real t);

    T GetMin() const;
    T GetMax() const;
    Axis GetAxis() const;
    const T &GetAxis(Axis axis) const;
    static Vector4G<T> FromAxis(Axis axis);

    T &operator[](int i);
    const T &operator[](int i) const;
};

template <typename T>
bool operator==(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
bool operator!=(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
bool operator<(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
bool operator<=(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
bool operator>(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
bool operator>=(const Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> operator+(const Vector4G<T> &v1, const Vector4G<T> &v2);

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &v1, const Vector4G<T> &v2);

template <typename T>
Vector4G<T> operator*(const T &a, const Vector4G<T> &v);

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &v, const T &a);

template <typename T>
Vector4G<T> operator/(const T &a, const Vector4G<T> &v);

template <typename T>
Vector4G<T> operator/(const Vector4G<T> &v, const T &a);

template <typename T>
Vector4G<T> operator/(const Vector4G<T> &v1, const Vector4G<T> &v2);

template <typename T>
Vector4G<T> &operator+=(Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> &operator-=(Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> &operator*=(Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> &operator/=(Vector4G<T> &lhs, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> operator+(const T &a, const Vector4G<T> &v);

template <typename T>
Vector4G<T> operator+(const Vector4G<T> &v, const T &a);

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v1, const Vector4G<T> &v2);

template <typename T>
Vector4G<T> operator-(const T &a, const Vector4G<T> &v);

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v, const T &a);

template <typename T>
Vector4G<T> &operator+=(Vector4G<T> &lhs, const T &a);

template <typename T>
Vector4G<T> &operator-=(Vector4G<T> &lhs, const T &a);

template <typename T>
Vector4G<T> &operator*=(Vector4G<T> &lhs, const T &a);

template <typename T>
Vector4G<T> &operator/=(Vector4G<T> &lhs, const T &a);

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v);
}  // namespace Bang

BANG_MATH_DEFINE_USINGS(Vector4)

#include "BangMath/Vector4.tcc"
