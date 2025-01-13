/***********************************************
 * Project Name     : Exception
 * Author           : Slavnem
 * Date             : 13/01/2025
 * License          : Slavnem Development License (SGL) v1.0
 * Description      : Exceptions for errors or unintended circumstances
 ***********************************************/
#ifndef EXCEPTION_INC_H
#define EXCEPTION_INC_H

#include <iostream>
#include <stdexcept>

// Exception
namespace Exception
{
    // Message
    class Message
    {
        public:
            explicit Message(const std::string& _msg);
    };

    // Basic
    class Basic : public std::exception
    {
        private:
            std::string message;

        public:
            explicit Basic(const std::string& _msg);
            
            virtual const char* what() const noexcept override;
    };

    // Critical
    class Critical : public std::runtime_error
    {
        public:
            explicit Critical(const std::string& _msg);

            virtual const char* what() const noexcept override;
    };
}

#endif // EXCEPTION_INC_H