#pragma once

#include <array>
#include <ostream>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector2G;
template <typename>
class Vector3G;
template <typename>
class Vector4G;
template <typename>
class Matrix4G;

template <typename T>
using RectPointsG = std::array<Vector2G<T>, 4>;
using RectPoints = RectPointsG<MathDefaultType>;

template <typename T>
class RectG
{
public:
    const static RectG<T> &NDCRect();
    const static RectG<T> &Zero();

    RectG();

    RectG(const Vector2G<T> &center,
          const Vector2G<T> &axis0,
          const T &halfSizeAxis0,
          const T &halfSizeAxis1);

    template <typename OtherT>
    explicit RectG(const RectG<OtherT> &r);

    RectG(const Vector2G<T> &center,
          const Vector2G<T> &axis0,
          const Vector2G<T> &halfSizeAxis);
    void SetCenter(const Vector2G<T> &center);
    void SetAxis(const Vector2G<T> &axis0);
    void SetHalfSize(int i, const T &halfSize);
    void SetHalfSizes(const T &halfSizeAxis0, const T &halfSizeAxis1);

    const Vector2G<T> &GetCenter() const;
    Vector2G<T> GetAxis(int i) const;
    T GetHalfSize(int i) const;
    Vector2G<T> GetHalfExtent(int i) const;
    Vector2G<T> GetHalfSize() const;
    Vector2G<T> GetSize() const;
    bool Contains(const Vector2G<T> &point) const;
    Vector2G<T> GetLeftBot() const;
    Vector2G<T> GetRightBot() const;
    Vector2G<T> GetLeftTop() const;
    Vector2G<T> GetRightTop() const;
    void GetPoints(Vector2G<T> *p0,
                   Vector2G<T> *p1,
                   Vector2G<T> *opposedP0) const;
    void GetPoints(Vector2G<T> *p0,
                   Vector2G<T> *p1,
                   Vector2G<T> *opposedP0,
                   Vector2G<T> *opposedP1) const;
    RectPointsG<T> GetPoints() const;

private:
    Vector2G<T> m_center;
    Vector2G<T> m_axis0;
    T m_halfSizeAxis0;
    T m_halfSizeAxis1;
};

template <typename T>
bool operator==(const RectG<T> &r1, const RectG<T> &r2);

template <typename T>
bool operator!=(const RectG<T> &r1, const RectG<T> &r2);

template <typename T>
void operator*=(RectG<T> &r, T a);

template <typename T>
void operator/=(RectG<T> &r, T a);

template <typename T>
void operator*=(RectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator/=(RectG<T> &r, const Vector2G<T> &v);

template <typename T>
RectG<T> operator*(const Matrix4G<T> &m, const RectG<T> &r);

template <typename T>
RectG<T> operator/(T a, const RectG<T> &r);

template <typename T>
RectG<T> operator/(const RectG<T> &r, T a);

template <typename T>
RectG<T> operator*(T a, const RectG<T> &r);

template <typename T>
RectG<T> operator*(const RectG<T> &r, T a);

template <typename T>
RectG<T> operator*(const Vector2G<T> &v, const RectG<T> &r);

template <typename T>
RectG<T> operator*(const RectG<T> &r, const Vector2G<T> &v);

template <typename T>
RectG<T> operator/(const Vector2G<T> &v, const RectG<T> &r);

template <typename T>
RectG<T> operator/(const RectG<T> &r, const Vector2G<T> &v);

template <typename T>
RectG<T> operator-(T a, const RectG<T> &r);

template <typename T>
RectG<T> operator-(const RectG<T> &r, T a);

template <typename T>
RectG<T> operator-(const Vector2G<T> &v, const RectG<T> &r);

template <typename T>
RectG<T> operator-(const RectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator-=(RectG<T> &r, const Vector2G<T> &v);

template <typename T>
RectG<T> operator+(T a, const RectG<T> &r);

template <typename T>
RectG<T> operator+(const RectG<T> &r, T a);

template <typename T>
RectG<T> operator+(const Vector2G<T> &v, const RectG<T> &r);

template <typename T>
RectG<T> operator+(const RectG<T> &r, const Vector2G<T> &v);

template <typename T>
void operator+=(RectG<T> &r, const Vector2G<T> &v);

template <typename T>
std::ostream &operator<<(std::ostream &log, const RectG<T> &r)
{
    log << "(" << r.GetPoints()[0] << ", " << r.GetPoints()[1] << ", "
        << r.GetPoints()[2] << ", " << r.GetPoints()[3] << ")";
    return log;
}

BANG_MATH_DEFINE_USINGS(Rect)
}

#include "BangMath/Rect.tcc"
