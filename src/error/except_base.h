#pragma once

// Base class for all exceptions

// project headers
#include "os_error_code.h"

// standard headers
#include <stdexcept>

namespace ft {
namespace base {
namespace error {

class except_base : public std::exception
{
protected:
    // Construct with just a string message
    template<class T>
    except_base(const T*, std::string && p_message) noexcept;

    // Construct from an os specific error code
    template<class T>
    except_base(const T*, const os_error_code p_code) noexcept;

private:
    // Base constructor
    template<class T>
    explicit except_base(const T*) noexcept;

public:
    // Polymorphic
    virtual ~except_base() = default;

    // Get the name of this exception
    virtual const char * name() const = 0;

    // Get the description of this exception
    const std::string & get_message() const noexcept;

    // Override for `std::exception`
    // Returns a pointer to the string returned by `get_message()`
    const char * what() const noexcept override;

private:
    // The message
    std::string m_message;

};  // class except_base

}   // namespace error
}   // namespace base
}   // namespace ft

#include "except_base.hpp"
