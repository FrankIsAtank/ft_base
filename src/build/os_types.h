#pragma once

// Identifes platform specific types

// project headers
#include "platform.h"

// standard headers
#include <cstdint>

namespace ft {
namespace base {
namespace os {

#ifdef FT_OS_WINDOWS

using error_code = std::uint32_t;

#else
#error Unknown platform
#endif

}   // namespace os
}   // namespace base
}   // namespace ft
