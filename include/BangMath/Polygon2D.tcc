#include "BangMath/Polygon2D.h"

#include <cassert>

#include "BangMath/Geometry.h"

namespace Bang
{
template <typename T>
void Polygon2DG<T>::AddPoint(const Vector2G<T> &p)
{
    m_points.push_back(p);
}

template <typename T>
void Polygon2DG<T>::SetPoint(int i, const Vector2G<T> &p)
{
    assert(i >= 0 && i < static_cast<int>(GetPoints().size()));
    m_points[i] = p;
}

template <typename T>
bool Polygon2DG<T>::Contains(const Vector2G<T> &p)
{
    assert(GetPoints().size() >= 3u);

    auto minPoint = GetPoint(0);
    auto maxPoint = GetPoint(0);
    for (const Vector2G<T> &point : GetPoints())
    {
        minPoint = Vector2G<T>::Min(minPoint, point);
        maxPoint = Vector2G<T>::Max(maxPoint, point);
    }

    const auto VeryFar = Vector2G<T>::Distance(minPoint, maxPoint) * 10;

    auto intersectionCount = 0;
    const auto testRay = RayG<T>(p, p + Vector2G<T>(VeryFar));
    for (uint i = 0; i < GetPoints().size(); ++i)
    {
        const auto segment = Segment2DG<T>(GetPoint(i),
                           GetPoint((i + 1) % GetPoints().size()));

        bool intersected;
        Vector2G<T> intersPoint;
        Geometry::IntersectRay2DSegment2D(
            testRay, segment, &intersected, &intersPoint);
        intersectionCount += (intersected ? 1 : 0);
    }
    return (intersectionCount % 2) == 1;
}

template <typename T>
const Vector2G<T> &Polygon2DG<T>::GetPoint(int i) const
{
    assert(i >= 0 && i < static_cast<int>(GetPoints().size()));
    return m_points[i];
}

template <typename T>
const std::vector<Vector2G<T>> &Polygon2DG<T>::GetPoints() const
{
    return m_points;
}
}
