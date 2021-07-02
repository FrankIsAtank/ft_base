#pragma once

// Helper to work around a VS2017 bug
// Calls a function and assigns the result to a promise
//  or calls the function and sets the promise if the return type is void

// standard headers
#include <future>
#include <type_traits>

namespace ft {
namespace base {
namespace thread {

template<class F, class R = decltype(std::declval<std::decay_t<F>>()())>
void promise_from_lambda(F&& p_function, std::promise<R> & p_promise)
{
    if constexpr (std::is_same_v<R, void>)
    {
        p_function();
        p_promise.set_value();
    }
    else
    {
        p_promise.set_value(p_function());
    }
}


}   // namespace thread
}   // namespace base
}   // namespace ft
