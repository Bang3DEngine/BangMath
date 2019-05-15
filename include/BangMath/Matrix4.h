#pragma once

#include "BangMath/Defines.h"
#include "BangMath/Vector4.h"

namespace Bang
{
template <typename>
class Matrix3G;
template <typename>
class QuaternionG;
template <typename>
class Vector3G;
template <typename T>
class Vector4G;

template <typename T>
class Matrix4G
{
public:
    static const Matrix4G<T> &Identity();

    Vector4G<T> c0, c1, c2, c3;

    Matrix4G();

    template <typename OtherT>
    Matrix4G(const Matrix4G<OtherT> &m);

    Matrix4G(const Vector4G<T> &col0,
             const Vector4G<T> &col1,
             const Vector4G<T> &col2,
             const Vector4G<T> &col3);

    Matrix4G(const T &m00,
             const T &m01,
             const T &m02,
             const T &m03,
             const T &m10,
             const T &m11,
             const T &m12,
             const T &m13,
             const T &m20,
             const T &m21,
             const T &m22,
             const T &m23,
             const T &m30,
             const T &m31,
             const T &m32,
             const T &m33);

    template <typename OtherT>
    explicit Matrix4G(const Matrix3G<OtherT> &m);

    template <typename OtherT>
    explicit Matrix4G(const OtherT &a);

    Vector3G<T> TransformedPoint(const Vector3G<T> &point) const;
    Vector3G<T> TransformedVector(const Vector3G<T> &vector) const;

    Matrix4G<T> Inversed(T invertiblePrecision = T(0.00000001),
                         bool *isInvertible = nullptr) const;
    Matrix4G<T> Transposed() const;
    T GetDeterminant() const;

    T *Data();
    const T *Data() const;

    void SetTranslation(const Vector3G<T> &translate);
    void SetScale(const Vector3G<T> &scale);
    Vector3G<T> GetTranslation() const;
    QuaternionG<T> GetRotation() const;
    Vector3G<T> GetScale() const;

    static Matrix4G<T> LookAt(const Vector3G<T> &eyePosition,
                              const Vector3G<T> &focusPoint,
                              const Vector3G<T> &up);

    static Matrix4G<T> TransformMatrix(const Vector3G<T> &position,
                                       const QuaternionG<T> &rotation,
                                       const Vector3G<T> &scale);
    static Matrix4G<T> TransformMatrixInverse(const Vector3G<T> &position,
                                              const QuaternionG<T> &rotation,
                                              const Vector3G<T> &scale);

    static Matrix4G<T> Perspective(T fovYRads, T aspect, T zNear, T zFar);

    static Matrix4G<T> Ortho(T left, T right, T bottom, T top, T zNear, T zFar);

    static Matrix4G<T> TranslateMatrix(const Vector3G<T> &v);
    static Matrix4G<T> RotateMatrix(const QuaternionG<T> &q);
    static Matrix4G<T> ScaleMatrix(const Vector3G<T> &v);
    static QuaternionG<T> ToQuaternion(const Matrix4G<T> &m);

    Vector4G<T> &operator[](std::size_t i);
    const Vector4G<T> &operator[](std::size_t i) const;
};

// Operators
template <typename T>
bool operator==(const Matrix4G<T> &m1, const Matrix4G<T> &m2);

template <typename T>
bool operator!=(const Matrix4G<T> &m1, const Matrix4G<T> &m2);

template <typename T>
Matrix4G<T> operator+(const Matrix4G<T> &m1, const Matrix4G<T> &rhs);

template <typename T>
Matrix4G<T> operator-(const Matrix4G<T> &m1, const Matrix4G<T> &rhs);

template <typename T>
Matrix4G<T> operator-(const Matrix4G<T> &m);

template <typename T>
Matrix4G<T> operator*(const Matrix4G<T> &m1, const Matrix4G<T> &rhs);

template <typename T>
Vector4G<T> operator*(const Matrix4G<T> &m, const Vector4G<T> &v);

template <typename T>
void operator*=(Matrix4G<T> &m, const Matrix4G<T> &rhs);

template <typename T>
void operator+=(Matrix4G<T> &m, const Matrix4G<T> &rhs);

template <typename T>
void operator-=(Matrix4G<T> &m, const Matrix4G<T> &rhs);

template <typename T>
std::ostream &operator<<(std::ostream &log, const Matrix4G<T> &m)
{
    log << std::endl;
    log << "(" << m.c0[0] << ", " << m.c1[0] << ", " << m.c2[0] << ", "
        << m.c3[0] << "," << std::endl;
    log << " " << m.c0[1] << ", " << m.c1[1] << ", " << m.c2[1] << ", "
        << m.c3[1] << "," << std::endl;
    log << " " << m.c0[2] << ", " << m.c1[2] << ", " << m.c2[2] << ", "
        << m.c3[2] << "," << std::endl;
    log << " " << m.c0[3] << ", " << m.c1[3] << ", " << m.c2[3] << ", "
        << m.c3[3] << ")" << std::endl;
    return log;
}

BANG_MATH_DEFINE_USINGS(Matrix4)
}

#include "BangMath/Matrix4.tcc"
