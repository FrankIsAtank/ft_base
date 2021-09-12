#pragma once

#include "except_impl.h"


// Throw an exception of this type
template<class T, auto t_tag>
template<class ... t_args>
[[ noreturn ]]
void ft::base::error::except_impl<T, t_tag>::raise(t_args&& ... p_args)
{
    throw make(std::forward<t_args>(p_args)...);
}


// Make an instance of this exception but don't throw it immediatly
template<class T, auto t_tag>
template<class ... t_args>
ft::base::error::except_impl<T, t_tag>
ft::base::error::except_impl<T, t_tag>::except_impl::make(t_args&& ... p_args)
{ 
    constexpr auto this_null = static_cast<const except_impl*>(nullptr);
    return except_impl{ this_null, std::forward<t_args>(p_args)... };
}


// Get this exception's name
template<class T, auto t_tag>
const char * ft::base::error::except_impl<T, t_tag>::name() const
{
    using this_type = std::remove_const_t<std::remove_pointer_t<decltype(this)>>;
    return except_impl_name<this_type>::name();
}


// Constructor
template<class T, auto t_tag>
template<class U, class ... t_args>
ft::base::error::except_impl<T, t_tag>::except_impl(const U * const p_leaf, t_args&& ... p_args) :
    T{ p_leaf, std::forward<t_args>(p_args)... }
{ }
