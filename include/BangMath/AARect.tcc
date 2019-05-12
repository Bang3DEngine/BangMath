#pragma once

#include "AARect.h"

namespace Bang
{

template <typename T>
AARectG<T>::AARectG(T minx, T miny, T maxx, T maxy)
{
    m_min = Vector2G<T>(Math::Min(minx, maxx), Math::Min(miny, maxy));
    m_max = Vector2G<T>(Math::Max(minx, maxx), Math::Max(miny, maxy));
}

template <typename T>
AARectG<T>::AARectG(const Vector2G<T> &p1, const Vector2G<T> &p2)
{
    m_min = Vector2G<T>::Min(p1, p2);
    m_max = Vector2G<T>::Max(p1, p2);
}

template <typename T>
template <class OtherT>
AARectG<T>::AARectG(const RectG<OtherT> &r)
{
    Vector2G<OtherT> p0, p1, opposedP0;
    r.GetPoints(&p0, &p1, &opposedP0);
    *this = AARectG(Vector2G<T>(p0), Vector2G<T>(opposedP0));
}


template <typename T>
template <typename U>
AARectG<T>::AARectG(const AARectG<U> &otherRect)
{
    SetMin(Vector2G<T>(otherRect.GetMin()));
    SetMax(Vector2G<T>(otherRect.GetMax()));
}

template <typename T>
void AARectG<T>::SetMin(const Vector2G<T> &minv)
{
    m_min = minv;
}

template <typename T>
void AARectG<T>::SetMax(const Vector2G<T> &maxv)
{
    m_max = maxv;
}

template <typename T>
bool AARectG<T>::IsValid() const
{
    return GetMin() < GetMax();
}

template <typename T>
void AARectG<T>::AddPoint(const Vector2G<T> &point)
{
    SetMin(Vector2G<T>::Min(GetMin(), point));
    SetMax(Vector2G<T>::Max(GetMax(), point));
}

template <typename T>
Vector2G<T> AARectG<T>::GetMinXMaxY() const
{
    return Vector2G<T>(GetMin().x, GetMax().y);
}

template <typename T>
Vector2G<T> AARectG<T>::GetMaxXMaxY() const
{
    return Vector2G<T>(GetMax().x, GetMax().y);
}

template <typename T>
Vector2G<T> AARectG<T>::GetMinXMinY() const
{
    return Vector2G<T>(GetMin().x, GetMin().y);
}

template <typename T>
Vector2G<T> AARectG<T>::GetMaxXMinY() const
{
    return Vector2G<T>(GetMax().x, GetMin().y);
}

template <typename T>
const Vector2G<T> &AARectG<T>::GetMin() const
{
    return m_min;
}

template <typename T>
const Vector2G<T> &AARectG<T>::GetMax() const
{
    return m_max;
}

template <typename T>
T AARectG<T>::GetWidth() const
{
    return (GetMax().x - GetMin().x);
}

template <typename T>
T AARectG<T>::GetHeight() const
{
    return (GetMax().y - GetMin().y);
}

template <typename T>
T AARectG<T>::GetArea() const
{
    return GetWidth() * GetHeight();
}

template <typename T>
Vector2G<T> AARectG<T>::GetSize() const
{
    return Vector2G<T>(GetWidth(), GetHeight());
}

template <typename T>
Vector2G<T> AARectG<T>::GetCenter() const
{
    return (GetMin() + GetMax()) / static_cast<T>(2);
}

template <typename T>
bool AARectG<T>::Contains(const Vector2G<T> &p) const
{
    return p.x >= GetMin().x && p.x < GetMax().x && p.y >= GetMin().y &&
           p.y < GetMax().y;
}

template <typename T>
AARectG<T> AARectG<T>::Union(const AARectG<T> &r1, const AARectG<T> &r2)
{
    return AARectG<T>(Math::Min(r1.GetMin().x, r2.GetMin().x),
                      Math::Min(r1.GetMin().y, r2.GetMin().y),
                      Math::Max(r1.GetMax().x, r2.GetMax().x),
                      Math::Max(r1.GetMax().y, r2.GetMax().y));
}

template <typename T>
template <typename Iterator>
AARectG<T> AARectG<T>::Union(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return AARectG<T>::Zero();
    }
    AARectG<T> unionRect = *begin;
    for (auto it = begin; it != end; ++it)
    {
        unionRect = AARectG<T>::Union(unionRect, *it);
    }
    return unionRect;
}

template <typename T>
AARectG<T> AARectG<T>::Intersection(const AARectG<T> &r1, const AARectG<T> &r2)
{
    T minx = Math::Max(r1.GetMin().x, r2.GetMin().x);
    T miny = Math::Max(r1.GetMin().y, r2.GetMin().y);
    T maxx = Math::Min(r1.GetMax().x, r2.GetMax().x);
    T maxy = Math::Min(r1.GetMax().y, r2.GetMax().y);

    if (minx > maxx || miny > maxy)
    {
        return AARectG<T>::Zero();
    }

    return AARectG<T>(minx, miny, maxx, maxy);
}

template <typename T>
template <typename Iterator>
AARectG<T> AARectG<T>::Intersection(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return AARectG<T>::Zero();
    }
    AARectG<T> intersectionRect = *begin;
    for (auto it = begin; it != end; ++it)
    {
        intersectionRect = AARectG<T>::Intersection(intersectionRect, *it);
    }
    return intersectionRect;
}

template <typename T>
template <typename Iterator>
AARectG<T> AARectG<T>::GetBoundingRectFromPositions(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return AARectG<T>::Zero();
    }

    Vector2G<T> minv = *begin, maxv = *begin;
    for (auto it = begin; it != end; ++it)
    {
        const Vector2G<T> &p = *it;
        minv = Vector2G<T>::Min(p, minv);
        maxv = Vector2G<T>::Max(p, maxv);
    }
    return AARectG<T>(minv, maxv);
}

template <typename T>
template <typename OtherT>
Vector2G<T> AARectG<T>::GetClosestPointInAARect(const Vector2G<T> &point) const
{
    Vector2G<T> closestPoint;
    closestPoint.x = Math::Clamp(point.x, GetMin().x, GetMax().x);
    closestPoint.y = Math::Clamp(point.y, GetMin().y, GetMax().y);
    return closestPoint;
}

template <typename T>
template <typename OtherT>
RectG<OtherT> AARectG<T>::ToRect() const
{
    return RectG<OtherT>(Vector2G<OtherT>(GetCenter()),
                         Vector2G<OtherT>::Right(),
                         static_cast<OtherT>(GetWidth() * 0.5),
                         static_cast<OtherT>(GetHeight() * 0.5));
}

template <typename T>
const AARectG<T> &AARectG<T>::NDCRect()
{
    static const AARectG<T> r = AARectG<T>(Vector2G<T>(static_cast<T>(-1)),
                                           Vector2G<T>(static_cast<T>(1)));
    return r;
}

template <typename T>
const AARectG<T> &AARectG<T>::Zero()
{
    static const AARectG<T> r = AARectG<T>(static_cast<T>(0),
                                           static_cast<T>(0),
                                           static_cast<T>(0),
                                           static_cast<T>(0));
    return r;
}

template <typename T>
bool operator==(const AARectG<T> &r1, const AARectG<T> &r2)
{
    return r1.GetMin() == r2.GetMin() && r1.GetMax() == r2.GetMax();
}

template <typename T>
bool operator!=(const AARectG<T> &r1, const AARectG<T> &r2)
{
    return !(r1 == r2);
}

template <typename T>
void operator*=(AARectG<T> &r, T a)
{
    r.m_min *= a;
    r.m_max *= a;
}

template <typename T>
void operator/=(AARectG<T> &r, T a)
{
    r.m_min /= a;
    r.m_max /= a;
}

template <typename T>
void operator*=(AARectG<T> &r, const Vector2G<T> &v)
{
    r.m_min *= v;
    r.m_max *= v;
}

template <typename T>
void operator/=(AARectG<T> &r, const Vector2G<T> &v)
{
    r.m_min /= v;
    r.m_max /= v;
}

template <typename T>
AARectG<T> operator*(const Matrix4G<T> &m, const AARectG<T> &r)
{
    return AARectG<T>((m * Vector4G<T>(r.GetMin(), 0, 1)).xy(),
                      (m * Vector4G<T>(r.GetMax(), 0, 1)).xy());
}

template <typename T>
AARectG<T> operator/(T a, const AARectG<T> &r)
{
    return AARectG<T>(a / r.GetMin(), a / r.GetMax());
}

template <typename T>
AARectG<T> operator/(const AARectG<T> &r, T a)
{
    return AARectG<T>(r.GetMin() / a, r.GetMax() / a);
}

template <typename T>
AARectG<T> operator*(T a, const AARectG<T> &r)
{
    return AARectG<T>(a * r.GetMin(), a * r.GetMax());
}

template <typename T>
AARectG<T> operator*(const AARectG<T> &r, T a)
{
    return a * r;
}

template <typename T>
AARectG<T> operator*(const Vector2G<T> &v, const AARectG<T> &r)
{
    return AARectG<T>(v * r.GetMin(), v * r.GetMax());
}

template <typename T>
AARectG<T> operator*(const AARectG<T> &r, const Vector2G<T> &v)
{
    return v * r;
}

template <typename T>
AARectG<T> operator/(const Vector2G<T> &v, const AARectG<T> &r)
{
    return AARectG<T>(v / r.GetMin(), v / v.GetMax());
}

template <typename T>
AARectG<T> operator/(const AARectG<T> &r, const Vector2G<T> &v)
{
    return AARectG<T>(r.GetMin() / v, r.GetMax() / v);
}

template <typename T>
AARectG<T> operator-(T a, const AARectG<T> &r)
{
    return Vector2G<T>(a) - r;
}

template <typename T>
AARectG<T> operator-(const AARectG<T> &r, T a)
{
    return r - Vector2G<T>(a);
}

template <typename T>
AARectG<T> operator-(const Vector2G<T> &v, const AARectG<T> &r)
{
    return AARectG<T>(v - r.GetMin(), v - r.GetMax());
}

template <typename T>
AARectG<T> operator-(const AARectG<T> &r, const Vector2G<T> &v)
{
    return AARectG<T>(r.GetMin() - v, r.GetMax() - v);
}

template <typename T>
void operator-=(AARectG<T> &r, const Vector2G<T> &v)
{
    r.SetMin(r.GetMin() - v);
    r.SetMax(r.GetMax() - v);
}

template <typename T>
AARectG<T> operator+(T a, const AARectG<T> &r)
{
    return Vector2G<T>(a) + r;
}

template <typename T>
AARectG<T> operator+(const AARectG<T> &r, T a)
{
    return Vector2G<T>(a) + r;
}

template <typename T>
AARectG<T> operator+(const Vector2G<T> &v, const AARectG<T> &r)
{
    AARectG<T> res = r;
    res += v;
    return res;
}

template <typename T>
AARectG<T> operator+(const AARectG<T> &r, const Vector2G<T> &v)
{
    return v + r;
}

template <typename T>
void operator+=(AARectG<T> &r, const Vector2G<T> &v)
{
    r.SetMin(r.GetMin() + v);
    r.SetMax(r.GetMax() + v);
}

BANG_MATH_DEFINE_USINGS(AARect)

}  // namespace Bang
