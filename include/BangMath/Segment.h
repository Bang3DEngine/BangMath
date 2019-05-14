#pragma once

#include "BangMath/Defines.h"

namespace Bang
{
template <typename T>
class Vector3G;

template <typename T>
class SegmentG
{
public:
    SegmentG() = default;
    SegmentG(const Vector3G<T> &origin, const Vector3G<T> &destiny);
    ~SegmentG() = default;

    void SetOrigin(const Vector3G<T> &origin);
    void SetDestiny(const Vector3G<T> &destiny);

    T GetLength() const;
    T GetSqLength() const;
    Vector3G<T> GetDirection() const;
    const Vector3G<T> &GetOrigin() const;
    const Vector3G<T> &GetDestiny() const;

private:
    Vector3G<T> m_origin = Vector3G<T>::Zero();
    Vector3G<T> m_destiny = Vector3G<T>::Zero();
};

BANG_MATH_DEFINE_USINGS(Segment)
}

#include "Segment.tcc"
