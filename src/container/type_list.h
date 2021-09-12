#pragma once

// Enumerates a list of types
// Provides :

// struct type_list<T...>
// Lists the arguments `T`

// struct type_list_template<T, A...>
// Produces a type_list<T<A>...> where `T` is a type template
//  with a single non-type argument of the same type as `A`

// struct type_list_from_values<A...>
// Produce a type_list<std::integeral_constant<T, A>...> 
// Where `T` the integral type common to all the `A`s

// using type_list_cat = ...
// Joins any number of type lists
// Ex. type_list_cat<type_list<int, double>, type_list<int, char>>
//  is type_list<int, double, int, char>

// standard headers
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

namespace ft {
namespace base {
namespace container {

namespace details {
namespace type_list_ns {

// See if a list contains a type
template<class T, class L, std::size_t I = 0>
constexpr std::size_t find_type()
{
    if constexpr (I + 1 >= std::tuple_size_v<L>)
    {
        // Last element
        if constexpr (std::is_same_v<std::tuple_element_t<I, L>, T>)
        {
            return I;
        }
        else
        {
            static_assert(I + 1 == std::tuple_size_v<L>);
            return I + 1;
        }
    }
    else if constexpr (std::is_same_v<std::tuple_element_t<I, L>, T>)
    {
        // Found the type
        return I;
    }
    else
    {
        // Recursion
        return find_type<T, L, I + 1>();
    }
}

// See if the list contains any type other than T
template<class T, class L, std::size_t I = 0>
constexpr bool is_all_type()
{
    if constexpr (I + 1 >= std::tuple_size_v<L>)
    {
        // Last element
        return std::is_same_v<T, std::tuple_element_t<I, L>>;
    }
    else if constexpr (!std::is_same_v<T, std::tuple_element_t<I, L>>)
    {
        return false;
    }
    else
    {
        return is_all_type<T, L, I + 1>();
    }
}



};  // namespace type_list_ns
};  // namespace details

// A list of types
template<class ... T>
struct type_list
{
    using tuple = std::tuple<T...>;
    using variant = std::variant<T...>;

    template<std::size_t S>
    using element = std::tuple_element_t<S, tuple>;

    using count = std::integral_constant<std::size_t, sizeof...(T)>;

    template<class U>
    using has_type = std::bool_constant < details::type_list_ns::find_type<U, tuple>() < sizeof...(T) > ;

    template<class U>
    using is_all_type = std::bool_constant<details::type_list_ns::is_all_type<U, tuple>()>;

    using is_uniform = std::conditional_t<sizeof...(T) == 0,
        std::true_type,
        is_all_type<std::tuple_element_t<0, tuple>>>;
};


// A list of types generated from a type template
template<template<auto> class T, auto ... A>
struct type_list_template : type_list<T<A>...> {};

namespace details {
namespace type_list_ns {

template<class T, auto ... A>
struct from_values
{
    using type = ft::base::container::type_list<std::integral_constant<T, A>...>;
};

template<class T>
struct from_other_type {};

template<class ... T>
struct from_other_type<std::tuple<T...>> {
    using type = type_list<T...>;
};

template<class ... T>
struct from_other_type<std::variant<T...>> {
    using type = type_list<T...>;
};

};  // namespace type_list_ns
};  // namespace details

// A list of types gemerated from a type template with a non-type argument
template<auto ... A>
using type_list_from_values = typename details::type_list_ns::from_values<std::common_type_t<decltype(A)...>, A...>::type;


// Get the argument types from a tuple or variant
template<class T>
using type_list_from_type = typename details::type_list_ns::from_other_type<T>::type;


// Concatenate type lists
template<class ... T>
using type_list_cat = type_list_from_type<decltype(std::tuple_cat(std::declval<typename T::tuple>()...))>;


namespace details {
namespace type_list_ns {

// Permutations
template<template<class> class T, class L>
struct permutation {};

template<template<class> class T, class ... E>
struct permutation<T, type_list<E...>> {
    using type = type_list_cat<T<E>...>;
};

};  // namespace type_list_ns
};  // namespace details


// Take a type_list<T> template and a list of types L
// Generates a type_list for each type in L and concatenates
//  them into a new type_list
template<template<class> class T, class L>
using type_list_permutations = typename details::type_list_ns::permutation<T, L>::type;

}   // namespace container
}   // namespace base
}   // namespace ft
