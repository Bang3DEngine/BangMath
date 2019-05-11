#include "BangMath/Polygon.h"

#include "BangMath/Array.tcc"
#include "BangMath/Assert.h"
#include "BangMath/Plane.h"
#include "BangMath/Polygon2D.h"
#include "BangMath/Triangle.h"
#include "BangMath/Vector2.h"

using namespace Bang;

void Polygon::AddPoint(const Vector3G<T> &p)
{
    m_points.PushBack(p);
}

void Polygon::AddPoints(const Array<Vector3> &points)
{
    for (const Vector3G<T> &p : points)
    {
        AddPoint(p);
    }
}

void Polygon::SetPoint(int i, const Vector3G<T> &p)
{
    ASSERT(i >= 0 && i < SCAST<int>(GetPoints().Size()));
    m_points[i] = p;
}

Plane Polygon::GetPlane() const
{
    ASSERT(GetPoints().Size() >= 3u);
    return Triangle(GetPoint(0), GetPoint(1), GetPoint(2)).GetPlane();
}

Vector3G<T> Polygon::GetNormal() const
{
    ASSERT(GetPoints().Size() >= 3);
    return Triangle(GetPoint(0), GetPoint(1), GetPoint(2)).GetNormal();
}

Polygon2D Polygon::ProjectedOnAxis(Axis3D axis) const
{
    Polygon2D projectedPoly;
    for (uint i = 0; i < GetPoints().Size(); ++i)
    {
        Vector3G<T> p = GetPoint(i);
        Vector2G<T> projP = p.ProjectedOnAxis(axis);
        projectedPoly.AddPoint(projP);
    }
    return projectedPoly;
}

const Vector3G<T> &Polygon::GetPoint(int i) const
{
    ASSERT(i >= 0 && i < SCAST<int>(GetPoints().Size()));
    return GetPoints()[i];
}

const Array<Vector3> &Polygon::GetPoints() const
{
    return m_points;
}

Vector3G<T> &Polygon::operator[](std::size_t i)
{
    return m_points[i];
}

const Vector3G<T> &Polygon::operator[](std::size_t i) const
{
    return GetPoint(SCAST<int>(i));
}
