#pragma once

#include <ostream>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Matrix4G;
template <typename>
class Vector3G;
template <typename>
class Vector4G;

template <typename T>  // Most of it almost copied from glm
class QuaternionG
{
public:
    static const QuaternionG<T> &Identity();

    T x, y, z, w;

    QuaternionG();
    QuaternionG(T _x, T _y, T _z, T _w);

    T Length() const;
    T SqLength() const;
    QuaternionG<T> Conjugated() const;
    QuaternionG<T> Normalized() const;
    QuaternionG<T> Inversed() const;
    Vector3G<T> GetEulerAnglesDegrees() const;
    T GetPitch() const;
    T GetYaw() const;
    T GetRoll() const;
    Vector3G<T> GetAngleAxis() const;

    static T Dot(const QuaternionG<T> &q1, const QuaternionG<T> &q2);
    static QuaternionG<T> Cross(const QuaternionG<T> &q1,
                                const QuaternionG<T> &q2);

    static QuaternionG<T> FromEulerAnglesRads(
        const Vector3G<T> &eulerAnglesRads);
    static Vector3G<T> GetEulerAnglesDegrees(const QuaternionG<T> &q);

    static QuaternionG<T> Lerp(const QuaternionG<T> &from,
                               const QuaternionG<T> &to,
                               T t);

    static QuaternionG<T> SLerp(const QuaternionG<T> &from,
                                const QuaternionG<T> &_to,
                                T t);

    static QuaternionG<T> FromTo(const Vector3G<T> &from,
                                 const Vector3G<T> &to);

    static QuaternionG<T> LookDirection(
        const Vector3G<T> &_forward,
        const Vector3G<T> &_up = Vector3G<T>::Up());

    template <typename OtherT>
    static QuaternionG<T> AngleAxis(T angleRads, const Vector3G<OtherT> &axis);
};

template <typename T>
bool operator==(const QuaternionG<T> &q1, const QuaternionG<T> &q2);

template <typename T>
bool operator!=(const QuaternionG<T> &q1, const QuaternionG<T> &q2);

template <typename T>
QuaternionG<T> operator+(const QuaternionG<T> &q1, const QuaternionG<T> &q2);

template <typename T>
QuaternionG<T> &operator+=(QuaternionG<T> &lhs, const QuaternionG<T> &rhs);

template <typename T, class OtherT>
QuaternionG<T> operator*(const QuaternionG<T> &q, OtherT a);

template <typename T, class OtherT>
QuaternionG<T> operator*(OtherT a, const QuaternionG<T> &q);

template <typename T, class OtherT>
QuaternionG<T> operator/(OtherT a, const QuaternionG<T> &q);

template <typename T, class OtherT>
QuaternionG<T> operator/(const QuaternionG<T> &q, OtherT a);

template <typename T>
QuaternionG<T> &operator*=(QuaternionG<T> &lhs, const QuaternionG<T> &rhs);

template <typename T>
QuaternionG<T> operator*(const QuaternionG<T> &q1, const QuaternionG<T> &q2);

template <typename T>
QuaternionG<T> operator-(const QuaternionG<T> &q);

template <typename T>
Vector4G<T> operator*(QuaternionG<T> q, const Vector4G<T> &rhs);

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &lhs, QuaternionG<T> q);

template <typename T>
Vector3G<T> operator*(const QuaternionG<T> &q, const Vector3G<T> &rhs);

template <typename T>
Vector3G<T> operator*(const Vector3G<T> &lhs, const QuaternionG<T> &q);

template <typename T>
std::ostream &operator<<(std::ostream &log, const QuaternionG<T> &q)
{
    log << "(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
    return log;
}

BANG_MATH_DEFINE_USINGS(Quaternion)
}

#include "BangMath/Quaternion.tcc"
