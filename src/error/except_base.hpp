#pragma once

// project headers
#include "except_base.h"

// standard headers
#include <string>
#include <type_traits>

    // Base constructor
template<class T>
ft::base::error::except_base::except_base(const T*) noexcept
{
    static_assert(std::is_base_of_v<except_base, T>,
        "Constructor template argument `T` is the a derived type");
}


// Construct with a string message
template<class T>
ft::base::error::except_base::except_base(const T* p_leaf, std::string && p_message) noexcept :
    except_base(p_leaf)
{
    m_message = std::move(p_message);
}


// Construct from an os specific error code
template<class T>
ft::base::error::except_base::except_base(const T*  p_leaf, const os_error_code p_code) noexcept :
    except_base(p_leaf, "Error code " + std::to_string(p_code.code))
{
}
