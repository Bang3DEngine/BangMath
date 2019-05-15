#include "BangMath/Matrix3.h"

#include <cassert>

namespace Bang
{
template <typename T>
Matrix3G<T>::Matrix3G() : Matrix3G<T>(1)
{
}

template <typename T>
template <typename OtherT>
Matrix3G<T>::Matrix3G(const OtherT &a)
{
    c0 = Vector3G<T>(static_cast<T>(a), static_cast<T>(0), static_cast<T>(0));
    c1 = Vector3G<T>(static_cast<T>(0), static_cast<T>(a), static_cast<T>(0));
    c2 = Vector3G<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(a));
}

template <typename T>
Matrix3G<T>::Matrix3G(const Vector3G<T> &col0,
                      const Vector3G<T> &col1,
                      const Vector3G<T> &col2)
{
    c0 = col0;
    c1 = col1;
    c2 = col2;
}

template <typename T>
Matrix3G<T>::Matrix3G(const T &m00,
                      const T &m01,
                      const T &m02,
                      const T &m10,
                      const T &m11,
                      const T &m12,
                      const T &m20,
                      const T &m21,
                      const T &m22)
{
    c0 = Vector3(m00, m10, m20);
    c1 = Vector3(m01, m11, m21);
    c2 = Vector3(m02, m12, m22);
}

template <typename T>
Matrix3G<T> Matrix3G<T>::Inversed() const
{
    const auto &m = *this;
    const auto div = (m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2]) -
                      m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2]) +
                      m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

    if (div < static_cast<T>(10e-9))
    {
        return m;
    }  // Non invertible

    const auto invDet = static_cast<T>(1) / div;

    Matrix3G<T> res;
    res[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * invDet;
    res[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * invDet;
    res[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * invDet;
    res[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * invDet;
    res[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * invDet;
    res[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * invDet;
    res[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * invDet;
    res[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * invDet;
    res[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * invDet;
    return res;
}

template <typename T>
Matrix3G<T> Matrix3G<T>::Transposed() const
{
    Matrix3G<T> trans;
    const auto &m = *this;

    trans[0].x = m[0].x;
    trans[0].y = m[1].x;
    trans[0].z = m[2].x;

    trans[1].x = m[0].y;
    trans[1].y = m[1].y;
    trans[1].z = m[2].y;

    trans[2].x = m[0].z;
    trans[2].y = m[1].z;
    trans[2].z = m[2].z;

    return trans;
}

template <typename T>
T *Matrix3G<T>::Data()
{
    return static_cast<T *>(&(c0.x));
}

template <typename T>
const T *Matrix3G<T>::Data() const
{
    return static_cast<const T *>(&(c0.x));
}

template <typename T>
Vector3G<T> &Matrix3G<T>::operator[](std::size_t i)
{
    switch (i)
    {
        case 0: return c0;
        case 1: return c1;
        case 2: return c2;
    }
    assert(!"Matrix3G<T> index >= 3");
    return c2;
}

template <typename T>
const Vector3G<T> &Matrix3G<T>::operator[](std::size_t i) const
{
    return const_cast<Matrix3G<T> *>(this)->operator[](i);
}

template <typename T>
const Matrix3G<T> &Matrix3G<T>::Identity()
{
    static const auto m = Matrix3G<T>(1);
    return m;
}

template <typename T, class OtherT>
Matrix3G<T> operator*(const Matrix3G<T> &m1, const Matrix3G<OtherT> &m2)
{
    const auto vA00 = m1[0][0];
    const auto vA01 = m1[0][1];
    const auto vA02 = m1[0][2];
    const auto vA10 = m1[1][0];
    const auto vA11 = m1[1][1];
    const auto vA12 = m1[1][2];
    const auto vA20 = m1[2][0];
    const auto vA21 = m1[2][1];
    const auto vA22 = m1[2][2];
          auto
    const auto vB00 = static_cast<T>(m2[0][0]);
    const auto vB01 = static_cast<T>(m2[0][1]);
    const auto vB02 = static_cast<T>(m2[0][2]);
    const auto vB10 = static_cast<T>(m2[1][0]);
    const auto vB11 = static_cast<T>(m2[1][1]);
    const auto vB12 = static_cast<T>(m2[1][2]);
    const auto vB20 = static_cast<T>(m2[2][0]);
    const auto vB21 = static_cast<T>(m2[2][1]);
    const auto vB22 = static_cast<T>(m2[2][2]);

    Matrix3G<T> res;
    res[0][0] = vA00 * vB00 + vA10 * vB01 + vA20 * vB02;
    res[0][1] = vA01 * vB00 + vA11 * vB01 + vA21 * vB02;
    res[0][2] = vA02 * vB00 + vA12 * vB01 + vA22 * vB02;
    res[1][0] = vA00 * vB10 + vA10 * vB11 + vA20 * vB12;
    res[1][1] = vA01 * vB10 + vA11 * vB11 + vA21 * vB12;
    res[1][2] = vA02 * vB10 + vA12 * vB11 + vA22 * vB12;
    res[2][0] = vA00 * vB20 + vA10 * vB21 + vA20 * vB22;
    res[2][1] = vA01 * vB20 + vA11 * vB21 + vA21 * vB22;
    res[2][2] = vA02 * vB20 + vA12 * vB21 + vA22 * vB22;
    return res;
}

template <typename T>
bool operator==(const Matrix3G<T> &m1, const Matrix3G<T> &m2)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (m1[i][j] != m2[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
template <typename T>
bool operator!=(const Matrix3G<T> &m1, const Matrix3G<T> &m2)
{
    return !(m1 == m2);
}
}  // namespace Bang
