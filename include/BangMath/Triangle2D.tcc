#include "BangMath/Triangle2D.h"

#include <cassert>
#include "BangMath/Geometry.h"
#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
Triangle2DG<T>::Triangle2DG(const Vector2G<T> &point0,
                            const Vector2G<T> &point1,
                            const Vector2G<T> &point2)
{
    SetPoint(0, point0);
    SetPoint(1, point1);
    SetPoint(2, point2);
}

template <typename T>
void Triangle2DG<T>::SetPoint(int i, const Vector2G<T> &point)
{
    assert(i >= 0 && i <= 2);
    m_points[i] = point;
}

template <typename T>
T Triangle2DG<T>::GetArea() const
{
    const auto &p0 = GetPoint(0);
    const auto &p1 = GetPoint(1);
    const auto &p2 = GetPoint(2);
    return Math::Abs(p0.x * (p1.y - p2.y) + p1.x * (p2.y - p0.y) +
                     p2.x * (p0.y - p1.y)) /
           T(2.0);
}

template <typename T>
bool Triangle2DG<T>::Contains(const Vector2G<T> &point) const
{
    const auto &p0 = GetPoint(0);
    const auto &p1 = GetPoint(1);
    const auto &p2 = GetPoint(2);

    const auto triOri = Geometry::GetOrientation(p0, p1, p2);
    const auto ori01 = GetOrientation(p0, p1, point);
    const auto ori12 = GetOrientation(p1, p2, point);
    const auto ori20 = GetOrientation(p2, p0, point);

    return (ori01 == triOri || ori01 == Orientation::ZERO) &&
           (ori12 == triOri || ori12 == Orientation::ZERO) &&
           (ori20 == triOri || ori20 == Orientation::ZERO);
}

template <typename T>
Vector3G<T> Triangle2DG<T>::GetBarycentricCoordinates(
    const Vector2G<T> &point) const
{
    const auto v0 = GetPoint(1) - GetPoint(0);
    const auto v1 = GetPoint(2) - GetPoint(0);

    const auto v2 = point - GetPoint(0);
    const auto d00 = Vector2G<T>::Dot(v0, v0);
    const auto d01 = Vector2G<T>::Dot(v0, v1);
    const auto d11 = Vector2G<T>::Dot(v1, v1);
    const auto d20 = Vector2G<T>::Dot(v2, v0);
    const auto d21 = Vector2G<T>::Dot(v2, v1);
    const auto denom = d00 * d11 - d01 * d01;

    Vector3G<T> baryCoords;
    baryCoords.y = (d11 * d20 - d01 * d21) / denom;
    baryCoords.z = (d00 * d21 - d01 * d20) / denom;
    baryCoords.x = 1.0f - baryCoords.y - baryCoords.z;
    return baryCoords;
}

template <typename T>
Vector2G<T> Triangle2DG<T>::GetPoint(
    const Vector3G<T> &barycentricCoordinates) const
{
    const auto point = GetPoint(0) * barycentricCoordinates[0] +
                       GetPoint(1) * barycentricCoordinates[1] +
                       GetPoint(2) * barycentricCoordinates[2];
    return point;
}

template <typename T>
const Vector2G<T> &Triangle2DG<T>::GetPoint(int i) const
{
    assert(i >= 0 && i <= 2);
    return GetPoints()[i];
}

template <typename T>
const std::array<Vector2G<T>, 3> &Triangle2DG<T>::GetPoints() const
{
    return m_points;
}

template <typename T>
Vector2G<T> &Triangle2DG<T>::operator[](std::size_t i)
{
    return m_points[i];
}

template <typename T>
const Vector2G<T> &Triangle2DG<T>::operator[](std::size_t i) const
{
    return GetPoints()[i];
}
}
