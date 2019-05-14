#pragma once

#include <cstddef>
#include <vector>

#include "BangMath/Axis.h"
#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class PlaneG;
template <typename>
class Polygon2DG;
template <typename>
class Vector3G;
template <typename>
class Vector2G;
template <typename>
class TriangleG;

template <typename T>
class PolygonG
{
public:
    PolygonG() = default;
    ~PolygonG() = default;

    void AddPoint(const Vector3G<T> &p);
    void AddPoints(const std::vector<Vector3G<T>> &points);
    void SetPoint(int i, const Vector3G<T> &p);

    PlaneG<T> GetPlane() const;
    Vector3G<T> GetNormal() const;
    Polygon2DG<T> ProjectedOnAxis(Axis3D axis) const;

    const Vector3G<T> &GetPoint(int i) const;
    const std::vector<Vector3G<T>> &GetPoints() const;

    Vector3G<T> &operator[](std::size_t i);
    const Vector3G<T> &operator[](std::size_t i) const;

private:
    std::vector<Vector3G<T>> m_points;
};

BANG_MATH_DEFINE_USINGS(Polygon)
}

#include "Polygon.tcc"
