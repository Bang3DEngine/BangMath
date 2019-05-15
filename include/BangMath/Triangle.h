#pragma once

#include <array>
#include <cstddef>
#include <ostream>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector3G;
template <typename>
class PlaneG;
template <typename>
class Vector3G;
template <typename>
class PolygonG;
template <typename>
class Matrix4G;

template <typename T>
class TriangleG
{
public:
    TriangleG() = default;
    TriangleG(const Vector3G<T> &point0,
              const Vector3G<T> &point1,
              const Vector3G<T> &point2);
    ~TriangleG() = default;

    void SetPoint(int i, const Vector3G<T> &point);

    T GetArea() const;
    PlaneG<T> GetPlane() const;
    Vector3G<T> GetNormal() const;
    Vector3G<T> GetBarycentricCoordinates(const Vector3G<T> &point) const;
    Vector3G<T> GetPoint(const Vector3G<T> &barycentricCoordinates) const;
    const std::array<Vector3G<T>, 3> &GetPoints() const;
    const Vector3G<T> &GetPoint(int i) const;
    PolygonG<T> ToPolygon() const;

    Vector3G<T> &operator[](std::size_t i);
    const Vector3G<T> &operator[](std::size_t i) const;

private:
    std::array<Vector3G<T>, 3> m_points;
};

template <typename T>
TriangleG<T> operator*(const Matrix4G<T> &m, const TriangleG<T> &t);

template <typename T>
std::ostream &operator<<(std::ostream &log, const TriangleG<T> &t)
{
    log << "(" << t[0] << ", " << t[1] << ", " << t[2] << ")";
    return log;
}

BANG_MATH_DEFINE_USINGS(Triangle)
}

#include "BangMath/Triangle.tcc"
