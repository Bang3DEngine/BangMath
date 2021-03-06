#pragma once

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector3G;

template <typename T>
class PlaneG
{
public:
    PlaneG() = default;
    PlaneG(const Vector3G<T> &point, const Vector3G<T> &normal);
    ~PlaneG() = default;

    void SetPoint(const Vector3G<T> &point);
    void SetNormal(const Vector3G<T> &normal);

    const Vector3G<T> &GetPoint() const;
    const Vector3G<T> &GetNormal() const;
    T GetDistanceTo(const Vector3G<T> &point) const;
    Vector3G<T> GetMirroredPoint(const Vector3G<T> &point) const;
    Vector3G<T> GetMirroredVector(const Vector3G<T> &vector) const;
    Vector3G<T> GetProjectedPoint(const Vector3G<T> &point) const;
    Vector3G<T> GetProjectedVector(const Vector3G<T> &vector) const;

private:
    Vector3G<T> m_point = Vector3G<T>::Zero();
    Vector3G<T> m_normal = Vector3G<T>::Up();
};

BANG_MATH_DEFINE_USINGS(Plane)
}

#include "BangMath/Plane.tcc"
