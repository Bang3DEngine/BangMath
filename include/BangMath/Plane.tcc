#include "BangMath/Plane.h"

#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
PlaneG<T>::PlaneG(const Vector3G<T> &point, const Vector3G<T> &normal)
{
    SetPoint(point);
    SetNormal(normal);
}

template <typename T>
void PlaneG<T>::SetPoint(const Vector3G<T> &point)
{
    m_point = point;
}

template <typename T>
void PlaneG<T>::SetNormal(const Vector3G<T> &normal)
{
    m_normal = normal.NormalizedSafe();
}

template <typename T>
const Vector3G<T> &PlaneG<T>::GetPoint() const
{
    return m_point;
}

template <typename T>
const Vector3G<T> &PlaneG<T>::GetNormal() const
{
    return m_normal;
}

template <typename T>
Vector3G<T> PlaneG<T>::GetMirroredPoint(const Vector3G<T> &point) const
{
    Vector3G<T> mirroredPoint =
        point - (GetNormal() * GetDistanceTo(point)) * T(2);
    return mirroredPoint;
}

template <typename T>
Vector3G<T> PlaneG<T>::GetProjectedPoint(const Vector3G<T> &point) const
{
    Vector3G<T> projectedPoint = point - (GetNormal() * GetDistanceTo(point));
    return projectedPoint;
}

template <typename T>
Vector3G<T> PlaneG<T>::GetProjectedVector(const Vector3G<T> &vector) const
{
    return PlaneG<T>::GetProjectedPoint(vector);
}

template <typename T>
Vector3G<T> PlaneG<T>::GetMirroredVector(const Vector3G<T> &vector) const
{
    return GetMirroredPoint(GetPoint() + vector) - GetPoint();
}

template <typename T>
T PlaneG<T>::GetDistanceTo(const Vector3G<T> &point) const
{
    T dist = Vector3G<T>::Dot(point - GetPoint(), GetNormal());
    return dist;
}
}
