#pragma once
#include "BangMath/Ray2D.h"

#include "BangMath/Vector2.h"

namespace Bang
{
template <typename T>
Ray2DG<T>::Ray2DG(const Vector2G<T> &origin, const Vector2G<T> &direction)
{
    SetOrigin(origin);
    SetDirection(direction);
}

template <typename T>
void Ray2DG<T>::SetOrigin(const Vector2G<T> &origin)
{
    m_origin = origin;
}

template <typename T>
void Ray2DG<T>::SetDirection(const Vector2G<T> &direction)
{
    m_direction = direction.NormalizedSafe();
}

template <typename T>
Vector2G<T> Ray2DG<T>::GetPoint(T t) const
{
    return GetOrigin() + GetDirection() * t;
}

template <typename T>
const Vector2G<T> &Ray2DG<T>::GetOrigin() const
{
    return m_origin;
}

template <typename T>
const Vector2G<T> &Ray2DG<T>::GetDirection() const
{
    return m_direction;
}
}
