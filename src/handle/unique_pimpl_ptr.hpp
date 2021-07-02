#pragma once

// Provides an alias to `std::unique_ptr` but with an unspecied deleter
//  for use with incomplete type
// Implementation types must do the following to be compatible :
// 1. Include the header `#include "utility/unique_pimpl_ptr_impl.hpp"`
// 2. Include this statement  in the source file :
// template void ft::vtt::util::unique_pimpl_ptr_deleter<T>::operator()(arg);
//  where `T` is the implementation details type

// standard headers
#include <memory>

namespace ft {
namespace base {
namespace handle {

// Define the deleter abstraction
template<class T>
struct unique_pimpl_ptr_deleter {
    using type = T;
    using arg = const type *;
    void operator()(arg p_ptr);
};

// Define the alias
template<class T>
struct unique_pimpl_ptr : public std::unique_ptr<T, unique_pimpl_ptr_deleter<T>> 
{
    // Import all constructors
    using base = std::unique_ptr<T, unique_pimpl_ptr_deleter<T>>;
    using base::base;

    // Allow conversion from `std::unique_ptr<T>`
    unique_pimpl_ptr(std::unique_ptr<T> && p_other) {
        (*this) = std::move(p_other);
    }

    // Allow conversion from `std::unique_ptr<T>`
    unique_pimpl_ptr & operator=(std::unique_ptr<T> && p_other)
    {
        reset(p_other.release());
        return *this;
    }
};

}   // namespace handle
}   // namespace base
}   // namespace ft
