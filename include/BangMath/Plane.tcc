#include "BangMath/Plane.h"

#include "BangMath/Vector3.h"

using namespace Bang;

Plane::Plane(const Vector3G<T> &point, const Vector3G<T> &normal)
{
    SetPoint(point);
    SetNormal(normal);
}

void Plane::SetPoint(const Vector3G<T> &point)
{
    m_point = point;
}

void Plane::SetNormal(const Vector3G<T> &normal)
{
    m_normal = normal.NormalizedSafe();
}

const Vector3G<T> &Plane::GetPoint() const
{
    return m_point;
}

const Vector3G<T> &Plane::GetNormal() const
{
    return m_normal;
}

Vector3G<T> Plane::GetMirroredPoint(const Vector3G<T> &point) const
{
    Vector3G<T> mirroredPoint =
        point - (GetNormal() * GetDistanceTo(point)) * 2.0f;
    return mirroredPoint;
}

Vector3G<T> Plane::GetProjectedPoint(const Vector3G<T> &point) const
{
    Vector3G<T> projectedPoint = point - (GetNormal() * GetDistanceTo(point));
    return projectedPoint;
}

Vector3G<T> Plane::GetProjectedVector(const Vector3G<T> &vector) const
{
    return Plane::GetProjectedPoint(vector);
}

Vector3G<T> Plane::GetMirroredVector(const Vector3G<T> &vector) const
{
    return GetMirroredPoint(GetPoint() + vector) - GetPoint();
}

float Plane::GetDistanceTo(const Vector3G<T> &point) const
{
    float dist = Vector3G<T>::Dot(point - GetPoint(), GetNormal());
    return dist;
}
