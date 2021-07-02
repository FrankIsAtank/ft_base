#pragma once

// Defines macros for the current build configuration

#include "platform.h"

namespace ft {
namespace base {
namespace build {

// Enum of all platforms
enum class t_build_configs : std::uint_fast32_t {
    unknown = 0,
    debug = 1,
    release = 2
};

#ifdef NDEBUG
#define FT_RELEASE
constexpr auto g_build_config = t_build_configs::release;
#else
#define FT_DEBUG
constexpr auto g_build_config = t_build_configs::debug;
#endif // DEBUG

}   // namespace build
}   // namespace base
}   // namespace ft
