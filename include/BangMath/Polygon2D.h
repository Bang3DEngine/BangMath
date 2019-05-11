#pragma once

#include <vector>

namespace Bang
{
template <typename T>
class Vector2G;

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
}

#include "BangMath/Polygon2D.tcc"
