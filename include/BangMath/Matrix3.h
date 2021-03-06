#pragma once

#include <cstddef>

#include "BangMath/Defines.h"

namespace Bang
{
template <typename>
class Vector3G;

template <typename T>  // Part of it copied from glm
class Matrix3G
{
public:
    static const Matrix3G<T> &Identity();

    Vector3G<T> c0, c1, c2;  // Matrix columns from left to right

    Matrix3G();

    template <typename OtherT>
    Matrix3G(const OtherT &a);

    Matrix3G(const Vector3G<T> &col0,
             const Vector3G<T> &col1,
             const Vector3G<T> &col2);

    Matrix3G(const T &m00,
             const T &m01,
             const T &m02,
             const T &m10,
             const T &m11,
             const T &m12,
             const T &m20,
             const T &m21,
             const T &m22);

    Matrix3G<T> Inversed() const;
    Matrix3G<T> Transposed() const;

    T *Data();
    const T *Data() const;

    Vector3G<T> &operator[](std::size_t i);
    const Vector3G<T> &operator[](std::size_t i) const;
};

template <typename T, class OtherT>
Matrix3G<T> operator*(const Matrix3G<T> &m1, const Matrix3G<OtherT> &m2);

template <typename T>
bool operator==(const Matrix3G<T> &m1, const Matrix3G<T> &m2);

template <typename T>
bool operator!=(const Matrix3G<T> &m1, const Matrix3G<T> &m2);

template <typename T>
std::ostream &operator<<(std::ostream &log, const Matrix3G<T> &m)
{
    log << std::endl;
    log << "(" << m.c0[0] << ", " << m.c1[0] << ", " << m.c2[0] << ","
        << std::endl;
    log << " " << m.c0[1] << ", " << m.c1[1] << ", " << m.c2[1] << ","
        << std::endl;
    log << " " << m.c0[2] << ", " << m.c1[2] << ", " << m.c2[2] << ","
        << std::endl;
    return log;
}

BANG_MATH_DEFINE_USINGS(Matrix3)
}

#include "BangMath/Matrix3.tcc"
