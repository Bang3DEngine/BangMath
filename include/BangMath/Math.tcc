#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
constexpr T Math::Pi()
{
    return static_cast<T>(3.1415926535897932384626);
}

template <typename T>
constexpr T Math::Min()
{
    return std::numeric_limits<T>::min();
}

template <typename T>
constexpr T Math::Max()
{
    return std::numeric_limits<T>::max();
}

template <typename T>
constexpr T Math::Infinity()
{
    return std::numeric_limits<T>::infinity();
}

template <typename T>
constexpr T Math::NegativeInfinity()
{
    return -std::numeric_limits<T>::infinity();
}

template <typename T>
constexpr T Math::IsInfinity(T value)
{
    return std::isinf(value);
}

template <typename T>
constexpr T Math::IsNaN(T value)
{
    return std::isnan(value);
}

template <typename T>
constexpr T Math::Min(T a, T b)
{
    return (a <= b) ? a : b;
}

template <typename T>
constexpr T Math::Max(T a, T b)
{
    return (a >= b) ? a : b;
}

template <typename T, class T2, class T3>
constexpr T Math::Clamp(T value, const T2 &min, const T3 &max)
{
    return Math::Min(Math::Max(static_cast<T>(value), static_cast<T>(min)),
                     static_cast<T>(max));
}

template <typename T>
constexpr T Math::Abs(T value)
{
    return value < 0 ? -value : value;
}

template <typename T, class T2>
constexpr T Math::Round(const T2 &value)
{
    return static_cast<T>(std::round(value));
}

template <typename T>
constexpr T Math::Ceil(T value)
{
    return std::ceil(value);
}

template <typename T>
constexpr T Math::Floor(T value)
{
    return std::floor(value);
}

template <typename T>
constexpr T Math::Fract(T value)
{
    return value - Math::Floor(value);
}

template <typename T>
constexpr T Math::Pow(T base, T exponent)
{
    return static_cast<T>(std::pow(base, exponent));
}

template <typename T>
constexpr T Math::Log(T value)
{
    return static_cast<T>(std::log(value));
}

template <typename T>
constexpr T Math::Log10(T value)
{
    return std::log10(value);
}

template <typename T>
constexpr T Math::Exp(T x)
{
    return static_cast<T>(std::exp(x));
}

template <typename T>
constexpr T Math::Sqrt(T x)
{
    return static_cast<T>(std::sqrt(x));
}

template <typename T>
constexpr T Math::Sin(T rad)
{
    return static_cast<T>(std::sin(rad));
}

template <typename T>
constexpr T Math::Cos(T rad)
{
    return static_cast<T>(std::cos(rad));
}

template <typename T>
constexpr T Math::Tan(T rad)
{
    return static_cast<T>(std::tan(rad));
}

template <typename T>
constexpr T Math::Sinh(T rad)
{
    return std::sinh(rad);
}

template <typename T>
constexpr T Math::Cosh(T rad)
{
    return std::cosh(rad);
}

template <typename T>
constexpr T Math::Tanh(T rad)
{
    return std::tanh(rad);
}

template <typename T>
constexpr T Math::ASin(T value)
{
    return std::asin(value);
}

template <typename T>
constexpr T Math::ACos(T value)
{
    return std::acos(value);
}

template <typename T>
constexpr T Math::ATan(T value)
{
    return std::atan(value);
}

template <typename T>
constexpr T Math::ASinh(T value)
{
    return std::asinh(value);
}

template <typename T>
constexpr T Math::ACosh(T value)
{
    return std::acosh(value);
}

template <typename T>
constexpr T Math::ATanh(T value)
{
    return std::atanh(value);
}

template <typename T>
constexpr T Math::ATan2(T valueX, T valueY)
{
    return std::atan2(valueX, valueY);
}

template <typename T>
constexpr T Math::FMod(T value, T length)
{
    return std::fmod(value, length);
}

template <typename T>
constexpr T Math::FModAbs(T value, T length)
{
    return (value < 0 ? Math::FMod(Math::FMod(value, length) + length, length)
                      : Math::FMod(value, length));
}

template <typename T>
constexpr T Math::Sign(T value)
{
    return static_cast<T>(value < 0 ? -1 : 1);
}

template <typename T>
constexpr T Math::Lerp(T a, T b, T t)
{
    return (b - a) * t + a;
}

template <typename T>
constexpr T Math::Map(T value, T srcMin, T srcMax, T destMin, T destMax)
{
    return ((value - srcMin) / (srcMax - srcMin)) * (destMax - destMin) +
           destMin;
}

template <typename T>
bool constexpr Math::Equals(T lhs, T rhs, T diff)
{
    return (Math::Abs(lhs - rhs) <= diff);
}

template <typename T>
constexpr bool Math::IsInt(T v, T tolerance)
{
    return (Math::Abs(v - Math::Round(v)) < tolerance);
}

template <typename T>
constexpr bool Math::IsPowerOfTwo(T v)
{
    return Math::IsInt(Math::Log10(float(v)) / Math::Log10(float(2.0)));
}

template <typename T>
constexpr T Math::DegToRad(T deg)
{
    return deg * static_cast<T>(Math::DegToRad<T>());
}

template <typename T>
constexpr T Math::RadToDeg(T rad)
{
    return rad * static_cast<T>(Math::RadToDeg<T>());
}

template <typename T>
constexpr T Math::RadToDeg()
{
    return 180.0 / Math::Pi<T>();
}

template <typename T>
constexpr T Math::DegToRad()
{
    return Math::Pi<T>() / 180.0;
}
}
