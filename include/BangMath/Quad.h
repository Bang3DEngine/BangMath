#pragma once

#include <array>
#include <cstddef>

#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
class PlaneG;
template <typename T>
class PolygonG;
template <typename T>
class TriangleG;

template <typename T>
class QuadG
{
public:
    QuadG() = default;

    // Points must be in CCW order!
    QuadG(const Vector3G<T> &p0,
          const Vector3G<T> &p1,
          const Vector3G<T> &p2,
          const Vector3G<T> &p3);

    ~QuadG() = default;

    void SetPoint(int i, const Vector3G<T> &p);

    Vector3G<T> GetNormal() const;
    PlaneG<T> GetPlane() const;
    const Vector3G<T> &GetPoint(int i) const;
    const std::array<Vector3G<T>, 4> &GetPoints() const;
    PolygonG<T> ToPolygon() const;

    // Returns the two triangles of this quad
    void GetTriangles(TriangleG<T> *t0, TriangleG<T> *t1) const;

    Vector3G<T> &operator[](std::size_t i);
    const Vector3G<T> &operator[](std::size_t i) const;

private:
    std::array<Vector3G<T>, 4> m_points = {{Vector3G<T>::Zero(),
                                            Vector3G<T>::Zero(),
                                            Vector3G<T>::Zero(),
                                            Vector3G<T>::Zero()}};
};

template <typename T>
QuadG<T> operator*(const Matrix4G<T> &m, const QuadG<T> &q);
}

#include "BangMath/Quad.tcc"
