#include "BangMath/Matrix4.h"

namespace Bang
{
template <typename T>
Matrix4G<T>::Matrix4G() : Matrix4G<T>(1)
{
}

template <typename T>
template <typename OtherT>
Matrix4G<T>::Matrix4G(const Matrix4G<OtherT> &m)
{
    c0 = Vector4G<T>(m.c0);
    c1 = Vector4G<T>(m.c1);
    c2 = Vector4G<T>(m.c2);
    c3 = Vector4G<T>(m.c3);
}

template <typename T>
Matrix4G<T>::Matrix4G(const Vector4G<T> &col0,
                      const Vector4G<T> &col1,
                      const Vector4G<T> &col2,
                      const Vector4G<T> &col3)
{
    c0 = col0;
    c1 = col1;
    c2 = col2;
    c3 = col3;
}

template <typename T>
Matrix4G<T>::Matrix4G(const T &m00,
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
                      const T &m33)
{
    c0 = Vector4G<T>(m00, m10, m20, m30);
    c1 = Vector4G<T>(m01, m11, m21, m31);
    c2 = Vector4G<T>(m02, m12, m22, m32);
    c3 = Vector4G<T>(m03, m13, m23, m33);
}

template <typename T>
template <typename OtherT>
Matrix4G<T>::Matrix4G(const Matrix3G<OtherT> &m)
{
    c0 = Vector4G<T>(m.c0, 0);
    c1 = Vector4G<T>(m.c1, 0);
    c2 = Vector4G<T>(m.c2, 0);
    c3 = Vector4G<T>(0, 0, 0, 1);
}

template <typename T>
template <typename OtherT>
Matrix4G<T>::Matrix4G(const OtherT &a)
{
    c0 = Vector4G<T>(static_cast<T>(a),
                     static_cast<T>(0),
                     static_cast<T>(0),
                     static_cast<T>(0));
    c1 = Vector4G<T>(static_cast<T>(0),
                     static_cast<T>(a),
                     static_cast<T>(0),
                     static_cast<T>(0));
    c2 = Vector4G<T>(static_cast<T>(0),
                     static_cast<T>(0),
                     static_cast<T>(a),
                     static_cast<T>(0));
    c3 = Vector4G<T>(static_cast<T>(0),
                     static_cast<T>(0),
                     static_cast<T>(0),
                     static_cast<T>(a));
}

template <typename T>
Vector3G<T> Matrix4G<T>::TransformedPoint(const Vector3G<T> &point) const
{
    return ((*this) * Vector4G<T>(point, 1)).xyz();
}
template <typename T>
Vector3G<T> Matrix4G<T>::TransformedVector(const Vector3G<T> &vector) const
{
    return ((*this) * Vector4G<T>(vector, 0)).xyz();
}

template <typename T>
Matrix4G<T> Matrix4G<T>::Inversed(T invertiblePrecision,
                                  bool *isInvertibleOut) const
{
    Matrix4G<T> inv;
    const Matrix4G<T> &m = *this;

    inv.c0.x = m.c1.y * m.c2.z * m.c3.w - m.c1.y * m.c2.w * m.c3.z -
               m.c2.y * m.c1.z * m.c3.w + m.c2.y * m.c1.w * m.c3.z +
               m.c3.y * m.c1.z * m.c2.w - m.c3.y * m.c1.w * m.c2.z;

    inv.c1.x = -m.c1.x * m.c2.z * m.c3.w + m.c1.x * m.c2.w * m.c3.z +
               m.c2.x * m.c1.z * m.c3.w - m.c2.x * m.c1.w * m.c3.z -
               m.c3.x * m.c1.z * m.c2.w + m.c3.x * m.c1.w * m.c2.z;

    inv.c2.x = m.c1.x * m.c2.y * m.c3.w - m.c1.x * m.c2.w * m.c3.y -
               m.c2.x * m.c1.y * m.c3.w + m.c2.x * m.c1.w * m.c3.y +
               m.c3.x * m.c1.y * m.c2.w - m.c3.x * m.c1.w * m.c2.y;

    inv.c3.x = -m.c1.x * m.c2.y * m.c3.z + m.c1.x * m.c2.z * m.c3.y +
               m.c2.x * m.c1.y * m.c3.z - m.c2.x * m.c1.z * m.c3.y -
               m.c3.x * m.c1.y * m.c2.z + m.c3.x * m.c1.z * m.c2.y;

    inv.c0.y = -m.c0.y * m.c2.z * m.c3.w + m.c0.y * m.c2.w * m.c3.z +
               m.c2.y * m.c0.z * m.c3.w - m.c2.y * m.c0.w * m.c3.z -
               m.c3.y * m.c0.z * m.c2.w + m.c3.y * m.c0.w * m.c2.z;

    inv.c1.y = m.c0.x * m.c2.z * m.c3.w - m.c0.x * m.c2.w * m.c3.z -
               m.c2.x * m.c0.z * m.c3.w + m.c2.x * m.c0.w * m.c3.z +
               m.c3.x * m.c0.z * m.c2.w - m.c3.x * m.c0.w * m.c2.z;

    inv.c2.y = -m.c0.x * m.c2.y * m.c3.w + m.c0.x * m.c2.w * m.c3.y +
               m.c2.x * m.c0.y * m.c3.w - m.c2.x * m.c0.w * m.c3.y -
               m.c3.x * m.c0.y * m.c2.w + m.c3.x * m.c0.w * m.c2.y;

    inv.c3.y = m.c0.x * m.c2.y * m.c3.z - m.c0.x * m.c2.z * m.c3.y -
               m.c2.x * m.c0.y * m.c3.z + m.c2.x * m.c0.z * m.c3.y +
               m.c3.x * m.c0.y * m.c2.z - m.c3.x * m.c0.z * m.c2.y;

    inv.c0.z = m.c0.y * m.c1.z * m.c3.w - m.c0.y * m.c1.w * m.c3.z -
               m.c1.y * m.c0.z * m.c3.w + m.c1.y * m.c0.w * m.c3.z +
               m.c3.y * m.c0.z * m.c1.w - m.c3.y * m.c0.w * m.c1.z;

    inv.c1.z = -m.c0.x * m.c1.z * m.c3.w + m.c0.x * m.c1.w * m.c3.z +
               m.c1.x * m.c0.z * m.c3.w - m.c1.x * m.c0.w * m.c3.z -
               m.c3.x * m.c0.z * m.c1.w + m.c3.x * m.c0.w * m.c1.z;

    inv.c2.z = m.c0.x * m.c1.y * m.c3.w - m.c0.x * m.c1.w * m.c3.y -
               m.c1.x * m.c0.y * m.c3.w + m.c1.x * m.c0.w * m.c3.y +
               m.c3.x * m.c0.y * m.c1.w - m.c3.x * m.c0.w * m.c1.y;

    inv.c3.z = -m.c0.x * m.c1.y * m.c3.z + m.c0.x * m.c1.z * m.c3.y +
               m.c1.x * m.c0.y * m.c3.z - m.c1.x * m.c0.z * m.c3.y -
               m.c3.x * m.c0.y * m.c1.z + m.c3.x * m.c0.z * m.c1.y;

    inv.c0.w = -m.c0.y * m.c1.z * m.c2.w + m.c0.y * m.c1.w * m.c2.z +
               m.c1.y * m.c0.z * m.c2.w - m.c1.y * m.c0.w * m.c2.z -
               m.c2.y * m.c0.z * m.c1.w + m.c2.y * m.c0.w * m.c1.z;

    inv.c1.w = m.c0.x * m.c1.z * m.c2.w - m.c0.x * m.c1.w * m.c2.z -
               m.c1.x * m.c0.z * m.c2.w + m.c1.x * m.c0.w * m.c2.z +
               m.c2.x * m.c0.z * m.c1.w - m.c2.x * m.c0.w * m.c1.z;

    inv.c2.w = -m.c0.x * m.c1.y * m.c2.w + m.c0.x * m.c1.w * m.c2.y +
               m.c1.x * m.c0.y * m.c2.w - m.c1.x * m.c0.w * m.c2.y -
               m.c2.x * m.c0.y * m.c1.w + m.c2.x * m.c0.w * m.c1.y;

    inv.c3.w = m.c0.x * m.c1.y * m.c2.z - m.c0.x * m.c1.z * m.c2.y -
               m.c1.x * m.c0.y * m.c2.z + m.c1.x * m.c0.z * m.c2.y +
               m.c2.x * m.c0.y * m.c1.z - m.c2.x * m.c0.z * m.c1.y;

    float det = m.c0.x * inv.c0.x + m.c0.y * inv.c1.x + m.c0.z * inv.c2.x +
                m.c0.w * inv.c3.x;

    bool isInvertible = (Math::Abs(det) > invertiblePrecision);
    if (isInvertibleOut)
    {
        *isInvertibleOut = isInvertible;
    }
    if (!isInvertible)
    {
        return *this;
    }

    inv.c0 /= det;
    inv.c1 /= det;
    inv.c2 /= det;
    inv.c3 /= det;

    return inv;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::Transposed() const
{
    Matrix4G<T> trans;
    const Matrix4G<T> &m = *this;

    trans.c0.x = m.c0.x;
    trans.c0.y = m.c1.x;
    trans.c0.z = m.c2.x;
    trans.c0.w = m.c3.x;

    trans.c1.x = m.c0.y;
    trans.c1.y = m.c1.y;
    trans.c1.z = m.c2.y;
    trans.c1.w = m.c3.y;

    trans.c2.x = m.c0.z;
    trans.c2.y = m.c1.z;
    trans.c2.z = m.c2.z;
    trans.c2.w = m.c3.z;

    trans.c3.x = m.c0.w;
    trans.c3.y = m.c1.w;
    trans.c3.z = m.c2.w;
    trans.c3.w = m.c3.w;

    return trans;
}

template <typename T>
T Matrix4G<T>::GetDeterminant() const
{
    const Matrix4G<T> &m = *this;

    T d01 = (m[2][0] * m[3][1] - m[3][0] * m[2][1]);
    T d02 = (m[2][0] * m[3][2] - m[3][0] * m[2][2]);
    T d12 = (m[2][1] * m[3][2] - m[3][1] * m[2][2]);
    T d13 = (m[2][1] * m[3][3] - m[3][1] * m[2][3]);
    T d23 = (m[2][2] * m[3][3] - m[3][2] * m[2][3]);
    T d30 = (m[2][3] * m[3][0] - m[3][3] * m[2][0]);

    T t0 = (m[1][1] * d23 - m[1][2] * d13 + m[1][3] * d12);
    T t1 = -(m[1][0] * d23 + m[1][2] * d30 + m[1][3] * d02);
    T t2 = (m[1][0] * d13 + m[1][1] * d30 + m[1][3] * d01);
    T t3 = -(m[1][0] * d12 - m[1][1] * d02 + m[1][2] * d01);

    T det = m[0][0] * t0 + m[0][1] * t1 + m[0][2] * t2 + m[0][3] * t3;
    return det;
}

template <typename T>
T *Matrix4G<T>::Data()
{
    return static_cast<T *>(&(c0.x));
}

template <typename T>
const T *Matrix4G<T>::Data() const
{
    return static_cast<const T *>(&(c0.x));
}

template <typename T>
void Matrix4G<T>::SetTranslation(const Vector3G<T> &translate)
{
    c3.x = translate.x;
    c3.y = translate.y;
    c3.z = translate.z;
}
template <typename T>
void Matrix4G<T>::SetScale(const Vector3G<T> &scale)
{
    c0.x = scale.x;
    c1.y = scale.y;
    c2.z = scale.z;
}

template <typename T>
Vector3G<T> Matrix4G<T>::GetTranslation() const
{
    return c3.xyz();
}
template <typename T>
QuaternionG<T> Matrix4G<T>::GetRotation() const
{
    Vector3G<T> scale = GetScale();

    constexpr T Eps = static_cast<T>(1e-3);
    if (Math::Abs(scale.x) <= Eps)
    {
        scale.x = Math::Sign(scale.x) * Eps;
    }
    if (Math::Abs(scale.y) <= Eps)
    {
        scale.y = Math::Sign(scale.y) * Eps;
    }
    if (Math::Abs(scale.z) <= Eps)
    {
        scale.z = Math::Sign(scale.z) * Eps;
    }

    Matrix4G<T> rotMatrix;
    rotMatrix.c0 = Vector4G<T>(c0.xyz() / scale.x, 0);
    rotMatrix.c1 = Vector4G<T>(c1.xyz() / scale.y, 0);
    rotMatrix.c2 = Vector4G<T>(c2.xyz() / scale.z, 0);
    rotMatrix.c3 = Vector4G<T>(0, 0, 0, 1);

    return Matrix4G<T>::ToQuaternion(rotMatrix).Normalized();
}
template <typename T>
Vector3G<T> Matrix4G<T>::GetScale() const
{
    return Vector3G<T>(c0.xyz().Length(), c1.xyz().Length(), c2.xyz().Length());
}

template <typename T>
Matrix4G<T> Matrix4G<T>::LookAt(const Vector3G<T> &eyePosition,
                                const Vector3G<T> &focusPoint,
                                const Vector3G<T> &up)
{
    const Vector3G<T> f((focusPoint - eyePosition).NormalizedSafe());
    const Vector3G<T> s((Vector3G<T>::Cross(f, up)).NormalizedSafe());
    const Vector3G<T> u(Vector3G<T>::Cross(s, f));

    Matrix4G<T> res(1);
    res[0][0] = s.x;
    res[1][0] = s.y;
    res[2][0] = s.z;
    res[0][1] = u.x;
    res[1][1] = u.y;
    res[2][1] = u.z;
    res[0][2] = -f.x;
    res[1][2] = -f.y;
    res[2][2] = -f.z;
    res[3][0] = -Vector3G<T>::Dot(s, eyePosition);
    res[3][1] = -Vector3G<T>::Dot(u, eyePosition);
    res[3][2] = Vector3G<T>::Dot(f, eyePosition);
    return res;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::TransformMatrix(const Vector3G<T> &position,
                                         const QuaternionG<T> &rotation,
                                         const Vector3G<T> &scale)
{
    Matrix4G<T> transformMatrix;
    if (rotation == QuaternionG<T>::Identity())
    {
        transformMatrix.SetTranslation(position);
        transformMatrix.SetScale(scale);
    }
    else
    {
        transformMatrix.SetScale(scale);
        transformMatrix = Matrix4G<T>::RotateMatrix(rotation) * transformMatrix;
        transformMatrix.SetTranslation(position);
    }
    return transformMatrix;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::TransformMatrixInverse(const Vector3G<T> &position,
                                                const QuaternionG<T> &rotation,
                                                const Vector3G<T> &scale)
{
    const Vector3G<T> inversePosition = -position;
    const QuaternionG<T> inverseRotation = rotation.Inversed();
    const Vector3G<T> inverseScale = (1.0f / scale);

    Matrix4G<T> transformMatrix = Matrix4G<T>::ScaleMatrix(inverseScale) *
                                  Matrix4G<T>::RotateMatrix(inverseRotation) *
                                  Matrix4G<T>::TranslateMatrix(inversePosition);
    return transformMatrix;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::Perspective(T fovYRads, T aspect, T zNear, T zFar)
{
    const T tanHalfFovy = Math::Tan(fovYRads / static_cast<T>(2));

    Matrix4G<T> res(0);
    res[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
    res[1][1] = static_cast<T>(1) / (tanHalfFovy);
    res[2][2] = -(zFar + zNear) / (zFar - zNear);
    res[2][3] = -static_cast<T>(1);
    res[3][2] = -(static_cast<T>(2) * zFar * zNear) / (zFar - zNear);

    return res;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::Ortho(T left,
                               T right,
                               T bottom,
                               T top,
                               T zNear,
                               T zFar)
{
    Matrix4G<T> res(1);
    res[0][0] = static_cast<T>(2) / (right - left);
    res[1][1] = static_cast<T>(2) / (top - bottom);
    res[2][2] = -static_cast<T>(2) / (zFar - zNear);
    res[3][0] = -static_cast<T>(right + left) / static_cast<T>(right - left);
    res[3][1] = -static_cast<T>(top + bottom) / static_cast<T>(top - bottom);
    res[3][2] = -static_cast<T>(zFar + zNear) / static_cast<T>(zFar - zNear);
    return res;
}

template <typename T>
Matrix4G<T> Matrix4G<T>::TranslateMatrix(const Vector3G<T> &v)
{
    return Matrix4G<T>(1, 0, 0, v.x, 0, 1, 0, v.y, 0, 0, 1, v.z, 0, 0, 0, 1);
}

template <typename T>
Matrix4G<T> Matrix4G<T>::RotateMatrix(const QuaternionG<T> &q)
{
    T qxx(q.x * q.x);
    T qyy(q.y * q.y);
    T qzz(q.z * q.z);
    T qxz(q.x * q.z);
    T qxy(q.x * q.y);
    T qyz(q.y * q.z);
    T qwx(q.w * q.x);
    T qwy(q.w * q.y);
    T qwz(q.w * q.z);

    Matrix4G<T> res(1);

    res.c0.x = 1 - 2 * (qyy + qzz);
    res.c0.y = 2 * (qxy + qwz);
    res.c0.z = 2 * (qxz - qwy);

    res.c1.x = 2 * (qxy - qwz);
    res.c1.y = 1 - 2 * (qxx + qzz);
    res.c1.z = 2 * (qyz + qwx);

    res.c2.x = 2 * (qxz + qwy);
    res.c2.y = 2 * (qyz - qwx);
    res.c2.z = 1 - 2 * (qxx + qyy);

    return res;
}
template <typename T>
Matrix4G<T> Matrix4G<T>::ScaleMatrix(const Vector3G<T> &v)
{
    return Matrix4G<T>(v.x, 0, 0, 0, 0, v.y, 0, 0, 0, 0, v.z, 0, 0, 0, 0, 1);
}

template <typename T>
QuaternionG<T> Matrix4G<T>::ToQuaternion(const Matrix4G<T> &m)
{
    const auto fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
    const auto fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
    const auto fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
    const auto fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

    auto biggestIndex = 0;
    auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
    {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    const auto biggestVal =
        Math::Sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) *
        static_cast<T>(0.5);
    const auto mult = static_cast<T>(0.25) / biggestVal;

    QuaternionG<T> res;
    switch (biggestIndex)
    {
        case 0:
            res.x = (m.c1[2] - m.c2[1]) * mult;
            res.y = (m.c2[0] - m.c0[2]) * mult;
            res.z = (m.c0[1] - m.c1[0]) * mult;
            res.w = biggestVal;
            break;
        case 1:
            res.x = biggestVal;
            res.y = (m.c0[1] + m.c1[0]) * mult;
            res.z = (m.c2[0] + m.c0[2]) * mult;
            res.w = (m.c1[2] - m.c2[1]) * mult;
            break;
        case 2:
            res.x = (m.c0[1] + m.c1[0]) * mult;
            res.y = biggestVal;
            res.z = (m.c1[2] + m.c2[1]) * mult;
            res.w = (m.c2[0] - m.c0[2]) * mult;
            break;
        case 3:
            res.x = (m.c2[0] + m.c0[2]) * mult;
            res.y = (m.c1[2] + m.c2[1]) * mult;
            res.z = biggestVal;
            res.w = (m.c0[1] - m.c1[0]) * mult;
            break;
        default: break;
    }
    return res;
}

template <typename T>
Vector4G<T> &Matrix4G<T>::operator[](std::size_t i)
{
    switch (i)
    {
        case 0: return c0;
        case 1: return c1;
        case 2: return c2;
        case 3: return c3;
    }
    return c3;
}
template <typename T>
const Vector4G<T> &Matrix4G<T>::operator[](std::size_t i) const
{
    return const_cast<Matrix4G<T> *>(this)->operator[](i);
}

template <typename T>
const Matrix4G<T> &Matrix4G<T>::Identity()
{
    static const Matrix4G<T> m = Matrix4G<T>(1);
    return m;
}

template <typename T>
bool operator==(const Matrix4G<T> &m1, const Matrix4G<T> &m2)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
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
bool operator!=(const Matrix4G<T> &m1, const Matrix4G<T> &m2)
{
    return !(m1 == m2);
}

template <typename T>
Matrix4G<T> operator+(const Matrix4G<T> &m1, const Matrix4G<T> &m2)
{
    return Matrix4G<T>(
        m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]);
}
template <typename T>
Matrix4G<T> operator-(const Matrix4G<T> &m1, const Matrix4G<T> &m2)
{
    return Matrix4G<T>(
        m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]);
}
template <typename T>
Matrix4G<T> operator-(const Matrix4G<T> &m)
{
    return Matrix4G<T>(-m[0], -m[1], -m[2], -m[3]);
}
template <typename T>
Matrix4G<T> operator*(const Matrix4G<T> &m1, const Matrix4G<T> &m2)
{
    Matrix4G<T> m;
    m.c0 = Vector4G<T>((m1.c0.x * m2.c0.x) + (m1.c1.x * m2.c0.y) +
                           (m1.c2.x * m2.c0.z) + (m1.c3.x * m2.c0.w),
                       (m1.c0.y * m2.c0.x) + (m1.c1.y * m2.c0.y) +
                           (m1.c2.y * m2.c0.z) + (m1.c3.y * m2.c0.w),
                       (m1.c0.z * m2.c0.x) + (m1.c1.z * m2.c0.y) +
                           (m1.c2.z * m2.c0.z) + (m1.c3.z * m2.c0.w),
                       (m1.c0.w * m2.c0.x) + (m1.c1.w * m2.c0.y) +
                           (m1.c2.w * m2.c0.z) + (m1.c3.w * m2.c0.w));

    m.c1 = Vector4G<T>((m1.c0.x * m2.c1.x) + (m1.c1.x * m2.c1.y) +
                           (m1.c2.x * m2.c1.z) + (m1.c3.x * m2.c1.w),
                       (m1.c0.y * m2.c1.x) + (m1.c1.y * m2.c1.y) +
                           (m1.c2.y * m2.c1.z) + (m1.c3.y * m2.c1.w),
                       (m1.c0.z * m2.c1.x) + (m1.c1.z * m2.c1.y) +
                           (m1.c2.z * m2.c1.z) + (m1.c3.z * m2.c1.w),
                       (m1.c0.w * m2.c1.x) + (m1.c1.w * m2.c1.y) +
                           (m1.c2.w * m2.c1.z) + (m1.c3.w * m2.c1.w));

    m.c2 = Vector4G<T>((m1.c0.x * m2.c2.x) + (m1.c1.x * m2.c2.y) +
                           (m1.c2.x * m2.c2.z) + (m1.c3.x * m2.c2.w),
                       (m1.c0.y * m2.c2.x) + (m1.c1.y * m2.c2.y) +
                           (m1.c2.y * m2.c2.z) + (m1.c3.y * m2.c2.w),
                       (m1.c0.z * m2.c2.x) + (m1.c1.z * m2.c2.y) +
                           (m1.c2.z * m2.c2.z) + (m1.c3.z * m2.c2.w),
                       (m1.c0.w * m2.c2.x) + (m1.c1.w * m2.c2.y) +
                           (m1.c2.w * m2.c2.z) + (m1.c3.w * m2.c2.w));

    m.c3 = Vector4G<T>((m1.c0.x * m2.c3.x) + (m1.c1.x * m2.c3.y) +
                           (m1.c2.x * m2.c3.z) + (m1.c3.x * m2.c3.w),
                       (m1.c0.y * m2.c3.x) + (m1.c1.y * m2.c3.y) +
                           (m1.c2.y * m2.c3.z) + (m1.c3.y * m2.c3.w),
                       (m1.c0.z * m2.c3.x) + (m1.c1.z * m2.c3.y) +
                           (m1.c2.z * m2.c3.z) + (m1.c3.z * m2.c3.w),
                       (m1.c0.w * m2.c3.x) + (m1.c1.w * m2.c3.y) +
                           (m1.c2.w * m2.c3.z) + (m1.c3.w * m2.c3.w));
    return m;
}
template <typename T>
Vector4G<T> operator*(const Matrix4G<T> &m, const Vector4G<T> &v)
{
    return Vector4G<T>(
        (m.c0.x * v.x) + (m.c1.x * v.y) + (m.c2.x * v.z) + (m.c3.x * v.w),
        (m.c0.y * v.x) + (m.c1.y * v.y) + (m.c2.y * v.z) + (m.c3.y * v.w),
        (m.c0.z * v.x) + (m.c1.z * v.y) + (m.c2.z * v.z) + (m.c3.z * v.w),
        (m.c0.w * v.x) + (m.c1.w * v.y) + (m.c2.w * v.z) + (m.c3.w * v.w));
}
template <typename T>
void operator*=(Matrix4G<T> &m, const Matrix4G<T> &rhs)
{
    m = m * rhs;
}
template <typename T>
void operator+=(Matrix4G<T> &m, const Matrix4G<T> &rhs)
{
    m = m + rhs;
}
template <typename T>
void operator-=(Matrix4G<T> &m, const Matrix4G<T> &rhs)
{
    m = m - rhs;
}
}  // namespace Bang
