#include "BangMath/Vector4.h"

#include "BangMath/Axis.h"
#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
Vector4G<T>::Vector4G()
{
    for (int i = 0; i < 4; ++i)
    {
        At(i) = static_cast<T>(0);
    }
}

template <typename T>
Vector4G<T>::Vector4G(const T &a)
{
    for (int i = 0; i < 4; ++i)
    {
        At(i) = static_cast<T>(a);
    }
}

template <typename T>
template <typename OtherT>
Vector4G<T>::Vector4G(const Vector4G<OtherT> &v)
{
    for (int i = 0; i < 4; ++i)
    {
        At(i) = static_cast<T>(v[i]);
    }
}

template <typename T>
template <typename OtherT1, class OtherT2, class OtherT3, class OtherT4>
Vector4G<T>::Vector4G(OtherT1 _x, OtherT2 _y, OtherT3 _z, OtherT4 _w)
    : x(static_cast<T>(_x)),
      y(static_cast<T>(_y)),
      z(static_cast<T>(_z)),
      w(static_cast<T>(_w))
{
}

template <typename T>
template <typename OtherT1, class OtherT2, class OtherT3>
Vector4G<T>::Vector4G(const Vector2G<OtherT1> &v,
                      const OtherT2 &_z,
                      const OtherT3 &_w)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(_z)),
      w(static_cast<T>(_w))
{
}

template <typename T>
template <typename OtherT1, class OtherT2, class OtherT3>
Vector4G<T>::Vector4G(const OtherT1 &_x,
                      const Vector2G<OtherT2> &v,
                      const OtherT3 &_w)
    : x(static_cast<T>(_x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(_w))
{
}

template <typename T>
template <typename OtherT1, class OtherT2, class OtherT3>
Vector4G<T>::Vector4G(const OtherT1 &_x,
                      const OtherT2 &_y,
                      const Vector2G<OtherT3> &v)
    : x(static_cast<T>(_x)),
      y(static_cast<T>(_y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(v.w))
{
}

template <typename T>
template <typename OtherT1, class OtherT2>
Vector4G<T>::Vector4G(const Vector3G<OtherT1> &v, const OtherT2 &_w)
    : x(static_cast<T>(v.x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(_w))
{
}

template <typename T>
template <typename OtherT1, class OtherT2>
Vector4G<T>::Vector4G(const OtherT1 &_x, const Vector3G<OtherT2> &v)
    : x(static_cast<T>(_x)),
      y(static_cast<T>(v.y)),
      z(static_cast<T>(v.z)),
      w(static_cast<T>(v.w))
{
}

template <typename T>
T Vector4G<T>::Length() const
{
    return Math::Sqrt(SqLength());
}

template <typename T>
T Vector4G<T>::SqLength() const
{
    auto res = static_cast<T>(0);
    for (int i = 0; i < 4; ++i)
    {
        res += At(i) * At(i);
    }
    return res;
}

template <typename T>
void Vector4G<T>::Normalize()
{
    *this /= Length();
}

template <typename T>
Vector4G<T> Vector4G<T>::NormalizedSafe() const
{
    if (*this == Vector4G<T>::Zero())
    {
        return Vector4G<T>::Zero();
    }
    return (*this).Normalized();
}

template <typename T>
Vector4G<T> Vector4G<T>::Normalized() const
{
    auto v = *this;
    v.Normalize();
    return v;
}

template <typename T>
Vector4G<T> Vector4G<T>::ToDegrees() const
{
    auto res = *this;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::RadToDeg(res[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::ToRadians() const
{
    auto res = *this;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::DegToRad(res[i]);
    }
    return res;
}

template <typename T>
T Vector4G<T>::Distance(const Vector4G<T> &p) const
{
    return Vector4G<T>::Distance(*this, p);
}

template <typename T>
T Vector4G<T>::SqDistance(const Vector4G<T> &p) const
{
    return Vector4G<T>::SqDistance(*this, p);
}

template <typename T>
T &Vector4G<T>::At(int i)
{
    return (*this)[i];
}
template <typename T>
const T &Vector4G<T>::At(int i) const
{
    return (*this)[i];
}

template <typename T>
template <typename Real>
Vector4G<T> Vector4G<T>::Lerp(const Vector4G<T> &v1,
                              const Vector4G<T> &v2,
                              Real t)
{
    return v1 + (v2 - v1) * t;
}

template <typename T>
Vector4G<T> Vector4G<T>::Abs() const
{
    auto res = *this;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Abs(res[i]);
    }
    return res;
}

template <typename T>
T *Vector4G<T>::Data()
{
    return &At(0);
}
template <typename T>
const T *Vector4G<T>::Data() const
{
    return &At(0);
}

template <typename T>
Vector4G<T> Vector4G<T>::Abs(const Vector4G<T> &v)
{
    return v.Abs();
}

template <typename T>
T Vector4G<T>::Dot(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    auto res = static_cast<T>(0);
    for (int i = 0; i < 4; ++i)
    {
        res += v1[i] * v2[i];
    }
    return res;
}

template <typename T>
T Vector4G<T>::Distance(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    return (v1 - v2).Length();
}

template <typename T>
T Vector4G<T>::SqDistance(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    return (v1 - v2).SqLength();
}

template <typename T>
Vector4G<T> Vector4G<T>::Max(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Max(v1[i], v2[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Min(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Min(v1[i], v2[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Floor(const Vector4G<T> &v1)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Floor(v1[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Ceil(const Vector4G<T> &v1)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Ceil(v1[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Round(const Vector4G<T> &v1)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = static_cast<T>(Math::Round(v1[i]));
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Clamp(const Vector4G<T> &v,
                               const Vector4G<T> &min,
                               const Vector4G<T> &max)
{
    auto res = v;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Clamp(res[i], min[i], max[i]);
    }
    return res;
}

template <typename T>
Vector4G<T> Vector4G<T>::Clamp2(const Vector4G<T> &v,
                                const Vector4G<T> &bound1,
                                const Vector4G<T> &bound2)
{
    auto res = v;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = Math::Clamp(res[i],
                             Math::Min(bound1[i], bound2[i]),
                             Math::Max(bound1[i], bound2[i]));
    }
    return res;
}

template <typename T>
Vector2G<T> Vector4G<T>::xy() const
{
    return Vector2G<T>(x, y);
}

template <typename T>
Vector3G<T> Vector4G<T>::xyz() const
{
    return Vector3G<T>(x, y, z);
}

template <typename T>
T Vector4G<T>::GetMin() const
{
    return Math::Min(x, Math::Min(y, Math::Min(z, w)));
}

template <typename T>
T Vector4G<T>::GetMax() const
{
    return Math::Max(x, Math::Max(y, Math::Max(z, w)));
}

template <typename T>
Axis Vector4G<T>::GetAxis() const
{
    return x == 1 ? Axis::HORIZONTAL : Axis::VERTICAL;
}
template <typename T>
const T &Vector4G<T>::GetAxis(Axis axis) const
{
    return (axis == Axis::HORIZONTAL) ? x : y;
}
template <typename T>
Vector4G<T> Vector4G<T>::FromAxis(Axis axis)
{
    return (axis == Axis::HORIZONTAL) ? Vector4G<T>::Right : Vector4G<T>::Up;
}

template <typename T>
T &Vector4G<T>::operator[](int i)
{
    return (reinterpret_cast<T *>(this))[i];
}

template <typename T>
const T &Vector4G<T>::operator[](int i) const
{
    return (reinterpret_cast<const T *>(this))[i];
}

/* Operators */

template <typename T>
bool operator==(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        if (lhs[i] != rhs[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator<(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        if (lhs[i] >= rhs[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator<=(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        if (lhs[i] > rhs[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool operator>(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    return (rhs < lhs);
}

template <typename T>
bool operator>=(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    return (rhs <= lhs);
}

template <typename T>
bool operator!=(const Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
Vector4G<T> operator+(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v1[i] + v2[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v1[i] * v2[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator*(const T &a, const Vector4G<T> &v)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = a * v[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator*(const Vector4G<T> &v, const T &a)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v[i] * a;
    }
    return res;
}

template <typename T>
Vector4G<T> operator/(const T &a, const Vector4G<T> &v)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = a / v[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator/(const Vector4G<T> &v, const T &a)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v[i] / a;
    }
    return res;
}

template <typename T>
Vector4G<T> operator/(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v1[i] / v2[i];
    }
    return res;
}

template <typename T>
Vector4G<T> &operator+=(Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator-=(Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator*=(Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] *= rhs[i];
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator/=(Vector4G<T> &lhs, const Vector4G<T> &rhs)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

template <typename T>
Vector4G<T> operator+(const T &a, const Vector4G<T> &v)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = a + v[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator+(const Vector4G<T> &v, const T &a)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v[i] + a;
    }
    return res;
}

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v1, const Vector4G<T> &v2)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v1[i] - v2[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator-(const T &a, const Vector4G<T> &v)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = a - v[i];
    }
    return res;
}

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v, const T &a)
{
    Vector4G<T> res;
    for (int i = 0; i < 4; ++i)
    {
        res[i] = v[i] - a;
    }
    return res;
}

template <typename T>
Vector4G<T> &operator+=(Vector4G<T> &lhs, const T &a)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] += a;
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator-=(Vector4G<T> &lhs, const T &a)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] -= a;
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator*=(Vector4G<T> &lhs, const T &a)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] *= a;
    }
    return lhs;
}

template <typename T>
Vector4G<T> &operator/=(Vector4G<T> &lhs, const T &a)
{
    for (int i = 0; i < 4; ++i)
    {
        lhs[i] /= a;
    }
    return lhs;
}

template <typename T>
Vector4G<T> operator-(const Vector4G<T> &v)
{
    return v * static_cast<T>(-1);
}

template <typename T>
const Vector4G<T> &Vector4G<T>::Up()
{
    static const auto v = Vector4G<T>(static_cast<T>(0),
                                      static_cast<T>(1),
                                      static_cast<T>(0),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Down()
{
    static const auto v = Vector4G<T>(static_cast<T>(0),
                                      static_cast<T>(-1),
                                      static_cast<T>(0),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Right()
{
    static const auto v = Vector4G<T>(static_cast<T>(1),
                                      static_cast<T>(0),
                                      static_cast<T>(0),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Left()
{
    static const auto v = Vector4G<T>(static_cast<T>(-1),
                                      static_cast<T>(0),
                                      static_cast<T>(0),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Zero()
{
    static const auto v = Vector4G<T>(static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::One()
{
    static const auto v = Vector4G<T>(static_cast<T>(1));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Forward()
{
    static const auto v = Vector4G<T>(static_cast<T>(0),
                                      static_cast<T>(0),
                                      static_cast<T>(-1),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Back()
{
    static const auto v = Vector4G<T>(static_cast<T>(0),
                                      static_cast<T>(0),
                                      static_cast<T>(1),
                                      static_cast<T>(0));
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::Infinity()
{
    static const auto v = Vector4G<T>(Math::Infinity<T>());
    return v;
}
template <typename T>
const Vector4G<T> &Vector4G<T>::NInfinity()
{
    static const auto v = Vector4G<T>(Math::NegativeInfinity<T>());
    return v;
}

}  // namespace Bang
