#ifndef BOX_H
#define BOX_H

#include <array>

#include "BangMath/Quaternion.h"
#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
class QuadG;

template <typename T>
class BoxG
{
public:
    BoxG() = default;
    ~BoxG() = default;

    void SetCenter(const Vector3G<T> &center);
    void SetLocalExtents(const Vector3G<T> &localExtents);
    void SetOrientation(const QuaternionG<T> &orientation);

    bool Contains(const Vector3G<T> &point) const;
    Vector3G<T> GetExtentX() const;
    Vector3G<T> GetExtentY() const;
    Vector3G<T> GetExtentZ() const;
    const Vector3G<T> &GetCenter() const;
    std::array<QuadG<T>, 6> GetQuads() const;
    const Vector3G<T> &GetLocalExtents() const;
    const QuaternionG<T> &GetOrientation() const;

private:
    Vector3G<T> m_center;
    Vector3G<T> m_localExtents;
    QuaternionG<T> m_orientation;
};
}

#endif  // BOX_H
