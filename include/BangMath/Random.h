#ifndef RANDOM_H
#define RANDOM_H

#include <cstdlib>

#include "BangMath/Color.h"

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

    template <typename T = float>
    static T GetValue01();

    template <typename T = uint64_t>
    static T GetValue();

    template <typename T = float>
    static T GetRange(T minIncluded, T maxExcluded);

    static bool GetBool();

    template <typename T = float>
    static Vector2G<T> GetInsideUnitCircle();

    template <typename T = float>
    static Vector3G<T> GetInsideUnitSphere();

    template <typename T = float>
    static Vector2G<T> GetRandomVector2();

    template <typename T = float>
    static Vector3G<T> GetRandomVector3();

    template <typename T = float>
    static Vector4G<T> GetRandomVector4();

    template <typename T = float>
    static QuaternionG<T> GetRotation();

    template <typename T = float>
    static ColorG<T> GetColor();

    template <typename T = float>
    static ColorG<T> GetColorOpaque();

    Random() = delete;
};

}  // namespace Bang

#include "BangMath/Random.tcc"

#endif  // RANDOM_H
