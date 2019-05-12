#pragma once
#include "BangMath/Transformation.h"

#include "BangMath/Matrix4.h"
#include "BangMath/Quaternion.h"
#include "BangMath/Vector3.h"

namespace Bang
{
template <typename T>
TransformationG<T>::TransformationG(const Vector3G<T> &position,
                                    const QuaternionG<T> &rotation,
                                    const Vector3G<T> &scale)
{
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
}

template <typename T>
TransformationG<T>::TransformationG(const Matrix4G<T> &transformationMatrix)
{
    FillFromMatrix(transformationMatrix);
}

template <typename T>
const TransformationG<T> &TransformationG<T>::Identity()
{
    static const TransformationG identity;
    return identity;
}

template <typename T>
TransformationG<T> TransformationG<T>::Inversed() const
{
    return TransformationG(
        -GetPosition(), GetRotation().Inversed(), 1.0f / GetScale());
}

template <typename T>
Matrix4G<T> TransformationG<T>::GetMatrix() const
{
    return Matrix4G<T>::TransformMatrixInverse(
        GetPosition(), GetRotation(), GetScale());
}

template <typename T>
Matrix4G<T> TransformationG<T>::GetMatrixInverse() const
{
    return Matrix4::TransformMatrix(GetPosition(), GetRotation(), GetScale());
}

template <typename T>
void TransformationG<T>::FillFromMatrix(const Matrix4G<T> &transformMatrix)
{
    Vector3G<T> position = transformMatrix.GetTranslation();
    QuaternionG<T> rotation = transformMatrix.GetRotation();
    Vector3G<T> scale = transformMatrix.GetScale();
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
}

template <typename T>
void TransformationG<T>::SetPosition(const Vector3G<T> &position)
{
    m_position = position;
}

template <typename T>
void TransformationG<T>::SetRotation(const QuaternionG<T> &rotation)
{
    m_rotation = rotation;
}

template <typename T>
void TransformationG<T>::SetScale(const Vector3G<T> &scale)
{
    m_scale = scale;
}

template <typename T>
void TransformationG<T>::LookAt(const Vector3G<T> &target,
                                const Vector3G<T> &up)
{
    if (target != GetPosition())
    {
        SetRotation(Quaternion::LookDirection(target - GetPosition(), up));
    }
}

template <typename T>
void TransformationG<T>::LookInDirection(const Vector3G<T> &dir,
                                         const Vector3G<T> &up)
{
    LookAt(GetPosition() + dir, up);
}

template <typename T>
void TransformationG<T>::Translate(const Vector3G<T> &translation)
{
    SetPosition(GetPosition() + translation);
}

template <typename T>
void TransformationG<T>::Rotate(const QuaternionG<T> &rotation)
{
    SetRotation(rotation * GetRotation());
}

template <typename T>
void TransformationG<T>::Scale(const Vector3G<T> &scale)
{
    SetScale(scale * GetScale());
}

template <typename T>
TransformationG<T> TransformationG<T>::Composed(const TransformationG<T> &lhs,
                                                const TransformationG<T> &rhs)
{
    const Vector3G<T> &lp = lhs.GetPosition();
    const QuaternionG<T> &lr = lhs.GetRotation();
    const Vector3G<T> &ls = lhs.GetScale();
    const Vector3G<T> &rp = rhs.GetPosition();
    const QuaternionG<T> &rr = rhs.GetRotation();
    const Vector3G<T> &rs = rhs.GetScale();

    TransformationG<T> newTransformation;
    newTransformation.SetPosition(lp + (lr * (ls * rp)));
    newTransformation.SetRotation(lr * rr);
    newTransformation.SetScale(ls * rs);

    return newTransformation;
}

template <typename T>
Vector3G<T> TransformationG<T>::TransformedPoint(const Vector3G<T> &point)
{
    return ((*this) * Vector4(point, 1)).xyz();
}

template <typename T>
Vector3G<T> TransformationG<T>::TransformedVector(const Vector3G<T> &vector)
{
    return ((*this) * Vector4(vector, 0)).xyz();
}

template <typename T>
Vector3G<T> TransformationG<T>::FromLocalToWorldPoint(
    const Vector3G<T> &point) const
{
    return GetMatrix().TransformedPoint(point);
}

template <typename T>
Vector3G<T> TransformationG<T>::FromLocalToWorldVector(
    const Vector3G<T> &vector) const
{
    return GetMatrix().TransformedVector(vector);
}

template <typename T>
Vector3G<T> TransformationG<T>::FromLocalToWorldDirection(
    const Vector3G<T> &dir) const
{
    return GetRotation() * dir;
}

template <typename T>
Vector3G<T> TransformationG<T>::FromWorldToLocalPoint(
    const Vector3G<T> &point) const
{
    return GetMatrixInverse().TransformedPoint(point);
}

template <typename T>
Vector3G<T> TransformationG<T>::FromWorldToLocalVector(
    const Vector3G<T> &vector) const
{
    return GetMatrixInverse().TransformedVector(vector);
}

template <typename T>
Vector3G<T> TransformationG<T>::FromWorldToLocalDirection(
    const Vector3G<T> &dir) const
{
    return GetRotation().Inversed() * dir;
}

template <typename T>
const Vector3G<T> &TransformationG<T>::GetPosition() const
{
    return m_position;
}

template <typename T>
const QuaternionG<T> &TransformationG<T>::GetRotation() const
{
    return m_rotation;
}

template <typename T>
const Vector3G<T> &TransformationG<T>::GetScale() const
{
    return m_scale;
}

template <typename T>
Vector3G<T> TransformationG<T>::GetForward() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Forward());
}

template <typename T>
Vector3G<T> TransformationG<T>::GetBack() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Back());
}

template <typename T>
Vector3G<T> TransformationG<T>::GetRight() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Right());
}

template <typename T>
Vector3G<T> TransformationG<T>::GetLeft() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Left());
}

template <typename T>
Vector3G<T> TransformationG<T>::GetUp() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Up());
}

template <typename T>
Vector3G<T> TransformationG<T>::GetDown() const
{
    return FromLocalToWorldDirection(Vector3G<T>::Down());
}
};
