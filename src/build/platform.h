#pragma once
// Defines macros for the target platform being built

// standard headers
#include <cstdint>

namespace ft {
namespace base {
namespace os {

// Enum of all platforms
enum class t_platforms : std::uint_fast32_t {

    unknown = 0,
    windows_any = 0x01,
    windows_x86 = 0x02 | windows_any,
    windows_x64 = 0x04 | windows_any
};

#ifdef _WIN32

    #define FT_OS_WINDOWS
    
    #ifdef _WIN64
        #define FT_x64
        constexpr auto g_platform = t_platforms::windows_x64;
    #else
        #define FT_X86
        constexpr auto g_platform = t_platforms::windows_x86;
    #endif  // _WIN64

#else

    constexpr auto g_platform = t_platforms::unknown;
    #error Unsupported platform

#endif  // _WIN32

}   // namespace os
}   // namespace base
}   // namespace ft
