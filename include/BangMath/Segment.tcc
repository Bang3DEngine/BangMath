#include "BangMath/Segment.h"

#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
SegmentG<T>::Segment(const Vector3G<T> &origin, const Vector3G<T> &destiny)
{
    SetOrigin(origin);
    SetDestiny(destiny);
}

template <typename T>
void SegmentG<T>::SetOrigin(const Vector3G<T> &origin)
{
    m_origin = origin;
}

template <typename T>
void SegmentG<T>::SetDestiny(const Vector3G<T> &destiny)
{
    m_destiny = destiny;
}

template <typename T>
T SegmentG<T>::GetLength() const
{
    return (GetDestiny() - GetOrigin()).Length();
}

template <typename T>
T SegmentG<T>::GetSqLength() const
{
    return (GetDestiny() - GetOrigin()).SqLength();
}

template <typename T>
Vector3G<T> SegmentG<T>::GetDirection() const
{
    return (GetDestiny() - GetOrigin()).NormalizedSafe();
}

template <typename T>
const Vector3G<T> &SegmentG<T>::GetOrigin() const
{
    return m_origin;
}

template <typename T>
const Vector3G<T> &SegmentG<T>::GetDestiny() const
{
    return m_destiny;
}
}
