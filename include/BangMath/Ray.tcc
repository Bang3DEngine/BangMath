#pragma once
#include "BangMath/Ray.h"

#include "BangMath/Matrix4.h"
#include "BangMath/Vector3.h"
#include "BangMath/Vector4.h"

namespace Bang
{
template <typename T>
RayG<T>::RayG(const Vector3G<T> &origin, const Vector3G<T> &direction)
{
    SetOrigin(origin);
    SetDirection(direction);
}

template <typename T>
void RayG<T>::SetOrigin(const Vector3G<T> &origin)
{
    m_origin = origin;
}

template <typename T>
void RayG<T>::SetDirection(const Vector3G<T> &direction)
{
    m_direction = direction.NormalizedSafe();
}

template <typename T>
Vector3G<T> RayG<T>::GetPoint(T t) const
{
    return GetOrigin() + GetDirection() * t;
}

template <typename T>
const Vector3G<T> &RayG<T>::GetOrigin() const
{
    return m_origin;
}

template <typename T>
const Vector3G<T> &RayG<T>::GetDirection() const
{
    return m_direction;
}

template <typename T>
RayG<T> operator*(const Matrix4G<T> &m, const RayG<T> &ray)
{
    Vector3G<T> newDir = m.TransformedVector(ray.GetDirection());
    Vector3G<T> newOrigin = m.TransformedPoint(ray.GetOrigin());
    return RayG<T>(newOrigin, newDir);
}
}
