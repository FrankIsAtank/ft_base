#pragma once

// project headers
#include "except_base.h"

// standard headers
#include <type_traits>

namespace ft {
namespace base {
namespace error {

// Template implementation for all template types
template<class T, auto t_tag>
class except_impl : public T
{
    static_assert(std::is_base_of_v<except_base, T>,
        "Exception type does not derive from `except_base`");

public:
    static constexpr std::decay_t<decltype(t_tag)> tag = t_tag;

public:
    // Throw an exception of this type
    template<class ... t_args>
    static except_impl make(t_args&& ... p_args);

    // Get this exception's name
    virtual const char * name() const override;

protected:
    // Constructor
    template<class U, class ... t_args>
    except_impl(const U * const p_leaf, t_args&&... p_args);

};  // class except_base


// Specialize to name an exception type
template<class T>
struct except_impl_name
{
    static const char * name() {
        return "exception";
    };
};

}   // namespace error
}   // namespace base
}   // namespace ft

#include "except_impl.hpp"
