#include "BangMath/Polygon.h"

#include <cassert>

namespace Bang
{
template <typename T>
void PolygonG<T>::AddPoint(const Vector3G<T> &p)
{
    m_points.push_back(p);
}

template <typename T>
void PolygonG<T>::AddPoints(const std::vector<Vector3G<T>> &points)
{
    for (const Vector3G<T> &p : points)
    {
        AddPoint(p);
    }
}

template <typename T>
void PolygonG<T>::SetPoint(int i, const Vector3G<T> &p)
{
    assert(i >= 0 && i < static_cast<int>(GetPoints().size()));
    m_points[i] = p;
}

template <typename T>
PlaneG<T> PolygonG<T>::GetPlane() const
{
    assert(GetPoints().size() >= 3u);
    return TriangleG<T>(GetPoint(0), GetPoint(1), GetPoint(2)).GetPlane();
}

template <typename T>
Vector3G<T> PolygonG<T>::GetNormal() const
{
    assert(GetPoints().size() >= 3);
    return TriangleG<T>(GetPoint(0), GetPoint(1), GetPoint(2)).GetNormal();
}

template <typename T>
Polygon2DG<T> PolygonG<T>::ProjectedOnAxis(Axis3D axis) const
{
    Polygon2DG<T> projectedPoly;
    for (int i = 0; i < GetPoints().size(); ++i)
    {
        const auto p = GetPoint(i);
        const auto projP = p.ProjectedOnAxis(axis);
        projectedPoly.AddPoint(projP);
    }
    return projectedPoly;
}

template <typename T>
const Vector3G<T> &PolygonG<T>::GetPoint(int i) const
{
    assert(i >= 0 && i < static_cast<int>(GetPoints().size()));
    return GetPoints()[i];
}

template <typename T>
const std::vector<Vector3G<T>> &PolygonG<T>::GetPoints() const
{
    return m_points;
}

template <typename T>
Vector3G<T> &PolygonG<T>::operator[](std::size_t i)
{
    return m_points[i];
}

template <typename T>
const Vector3G<T> &PolygonG<T>::operator[](std::size_t i) const
{
    return GetPoint(static_cast<int>(i));
}
}
