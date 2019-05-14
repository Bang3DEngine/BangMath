#pragma once

#include <vector>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector2G;
template <typename>
class Ray2DG;
template <typename>
class Segment2DG;

template <typename T>
class Polygon2DG
{
public:
    Polygon2DG() = default;

    void AddPoint(const Vector2G<T> &p);
    void SetPoint(int i, const Vector2G<T> &p);
    bool Contains(const Vector2G<T> &p);

    const Vector2G<T> &GetPoint(int i) const;
    const std::vector<Vector2G<T>> &GetPoints() const;

private:
    std::vector<Vector2G<T>> m_points;
};

BANG_MATH_DEFINE_USINGS(Polygon2D)

}

#include "BangMath/Polygon2D.tcc"
