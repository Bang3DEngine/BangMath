#pragma once

#include <ostream>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector2G;
template <typename>
class Vector4G;
template <typename>
class Matrix4G;

template <typename>
class RectG;

template <typename T>
class AARectG
{
public:
    const static AARectG<T> &NDCRect();
    const static AARectG<T> &Zero();

    AARectG() = default;
    explicit AARectG(T minx, T miny, T maxx, T maxy);
    explicit AARectG(const Vector2G<T> &p1, const Vector2G<T> &p2);

    template <typename OtherT>
    explicit AARectG(const RectG<OtherT> &otherRect);

    template <typename OtherT>
    explicit AARectG(const AARectG<OtherT> &otherRect);

    void SetMin(const Vector2G<T> &minv);
    void SetMax(const Vector2G<T> &maxv);

    bool IsValid() const;

    void AddPoint(const Vector2G<T> &point);

    Vector2G<T> GetMinXMaxY() const;
    Vector2G<T> GetMaxXMaxY() const;
    Vector2G<T> GetMinXMinY() const;
    Vector2G<T> GetMaxXMinY() const;
    const Vector2G<T> &GetMin() const;
    const Vector2G<T> &GetMax() const;

    T GetWidth() const;
    T GetHeight() const;
    T GetArea() const;
    Vector2G<T> GetSize() const;
    Vector2G<T> GetCenter() const;

    bool Contains(const Vector2G<T> &p) const;

    static AARectG<T> Union(const AARectG<T> &r1, const AARectG<T> &r2);

    template <typename Iterator>
    static AARectG<T> Union(Iterator begin, Iterator end);

    static AARectG<T> Intersection(const AARectG<T> &r1, const AARectG<T> &r2);

    template <typename Iterator>
    static AARectG<T> Intersection(Iterator begin, Iterator end);

    template <typename Iterator>
    static AARectG<T> GetBoundingRectFromPositions(Iterator begin,
                                                   Iterator end);

    template <typename OtherT = T>
    Vector2G<T> GetClosestPointInAARect(const Vector2G<T> &point) const;

    template <typename OtherT = T>
    RectG<OtherT> ToRect() const;

private:
    Vector2G<T> m_min = Vector2G<T>::Infinity();
    Vector2G<T> m_max = Vector2G<T>::NInfinity();
};

template <typename T>
bool operator==(const AARectG<T> &r1, const AARectG<T> &r2);

template <typename T>
bool operator!=(const AARectG<T> &r1, const AARectG<T> &r2);

template <typename T>
void operator*=(AARectG<T> &r, T a);

template <typename T>
void operator/=(AARectG<T> &r, T a);

template <typename T>
void operator*=(AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator/=(AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
AARectG<T> operator*(const Matrix4G<T> &m, const AARectG<T> &r);

template <typename T>
AARectG<T> operator/(T a, const AARectG<T> &r);

template <typename T>
AARectG<T> operator/(const AARectG<T> &r, T a);

template <typename T>
AARectG<T> operator*(T a, const AARectG<T> &r);

template <typename T>
AARectG<T> operator*(const AARectG<T> &r, T a);

template <typename T>
AARectG<T> operator*(const Vector2G<T> &v, const AARectG<T> &r);

template <typename T>
AARectG<T> operator*(const AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
AARectG<T> operator/(const Vector2G<T> &v, const AARectG<T> &r);

template <typename T>
AARectG<T> operator/(const AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
AARectG<T> operator-(T a, const AARectG<T> &r);

template <typename T>
AARectG<T> operator-(const AARectG<T> &r, T a);

template <typename T>
AARectG<T> operator-(const Vector2G<T> &v, const AARectG<T> &r);

template <typename T>
AARectG<T> operator-(const AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator-=(AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
AARectG<T> operator+(T a, const AARectG<T> &r);

template <typename T>
AARectG<T> operator+(const AARectG<T> &r, T a);

template <typename T>
AARectG<T> operator+(const Vector2G<T> &v, const AARectG<T> &r);

template <typename T>
AARectG<T> operator+(const AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator+=(AARectG<T> &r, const Vector2G<T> &v);

template <typename T>
std::ostream &operator<<(std::ostream &log, const AARectG<T> &r)
{
    log << "(" << r.GetMin() << ", " << r.GetMax() << ")";
    return log;
}

BANG_MATH_DEFINE_USINGS(AARect)

}  // namespace Bang

#include "AARect.tcc"
