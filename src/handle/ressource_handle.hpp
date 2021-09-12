#pragma once

// Stores and cleans up a ressource

// The cleanup function is called on destruction if the stored
//  ressource's value is not equal to `void_value`
// After the cleanup function is called, the stored ressource is set
//  to `void_value`
// Default constructed and moved-from instances have a stored ressource
//  equal to `void_value`

// standard headers
#include <functional>
#include <utility>

namespace ft {
namespace base {
namespace handle {

// Wraps and handle a unique ressource
template<class T, auto void_value = T{} >
class ressource_handle
{
public:
    // Cleanup function type
    using t_cleanup = std::function<void(T&)>;

public:
    // Allow default construction
    // Equivalent to a moved-from instance
    ressource_handle() noexcept {};

    // Wrap a ressource
    ressource_handle(T&& p_value, t_cleanup p_cleanup_function) :
        m_obj(std::move(p_value)),
        m_cleanup(std::move(p_cleanup_function))
    { }

    // Wrap a ressource
    ressource_handle(const T & p_value, t_cleanup p_cleanup_function) :
        m_obj(p_value),
        m_cleanup(std::move(p_cleanup_function))
    { }


    // Destructor
    // Invokes the cleanup function
    ~ressource_handle() noexcept
    {
        clear();
    }

    // Prevent copy
    ressource_handle(const ressource_handle &) = delete;
    ressource_handle & operator=(const ressource_handle &) = delete;

    // Move constructor
    ressource_handle(ressource_handle && p_ref) noexcept
    {
        (*this) = std::move(p_ref);
    }

    // Move assignment operator
    ressource_handle & operator=(ressource_handle && p_ref) noexcept
    {
        swap(p_ref);
        p_ref.clear();
        return *this;
    }

    // Swap with another isntance
    void swap(ressource_handle & p_ref) noexcept
    {
        p_ref.m_cleanup.swap(m_cleanup);

        using std::swap;
        swap(m_obj, p_ref.m_obj);
    }

    // Allow implicit conversion to the underlying type
    operator const T& () const {
        return m_obj;
    }
    operator T& () & {
        return m_obj;
    }
    operator T && () && {
        return std::move(m_obj);
    }

    // Explicitly convert to underlying type
    decltype(auto) operator*() {
        return static_cast<T&>(*this);
    }
    decltype(auto) operator*() const {
        return static_cast<const T&>(*this);
    }
    decltype(auto) operator->() {
        return &static_cast<T&>(*this);
    }
    decltype(auto) operator->() const {
        return &static_cast<const T&>(*this);
    }

    // Allow implicit conversion to bool to check validity
    operator bool() const {
        return has_ressource();
    }
    bool has_ressource() const {
        return m_obj != void_value;
    }

private:
    // Cleanup the ressource if it has any
    void clear()
    {
        if (has_ressource()) {
            m_cleanup(m_obj);
            m_obj = void_value;
        }
    }

    // The ressource
    T m_obj = void_value;

    // Cleanup function
    t_cleanup m_cleanup = [](T&) {};
};

}   // namespace handle
}   // namespace base
}   // namespace ft

