#pragma once

// Wraps an object such that it requires a mutex lock to be accessed
// volatile member functions are usurped to mean thread-safe functions
//  that can be called without first locking the object
// T is the type being wrapped
// M is the type of mutex to use (default std::recursive_mutex)
// L is the type of lock to use (default : std::unique_lock)

// Do not move a locked instance

// project headers
#include "lockable_lock.h"

// standard headers
#include <memory>
#include <mutex>
#include <utility>

namespace ft {
namespace base {
namespace thread {

template<class T, class M = std::recursive_mutex, class L = std::unique_lock<M>>
class lockable
{
public:
    using value_type = T;
    using mutex = M;
    using lock = L;

public:
    // Constructor
    // Forwards to `value_type` constructor
    template<class ... Args>
    lockable(Args&& ... p_args) :
        m_object(std::forward<Args>(p_args)...)
    { }

    // Return a lock that both owns the lock and provides a pointer-like interface
    //  to the now locked object
    lockable_lock<T, L> make_lock()
    {
        FT_ASSERT(m_mutex != nullptr);
        return { &m_object, L{*m_mutex} };
    }


    // Return a lock that both owns the lock and provides a pointer-like interface
    //  to the now locked object
    lockable_lock_const<T, L> make_lock() const
    {
        FT_ASSERT(m_mutex != nullptr);
        return { &m_object, L{*m_mutex} };
    }

    // Copy construction
    // Available if `value_type` is copyable
    template<class U = T>
    lockable(std::enable_if_t<std::is_copy_constructible_v<U>, const lockable&> p_ref) :
        m_object(p_ref.m_object)
        // Don't copy the mutex, make a new one
    { }

    // Explicitly disable copy when `value_type` doesn't allow it
    template<class U = T>
    lockable(std::enable_if_t<!std::is_copy_constructible_v<U>, const lockable&>) = delete;


    // Allow move construction
    // Available if `value_type` is moveable
    template<class U = T>
    lockable(std::enable_if_t<std::is_move_constructible_v<U>, lockable&&> p_ref) :
        m_object(std::move(p_ref.m_object)),
        m_mutex(std::move(p_ref.m_mutex))
    { }

    // Explicitly disable copy when `value_type` doesn't allow it
    template<class U = T>
    lockable(std::enable_if_t<!std::is_move_constructible_v<U>, lockable&&>) = delete;


    // Copy assignment
    // Available if `value_type` is copyable
    template<class U = T, class = std::enable_if_t<std::is_copy_assignable_v<U>>>
    lockable& operator=(const lockable& p_ref)
    {
        // Don't copy the mutex, each instance has it's own
        m_object = p_ref.m_object;
        return *this;
    }

    // Copy assignment
    // Explicitly disable copy when `value_type` doesn't allow it
    template<class U = T>
    lockable& operator=(std::enable_if_t<!std::is_copy_assignable_v<U>, const lockable&>) = delete;


    // Move assignment
    // Available if `value_type` is moveable
    template<class U = T>
    lockable& operator=(std::enable_if_t<std::is_move_assignable_v<U>, lockable&&> p_ref)
    {
        m_object = std::move(p_ref.m_object);
        m_mutex = std::move(p_ref.m_mutex);
    }

    // Move assignment
    // Explicitly disable copy when `value_type` doesn't allow it
    template<class U = T>
    lockable& operator=(std::enable_if_t<!std::is_move_assignable_v<U>, lockable&&>) = delete;

private:
    // The wrapped object
    value_type m_object;

    // The mutex guarding the object
    std::unique_ptr<mutex> m_mutex = std::make_unique<mutex>();

};  // class lockable

}   // namespace thread
}   // namespace base
}   // namespace ft

