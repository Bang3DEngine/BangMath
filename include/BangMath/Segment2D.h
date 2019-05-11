#pragma once

namespace Bang
{
template <typename T>
class Vector2G;

template <typename T>
class Segment2DG
{
public:
    Segment2DG() = default;
    Segment2DG(const Vector2G<T> &origin, const Vector2G<T> &destiny);
    ~Segment2DG() = default;

    void SetOrigin(const Vector2G<T> &p);
    void SetDestiny(const Vector2G<T> &p);

    T GetLength() const;
    Vector2G<T> GetDirection() const;
    const Vector2G<T> &GetOrigin() const;
    const Vector2G<T> &GetDestiny() const;

private:
    Vector2G<T> m_origin = Vector2G<T>::Zero();
    Vector2G<T> m_destiny = Vector2G<T>::Zero();
};
}
