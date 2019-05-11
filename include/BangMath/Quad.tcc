#include "BangMath/Quad.h"

#include <cassert>

#include "BangMath/Matrix4.tcc"
#include "BangMath/Plane.h"
#include "BangMath/Polygon.h"
#include "BangMath/Triangle.h"

namespace Bang
{
template <typename T>
QuadG<T>::QuadG(const Vector3G<T> &p0,
                const Vector3G<T> &p1,
                const Vector3G<T> &p2,
                const Vector3G<T> &p3)
{
    SetPoint(0, p0);
    SetPoint(1, p1);
    SetPoint(2, p2);
    SetPoint(3, p3);
}

template <typename T>
void QuadG<T>::SetPoint(int i, const Vector3G<T> &p)
{
    (*this)[i] = p;
}

template <typename T>
Vector3G<T> QuadG<T>::GetNormal() const
{
    return TriangleG<T>(GetPoint(0), GetPoint(1), GetPoint(2)).GetNormal();
}

template <typename T>
PlaneG<T> QuadG<T>::GetPlane() const
{
    return PlaneG<T>(GetPoint(0), GetNormal());
}

template <typename T>
const Vector3G<T> &QuadG<T>::GetPoint(int i) const
{
    return (*this)[i];
}

template <typename T>
const std::array<Vector3G<T>, 4> &QuadG<T>::GetPoints() const
{
    return m_points;
}

template <typename T>
PolygonG<T> QuadG<T>::ToPolygon() const
{
    PolygonG<T> poly;
    poly.AddPoint(GetPoint(0));
    poly.AddPoint(GetPoint(1));
    poly.AddPoint(GetPoint(2));
    poly.AddPoint(GetPoint(3));
    return poly;
}

template <typename T>
void QuadG<T>::GetTriangles(TriangleG<T> *t0, TriangleG<T> *t1) const
{
    *t0 = TriangleG<T>(GetPoint(0), GetPoint(1), GetPoint(2));
    *t1 = TriangleG<T>(GetPoint(0), GetPoint(2), GetPoint(3));
}

template <typename T>
Vector3G<T> &QuadG<T>::operator[](std::size_t i)
{
    assert(i >= 0 && i <= 3);
    return m_points[i];
}

template <typename T>
const Vector3G<T> &QuadG<T>::operator[](std::size_t i) const
{
    assert(i >= 0 && i <= 3);
    return m_points[i];
}

template <typename T>
QuadG<T> operator*(const Matrix4G<T> &m, const QuadG<T> &q)
{
    return QuadG<T>(m.TransformedPoint(q[0]),
                    m.TransformedPoint(q[1]),
                    m.TransformedPoint(q[2]),
                    m.TransformedPoint(q[3]));
}
}
