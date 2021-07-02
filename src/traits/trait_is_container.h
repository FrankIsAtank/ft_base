#pragma once

// Type trait which provides a `value` member which is `true` if an instance
//  of type `T` could be used with `std::begin` and `std::end`

// standard headers
#include <type_traits>

namespace ft {
namespace base {
namespace traits {

template<class T>
struct is_container;

template<class T>
inline constexpr bool is_container_v = is_container<T>::value;

template<class T>
struct is_container
{
    template<class U>
    static std::true_type eval(
        void*,
        decltype(std::begin(std::declval<U>()))* = nullptr,
        decltype(std::end(std::declval<U>()))* = nullptr) 
    {
        return {};
    }

    template<class U>
    static std::false_type eval(...)
    {
        return {};
    }

    using type = decltype(eval<T>(nullptr));
    static constexpr bool value = type::value;
};

}   // namespace traits
}   // namespace base
}   // namespace ft
