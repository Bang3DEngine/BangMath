#pragma once

#include <vector>

#include "BangMath/Defines.h"
#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
class AABoxG;
template <typename T>
class Vector3G;

template <typename T>
class SphereG
{
public:
    SphereG() = default;
    SphereG(T radius);
    SphereG(const Vector3G<T> &center, T radius);
    ~SphereG() = default;

    void SetCenter(const Vector3G<T> &center);
    void SetRadius(T radius);

    std::vector<Vector3G<T>> GetPoints() const;
    T GetDiameter() const;
    T GetArea() const;
    T GetVolume() const;
    const Vector3G<T> &GetCenter() const;
    T GetRadius() const;

    bool Contains(const Vector3G<T> &point) const;
    bool CheckCollision(const SphereG<T> &sphere) const;
    bool CheckCollision(const AABoxG<T> &aabox,
                        Vector3G<T> *point = nullptr,
                        Vector3G<T> *normal = nullptr) const;

    void FillFromBox(const AABoxG<T> &box);

    static SphereG<T> FromBox(const AABoxG<T> &box);


private:
    Vector3G<T> m_center = Vector3G<T>::Zero();
    T m_radius = 0.0f;
};
BANG_MATH_DEFINE_USINGS(Sphere)
}

#include "BangMath/Sphere.tcc"
