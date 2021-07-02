#include "except_base.h"

// Get the description of this exception
const std::string & ft::base::error::except_base::get_message() const noexcept
{
    return m_message;
}


// Override for `std::exception`
// Returns a pointer to the string returned by `get_message()`
const char * ft::base::error::except_base::what() const noexcept
{
    return m_message.c_str();
}
