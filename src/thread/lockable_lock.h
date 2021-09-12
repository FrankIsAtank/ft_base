#pragma once

// Type returned by lockable when trying to lock it
// Stores a lock handle and a pointer to the object

// T is the type of object being pointed
// L is the type of lock used

// Provides :
// lockable_lock<T, L> : mutable lock
// lockable_lock_const<T, L> : immutable lock

// project headers
#include "error/ft_assert.h"

// standard headers
#include <type_traits>

namespace ft {
namespace base {
namespace thread {

// C is a bool (is this a const lock?)

template<class T, class L, bool C = false>
class lockable_lock
{
public:
    static constexpr auto is_const = C;
    using value_type = T;
    using pointer_const = const T*;
    using pointer = std::conditional_t<is_const, pointer_const, T*>;
    using reference_const = const T&;
    using reference = std::conditional_t<is_const, reference_const, T&>;
    using lock_type = L;

public:
    // Default constructor
    // Equivalent to a moved-from intance
    lockable_lock() = default;

    // Construct a lock
    lockable_lock(pointer p_ptr, L&& p_lock) :
        m_obj(p_ptr),
        m_lock(std::move(p_lock))
    { }

    // Explicitly dereference
    reference get()
    {
        FT_ASSERT(m_obj != nullptr);
        return *m_obj;
    }

    // Explicitly dereference
    reference_const get() const
    {
        FT_ASSERT(m_obj != nullptr);
        return *m_obj;
    }

    // Access locked object member
    pointer operator->()
    {
        FT_ASSERT(m_obj != nullptr);
        return m_obj;
    }

    // Access locked object member
    pointer_const operator->() const
    {
        FT_ASSERT(m_obj != nullptr);
        return m_obj;
    }

    // Dereference the object
    reference operator*()
    {
        return get();
    }

    // Dereference the object
    reference_const operator*() const
    {
        return get();
    }

    // Release the lock
    void unlock()
    {
        m_lock.unlock();
    }

    // Relock a release lock
    void lock()
    {
        m_lock.lock();
    }

    // Allow implicit conversion to references of the pointed object
    operator const reference_const() const {
        return get();
    }
    operator reference ()& {
        return get();
    }
    template<class U = T, class = std::enable_if_t<!C>>
    operator T && ()&& {
        return std::move(get());
    }

    // Allow assignment as-if this object was the locked object
    template<class U = T, class = std::enable_if_t<!C>>
    T& operator=(const T& p_other) {
        get() = p_other;
        return get();
    }

    // Allow assignment as-if this object was the locked object
    template<class U = T, class = std::enable_if_t<!C>>
    T& operator=(T&& p_other) {
        get() = std::move(p_other);
        return get();
    }


private:
    // Pointer to the locked object
    pointer m_obj = nullptr;

    // The actual lock
    L m_lock;
};

template<class T, class L>
using lockable_lock_const = lockable_lock<T, L, true>;

}   // namespace thread
}   // namespace base
}   // namespace ft
