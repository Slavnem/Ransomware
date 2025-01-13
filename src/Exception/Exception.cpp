/***********************************************
 * Project Name     : Exception
 * Author           : Slavnem
 * Date             : 13/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Exceptions for errors or unintended circumstances
 ***********************************************/
#include <iostream>
#include <stdexcept>

#include <Exception/Exception.hpp>

// Exception
namespace Exception
{
    // Message
    Message::Message(const std::string& _msg)
    {
        std::cout << _msg.data() << std::endl;
    }

    // Basic
    Basic::Basic(const std::string& _msg)
        : message(_msg)
    { /* NOTHING */ }

    // Basic:what
    const char* Basic::what() const noexcept
    {
        return message.data();
    }

    // Critical
    Critical::Critical(const std::string& _msg)
        : std::runtime_error(_msg)
    { /* NOTHING */   }

    // Critical:what
    const char* Critical::what() const noexcept
    {
        return std::runtime_error::what();
    }
}