#pragma once

#include <array>
#include <vector>

#include "BangMath/Axis.h"
#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class QuadG;
template <typename>
class Vector3G;
template <typename>
class SphereG;
template <typename>
class Matrix4G;

template <typename T>
class AABoxG
{
public:
    static const AABoxG<T> &Empty();

    AABoxG();
    AABoxG(T minx, T maxx, T miny, T maxy, T minz, T maxz);
    explicit AABoxG(const Vector3G<T> &p);
    AABoxG(const Vector3G<T> &p1, const Vector3G<T> &p2);
    AABoxG(const AABoxG &b);

    void SetMin(const Vector3G<T> &bMin);
    void SetMax(const Vector3G<T> &bMax);

    const Vector3G<T> &GetMin() const;
    const Vector3G<T> &GetMax() const;
    Vector3G<T> GetDiagonal() const;
    T GetWidth() const;
    T GetHeight() const;
    T GetDepth() const;
    Vector3G<T> GetCenter() const;
    Vector3G<T> GetSize() const;
    T GetArea() const;
    T GetVolume() const;
    Vector3G<T> GetExtents() const;
    Vector3G<T> GetClosestPointInAABB(const Vector3G<T> &point) const;
    std::array<Vector3G<T>, 8> GetPointsC() const;
    std::vector<Vector3G<T>> GetPoints() const;

    QuadG<T> GetQuad(Axis3D axis, bool sign) const;
    QuadG<T> GetRightQuad() const;
    QuadG<T> GetLeftQuad() const;
    QuadG<T> GetTopQuad() const;
    QuadG<T> GetBotQuad() const;
    QuadG<T> GetFrontQuad() const;
    QuadG<T> GetBackQuad() const;
    std::array<QuadG<T>, 6> GetQuads() const;

    bool CheckCollision(const SphereG<T> &sphere,
                        Vector3G<T> *point = nullptr,
                        Vector3G<T> *normal = nullptr) const;
    bool CheckCollision(const AABoxG<T> &AABoxG) const;
    bool Contains(const Vector3G<T> &point) const;
    bool Overlap(const AABoxG<T> &AABoxG) const;

    void AddPoint(const Vector3G<T> &point);
    static AABoxG<T> Union(const AABoxG<T> &b1, const AABoxG<T> &b2);
    void CreateFromPositions(const std::vector<Vector3G<T>> &positions);

    static AABoxG<T> FromPointAndSize(const Vector3G<T> &point,
                                      const Vector3G<T> &size);
    static AABoxG<T> FromSphere(const SphereG<T> &sphere);

private:
    Vector3G<T> m_minv = Vector3G<T>::Infinity();
    Vector3G<T> m_maxv = Vector3G<T>::NInfinity();
};

template <typename T>
AABoxG<T> operator*(const Matrix4G<T> &m, const AABoxG<T> &b);

template <typename T>
bool operator==(const AABoxG<T> &b1, const AABoxG<T> &b2);

template <typename T>
bool operator!=(const AABoxG<T> &b1, const AABoxG<T> &b2);

BANG_MATH_DEFINE_USINGS(AABox)

}  // namespace Bang

#include "BangMath/AABox.tcc"
