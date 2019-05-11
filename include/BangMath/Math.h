#ifndef MATH_H
#define MATH_H

#include <cmath>
#include <limits>

namespace Bang
{
class Math
{
public:
    template <typename T>
    static constexpr T Pi()
    {
        return static_cast<T>(3.1415926535897932384626);
    }

    Math() = delete;

    template <typename T>
    static constexpr T Min()
    {
        return std::numeric_limits<T>::min();
    }

    template <typename T>
    static constexpr T Max()
    {
        return std::numeric_limits<T>::max();
    }

    template <typename T>
    static constexpr T Infinity()
    {
        return std::numeric_limits<T>::infinity();
    }

    template <typename T>
    static constexpr T NaN()
    {
        return 0;
    }

    template <typename T>
    static constexpr T NegativeInfinity()
    {
        return -std::numeric_limits<T>::infinity();
    }

    template <typename T>
    static constexpr T IsInfinity(T value)
    {
        return std::isinf(value);
    }

    template <typename T>
    static constexpr T IsNaN(T value)
    {
        return std::isnan(value);
    }

    template <typename T>
    static constexpr T Min(T a, T b)
    {
        return (a <= b) ? a : b;
    }

    template <typename T>
    static constexpr T Max(T a, T b)
    {
        return (a >= b) ? a : b;
    }

    template <typename T, class T2, class T3>
    static constexpr T Clamp(T value, const T2 &min, const T3 &max)
    {
        return Math::Min(Math::Max(static_cast<T>(value), static_cast<T>(min)),
                         static_cast<T>(max));
    }

    template <typename T>
    static constexpr T Abs(T value)
    {
        return value < 0 ? -value : value;
    }

    template <typename T = int, class T2>
    static constexpr T Round(const T2 &value)
    {
        return static_cast<T>(std::round(value));
    }

    template <typename T>
    static constexpr T Ceil(T value)
    {
        return std::ceil(value);
    }

    template <typename T>
    static constexpr T Floor(T value)
    {
        return std::floor(value);
    }

    template <typename T>
    static constexpr T Fract(T value)
    {
        return value - Math::Floor(value);
    }

    template <typename T>
    static constexpr T Pow(T base, T exponent)
    {
        return static_cast<T>(std::pow(base, exponent));
    }

    template <typename T>
    static constexpr T Log(T value)
    {
        return static_cast<T>(std::log(value));
    }

    template <typename T>
    static constexpr T Log10(T value)
    {
        return std::log10(value);
    }

    template <typename T>
    static constexpr T Exp(T x)
    {
        return static_cast<T>(std::exp(x));
    }

    template <typename T>
    static constexpr T Sqrt(T x)
    {
        return static_cast<T>(std::sqrt(x));
    }

    template <typename T>
    static constexpr T Sin(T rad)
    {
        return static_cast<T>(std::sin(rad));
    }

    template <typename T>
    static constexpr T Cos(T rad)
    {
        return static_cast<T>(std::cos(rad));
    }

    template <typename T>
    static constexpr T Tan(T rad)
    {
        return static_cast<T>(std::tan(rad));
    }

    template <typename T>
    static constexpr T Sinh(T rad)
    {
        return std::sinh(rad);
    }

    template <typename T>
    static constexpr T Cosh(T rad)
    {
        return std::cosh(rad);
    }

    template <typename T>
    static constexpr T Tanh(T rad)
    {
        return std::tanh(rad);
    }

    template <typename T>
    static constexpr T ASin(T value)
    {
        return std::asin(value);
    }

    template <typename T>
    static constexpr T ACos(T value)
    {
        return std::acos(value);
    }

    template <typename T>
    static constexpr T ATan(T value)
    {
        return std::atan(value);
    }

    template <typename T>
    static constexpr T ASinh(T value)
    {
        return std::asinh(value);
    }

    template <typename T>
    static constexpr T ACosh(T value)
    {
        return std::acosh(value);
    }

    template <typename T>
    static constexpr T ATanh(T value)
    {
        return std::atanh(value);
    }

    template <typename T>
    static constexpr T ATan2(T valueX, T valueY)
    {
        return std::atan2(valueX, valueY);
    }

    template <typename T>
    static constexpr T FMod(T value, T length)
    {
        return std::fmod(value, length);
    }

    template <typename T>
    static constexpr T FModAbs(T value, T length)
    {
        return (value < 0
                    ? Math::FMod(Math::FMod(value, length) + length, length)
                    : Math::FMod(value, length));
    }

    template <typename T>
    static constexpr T Sign(T value)
    {
        return static_cast<T>(value < 0 ? -1 : 1);
    }

    template <typename T>
    static constexpr T Lerp(T a, T b, T t)
    {
        return (b - a) * t + a;
    }

    template <typename T>
    static constexpr T Map(T value, T srcMin, T srcMax, T destMin, T destMax)
    {
        return ((value - srcMin) / (srcMax - srcMin)) * (destMax - destMin) +
               destMin;
    }

    template <typename T>
    static bool constexpr Equals(T lhs, T rhs, T diff)
    {
        return (Math::Abs(lhs - rhs) <= diff);
    }

    template <typename T>
    static constexpr bool IsInt(T v, T tolerance = 0.0001)
    {
        return (Math::Abs(v - Math::Round(v)) < tolerance);
    }

    template <typename T>
    static constexpr bool IsPowerOfTwo(T v)
    {
        return Math::IsInt(Math::Log10(v) / Math::Log10(static_cast<T>(2.0)));
    }

    template <typename T>
    static constexpr T DegToRad(T deg)
    {
        return deg * static_cast<T>(Math::DegToRad);
    }

    template <typename T>
    static constexpr T RadToDeg(T rad)
    {
        return rad * static_cast<T>(Math::RadToDeg);
    }

private:
    template <typename T>
    static constexpr T RadToDeg()
    {
        return 180.0 / Math::Pi<T>();
    }

    template <typename T>
    static constexpr T DegToRad()
    {
        return Math::Pi<T>() / 180.0;
    }
};

template <>
inline double Math::NaN()
{
    return std::nan("");
}

template <>
inline float Math::NaN()
{
    return std::nanf("");
}
}  // namespace Bang

#endif  // MATH_H
