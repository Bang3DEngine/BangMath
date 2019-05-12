#pragma once
#include "BangMath/AABox.h"

#include <vector>

#include "BangMath/Math.h"
#include "BangMath/Matrix4.tcc"
#include "BangMath/Sphere.h"
#include "BangMath/Vector4.h"

namespace Bang
{
template <typename T>
const AABoxG<T> &AABoxG<T>::Empty()
{
    static AABoxG<T> b = AABoxG<T>();
    return b;
}

template <typename T>
AABoxG<T>::AABoxG()
{
}

template <typename T>
AABoxG<T>::AABoxG(T minx, T maxx, T miny, T maxy, T minz, T maxz)
    : AABoxG<T>(Vector3G<T>(minx, miny, minz), Vector3G<T>(maxx, maxy, maxz))
{
}

template <typename T>
AABoxG<T>::AABoxG(const Vector3G<T> &p)
{
    SetMin(p);
    SetMax(p);
}

template <typename T>
AABoxG<T>::AABoxG(const Vector3G<T> &p1, const Vector3G<T> &p2)
{
    SetMin(Vector3G<T>::Min(p1, p2));
    SetMax(Vector3G<T>::Max(p1, p2));
}

template <typename T>
AABoxG<T>::AABoxG(const AABoxG<T> &b)
{
    // Dont use setters to avoid initialized check in case b is not initialized
    SetMin(b.m_minv);
    SetMax(b.m_maxv);
}

template <typename T>
void AABoxG<T>::SetMin(const Vector3G<T> &bMin)
{
    m_minv = bMin;
}

template <typename T>
void AABoxG<T>::SetMax(const Vector3G<T> &bMax)
{
    m_maxv = bMax;
}

template <typename T>
const Vector3G<T> &AABoxG<T>::GetMin() const
{
    return m_minv;
}

template <typename T>
const Vector3G<T> &AABoxG<T>::GetMax() const
{
    return m_maxv;
}

template <typename T>
Vector3G<T> AABoxG<T>::GetDiagonal() const
{
    return GetMax() - GetMin();
}

template <typename T>
T AABoxG<T>::GetWidth() const
{
    return (GetMax().x - GetMin().x);
}

template <typename T>
T AABoxG<T>::GetHeight() const
{
    return (GetMax().y - GetMin().y);
}

template <typename T>
T AABoxG<T>::GetDepth() const
{
    return (GetMax().z - GetMin().z);
}

template <typename T>
Vector3G<T> AABoxG<T>::GetCenter() const
{
    return (GetMin() + GetMax()) / 2.0f;
}

template <typename T>
Vector3G<T> AABoxG<T>::GetSize() const
{
    return Vector3G<T>(GetWidth(), GetHeight(), GetDepth());
}

template <typename T>
T AABoxG<T>::GetArea() const
{
    T w = GetWidth();
    T h = GetHeight();
    T d = GetDepth();
    return w * h * 2 + w * d * 2 + h * d * 2;
}

template <typename T>
T AABoxG<T>::GetVolume() const
{
    T w = GetWidth();
    T h = GetHeight();
    T d = GetDepth();
    return w * h * d;
}

template <typename T>
Vector3G<T> AABoxG<T>::GetExtents() const
{
    return (GetMax() - GetMin()) / 2.0f;
}

template <typename T>
Vector3G<T> AABoxG<T>::GetClosestPointInAABB(const Vector3G<T> &point) const
{
    Vector3G<T> closestPoint;
    closestPoint.x = Math::Clamp(point.x, GetMin().x, GetMax().x);
    closestPoint.y = Math::Clamp(point.y, GetMin().y, GetMax().y);
    closestPoint.z = Math::Clamp(point.z, GetMin().z, GetMax().z);
    return closestPoint;
}

template <typename T>
bool AABoxG<T>::CheckCollision(const SphereG<T> &sphere,
                               Vector3G<T> *point,
                               Vector3G<T> *normal) const
{
    Vector3G<T> closestPointToAABox = GetClosestPointInAABB(sphere.GetCenter());

    T sRadius = sphere.GetRadius();
    const Vector3G<T> &sCenter = sphere.GetCenter();
    T dCenterClosest = Vector3G<T>::Distance(closestPointToAABox, sCenter);
    bool collides = (dCenterClosest <= sRadius * sRadius);
    if (collides)
    {
        if (point)
        {
            *point = closestPointToAABox;
        }

        if (normal)
        {
            *normal = (closestPointToAABox - sCenter).Normalized();
        }
    }
    return collides;
}

template <typename T>
bool AABoxG<T>::CheckCollision(const AABoxG<T> &aaBox) const
{
    std::vector<Vector3G<T>> points = aaBox.GetPoints();
    return Contains(points[0]) || Contains(points[1]) || Contains(points[2]) ||
           Contains(points[3]) || Contains(points[4]) || Contains(points[5]) ||
           Contains(points[6]) || Contains(points[7]);
}

template <typename T>
bool AABoxG<T>::Contains(const Vector3G<T> &point) const
{
    return point >= GetMin() && point <= GetMax();
}

template <typename T>
bool AABoxG<T>::Overlap(const AABoxG<T> &aaBox) const
{
    return (GetMin().x <= aaBox.GetMax().x && GetMax().x >= GetMin().x &&
            GetMin().y <= aaBox.GetMax().y && GetMax().y >= GetMin().y &&
            GetMin().z <= aaBox.GetMax().z && GetMax().z >= GetMin().z);
}

template <typename T>
void AABoxG<T>::AddPoint(const Vector3G<T> &point)
{
    SetMin(Vector3G<T>::Min(GetMin(), point));
    SetMax(Vector3G<T>::Max(GetMax(), point));
}

template <typename T>
AABoxG<T> AABoxG<T>::Union(const AABoxG<T> &b1, const AABoxG<T> &b2)
{
    if (b1 == AABoxG<T>::Empty())
    {
        return b2;
    }

    if (b2 == AABoxG<T>::Empty())
    {
        return b1;
    }

    AABoxG<T> unionBox = AABoxG(Vector3G<T>::Min(b1.GetMin(), b2.GetMin()),
                                Vector3G<T>::Max(b1.GetMax(), b2.GetMax()));
    return unionBox;
}

template <typename T>
void AABoxG<T>::CreateFromPositions(const std::vector<Vector3G<T>> &positions)
{
    *this = AABoxG<T>::Empty();
    for (const Vector3G<T> &v : positions)
    {
        AddPoint(v);
    }
}

template <typename T>
AABoxG<T> AABoxG<T>::FromPointAndSize(const Vector3G<T> &point,
                                      const Vector3G<T> &size)
{
    return AABoxG(point, point + size);
}

template <typename T>
AABoxG<T> AABoxG<T>::FromSphere(const SphereG<T> &sphere)
{
    AABoxG<T> b(sphere.GetPoints().front());
    b.CreateFromPositions(sphere.GetPoints());
    return b;
}

template <typename T>
std::array<Vector3G<T>, 8> AABoxG<T>::GetPointsC() const
{
    const Vector3G<T> center = GetCenter();
    const Vector3G<T> extents = GetExtents();
    const Vector3G<T> p1 = center + extents * Vector3G<T>(-1, -1, -1);
    const Vector3G<T> p2 = center + extents * Vector3G<T>(-1, -1, 1);
    const Vector3G<T> p3 = center + extents * Vector3G<T>(-1, 1, -1);
    const Vector3G<T> p4 = center + extents * Vector3G<T>(-1, 1, 1);
    const Vector3G<T> p5 = center + extents * Vector3G<T>(1, -1, -1);
    const Vector3G<T> p6 = center + extents * Vector3G<T>(1, -1, 1);
    const Vector3G<T> p7 = center + extents * Vector3G<T>(1, 1, -1);
    const Vector3G<T> p8 = center + extents * Vector3G<T>(1, 1, 1);
    return {p1, p2, p3, p4, p5, p6, p7, p8};
}

template <typename T>
std::vector<Vector3G<T>> AABoxG<T>::GetPoints() const
{
    std::vector<Vector3G<T>> pointsArray;
    const auto points = GetPointsC();
    for (const Vector3G<T> &point : points)
    {
        pointsArray.push_back(point);
    }
    return pointsArray;
}

template <typename T>
QuadG<T> AABoxG<T>::GetQuad(Axis3D axis, bool sign) const
{
    const Vector3G<T> &ctr = GetCenter();
    const Vector3G<T> &ext = GetExtents();
    int xs0, xs1, xs2, xs3, ys0, ys1, ys2, ys3, zs0, zs1, zs2, zs3;
    switch (axis)  // Given in CCW order out facing the AABoxG
    {
        case Axis3D::X:
            xs0 = (sign ? 1 : -1);
            xs1 = (sign ? 1 : -1);
            xs2 = (sign ? 1 : -1);
            xs3 = (sign ? 1 : -1);
            ys0 = (sign ? -1 : -1);
            ys1 = (sign ? -1 : -1);
            ys2 = (sign ? 1 : 1);
            ys3 = (sign ? 1 : 1);
            zs0 = (sign ? 1 : -1);
            zs1 = (sign ? -1 : 1);
            zs2 = (sign ? -1 : 1);
            zs3 = (sign ? 1 : -1);
            break;

        case Axis3D::Y:
            xs0 = (sign ? -1 : -1);
            xs1 = (sign ? 1 : -1);
            xs2 = (sign ? 1 : 1);
            xs3 = (sign ? -1 : 1);
            ys0 = (sign ? 1 : -1);
            ys1 = (sign ? 1 : -1);
            ys2 = (sign ? 1 : -1);
            ys3 = (sign ? 1 : -1);
            zs0 = (sign ? 1 : 1);
            zs1 = (sign ? 1 : -1);
            zs2 = (sign ? -1 : -1);
            zs3 = (sign ? -1 : 1);
            break;

        default:
        case Axis3D::Z:
            xs0 = (sign ? -1 : -1);
            xs1 = (sign ? 1 : -1);
            xs2 = (sign ? 1 : 1);
            xs3 = (sign ? -1 : 1);
            ys0 = (sign ? -1 : -1);
            ys1 = (sign ? -1 : 1);
            ys2 = (sign ? 1 : 1);
            ys3 = (sign ? 1 : -1);
            zs0 = (sign ? 1 : -1);
            zs1 = (sign ? 1 : -1);
            zs2 = (sign ? 1 : -1);
            zs3 = (sign ? 1 : -1);
            break;
    }
    return QuadG<T>(ctr + Vector3G<T>(xs0 * ext.x, ys0 * ext.y, zs0 * ext.z),
                    ctr + Vector3G<T>(xs1 * ext.x, ys1 * ext.y, zs1 * ext.z),
                    ctr + Vector3G<T>(xs2 * ext.x, ys2 * ext.y, zs2 * ext.z),
                    ctr + Vector3G<T>(xs3 * ext.x, ys3 * ext.y, zs3 * ext.z));
}

template <typename T>
QuadG<T> AABoxG<T>::GetRightQuad() const
{
    return GetQuad(Axis3D::X, true);
}

template <typename T>
QuadG<T> AABoxG<T>::GetLeftQuad() const
{
    return GetQuad(Axis3D::X, false);
}

template <typename T>
QuadG<T> AABoxG<T>::GetTopQuad() const
{
    return GetQuad(Axis3D::Y, true);
}

template <typename T>
QuadG<T> AABoxG<T>::GetBotQuad() const
{
    return GetQuad(Axis3D::Y, false);
}

template <typename T>
QuadG<T> AABoxG<T>::GetFrontQuad() const
{
    return GetQuad(Axis3D::Z, true);
}

template <typename T>
QuadG<T> AABoxG<T>::GetBackQuad() const
{
    return GetQuad(Axis3D::Z, false);
}

template <typename T>
std::array<QuadG<T>, 6> AABoxG<T>::GetQuads() const
{
    const std::array<QuadG<T>, 6> aaBoxQuads = {{GetBotQuad(),
                                                 GetTopQuad(),
                                                 GetLeftQuad(),
                                                 GetRightQuad(),
                                                 GetFrontQuad(),
                                                 GetBackQuad()}};
    return aaBoxQuads;
}

template <typename T>
AABoxG<T> operator*(const Matrix4G<T> &m, const AABoxG<T> &b)
{
    std::vector<Vector3G<T>> points = b.GetPoints();
    for (uint i = 0; i < 8; ++i)
    {
        points[i] = m.TransformedPoint(points[i]);
    }

    AABoxG<T> bbox;
    bbox.CreateFromPositions(points);
    return bbox;
}

template <typename T>
bool operator==(const AABoxG<T> &b1, const AABoxG<T> &b2)
{
    return (b1.GetMin() == b2.GetMin()) && (b1.GetMax() == b2.GetMax());
}

template <typename T>
bool operator!=(const AABoxG<T> &b1, const AABoxG<T> &b2)
{
    return !(b1 == b2);
}
}  // namespace Bang
