#include "BangMath/Triangle2D.h"

#include "BangMath/Assert.h"
#include "BangMath/Geometry.h"

using namespace Bang;

Triangle2D::Triangle2D(const Vector2G<T> &point0,
                       const Vector2G<T> &point1,
                       const Vector2G<T> &point2)
{
    SetPoint(0, point0);
    SetPoint(1, point1);
    SetPoint(2, point2);
}

void Triangle2D::SetPoint(int i, const Vector2G<T> &point)
{
    ASSERT(i >= 0 && i <= 2);
    m_points[i] = point;
}

float Triangle2D::GetArea() const
{
    const Vector2G<T> &p0 = GetPoint(0);
    const Vector2G<T> &p1 = GetPoint(1);
    const Vector2G<T> &p2 = GetPoint(2);
    return Math::Abs(p0.x * (p1.y - p2.y) + p1.x * (p2.y - p0.y) +
                     p2.x * (p0.y - p1.y)) /
           2.0f;
}

bool Triangle2D::Contains(const Vector2G<T> &point) const
{
    const Vector2G<T> &p0 = GetPoint(0);
    const Vector2G<T> &p1 = GetPoint(1);
    const Vector2G<T> &p2 = GetPoint(2);

    const GeometryG::Orientation triOri = GeometryG::GetOrientation(p0, p1, p2);
    const GeometryG::Orientation ori01 =
        GeometryG::GetOrientation(p0, p1, point);
    const GeometryG::Orientation ori12 =
        GeometryG::GetOrientation(p1, p2, point);
    const GeometryG::Orientation ori20 =
        GeometryG::GetOrientation(p2, p0, point);

    return (ori01 == triOri || ori01 == GeometryG::Orientation::ZERO) &&
           (ori12 == triOri || ori12 == GeometryG::Orientation::ZERO) &&
           (ori20 == triOri || ori20 == GeometryG::Orientation::ZERO);
}

Vector3G<T> Triangle2D::GetBarycentricCoordinates(
    const Vector2G<T> &point) const
{
    Vector2G<T> v0 = GetPoint(1) - GetPoint(0);
    Vector2G<T> v1 = GetPoint(2) - GetPoint(0);

    Vector2G<T> v2 = point - GetPoint(0);
    float d00 = Vector2G<T>::Dot(v0, v0);
    float d01 = Vector2G<T>::Dot(v0, v1);
    float d11 = Vector2G<T>::Dot(v1, v1);
    float d20 = Vector2G<T>::Dot(v2, v0);
    float d21 = Vector2G<T>::Dot(v2, v1);
    float denom = d00 * d11 - d01 * d01;

    Vector3G<T> baryCoords;
    baryCoords.y = (d11 * d20 - d01 * d21) / denom;
    baryCoords.z = (d00 * d21 - d01 * d20) / denom;
    baryCoords.x = 1.0f - baryCoords.y - baryCoords.z;
    return baryCoords;
}

Vector2G<T> Triangle2D::GetPoint(
    const Vector3G<T> &barycentricCoordinates) const
{
    Vector2G<T> point = GetPoint(0) * barycentricCoordinates[0] +
                        GetPoint(1) * barycentricCoordinates[1] +
                        GetPoint(2) * barycentricCoordinates[2];
    return point;
}

const Vector2G<T> &Triangle2D::GetPoint(int i) const
{
    ASSERT(i >= 0 && i <= 2);
    return GetPoints()[i];
}

const std::array<Vector2, 3> &Triangle2D::GetPoints() const
{
    return m_points;
}

Vector2G<T> &Triangle2D::operator[](std::size_t i)
{
    return m_points[i];
}

const Vector2G<T> &Triangle2D::operator[](std::size_t i) const
{
    return GetPoints()[i];
}
