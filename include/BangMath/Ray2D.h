#pragma once

namespace Bang
{
template <typename T>
class Vector2G;

template <typename T>
class Ray2DG
{
public:
    Ray2DG() = default;
    Ray2DG(const Vector2G<T> &origin, const Vector2G<T> &direction);

    void SetOrigin(const Vector2G<T> &origin);
    void SetDirection(const Vector2G<T> &direction);

    Vector2G<T> GetPoint(T t) const;

    const Vector2G<T> &GetOrigin() const;
    const Vector2G<T> &GetDirection() const;

private:
    Vector2G<T> m_origin = Vector2G<T>::Zero();
    Vector2G<T> m_direction = Vector2G<T>(1, 0);
};
}
