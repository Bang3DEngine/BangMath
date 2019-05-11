#pragma once
#include "BangMath/Sphere.h"

#include "BangMath/AABox.h"
#include "BangMath/Math.h"
#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
SphereG<T>::SphereG(T radius)
{
    SetRadius(radius);
}

template <typename T>
SphereG<T>::SphereG(const Vector3G<T> &center, T radius)
{
    SetCenter(center);
    SetRadius(radius);
}

template <typename T>
void SphereG<T>::SetCenter(const Vector3G<T> &center)
{
    m_center = center;
}

template <typename T>
void SphereG<T>::SetRadius(T radius)
{
    m_radius = radius;
}

template <typename T>
std::vector<Vector3G<T>> SphereG<T>::GetPoints() const
{
    std::vector<Vector3G<T>> points;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            for (int k = -1; k <= 1; ++k)
            {
                Vector3G<T> dir = Vector3G<T>(i, j, k).NormalizedSafe();
                points.PushBack(GetCenter() + GetRadius() * dir);
            }
        }
    }
    return points;
}

template <typename T>
T SphereG<T>::GetDiameter() const
{
    return 2 * GetRadius();
}

template <typename T>
T SphereG<T>::GetArea() const
{
    return 2 * Math::Pi<T>() * GetRadius();
}

template <typename T>
T SphereG<T>::GetVolume() const
{
    return Math::Pi<T>() * GetRadius() * GetRadius();
}

template <typename T>
const Vector3G<T> &SphereG<T>::GetCenter() const
{
    return m_center;
}

template <typename T>
T SphereG<T>::GetRadius() const
{
    return m_radius;
}

template <typename T>
bool SphereG<T>::Contains(const Vector3G<T> &point) const
{
    return Vector3G<T>::SqDistance(point, GetCenter()) <
           GetRadius() * GetRadius();
}
}
