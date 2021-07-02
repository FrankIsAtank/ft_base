#pragma once

// project headers
#include "build/build.h"
#include "build/intrinsic.h"

// FT_ASSERT :      Assert macro
// FT_NOTIFY_IF :   Conditional breakpoint
//                  Breaks if the condition is `true`

#ifdef FT_DEBUG

    #include <cassert>

    #define FT_NOTIFY_IF( ft_condition ) { if(ft_condition) { FT_BREAKPOINT; } }

    #define FT_ASSERT( ft_condition ) {         \
        const bool ft_b = !!(ft_condition);     \
        FT_NOTIFY_IF( !ft_b );                  \
        assert( ft_b ); }  // Fall through if FT_NOTIFY_IF is not supported on the platform

#else	// RELEASE

    #define FT_NOTIFY_IF( ft_condition )

    #ifdef FT_OS_WINDOWS 

        // Release - Visual Studio
        #define FT_ASSERT( ft_condition ) { __assume( ft_condition ); }

    #else

        // Release - Unknown compiler
        #define FT_ASSERT( ft_condition ) { if(!(ft_condition)) { FT_UNREACHABLE; } } 

    #endif

#endif

