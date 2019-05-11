#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>

#include "BangMath/BangDefines.h"
#include "BangMath/Color.h"
#include "BangMath/String.h"

namespace Bang
{
class Random
{
public:
    static void SetSeed(long seed);
    static void SetSeed(const String &seed);

    template <typename T = float>
    static T GetValue01();

    template <typename T = uint64_t>
    static T GetValue();

    template <typename T>
    static T GetRange(T minIncluded, T maxExcluded);

    static bool GetBool();
    static Vector2G<T> GetInsideUnitCircle();
    static Vector3G<T> GetInsideUnitSphere();
    static Vector2G<T> GetRandomVector2();
    static Vector3G<T> GetRandomVector3();
    static Vector4G<T> GetRandomVector4();
    static Quaternion GetRotation();
    static Color GetColor();
    static Color GetColorOpaque();

private:
    Random();
};

template <typename T>
T Random::GetValue01()
{
    return SCAST<float>(rand()) / RAND_MAX;
}

template <typename T>
T Random::GetValue()
{
    return SCAST<T>(rand());
}

template <typename T>
T Random::GetRange(T minIncluded, T maxExcluded)
{
    return SCAST<T>(Random::GetValue01() * (maxExcluded - minIncluded)) +
           minIncluded;
}
}  // namespace Bang

#endif  // RANDOM_H
