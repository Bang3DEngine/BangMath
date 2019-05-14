#pragma once

#include <cstdlib>
#include <cstddef>

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
class ColorG;
template <typename>
class QuaternionG;

class Random
{
public:
    static void SetSeed(long seed);

    template <typename T = MathDefaultType>
    static T GetValue01();

    static unsigned long long GetValueLong();

    template <typename T = MathDefaultType>
    static T GetRange(T minIncluded, T maxExcluded);

    static bool GetBool();

    template <typename T = MathDefaultType>
    static Vector2G<T> GetInsideUnitCircle();

    template <typename T = MathDefaultType>
    static Vector3G<T> GetInsideUnitSphere();

    template <typename T = MathDefaultType>
    static Vector2G<T> GetRandomVector2();

    template <typename T = MathDefaultType>
    static Vector3G<T> GetRandomVector3();

    template <typename T = MathDefaultType>
    static Vector4G<T> GetRandomVector4();

    template <typename T = MathDefaultType>
    static QuaternionG<T> GetRotation();

    template <typename T = MathDefaultType>
    static ColorG<T> GetColor();

    template <typename T = MathDefaultType>
    static ColorG<T> GetColorOpaque();

    Random() = delete;
};

}  // namespace Bang

#include "BangMath/Random.tcc"
