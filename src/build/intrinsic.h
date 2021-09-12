#pragma once

#include "base/platform.h"

// FT_NORETURN		Marks a function that will never return (always throws or terminates)
// FT_NODISCARD		Marks a function whose return value must not be ignored
// FT_DEPRECATED	Marks a function that should not be used because support for it will end soon
// FT_RESTRICT		Marks a variable that never aliases another object (similar to https://en.cppreference.com/w/c/language/restrict)
// FT_FORCE_INLINE	Hint to the compiler that this function should always be inlined (use carefully!)
// FT_BREAKPOINT	Should cause any attached debugger to break
// FT_UNREACHABLE	Hint to the compiler that it is undefined behavior for control to reach this point (for optimizations)
// FT_NOTIFY		Attempt to notify the developper about something with a breakpoint or termination

#ifdef FT_OS_WINDOWS 

    // Visual studio
#include <intrin.h>	// Declares intrinsic prototypes
#define FT_NORETURN __declspec(noreturn)
#define FT_NODISCARD [[nodiscard]]
#define FT_DEPRECATED( msg, func ) __declspec(deprecated( #msg )) func
#define FT_RESTRICT __restrict
#define FT_FORCE_INLINE __forceinline
#define FT_BREAKPOINT __debugbreak();
#define FT_UNREACHABLE FT_BREAKPOINT __assume(0);

#else

    // Unknown compiler
#include <exception>	// for std::terminate()
#define FT_NORETURN
#define FT_NODISCARD
#define FT_DEPRECATED( func, msg ) func
#define FT_RESTRICT
#define FT_FORCE_INLINE
#define FT_BREAKPOINT
#define FT_UNREACHABLE FT_BREAKPOINT {*((int*)nullptr) = 0;}
#define FT_NOTIFY FT_BREAKPOINT

#endif

// Some intrinsics are used as functions
namespace ft {
namespace build {

// If a debugger is attached, causes it to break here
FT_FORCE_INLINE void breakpoint() { FT_BREAKPOINT }

}   // namespace build
} 	// namespace ft
