#include "BangMath/Ray.h"

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
    const auto newDir = m.TransformedVector(ray.GetDirection());
    const auto newOrigin = m.TransformedPoint(ray.GetOrigin());
    return RayG<T>(newOrigin, newDir);
}
}
