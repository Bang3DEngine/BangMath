#pragma once

#include "BangMath/Axis.h"

namespace Bang
{
template <typename>
class Vector2G;

template <typename T>
class Vector3G
{
public:
    static const Vector3G &Up();
    static const Vector3G &Down();
    static const Vector3G &Right();
    static const Vector3G &Left();
    static const Vector3G &Zero();
    static const Vector3G &One();
    static const Vector3G &Forward();
    static const Vector3G &Back();
    static const Vector3G &Infinity();
    static const Vector3G &NInfinity();

    T x, y, z;

    Vector3G();
    explicit Vector3G(const T &a);

    template <typename OtherT>
    explicit Vector3G(const Vector3G<OtherT> &v);

    template <typename OtherT1, class OtherT2, class OtherT3>
    explicit Vector3G(const OtherT1 &_x, const OtherT2 &_y, const OtherT3 &_z);

    template <typename OtherT1, class OtherT2>
    explicit Vector3G(const Vector2G<OtherT1> &v, const OtherT2 &_z);

    template <typename OtherT1, class OtherT2>
    explicit Vector3G(const OtherT1 &_x, const Vector2G<OtherT2> &v);

    T Length() const;
    T SqLength() const;
    void Normalize();

    Vector3G NormalizedSafe() const;
    Vector3G Normalized() const;

    Vector3G ToDegrees() const;
    Vector3G ToRadians() const;

    T Distance(const Vector3G<T> &p) const;
    T SqDistance(const Vector3G<T> &p) const;

    Vector3G<T> Abs() const;

    T &At(int i);
    const T &At(int i) const;

    T *Data();
    const T *Data() const;

    static T Dot(const Vector3G<T> &v1, const Vector3G<T> &v2);

    static T Distance(const Vector3G<T> &v1, const Vector3G<T> &v2);
    static T SqDistance(const Vector3G<T> &v1, const Vector3G<T> &v2);

    static Vector3G<T> Abs(const Vector3G<T> &v);
    static Vector3G<T> Max(const Vector3G<T> &v1, const Vector3G<T> &v2);
    static Vector3G<T> Min(const Vector3G<T> &v1, const Vector3G<T> &v2);

    static Vector3G<T> Floor(const Vector3G<T> &v1);
    static Vector3G<T> Ceil(const Vector3G<T> &v1);
    static Vector3G<T> Round(const Vector3G<T> &v1);
    static Vector3G<T> Clamp(const Vector3G<T> &v,
                             const Vector3G<T> &min,
                             const Vector3G<T> &max);
    static Vector3G<T> Clamp2(const Vector3G<T> &v,
                              const Vector3G<T> &bound1,
                              const Vector3G<T> &bound2);

    template <typename Real>
    static Vector3G<T> Lerp(const Vector3G<T> &v1,
                            const Vector3G<T> &v2,
                            Real t);

    T GetMax() const;
    T GetMin() const;
    Axis GetAxis() const;
    const T &GetAxis(Axis axis) const;
    static Vector3G<T> FromAxis(Axis axis);

    T &operator[](std::size_t i);
    const T &operator[](std::size_t i) const;

    Vector3G<T> ProjectedOnPlane(const Vector3G<T> &planeNormal,
                                 const Vector3G<T> &planePoint) const;
    Vector3G<T> ProjectedOnVector(const Vector3G<T> &vector) const;
    Vector2G<T> ProjectedOnAxis(Axis3D axis) const;
    T ProjectedOnAxisAsPoint(const Vector3G<T> &axis) const;

    template <typename OtherT1, class OtherT2>
    static Vector3G<T> Cross(const Vector3G<OtherT1> &v1,
                             const Vector3G<OtherT2> &v2);

    template <typename OtherT1, class OtherT2>
    static Vector3G<T> Reflect(const Vector3G<OtherT1> &incident,
                               const Vector3G<OtherT2> &normal);
};

template <typename T>
bool operator==(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
bool operator!=(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
bool operator<(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
bool operator<=(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
bool operator>(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
bool operator>=(const Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> operator+(const Vector3G<T> &v1, const Vector3G<T> &v2);

template <typename T>
Vector3G<T> operator*(const Vector3G<T> &v1, const Vector3G<T> &v2);

template <typename T>
Vector3G<T> operator*(const T &a, const Vector3G<T> &v);

template <typename T>
Vector3G<T> operator*(const Vector3G<T> &v, const T &a);

template <typename T>
Vector3G<T> operator/(const T &a, const Vector3G<T> &v);

template <typename T>
Vector3G<T> operator/(const Vector3G<T> &v, const T &a);

template <typename T>
Vector3G<T> operator/(const Vector3G<T> &v1, const Vector3G<T> &v2);

template <typename T>
Vector3G<T> &operator+=(Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> &operator-=(Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> &operator*=(Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> &operator/=(Vector3G<T> &lhs, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> operator+(const T &a, const Vector3G<T> &v);

template <typename T>
Vector3G<T> operator+(const Vector3G<T> &v, const T &a);

template <typename T>
Vector3G<T> operator-(const Vector3G<T> &v1, const Vector3G<T> &v2);

template <typename T>
Vector3G<T> operator-(const T &a, const Vector3G<T> &v);

template <typename T>
Vector3G<T> operator-(const Vector3G<T> &v, const T &a);

template <typename T>
Vector3G<T> &operator+=(Vector3G<T> &lhs, const T &a);

template <typename T>
Vector3G<T> &operator-=(Vector3G<T> &lhs, const T &a);

template <typename T>
Vector3G<T> &operator*=(Vector3G<T> &lhs, const T &a);

template <typename T>
Vector3G<T> &operator/=(Vector3G<T> &lhs, const T &a);

template <typename T>
Vector3G<T> operator-(const Vector3G<T> &v);

}  // namespace Bang

#include "BangMath/Vector3.tcc"
