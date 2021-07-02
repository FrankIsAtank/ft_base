#pragma once

// Report an error that is about to terminate the process

// standard headers
#include <string>

namespace ft {
namespace base {
namespace error {

class except_base;

// Report the error as a string
void report_unrecoverable(const std::string & p_message);

// Report the error from an exception
void report_unrecoverable(const except_base & p_exception);

// Report the error from a standard exception
void report_unrecoverable(const std::exception & p_exception);

// Report from a `catch` block
void report_unrecoverable_any();

}   // namespace error
}   // namespace base
}   // namespace ft
