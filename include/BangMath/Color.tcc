#include "BangMath/Color.h"

#include <cmath>
#include <sstream>

#include "BangMath/Math.h"

namespace Bang
{
template <typename T>
ColorG<T>::ColorG(T m) : ColorG<T>(m, m, m, m)
{
}

template <typename T>
ColorG<T>::ColorG(const Vector2G<T> &v, T b, T a) : ColorG<T>(v.x, v.y, b, a)
{
}

template <typename T>
ColorG<T>::ColorG(const Vector3G<T> &v, T a) : ColorG<T>(v.x, v.y, v.z, a)
{
}

template <typename T>
ColorG<T>::ColorG(const Vector4G<T> &v) : ColorG<T>(v.x, v.y, v.z, v.w)
{
}

template <typename T>
ColorG<T>::ColorG(T r, T g, T b) : ColorG<T>(r, g, b, 1)
{
}

template <typename T>
ColorG<T>::ColorG(T r, T g, T b, T a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

template <typename T>
ColorG<T>::ColorG(const ColorG<T> &c, T a) : ColorG<T>(c.r, c.g, c.b, a)
{
}

template <typename T>
ColorG<T> ColorG<T>::Lerp(const ColorG<T> &c1, const ColorG<T> &c2, T t)
{
    return ColorG<T>(Vector4G<T>::Lerp(Vector4G<T>(c1.r, c1.g, c1.b, c1.a),
                                       Vector4G<T>(c2.r, c2.g, c2.b, c2.a),
                                       t));
}

template <typename T>
ColorG<T> ColorG<T>::WithAlpha(T alpha) const
{
    return ColorG<T>(r, g, b, alpha);
}

template <typename T>
ColorG<T> ColorG<T>::WithValue(T value) const
{
    return ColorG<T>(r * value, g * value, b * value, a);
}

template <typename T>
ColorG<T> ColorG<T>::WithSaturation(T saturation) const
{
    auto c = *this;
    const auto length = Math::Sqrt(c.r * c.r + c.g * c.g + c.b * c.b);

    c.r = length + (c.r - length) * saturation;
    c.g = length + (c.g - length) * saturation;
    c.b = length + (c.b - length) * saturation;

    return c;
}

template <typename T>
ColorG<T> ColorG<T>::ToHSV() const
{
    // In:  RGB([0,1], [0,1], [0,1], [0,1])
    // Out: HSV([0,1], [0,1], [0,1], [0,1])

    const auto fCMax = Math::Max(Math::Max(r, g), b);
    const auto fCMin = Math::Min(Math::Min(r, g), b);
    const auto fDelta = fCMax - fCMin;

    T h, s, v;
    if (fDelta > 0)
    {
        if (fCMax == r)
        {
            h = 60 * (fmod(((g - b) / fDelta), 6));
        }
        else if (fCMax == g)
        {
            h = 60 * (((b - r) / fDelta) + 2);
        }
        else
        {
            h = 60 * (((r - g) / fDelta) + 4);
        }

        if (fCMax > 0)
        {
            s = fDelta / fCMax;
        }
        else
        {
            s = 0;
        }
        v = fCMax;
    }
    else
    {
        h = 0;
        s = 0;
        v = fCMax;
    }

    if (h < 0)
    {
        h = 360 + h;
    }
    h /= 360.0f;

    return ColorG<T>(h, s, v, a);
}

template <typename T>
ColorG<T> ColorG<T>::ToRGB() const
{
    // In:  HSV([0,1], [0,1], [0,1], [0,1])
    // Out: RGB([0,1], [0,1], [0,1], [0,1])

    const auto &h = r;
    const auto &s = g;
    const auto &v = b;

    const auto i = static_cast<int>(Math::Floor(h * 6));
    const auto f = h * 6 - i;
    const auto p = v * (1 - s);
    const auto q = v * (1 - f * s);
    const auto t = v * (1 - (1 - f) * s);

    T newR, newG, newB;
    switch (i % 6)
    {
        case 0:
            newR = v;
            newG = t;
            newB = p;
            break;
        case 1:
            newR = q;
            newG = v;
            newB = p;
            break;
        case 2:
            newR = p;
            newG = v;
            newB = t;
            break;
        case 3:
            newR = p;
            newG = q;
            newB = v;
            break;
        case 4:
            newR = t;
            newG = p;
            newB = v;
            break;
        case 5:
            newR = v;
            newG = p;
            newB = q;
            break;
        default: newR = newG = newB = 0.0f; break;
    }

    return ColorG<T>(newR, newG, newB, a);
}

template <typename T>
Vector3G<T> ColorG<T>::ToVector3() const
{
    return Vector3G<T>(r, g, b);
}

template <typename T>
Vector4G<T> ColorG<T>::ToVector4() const
{
    return Vector4G<T>(r, g, b, a);
}

template <typename T>
ColorG<T> ColorG<T>::FromVector3(const Vector3G<T> &v)
{
    return ColorG<T>(v.x, v.y, v.z, 1);
}

template <typename T>
ColorG<T> ColorG<T>::FromVector4(const Vector4G<T> &v)
{
    return ColorG<T>(v.x, v.y, v.z, v.w);
}

template <typename T>
T &ColorG<T>::operator[](int i)
{
    return (reinterpret_cast<T *>(this))[i];
}

template <typename T>
const T &ColorG<T>::operator[](int i) const
{
    return (reinterpret_cast<const T *>(this))[i];
}

template <typename T>
ColorG<T> operator+(const ColorG<T> &c1, const ColorG<T> &c2)
{
    return ColorG<T>(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a * c2.a);
}

template <typename T>
ColorG<T> operator*(const ColorG<T> &c1, const ColorG<T> &c2)
{
    return ColorG<T>(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a);
}

template <typename T>
ColorG<T> operator-(const ColorG<T> &c)
{
    return ColorG<T>(-c.r, -c.g, -c.b, -c.a);
}

template <typename T>
ColorG<T> operator*(const ColorG<T> &c, T m)
{
    return m * c;
}

template <typename T>
ColorG<T> operator*(T m, const ColorG<T> &c)
{
    return ColorG<T>(m * c.r, m * c.g, m * c.b, m * c.a);
}

template <typename T>
ColorG<T> operator/(T m, const ColorG<T> &c)
{
    return ColorG<T>(m / c.r, m / c.g, m / c.b, m / c.a);
}

template <typename T>
ColorG<T> operator/(const ColorG<T> &c, T m)
{
    return ColorG<T>(c.r / m, c.g / m, c.b / m, c.a / m);
}

template <typename T>
ColorG<T> operator/(const ColorG<T> &c1, const ColorG<T> &c2)
{
    return ColorG<T>(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b, c1.a / c2.a);
}

template <typename T>
ColorG<T> &operator+=(ColorG<T> &lhs, const ColorG<T> &rhs)
{
    lhs.r += rhs.r;
    lhs.g += rhs.g;
    lhs.b += rhs.b;
    lhs.a += rhs.a;
    return lhs;
}

template <typename T>
ColorG<T> &operator-=(ColorG<T> &lhs, const ColorG<T> &rhs)
{
    lhs.r -= rhs.r;
    lhs.g -= rhs.g;
    lhs.b -= rhs.b;
    lhs.a -= rhs.a;
    return lhs;
}

template <typename T>
ColorG<T> &operator*=(ColorG<T> &lhs, const ColorG<T> &rhs)
{
    lhs.r *= rhs.r;
    lhs.g *= rhs.g;
    lhs.b *= rhs.b;
    lhs.a *= rhs.a;
    return lhs;
}

template <typename T>
ColorG<T> &operator/=(ColorG<T> &lhs, const ColorG<T> &rhs)
{
    lhs.r /= rhs.r;
    lhs.g /= rhs.g;
    lhs.b /= rhs.b;
    lhs.a /= rhs.a;
    return lhs;
}

template <typename T>
ColorG<T> operator+(T m, const ColorG<T> &c)
{
    return ColorG<T>(m + c.r, m + c.g, m + c.b, m + c.a);
}

template <typename T>
ColorG<T> operator+(const ColorG<T> &c, T m)
{
    return m + c;
}

template <typename T>
ColorG<T> operator-(const ColorG<T> &c1, const ColorG<T> &c2)
{
    return ColorG<T>(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a);
}

template <typename T>
ColorG<T> operator-(T m, const ColorG<T> &c)
{
    return ColorG<T>(m - c.r, m - c.g, m - c.b, m - c.a);
}

template <typename T>
ColorG<T> operator-(const ColorG<T> &c, T m)
{
    return ColorG<T>(c.r - m, c.g - m, c.b - m, c.a - m);
}

template <typename T>
ColorG<T> &operator+=(ColorG<T> &lhs, T m)
{
    lhs.r += m;
    lhs.g += m;
    lhs.b += m;
    lhs.a += m;
    return lhs;
}

template <typename T>
ColorG<T> &operator-=(ColorG<T> &lhs, T m)
{
    lhs.r -= m;
    lhs.g -= m;
    lhs.b -= m;
    lhs.a -= m;
    return lhs;
}

template <typename T>
ColorG<T> &operator*=(ColorG<T> &lhs, T m)
{
    lhs.r *= m;
    lhs.g *= m;
    lhs.b *= m;
    lhs.a *= m;
    return lhs;
}

template <typename T>
ColorG<T> &operator/=(ColorG<T> &lhs, T m)
{
    lhs.r /= m;
    lhs.g /= m;
    lhs.b /= m;
    lhs.a /= m;
    return lhs;
}

template <typename T>
bool operator==(const ColorG<T> &lhs, const ColorG<T> &rhs)
{
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

template <typename T>
bool operator!=(const ColorG<T> &lhs, const ColorG<T> &rhs)
{
    return !(lhs == rhs);
}

template <typename T>
const ColorG<T> &ColorG<T>::Red()
{
    static const auto c = ColorG<T>(1, 0, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Orange()
{
    static const auto c = ColorG<T>(1, 0.5f, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Yellow()
{
    static const auto c = ColorG<T>(1, 1, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Green()
{
    static const auto c = ColorG<T>(0, 1, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Turquoise()
{
    static const auto c = ColorG<T>(1, 1, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::VeryLightBlue()
{
    static const auto c = ColorG<T>(0.8f, 0.95f, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::LightBlue()
{
    static const auto c = ColorG<T>(0.7f, 0.9f, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Blue()
{
    static const auto c = ColorG<T>(0, 0, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::DarkBlue()
{
    static const auto c = ColorG<T>(0, 0, 0.6f, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Purple()
{
    static const auto c = ColorG<T>(0.5f, 0, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Pink()
{
    static const auto c = ColorG<T>(1, 0, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Black()
{
    static const auto c = ColorG<T>(0, 0, 0, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::LightGray()
{
    static const auto c = ColorG<T>(0.8f, 0.8f, 0.8f, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::DarkGray()
{
    static const auto c = ColorG<T>(0.3f, 0.3f, 0.3f, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Gray()
{
    static const auto c = ColorG<T>(0.5f, 0.5f, 0.5f, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::White()
{
    static const auto c = ColorG<T>(1, 1, 1, 1);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::Zero()
{
    static const auto c = ColorG<T>(0, 0, 0, 0);
    return c;
}

template <typename T>
const ColorG<T> &ColorG<T>::One()
{
    static const auto c = ColorG<T>(1, 1, 1, 1);
    return c;
}
}  // namespace Bang
