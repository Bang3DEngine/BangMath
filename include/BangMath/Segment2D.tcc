#include "BangMath/Segment2D.h"

namespace Bang
{
template <typename T>
Segment2DG<T>::Segment2DG(const Vector2G<T> &origin, const Vector2G<T> &destiny)
{
    SetOrigin(origin);
    SetDestiny(destiny);
}

template <typename T>
void Segment2DG<T>::SetOrigin(const Vector2G<T> &p)
{
    m_origin = p;
}

template <typename T>
void Segment2DG<T>::SetDestiny(const Vector2G<T> &p)
{
    m_destiny = p;
}

template <typename T>
T Segment2DG<T>::GetLength() const
{
    return (GetDestiny() - GetOrigin()).Length();
}

template <typename T>
Vector2G<T> Segment2DG<T>::GetDirection() const
{
    return (GetDestiny() - GetOrigin()).NormalizedSafe();
}

template <typename T>
const Vector2G<T> &Segment2DG<T>::GetOrigin() const
{
    return m_origin;
}

template <typename T>
const Vector2G<T> &Segment2DG<T>::GetDestiny() const
{
    return m_destiny;
}
}
