// project headers
#include "except_base.h"
#include "report_unrecoverable.h"

// other groups
#include "build/intrinsic.h"

// standard headers
#include <iostream>

// Report the error as a string
void ft::base::error::report_unrecoverable(const std::string & p_message)
{
    FT_BREAKPOINT;
    std::cerr << "Unrecoverable : " << p_message << "\n\nTerminating\n";
}

// Report the error from an exception
void ft::base::error::report_unrecoverable(const except_base & p_exception)
{
    report_unrecoverable(p_exception.get_message());
}

// Report the error from a standard exception
void ft::base::error::report_unrecoverable(const std::exception & p_exception)
{
    report_unrecoverable(p_exception.what());
}

// Report from a `catch` block
void ft::base::error::report_unrecoverable_any()
{
    try { throw; }
    catch (const except_base & p_exception)
    {
        report_unrecoverable(p_exception);
    }
    catch (const std::exception & p_exception)
    {
        report_unrecoverable(p_exception);
    }
    catch (...)
    {
        report_unrecoverable("Unknown exception");
    }
}
