#pragma once

#include "BangMath/Defines.h"
#include "BangMath/Math.h"

namespace Bang
{
template <typename>
class Vector3G;

template <typename T>  // Most of it almost copied from glm
class QuaternionG
{
public:
    static const QuaternionG<T> &Identity();

    T x, y, z, w;

    QuaternionG()
        : x(static_cast<T>(0)),
          y(static_cast<T>(0)),
          z(static_cast<T>(0)),
          w(static_cast<T>(1))
    {
    }

    QuaternionG(T _x, T _y, T _z, T _w)
        : x(static_cast<T>(_x)),
          y(static_cast<T>(_y)),
          z(static_cast<T>(_z)),
          w(static_cast<T>(_w))
    {
    }

    T Length() const
    {
        return Math::Sqrt(SqLength());
    }
    T SqLength() const
    {
        return (x * x + y * y + z * z + w * w);
    }

    QuaternionG<T> Conjugated() const
    {
        return QuaternionG<T>(-x, -y, -z, w);
    }
    QuaternionG<T> Normalized() const
    {
        T length = Length();
        if (length == 0.0f)
        {
            return QuaternionG<T>::Identity();
        }
        return QuaternionG<T>(x / length, y / length, z / length, w / length);
    }
    QuaternionG<T> Inversed() const
    {
        return Conjugated() / QuaternionG<T>::Dot(*this, *this);
    }

    Vector3G<T> GetEulerAnglesDegrees() const
    {
        return QuaternionG<T>::GetEulerAnglesDegrees(*this);
    }

    T GetPitch() const
    {
        return static_cast<T>(Math::ATan2((static_cast<T>(2) * (y * z + w * x)),
                                          (w * w - x * x - y * y + z * z)));
    }

    T GetYaw() const
    {
        return Math::ASin(Math::Clamp(static_cast<T>(-2) * (x * z - w * y),
                                      static_cast<T>(-1),
                                      static_cast<T>(1)));
    }

    T GetRoll() const
    {
        return static_cast<T>(Math::ATan2((static_cast<T>(2) * (x * y + w * z)),
                                          (w * w + x * x - y * y - z * z)));
    }

    static T Dot(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
    {
        return q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
    }
    static QuaternionG<T> Cross(const QuaternionG<T> &q1,
                                const QuaternionG<T> &q2)
    {
        return QuaternionG<T>(
            q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
            q1.w * q2.y + q1.y * q2.w + q1.z * q2.x - q1.x * q2.z,
            q1.w * q2.z + q1.z * q2.w + q1.x * q2.y - q1.y * q2.x,
            q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
    }

    Vector3G<T> GetAngleAxis() const
    {
        T angle = 2 * Math::ACos(w);

        T w2 = w * w;
        T sqrt = Math::Sqrt(1.0f - w2);

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
    static QuaternionG<T> FromEulerAnglesRads(
        const Vector3G<T> &eulerAnglesRads)
    {
        QuaternionG<T> qx =
            QuaternionG<T>::AngleAxis(eulerAnglesRads.x, Vector3G<T>::Right());
        QuaternionG<T> qy =
            QuaternionG<T>::AngleAxis(eulerAnglesRads.y, Vector3G<T>::Up());
        QuaternionG<T> qz = QuaternionG<T>::AngleAxis(eulerAnglesRads.z,
                                                      Vector3G<T>::Forward());
        return (qz * qy * qx).Normalized();
    }
    static Vector3G<T> GetEulerAnglesDegrees(const QuaternionG<T> &q)
    {
        return Vector3G<T>(q.GetPitch(), q.GetYaw(), q.GetRoll()).ToDegrees();
    }

    static QuaternionG<T> Lerp(const QuaternionG<T> &from,
                               const QuaternionG<T> &to,
                               T t)
    {
        T cosTheta = QuaternionG<T>::Dot(from, to);

        if (cosTheta > static_cast<T>(1) - static_cast<T>(0.01))
        {
            return QuaternionG(Math::Lerp(from.x, to.x, t),
                               Math::Lerp(from.y, to.y, t),
                               Math::Lerp(from.z, to.z, t),
                               Math::Lerp(from.w, to.w, t));
        }
        else
        {
            T angle = Math::ACos(cosTheta);
            return (Math::Sin((static_cast<T>(1) - t) * angle) * from +
                    Math::Sin(t * angle) * to) /
                   Math::Sin(angle);
        }
    }

    static QuaternionG<T> SLerp(const QuaternionG<T> &from,
                                const QuaternionG<T> &_to,
                                T t)
    {
        QuaternionG<T> to = _to;

        T cosTheta = QuaternionG<T>::Dot(from, _to);

        // If cosTheta < 0, the interpolation will take the long way around the
        // sphere.
        // To fix this, one quat must be negated.
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
            T angle = Math::ACos(cosTheta);
            return (Math::Sin((static_cast<T>(1) - t) * angle) * from +
                    Math::Sin(t * angle) * to) /
                   Math::Sin(angle);
        }
    }
    static QuaternionG<T> FromTo(const Vector3G<T> &from, const Vector3G<T> &to)
    {
        Vector3G<T> v0 = from.Normalized();
        Vector3G<T> v1 = to.Normalized();

        const T d = Vector3G<T>::Dot(v0, v1);
        if (d >= 1.0)
        {
            return QuaternionG<T>::Identity();
        }
        else if (d <= -1.0)
        {
            Vector3G<T> axis(1, 0, 0);
            axis = Vector3G<T>::Cross(axis, v0);
            if (axis.Length() == 0)
            {
                axis = Vector3G<T>(0, 1, 0);
                axis = Vector3G<T>::Cross(axis, v0);
            }

            return QuaternionG<T>(axis.x, axis.y, axis.z, 0.0).Normalized();
        }

        const T s = static_cast<T>(Math::Sqrt((1 + d) * 2));
        const T invs = (1.0 / s);
        const Vector3G<T> c = Vector3G<T>::Cross(v0, v1) * invs;
        return QuaternionG<T>(c.x, c.y, c.z, s * 0.5).Normalized();
    }

    static QuaternionG<T> LookDirection(
        const Vector3G<T> &_forward,
        const Vector3G<T> &_up = Vector3G<T>::Up())
    {
        Vector3G<T> forward = _forward.NormalizedSafe();
        Vector3G<T> up = _up.NormalizedSafe();

        if (Vector3G<T>::Dot(forward, up) >= static_cast<T>(0.99) ||
            Vector3G<T>::Dot(forward, -up) >= static_cast<T>(0.99))
        {
            return QuaternionG<T>::Identity();
        }
        return Matrix4G<T>::ToQuaternion(
            Matrix4G<T>::LookAt(Vector3G<T>::Zero(), forward, up).Inversed());
    }

    template <typename OtherT>
    static QuaternionG<T> AngleAxis(T angleRads, const Vector3G<OtherT> &axis)
    {
        const T s = Math::Sin(angleRads * static_cast<T>(0.5));
        return QuaternionG<T>(static_cast<T>(axis.x) * s,
                              static_cast<T>(axis.y) * s,
                              static_cast<T>(axis.z) * s,
                              Math::Cos(angleRads * static_cast<T>(0.5)))
            .Normalized();
    }
};

template <typename T>
const QuaternionG<T> &QuaternionG<T>::Identity()
{
    static const QuaternionG<T> q = QuaternionG<T>();
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
    QuaternionG<T> res = q1;
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
    const QuaternionG<T> p(lhs);
    const QuaternionG<T> q(rhs);

    lhs.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
    lhs.y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
    lhs.z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
    lhs.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
    return lhs;
}
template <typename T>
QuaternionG<T> operator*(const QuaternionG<T> &q1, const QuaternionG<T> &q2)
{
    QuaternionG<T> res = q1;
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
    const Vector3G<T> qVector(q.x, q.y, q.z);
    const Vector3G<T> uv(Vector3G<T>::Cross(qVector, rhs));
    const Vector3G<T> uuv(Vector3G<T>::Cross(qVector, uv));

    return rhs + ((uv * q.w) + uuv) * static_cast<T>(2);
}
template <typename T>
Vector3G<T> operator*(const Vector3G<T> &lhs, const QuaternionG<T> &q)
{
    return q.Inversed() * lhs;
}

BANG_MATH_DEFINE_USINGS(Quaternion)

}  // namespace Bang
