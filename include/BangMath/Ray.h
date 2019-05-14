#pragma once

#include "BangMath/Defines.h"

namespace Bang
{
template <typename T>
class Vector3G;
template <typename T>
class Matrix4G;

template <typename T>
class RayG
{
public:
    RayG() = default;
    RayG(const Vector3G<T> &origin, const Vector3G<T> &direction);

    void SetOrigin(const Vector3G<T> &origin);
    void SetDirection(const Vector3G<T> &direction);

    // Gets a point along the ray with distance t to the ray origin
    Vector3G<T> GetPoint(T t) const;

    const Vector3G<T> &GetOrigin() const;
    const Vector3G<T> &GetDirection() const;

private:
    Vector3G<T> m_origin = Vector3G<T>::Zero();
    Vector3G<T> m_direction = Vector3G<T>::Forward();
};

template <typename T>
RayG<T> operator*(const Matrix4G<T> &m, const RayG<T> &ray);

BANG_MATH_DEFINE_USINGS(Ray)
}

#include "BangMath/Ray.tcc"
