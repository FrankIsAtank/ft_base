#pragma once

// Identifies an integer as representing a platform specific error code

// other groups
#include "build/os_types.h"

// standard headers
#include <cstdint>

namespace ft {
namespace base {
namespace error {

struct os_error_code
{
    ft::base::os::error_code code;

};  // class os_error_code

}   // namespace error
}   // namespace base
}   // namespace ft
