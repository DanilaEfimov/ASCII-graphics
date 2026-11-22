#pragma once

#include <SFML/System/Vector2.hpp>
#include <concepts>
#include <cstdint>
#include <type_traits>

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

template<CoordCategory C>
struct CoordTraits;

template<>
struct CoordTraits<CoordCategory::UnsignedInteger> {
    using v = decltype(sf::Vector2u{}.x);
};

template<>
struct CoordTraits<CoordCategory::FloatingPoint> {
    using v = decltype(sf::Vector2f{}.x);
};

template<CoordCategory C>
using coord_t = typename CoordTraits<C>::v;


template<CoordCategory C>
struct Vector2 {
    static_assert(sizeof(C) == 0, "Vector2: explicit implementation required");
};

template<>
struct Vector2<CoordCategory::UnsignedInteger> {
    using v = sf::Vector2u;
};

template<>
struct Vector2<CoordCategory::FloatingPoint> {
    using v = sf::Vector2f;
};

template<class T>
using vec_t = typename Vector2<categorize<T>()>::v;
