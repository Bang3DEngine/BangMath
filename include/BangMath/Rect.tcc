#pragma once
#include "BangMath/Rect.h"

namespace Bang
{
template <typename T>
const RectG<T> &RectG<T>::NDCRect()
{
    static const auto r = RectG<T>(Vector2G<T>(0), Vector2G<T>(1, 0), 1, 1);
    return r;
}

template <typename T>
const RectG<T> &RectG<T>::Zero()
{
    static const auto r = RectG<T>(Vector2G<T>(0), Vector2G<T>(0), 0, 0);
    return r;
}

template <typename T>
RectG<T>::RectG()
{
}

template <typename T>
RectG<T>::RectG(const Vector2G<T> &center,
                const Vector2G<T> &axis0,
                const T &halfSizeAxis0,
                const T &halfSizeAxis1)
{
    SetCenter(center);
    SetAxis(axis0);
    SetHalfSizes(halfSizeAxis0, halfSizeAxis1);
}

template <typename T>
template <typename OtherT>
RectG<T>::RectG(const RectG<OtherT> &r)
{
    SetCenter(Vector2G<T>(r.GetCenter()));
    SetAxis(Vector2G<T>(r.GetAxis(0)));
    SetHalfSizes(static_cast<T>(r.GetHalfSize(0)),
                 static_cast<T>(r.GetHalfSize(1)));
}

template <typename T>
RectG<T>::RectG(const Vector2G<T> &center,
                const Vector2G<T> &axis0,
                const Vector2G<T> &halfSizeAxis)
    : RectG(center, axis0, halfSizeAxis.x, halfSizeAxis.y)
{
}

template <typename T>
void RectG<T>::SetCenter(const Vector2G<T> &center)
{
    m_center = center;
}

template <typename T>
void RectG<T>::SetAxis(const Vector2G<T> &axis0)
{
    m_axis0 = axis0;
    if (m_axis0.SqLength() != 1.0f)
    {
        m_axis0 = m_axis0.NormalizedSafe();
    }
}

template <typename T>
void RectG<T>::SetHalfSize(int i, const T &halfSize)
{
    if (i == 0)
    {
        m_halfSizeAxis0 = halfSize;
    }
    else if (i == 1)
    {
        m_halfSizeAxis1 = halfSize;
    }
}

template <typename T>
void RectG<T>::SetHalfSizes(const T &halfSizeAxis0, const T &halfSizeAxis1)
{
    SetHalfSize(0, halfSizeAxis0);
    SetHalfSize(1, halfSizeAxis1);
}

template <typename T>
const Vector2G<T> &RectG<T>::GetCenter() const
{
    return m_center;
}

template <typename T>
Vector2G<T> RectG<T>::GetAxis(int i) const
{
    if (i == 0)
    {
        return m_axis0;
    }
    return m_axis0.Perpendicular();
}

template <typename T>
T RectG<T>::GetHalfSize(int i) const
{
    if (i == 0)
    {
        return m_halfSizeAxis0;
    }
    return m_halfSizeAxis1;
}

template <typename T>
Vector2G<T> RectG<T>::GetHalfExtent(int i) const
{
    return GetAxis(i) * GetHalfSize(i);
}

template <typename T>
Vector2G<T> RectG<T>::GetHalfSize() const
{
    return Vector2G<T>(GetHalfSize(0), GetHalfSize(1));
}

template <typename T>
Vector2G<T> RectG<T>::GetSize() const
{
    return GetHalfSize() * T(2);
}

template <typename T>
bool RectG<T>::Contains(const Vector2G<T> &point) const
{
    Vector2G<T> a, b, c, d;
    GetPoints(&a, &b, &c, &d);

    const auto e = (b - a);
    const auto f = (d - a);
    if ((point.x - a.x) * e.x + (point.y - a.y) * e.y < 0.0)
    {
        return false;
    }
    if ((point.x - b.x) * e.x + (point.y - b.y) * e.y > 0.0)
    {
        return false;
    }
    if ((point.x - a.x) * f.x + (point.y - a.y) * f.y < 0.0)
    {
        return false;
    }
    if ((point.x - d.x) * f.x + (point.y - d.y) * f.y > 0.0)
    {
        return false;
    }

    return true;
}

template <typename T>
Vector2G<T> RectG<T>::GetLeftBot() const
{
    return GetCenter() - GetHalfExtent(0) - GetHalfExtent(1);
}

template <typename T>
Vector2G<T> RectG<T>::GetRightBot() const
{
    return GetCenter() + GetHalfExtent(0) - GetHalfExtent(1);
}

template <typename T>
Vector2G<T> RectG<T>::GetLeftTop() const
{
    return GetCenter() - GetHalfExtent(0) + GetHalfExtent(1);
}

template <typename T>
Vector2G<T> RectG<T>::GetRightTop() const
{
    return GetCenter() + GetHalfExtent(0) + GetHalfExtent(1);
}

template <typename T>
void RectG<T>::GetPoints(Vector2G<T> *p0,
                         Vector2G<T> *p1,
                         Vector2G<T> *opposedP0) const
{
    *p0 = GetLeftBot();
    *p1 = GetRightBot();
    *opposedP0 = GetRightTop();
}

template <typename T>
void RectG<T>::GetPoints(Vector2G<T> *p0,
                         Vector2G<T> *p1,
                         Vector2G<T> *opposedP0,
                         Vector2G<T> *opposedP1) const
{
    GetPoints(p0, p1, opposedP0);
    *opposedP1 = GetLeftTop();
}

template <typename T>
RectPointsG<T> RectG<T>::GetPoints() const
{
    Vector2G<T> p0, p1, p2, p3;
    GetPoints(&p0, &p1, &p2, &p3);
    return {{p0, p1, p2, p3}};
}

template <typename T>
bool operator==(const RectG<T> &r1, const RectG<T> &r2)
{
    return r1.GetCenter() == r2.GetCenter() && r1.GetAxis0() == r2.GetAxis0() &&
           r1.GetHalfSize() == r2.GetHalfSize();
}

template <typename T>
bool operator!=(const RectG<T> &r1, const RectG<T> &r2)
{
    return !(r1 == r2);
}

template <typename T>
void operator*=(RectG<T> &r, T a)
{
    r.m_center *= a;
    r.m_halfSize0 *= a;
    r.m_halfSize1 *= a;
}

template <typename T>
void operator/=(RectG<T> &r, T a)
{
    r.m_center /= a;
    r.m_halfSize0 /= a;
    r.m_halfSize1 /= a;
}

template <typename T>
void operator*=(RectG<T> &r, const Vector2G<T> &v)
{
    r.m_center *= v;
    r.m_halfSize0 *= v[0];
    r.m_halfSize1 *= v[1];
}

template <typename T>
void operator/=(RectG<T> &r, const Vector2G<T> &v)
{
    r.m_center /= v;
    r.m_halfSize0 /= v[0];
    r.m_halfSize1 /= v[1];
}

template <typename T>
RectG<T> operator*(const Matrix4G<T> &m, const RectG<T> &r)
{
    return RectG<T>((m * Vector4G<T>(r.GetCenter(), 0, 1)).xy(),
                    (m * Vector4G<T>(r.GetAxis(0), 0, 0)).xy(),
                    (m * Vector4G<T>(r.GetHalfExtent(0), 0, 0)).xy().Length(),
                    (m * Vector4G<T>(r.GetHalfExtent(1), 0, 0)).xy().Length());
}

template <typename T>
RectG<T> operator/(T a, const RectG<T> &r)
{
    return RectG<T>(a / r.GetCenter(),
                    r.GetAxis(0),
                    a / r.GetHalfSize(0),
                    a / r.GetHalfSize(1));
}

template <typename T>
RectG<T> operator/(const RectG<T> &r, T a)
{
    return RectG<T>(r.GetCenter() / a,
                    r.GetAxis(0),
                    r.GetHalfSize(0) / a,
                    r.GetHalfSize(1) / a);
}

template <typename T>
RectG<T> operator*(T a, const RectG<T> &r)
{
    return RectG<T>(a * r.GetCenter(),
                    r.GetAxis(0),
                    a * r.GetHalfSize(0),
                    a * r.GetHalfSize(1));
}

template <typename T>
RectG<T> operator*(const RectG<T> &r, T a)
{
    return a * r;
}

template <typename T>
RectG<T> operator*(const Vector2G<T> &v, const RectG<T> &r)
{
    return RectG<T>(v * r.GetCenter(),
                    r.GetAxis(0),
                    v[0] * r.GetHalfSize(0),
                    v[1] * r.GetHalfSize(1));
}

template <typename T>
RectG<T> operator*(const RectG<T> &r, const Vector2G<T> &v)
{
    return v * r;
}

template <typename T>
RectG<T> operator/(const Vector2G<T> &v, const RectG<T> &r)
{
    return RectG<T>(v / r.GetCenter(),
                    r.GetAxis(0),
                    v[0] / r.GetHalfSize(0),
                    v[1] / r.GetHalfSize(1));
}

template <typename T>
RectG<T> operator/(const RectG<T> &r, const Vector2G<T> &v)
{
    return RectG<T>(r.GetCenter() / v,
                    r.GetAxis(0),
                    r.GetHalfSize(0) / v[0],
                    r.GetHalfSize(1) / v[1]);
}

template <typename T>
RectG<T> operator-(T a, const RectG<T> &r)
{
    return Vector2G<T>(a) - r;
}

template <typename T>
RectG<T> operator-(const RectG<T> &r, T a)
{
    return r - Vector2G<T>(a);
}

template <typename T>
RectG<T> operator-(const Vector2G<T> &v, const RectG<T> &r)
{
    return RectG<T>(v - r.GetCenter(),
                    r.GetAxis(0),
                    v[0] - r.GetHalfSize(0),
                    v[1] - r.GetHalfSize(1));
}

template <typename T>
RectG<T> operator-(const RectG<T> &r, const Vector2G<T> &v)
{
    return RectG<T>(r.GetCenter() - v,
                    r.GetAxis(0),
                    r.GetHalfSize(0) - v[0],
                    r.GetHalfSize(1) - v[1]);
}

template <typename T>
void operator-=(RectG<T> &r, const Vector2G<T> &v)
{
    r = r - v;
}

template <typename T>
RectG<T> operator+(T a, const RectG<T> &r)
{
    return Vector2G<T>(a) + r;
}

template <typename T>
RectG<T> operator+(const RectG<T> &r, T a)
{
    return Vector2G<T>(a) + r;
}

template <typename T>
RectG<T> operator+(const Vector2G<T> &v, const RectG<T> &r)
{
    auto res = r;
    res += v;
    return res;
}

template <typename T>
RectG<T> operator+(const RectG<T> &r, const Vector2G<T> &v)
{
    return v + r;
}

template <typename T>
void operator+=(RectG<T> &r, const Vector2G<T> &v)
{
    r = r + v;
}
}
