#pragma once

#include <cmath>
#include <limits>

namespace Bang
{
class Math
{
public:
    template <typename T>
    static constexpr T Pi();

    template <typename T>
    static constexpr T Min();

    template <typename T>
    static constexpr T Max();

    template <typename T>
    static constexpr T Infinity();

    template <typename T>
    static constexpr T NegativeInfinity();

    template <typename T>
    static constexpr T IsInfinity(T value);

    template <typename T>
    static constexpr T IsNaN(T value);

    template <typename T>
    static constexpr T Min(T a, T b);

    template <typename T>
    static constexpr T Max(T a, T b);

    template <typename T, class T2, class T3>
    static constexpr T Clamp(T value, const T2 &min, const T3 &max);

    template <typename T>
    static constexpr T Abs(T value);

    template <typename T = int, class T2>
    static constexpr T Round(const T2 &value);

    template <typename T>
    static constexpr T Ceil(T value);

    template <typename T>
    static constexpr T Floor(T value);

    template <typename T>
    static constexpr T Fract(T value);

    template <typename T>
    static constexpr T Pow(T base, T exponent);

    template <typename T>
    static constexpr T Log(T value);

    template <typename T>
    static constexpr T Log10(T value);

    template <typename T>
    static constexpr T Exp(T x);

    template <typename T>
    static constexpr T Sqrt(T x);

    template <typename T>
    static constexpr T Sin(T rad);

    template <typename T>
    static constexpr T Cos(T rad);

    template <typename T>
    static constexpr T Tan(T rad);

    template <typename T>
    static constexpr T Sinh(T rad);

    template <typename T>
    static constexpr T Cosh(T rad);

    template <typename T>
    static constexpr T Tanh(T rad);

    template <typename T>
    static constexpr T ASin(T value);

    template <typename T>
    static constexpr T ACos(T value);

    template <typename T>
    static constexpr T ATan(T value);

    template <typename T>
    static constexpr T ASinh(T value);

    template <typename T>
    static constexpr T ACosh(T value);

    template <typename T>
    static constexpr T ATanh(T value);

    template <typename T>
    static constexpr T ATan2(T valueX, T valueY);

    template <typename T>
    static constexpr T FMod(T value, T length);

    template <typename T>
    static constexpr T FModAbs(T value, T length);

    template <typename T>
    static constexpr T Sign(T value);

    template <typename T>
    static constexpr T Lerp(T a, T b, T t);

    template <typename T>
    static constexpr T Map(T value, T srcMin, T srcMax, T destMin, T destMax);

    template <typename T>
    static bool constexpr Equals(T lhs, T rhs, T diff);

    template <typename T>
    static constexpr bool IsInt(T v, T tolerance = 0.0001);

    template <typename T>
    static constexpr bool IsPowerOfTwo(T v);

    template <typename T>
    static constexpr T DegToRad(T deg);

    template <typename T>
    static constexpr T RadToDeg(T rad);

    Math() = delete;

private:
    template <typename T>
    static constexpr T RadToDeg();

    template <typename T>
    static constexpr T DegToRad();
};

}  // namespace Bang

#include "BangMath/Math.tcc"
