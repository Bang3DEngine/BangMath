#define BANG_MATH_DEFINE_USINGS(Type)       \
    using Type##f = Type##G<float>;         \
    using Type##d = Type##G<double>;        \
    using Type##i = Type##G<int>;           \
    using Type##ui = Type##G<unsigned int>; \
    using Type = Type##f;
