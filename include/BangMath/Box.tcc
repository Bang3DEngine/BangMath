#include "BangMath/Box.h"

namespace Bang
{
template <typename T>
void BoxG<T>::SetCenter(const Vector3G<T> &center)
{
    m_center = center;
}

template <typename T>
void BoxG<T>::SetLocalExtents(const Vector3G<T> &localExtents)
{
    m_localExtents = localExtents;
}

template <typename T>
void BoxG<T>::SetOrientation(const QuaternionG<T> &orientation)
{
    m_orientation = orientation;
}

template <typename T>
bool BoxG<T>::Contains(const Vector3G<T> &point) const
{
    const auto transform = Matrix4G<T>::RotateMatrix(-GetOrientation()) *
                           Matrix4G<T>::TranslateMatrix(-GetCenter());
    const auto localPoint = (transform * Vector4G<T>(point, 1)).xyz();

    const auto &lExt = GetLocalExtents();
    return (localPoint.x >= -lExt.x && localPoint.x <= lExt.x) &&
           (localPoint.y >= -lExt.y && localPoint.y <= lExt.y) &&
           (localPoint.z >= -lExt.z && localPoint.z <= lExt.z);
}

template <typename T>
Vector3G<T> BoxG<T>::GetExtentX() const
{
    return GetOrientation() * (GetLocalExtents().x * Vector3G<T>::Right());
}

template <typename T>
Vector3G<T> BoxG<T>::GetExtentY() const
{
    return GetOrientation() * (GetLocalExtents().y * Vector3G<T>::Up());
}

template <typename T>
Vector3G<T> BoxG<T>::GetExtentZ() const
{
    return GetOrientation() * (GetLocalExtents().z * Vector3G<T>::Forward());
}

template <typename T>
const Vector3G<T> &BoxG<T>::GetCenter() const
{
    return m_center;
}

template <typename T>
const Vector3G<T> &BoxG<T>::GetLocalExtents() const
{
    return m_localExtents;
}

template <typename T>
std::array<QuadG<T>, 6> BoxG<T>::GetQuads() const
{
    const auto &c = GetCenter();
    const auto ex = GetExtentX();
    const auto ey = GetExtentY();
    const auto ez = GetExtentZ();
    const auto leftQuad = QuadG<T>(
        c - ex + ey + ez, c - ex + ey - ez, c - ex - ey - ez, c - ex - ey + ez);
    const auto rightQuad = QuadG<T>(
        c + ex + ey + ez, c + ex + ey - ez, c + ex - ey - ez, c + ex - ey + ez);
    const auto topQuad = QuadG<T>(
        c + ex + ey + ez, c + ex + ey - ez, c - ex + ey - ez, c - ex + ey + ez);
    const auto botQuad = QuadG<T>(
        c + ex - ey + ez, c + ex - ey - ez, c - ex - ey - ez, c - ex - ey + ez);
    const auto frontQuad = QuadG<T>(
        c + ex + ey - ez, c + ex - ey - ez, c - ex - ey - ez, c - ex + ey - ez);
    const auto backQuad = QuadG<T>(
        c + ex + ey + ez, c + ex - ey + ez, c - ex - ey + ez, c - ex + ey + ez);

    std::array<QuadG<T>, 6> quads = {
        {leftQuad, rightQuad, topQuad, botQuad, frontQuad, backQuad}};
    return quads;
}

template <typename T>
const QuaternionG<T> &BoxG<T>::GetOrientation() const
{
    return m_orientation;
}
}
