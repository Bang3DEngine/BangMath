#include "BangMath/Random.h"

#include "BangMath/Math.h"

namespace Bang
{
inline void Random::SetSeed(long seed)
{
    srand(seed);
}

template <typename T>
T Random::GetValue01()
{
    return static_cast<T>(rand()) / RAND_MAX;
}

inline unsigned long long Random::GetValueLong()
{
    return static_cast<unsigned long long>(rand());
}

template <typename T>
T Random::GetRange(T minIncluded, T maxExcluded)
{
    return static_cast<T>(Random::GetValue01() * (maxExcluded - minIncluded)) +
           minIncluded;
}

inline bool Random::GetBool()
{
    return (GetValue01() > 0.5f);
}

template <typename T>
Vector2G<T> Random::GetInsideUnitCircle()
{
    return Random::GetRandomVector2<T>().NormalizedSafe();
}

template <typename T>
Vector3G<T> Random::GetInsideUnitSphere()
{
    return Random::GetRandomVector3<T>().NormalizedSafe();
}

template <typename T>
Vector2G<T> Random::GetRandomVector2()
{
    return Vector2G<T>(Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f));
}

template <typename T>
Vector3G<T> Random::GetRandomVector3()
{
    return Vector3G<T>(Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f));
}

template <typename T>
Vector4G<T> Random::GetRandomVector4()
{
    return Vector4G<T>(Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f),
                       Random::GetRange(-1.0f, 1.0f));
}

template <typename T>
QuaternionG<T> Random::GetRotation()
{
    const T angle =
        Random::GetRange(0.0f, 2.0f * static_cast<T>(Math::Pi<T>()));
    return QuaternionG<T>::AngleAxis(angle, Random::GetInsideUnitSphere<T>());
}

template <typename T>
ColorG<T> Random::GetColor()
{
    return ColorG<T>(Random::GetValue01(),
                     Random::GetValue01(),
                     Random::GetValue01(),
                     Random::GetValue01());
}

template <typename T>
ColorG<T> Random::GetColorOpaque()
{
    return ColorG<T>(
        Random::GetValue01(), Random::GetValue01(), Random::GetValue01(), 1.0f);
}
}
