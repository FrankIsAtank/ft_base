#pragma once

// Type trait which converts a tuple-like type `T<X...>` into a type `T<Y...>`
//  where `Y` is `X` with no `const` modifier

// standard headers
#include <array>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ft {
namespace base {
namespace traits {

template<class T>
struct tuple_non_const;

template<class T>
using tuple_non_const_t = typename tuple_non_const<T>::type;

// For `std::tuple` and `std::pair`
template<template<class...> class T, class ... U>
struct tuple_non_const<T<U...>> {
    using type = T<std::remove_const_t<U>...>;
};

// For `std::array`
template<class T, std::size_t N>
struct tuple_non_const<std::array<T, N>> {
    using type = std::array<std::remove_const_t<T>, N>;
};


namespace details {

// Construct an instance of `T` from a forwarded non-const version of itself
template<class T, std::size_t ... I>
auto from_non_const_to_T_impl(tuple_non_const_t<T> && p_source, std::index_sequence<I...>) -> T
{
    return { std::get<I>(std::move(p_source)), ... };
}

}   // namespace details

// Construct an instance of `T` from a forwarded non-const version of itself
template<class T>
auto from_non_const_to_T(tuple_non_const_t<T> && p_source) -> T
{
    return details::from_non_const_to_T_impl(std::move(p_source), std::make_index_sequence<std::tuple_size_v<T>>{});
}

}   // namespace traits
}   // namespace base
}   // namespace ft
