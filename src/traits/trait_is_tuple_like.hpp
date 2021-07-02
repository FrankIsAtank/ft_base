#pragma once

// Type trait which provides a `value` member which is `true` if `T` is an
//  `std::tuple`, `std::pair` or `std::array`

// standard headers
#include <array>
#include <tuple>
#include <type_traits>
#include <utility>

namespace ft {
namespace base {
namespace traits {

template<class T>
struct is_tuple_like;

template<class T>
inline constexpr bool is_tuple_like_v = is_tuple_like<T>::value;

template<class T>
struct is_tuple_like
{
    template<class U>
    static std::true_type eval(decltype(std::tuple_size<U>::value)*);

    template<class U>
    static std::false_type eval(...);

    using type = decltype(eval<T>(nullptr));
    static constexpr bool value = type::value;
};

}   // namespace traits
}   // namespace base
}   // namespace ft
