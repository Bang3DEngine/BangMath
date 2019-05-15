#pragma once
#include "BangMath/Quaternion.h"

#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
QuaternionG<T>::QuaternionG()
    : x(static_cast<T>(0)),
      y(static_cast<T>(0)),
      z(static_cast<T>(0)),
      w(static_cast<T>(1))
{
}

template <typename T>
QuaternionG<T>::QuaternionG(T _x, T _y, T _z, T _w)
    : x(static_cast<T>(_x)),
      y(static_cast<T>(_y)),
      z(static_cast<T>(_z)),
      w(static_cast<T>(_w))
{
}

template <typename T>
T QuaternionG<T>::Length() const
{
    return Math::Sqrt(SqLength());
}

template <typename T>
T QuaternionG<T>::SqLength() const
{
    return (x * x + y * y + z * z + w * w);
}

template <typename T>
QuaternionG<T> QuaternionG<T>::Conjugated() const
{
    return QuaternionG<T>(-x, -y, -z, w);
}

template <typename T>
QuaternionG<T> QuaternionG<T>::Normalized() const
{
    const auto length = Length();
    if (length == 0.0f)
    {
        return QuaternionG<T>::Identity();
    }
    return QuaternionG<T>(x / length, y / length, z / length, w / length);
}

template <typename T>
QuaternionG<T> QuaternionG<T>::Inversed() const
{
    return Conjugated() / QuaternionG<T>::Dot(*this, *this);
}

template <typename T>
Vector3G<T> QuaternionG<T>::GetEulerAnglesDegrees() const
{
    return QuaternionG<T>::GetEulerAnglesDegrees(*this);
}

template <typename T>
T QuaternionG<T>::GetPitch() const
{
    return static_cast<T>(Math::ATan2((static_cast<T>(2) * (y * z + w * x)),
                                      (w * w - x * x - y * y + z * z)));
}

template <typename T>
T QuaternionG<T>::GetYaw() const
{
    return Math::ASin(Math::Clamp(static_cast<T>(-2) * (x * z - w * y),
                                  static_cast<T>(-1),
                                  static_cast<T>(1)));
}

template <typename T>
T QuaternionG<T>::GetRoll() const
{
    return static_cast<T>(Math::ATan2((static_cast<T>(2) * (x * y + w * z)),
                                      (w * w + x * x - y * y - z * z)));
}

template <typename T>
T QuaternionG<T>::Dot(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

template <typename T>
QuaternionG<T> QuaternionG<T>::Cross(const QuaternionG<T> &q1,
                                     const QuaternionG<T> &q2)
{
    return QuaternionG<T>(
        q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
        q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
        q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
        q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
}

template <typename T>
Vector3G<T> QuaternionG<T>::GetAngleAxis() const
{
    const auto angle = 2 * Math::ACos(w);
    const auto w2 = w * w;
    const auto sqrt = Math::Sqrt(1.0f - w2);

    Vector3G<T> axis;
    if (sqrt != 0)
    {
        axis = Vector3G<T>(x / sqrt, y / sqrt, z / sqrt);
    }
    else
    {
        axis = Vector3G<T>::Zero();
    }

    return axis.NormalizedSafe() * angle;
}

template <typename T>
QuaternionG<T> QuaternionG<T>::FromEulerAnglesRads(
    const Vector3G<T> &eulerAnglesRads)
{
    const auto qx =
        QuaternionG<T>::AngleAxis(eulerAnglesRads.x, Vector3G<T>::Right());
    const auto qy =
        QuaternionG<T>::AngleAxis(eulerAnglesRads.y, Vector3G<T>::Up());
    const auto qz =
        QuaternionG<T>::AngleAxis(eulerAnglesRads.z, Vector3G<T>::Forward());
    return (qz * qy * qx).Normalized();
}

template <typename T>
Vector3G<T> QuaternionG<T>::GetEulerAnglesDegrees(const QuaternionG<T> &q)
{
    return Vector3G<T>(q.GetPitch(), q.GetYaw(), q.GetRoll()).ToDegrees();
}

template <typename T>
QuaternionG<T> QuaternionG<T>::Lerp(const QuaternionG<T> &from,
                                    const QuaternionG<T> &to,
                                    T t)
{
    const auto cosTheta = QuaternionG<T>::Dot(from, to);
    if (cosTheta > static_cast<T>(1) - static_cast<T>(0.01))
    {
        return QuaternionG(Math::Lerp(from.x, to.x, t),
                           Math::Lerp(from.y, to.y, t),
                           Math::Lerp(from.z, to.z, t),
                           Math::Lerp(from.w, to.w, t));
    }
    else
    {
        const auto angle = Math::ACos(cosTheta);
        return (Math::Sin((static_cast<T>(1) - t) * angle) * from +
                Math::Sin(t * angle) * to) /
               Math::Sin(angle);
    }
}

template <typename T>
QuaternionG<T> QuaternionG<T>::SLerp(const QuaternionG<T> &from,
                                     const QuaternionG<T> &_to,
                                     T t)
{
    auto to = _to;
    auto cosTheta = QuaternionG<T>::Dot(from, _to);

    // If cosTheta < 0, the interpolation will take the long way around the
    // sphere. To fix this, one quat must be negated.
    if (cosTheta < static_cast<T>(0))
    {
        to = -_to;
        cosTheta = -cosTheta;
    }

    if (cosTheta > static_cast<T>(1) - static_cast<T>(0.01))
    {
        return QuaternionG<T>(Math::Lerp(from.x, to.x, t),
                              Math::Lerp(from.y, to.y, t),
                              Math::Lerp(from.z, to.z, t),
                              Math::Lerp(from.w, to.w, t));
    }
    else
    {
        const auto angle = Math::ACos(cosTheta);
        return (Math::Sin((static_cast<T>(1) - t) * angle) * from +
                Math::Sin(t * angle) * to) /
               Math::Sin(angle);
    }
}

template <typename T>
QuaternionG<T> QuaternionG<T>::FromTo(const Vector3G<T> &from,
                                      const Vector3G<T> &to)
{
    const auto v0 = from.Normalized();
    const auto v1 = to.Normalized();

    const auto d = Vector3G<T>::Dot(v0, v1);
    if (d >= 1.0)
    {
        return QuaternionG<T>::Identity();
    }
    else if (d <= -1.0)
    {
        auto axis = Vector3G<T>::Cross(Vector3G<T>::Right(), v0);
        if (axis.Length() == 0)
        {
            axis = Vector3G<T>(0, 1, 0);
            axis = Vector3G<T>::Cross(axis, v0);
        }

        return QuaternionG<T>(axis.x, axis.y, axis.z, 0.0).Normalized();
    }

    const auto s = static_cast<T>(Math::Sqrt((1 + d) * 2));
    const auto invs = (static_cast<T>(1.0) / s);
    const auto c = Vector3G<T>::Cross(v0, v1) * invs;
    return QuaternionG<T>(c.x, c.y, c.z, s * 0.5).Normalized();
}

template <typename T>
QuaternionG<T> QuaternionG<T>::LookDirection(const Vector3G<T> &_forward,
                                             const Vector3G<T> &_up)
{
    const auto forward = _forward.NormalizedSafe();
    const auto up = _up.NormalizedSafe();

    if (Vector3G<T>::Dot(forward, up) >= static_cast<T>(0.99) ||
        Vector3G<T>::Dot(forward, -up) >= static_cast<T>(0.99))
    {
        return QuaternionG<T>::Identity();
    }
    return Matrix4G<T>::ToQuaternion(
        Matrix4G<T>::LookAt(Vector3G<T>::Zero(), forward, up).Inversed());
}

template <typename T>
template <typename OtherT>
QuaternionG<T> QuaternionG<T>::AngleAxis(T angleRads,
                                         const Vector3G<OtherT> &axis)
{
    const auto s = Math::Sin(angleRads * static_cast<T>(0.5));
    return QuaternionG<T>(static_cast<T>(axis.x) * s,
                          static_cast<T>(axis.y) * s,
                          static_cast<T>(axis.z) * s,
                          Math::Cos(angleRads * static_cast<T>(0.5)))
        .Normalized();
}

template <typename T>
const QuaternionG<T> &QuaternionG<T>::Identity()
{
    static const auto q = QuaternionG<T>();
    return q;
}

template <typename T>
bool operator==(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    return (q1.x == q2.x) && (q1.y == q2.y) && (q1.z == q2.z) && (q1.w == q2.w);
}

template <typename T>
bool operator!=(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    return !(q1 == q2);
}

template <typename T>
QuaternionG<T> operator+(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    auto res = q1;
    res += q2;
    return res;
}

template <typename T>
QuaternionG<T> &operator+=(QuaternionG<T> &lhs, const QuaternionG<T> &rhs)
{
    lhs.x += rhs.x;
    lhs.y += rhs.y;
    lhs.z += rhs.z;
    lhs.w += rhs.w;
    return lhs;
}

template <typename T, class OtherT>
QuaternionG<T> operator*(const QuaternionG<T> &q, OtherT a)
{
    return q * static_cast<T>(a);
}

template <typename T, class OtherT>
QuaternionG<T> operator*(OtherT a, const QuaternionG<T> &q)
{
    return QuaternionG<T>(q.x * static_cast<T>(a),
                          q.y * static_cast<T>(a),
                          q.z * static_cast<T>(a),
                          q.w * static_cast<T>(a));
}

template <typename T, class OtherT>
QuaternionG<T> operator/(OtherT a, const QuaternionG<T> &q)
{
    return QuaternionG<T>(static_cast<T>(a) / q.x,
                          static_cast<T>(a) / q.y,
                          static_cast<T>(a) / q.z,
                          static_cast<T>(a) / q.w);
}

template <typename T, class OtherT>
QuaternionG<T> operator/(const QuaternionG<T> &q, OtherT a)
{
    return QuaternionG<T>(q.x / a, q.y / a, q.z / a, q.w / a);
}
template <typename T>
QuaternionG<T> &operator*=(QuaternionG<T> &lhs, const QuaternionG<T> &rhs)
{
    const auto p = lhs;
    const auto q = rhs;

    lhs.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
    lhs.y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
    lhs.z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
    lhs.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
    return lhs;
}
template <typename T>
QuaternionG<T> operator*(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    auto res = q1;
    res *= q2;
    return res;
}
template <typename T>
QuaternionG<T> operator-(const QuaternionG<T> &q)
{
    return QuaternionG<T>(-q.x, -q.y, -q.z, -q.w);
}

template <typename T>
Vector4G<T> operator*(QuaternionG<T> q, const Vector4G<T> &rhs)
{
    return Vector4G<T>(q * Vector3G<T>(rhs.x, rhs.y, rhs.w), rhs.w);
}

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &lhs, QuaternionG<T> q)
{
    return q.Inversed() * lhs;
}

template <typename T>
Vector3G<T> operator*(const QuaternionG<T> &q, const Vector3G<T> &rhs)
{
    const auto qVector = Vector3G<T>(q.x, q.y, q.z);
    const auto uv(Vector3G<T>::Cross(qVector, rhs));
    const auto uuv(Vector3G<T>::Cross(qVector, uv));

    return rhs + ((uv * q.w) + uuv) * static_cast<T>(2);
}
template <typename T>
Vector3G<T> operator*(const Vector3G<T> &lhs, const QuaternionG<T> &q)
{
    return q.Inversed() * lhs;
}
}
