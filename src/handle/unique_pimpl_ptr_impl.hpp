#pragma once

#include "unique_pimpl_ptr.hpp"

namespace ft {
namespace base {
namespace handle {

// Define the deleter abstraction
template<class T>
void unique_pimpl_ptr_deleter<T>::operator()(arg p_ptr) 
{
    delete p_ptr;
};

}   // namespace handle
}   // namespace base
}   // namespace ft
