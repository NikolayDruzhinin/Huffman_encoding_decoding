#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>

class Exception : public std::exception
{
public:
    Exception(const std::string& msg) : _msg(msg) {}
    Exception(const std::string& msg, const std::string& add) : _msg(msg + add) {}
    const char* what() const noexcept
    {
        return _msg.c_str();
    }
private:
    std::string _msg;
};

#endif // EXCEPTION_H


