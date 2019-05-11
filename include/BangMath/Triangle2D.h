#ifndef TRIANGLE2D_H
#define TRIANGLE2D_H

#include <array>

#include "BangMath/Vector2.h"

namespace Bang
{
template <typename T>
class Vector3G;

template <typename T>
class Triangle2DG
{
public:
    Triangle2DG() = default;
    Triangle2DG(const Vector2G<T> &point0,
                const Vector2G<T> &point1,
                const Vector2G<T> &point2);
    ~Triangle2DG() = default;

    void SetPoint(int i, const Vector2G<T> &point);

    float GetArea() const;
    bool Contains(const Vector2G<T> &point) const;
    Vector3G<T> GetBarycentricCoordinates(const Vector2G<T> &point) const;
    Vector2G<T> GetPoint(const Vector3G<T> &barycentricCoordinates) const;
    const Vector2G<T> &GetPoint(int i) const;
    const std::array<Vector2G<T>, 3> &GetPoints() const;

    Vector2G<T> &operator[](std::size_t i);
    const Vector2G<T> &operator[](std::size_t i) const;

private:
    std::array<Vector2G<T>, 3> m_points;
};
}

#endif  // TRIANGLE2D_H
