#pragma once

#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <concepts>

enum class CoordCategory {
    UnsignedInteger,
    FloatingPoint,
};

template<class T>
    requires std::is_arithmetic_v<T>
inline constexpr CoordCategory categorize() {
    if constexpr (std::is_integral_v<T> && std::is_unsigned_v<T>)
        return CoordCategory::UnsignedInteger;
    else if constexpr (std::is_floating_point_v<T>)
        return CoordCategory::FloatingPoint;
    else
        static_assert(sizeof(T) == 0, "categorize: unsuported coord category");
}

template<class T, CoordCategory C=categorize<T>()>
struct CoordTraits;

template<class T>
struct CoordTraits<T, CoordCategory::UnsignedInteger> {
    using v = std::size_t;
};

template<class T>
struct CoordTraits<T, CoordCategory::FloatingPoint> {
    using v = double;
};

template<class T>
using coord_t = typename CoordTraits<T>::v;


template<class T>
    requires std::is_arithmetic_v<T>
struct Vector2 {
    static_assert(sizeof(T) == 0, "Vector2: explicit implementation required");
};

template<>
struct Vector2<std::size_t> {
    using v = sf::Vector2u;
};

template<>
struct Vector2<double> {
    using v = sf::Vector2f;
};

template<class T>
using vec_t = typename Vector2<coord_t<T>>::v;
