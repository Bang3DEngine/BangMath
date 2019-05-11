#pragma once

namespace Bang
{
template <typename T>
class Matrix4G;
template <typename T>
class Vector3G;
template <typename T>
class Vector4G;
template <typename T>
class QuaternionG;

template <typename T>
class TransformationG
{
public:
    TransformationG() = default;
    TransformationG(const Vector3G<T> &position,
                    const QuaternionG<T> &rotation,
                    const Vector3G<T> &scale);
    explicit TransformationG(const Matrix4G<T> &transformationMatrix);

    static const TransformationG<T> &Identity();

    TransformationG<T> Inversed() const;
    Matrix4G<T> GetMatrix() const;
    Matrix4G<T> GetMatrixInverse() const;
    void FillFromMatrix(const Matrix4G<T> &transformMatrix);

    void SetPosition(const Vector3G<T> &position);
    void SetRotation(const QuaternionG<T> &rotation);
    void SetScale(const Vector3G<T> &scale);
    void LookAt(const Vector3G<T> &target,
                const Vector3G<T> &up = Vector3G<T>::Up());
    void LookInDirection(const Vector3G<T> &dir,
                         const Vector3G<T> &up = Vector3G<T>::Up());

    void Translate(const Vector3G<T> &translation);
    void Rotate(const QuaternionG<T> &rotation);
    void Scale(const Vector3G<T> &scale);

    static TransformationG<T> Composed(const TransformationG<T> &lhs,
                                       const TransformationG<T> &rhs);
    Vector3G<T> TransformedPoint(const Vector3G<T> &point);
    Vector3G<T> TransformedVector(const Vector3G<T> &vector);

    Vector3G<T> FromLocalToWorldPoint(const Vector3G<T> &point) const;
    Vector3G<T> FromLocalToWorldVector(const Vector3G<T> &vector) const;
    Vector3G<T> FromLocalToWorldDirection(const Vector3G<T> &dir) const;
    Vector3G<T> FromWorldToLocalPoint(const Vector3G<T> &point) const;
    Vector3G<T> FromWorldToLocalVector(const Vector3G<T> &vector) const;
    Vector3G<T> FromWorldToLocalDirection(const Vector3G<T> &dir) const;

    const Vector3G<T> &GetPosition() const;
    const QuaternionG<T> &GetRotation() const;
    const Vector3G<T> &GetScale() const;
    Vector3G<T> GetForward() const;
    Vector3G<T> GetBack() const;
    Vector3G<T> GetRight() const;
    Vector3G<T> GetLeft() const;
    Vector3G<T> GetUp() const;
    Vector3G<T> GetDown() const;

private:
    Vector3G<T> m_position = Vector3G<T>::Zero();
    QuaternionG<T> m_rotation = QuaternionG<T>::Identity();
    Vector3G<T> m_scale = Vector3G<T>::One();
};

template <typename T>
inline bool operator==(const TransformationG<T> &lhs,
                       const TransformationG<T> &rhs)
{
    return (lhs.GetPosition() == rhs.GetPosition()) &&
           (lhs.GetRotation() == rhs.GetRotation()) &&
           (lhs.GetScale() == rhs.GetScale());
}

template <typename T>
inline bool operator!=(const TransformationG<T> &lhs,
                       const TransformationG<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
inline TransformationG<T> operator*(const TransformationG<T> &lhs,
                                    const TransformationG<T> &rhs)
{
    return TransformationG<T>::Composed(lhs, rhs);
}

template <typename T>
inline Vector4G<T> operator*(const TransformationG<T> &tr, const Vector4G<T> &v)
{
    return tr.GetMatrix() * v;
}

template <typename T>
inline void operator*=(TransformationG<T> &lhs, const TransformationG<T> &rhs)
{
    lhs = (lhs * rhs);
}
}
