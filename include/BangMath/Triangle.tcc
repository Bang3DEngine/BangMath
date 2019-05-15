#include "BangMath/Triangle.h"

#include <cassert>

#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
TriangleG<T>::TriangleG(const Vector3G<T> &point0,
                        const Vector3G<T> &point1,
                        const Vector3G<T> &point2)
{
    SetPoint(0, point0);
    SetPoint(1, point1);
    SetPoint(2, point2);
}

template <typename T>
void TriangleG<T>::SetPoint(int i, const Vector3G<T> &point)
{
    (*this)[i] = point;
}

template <typename T>
T TriangleG<T>::GetArea() const
{
    const auto &p0 = GetPoint(0);
    const auto &p1 = GetPoint(1);
    const auto &p2 = GetPoint(2);
    const auto p01 = (p1 - p0);
    const auto p02 = (p2 - p0);
    const auto cross = Vector3G<T>::Cross(p01, p02);
    return cross.Length() / 2.0f;
}

template <typename T>
PlaneG<T> TriangleG<T>::GetPlane() const
{
    return PlaneG<T>(GetPoint(0), GetNormal());
}

template <typename T>
Vector3G<T> TriangleG<T>::GetNormal() const
{
    return Vector3G<T>::Cross(GetPoint(1) - GetPoint(0),
                              GetPoint(2) - GetPoint(0))
        .NormalizedSafe();
}

template <typename T>
Vector3G<T> TriangleG<T>::GetBarycentricCoordinates(
    const Vector3G<T> &point) const
{
    const auto v0 = GetPoint(1) - GetPoint(0);
    const auto v1 = GetPoint(2) - GetPoint(0);

    const auto v2 = point - GetPoint(0);
    const auto d00 = Vector3G<T>::Dot(v0, v0);
    const auto d01 = Vector3G<T>::Dot(v0, v1);
    const auto d11 = Vector3G<T>::Dot(v1, v1);
    const auto d20 = Vector3G<T>::Dot(v2, v0);
    const auto d21 = Vector3G<T>::Dot(v2, v1);
    const auto denom = d00 * d11 - d01 * d01;

    Vector3G<T> baryCoords;
    baryCoords.y = (d11 * d20 - d01 * d21) / denom;
    baryCoords.z = (d00 * d21 - d01 * d20) / denom;
    baryCoords.x = 1.0f - baryCoords.y - baryCoords.z;
    return baryCoords;
}

template <typename T>
Vector3G<T> TriangleG<T>::GetPoint(
    const Vector3G<T> &barycentricCoordinates) const
{
    const auto point = GetPoint(0) * barycentricCoordinates[0] +
                       GetPoint(1) * barycentricCoordinates[1] +
                       GetPoint(2) * barycentricCoordinates[2];
    return point;
}

template <typename T>
const Vector3G<T> &TriangleG<T>::GetPoint(int i) const
{
    return (*this)[i];
}

template <typename T>
PolygonG<T> TriangleG<T>::ToPolygon() const
{
    PolygonG<T> poly;
    poly.AddPoint(GetPoint(0));
    poly.AddPoint(GetPoint(1));
    poly.AddPoint(GetPoint(2));
    return poly;
}

template <typename T>
const std::array<Vector3G<T>, 3> &TriangleG<T>::GetPoints() const
{
    return m_points;
}

template <typename T>
Vector3G<T> &TriangleG<T>::operator[](std::size_t i)
{
    assert(i >= 0 && i <= 2);
    return m_points[i];
}

template <typename T>
const Vector3G<T> &TriangleG<T>::operator[](std::size_t i) const
{
    assert(i >= 0 && i <= 2);
    return m_points[i];
}

template <typename T>
TriangleG<T> operator*(const Matrix4G<T> &m, const TriangleG<T> &t)
{
    return TriangleG<T>(m.TransformedPoint(t[0]),
                        m.TransformedPoint(t[1]),
                        m.TransformedPoint(t[2]));
}
}  // namespace Bang
