#ifndef CORE_EXCEPTION_H
#define CORE_EXCEPTION_H

#include <exception>
#include <string>


class exception : public std::exception
{
public:
    exception() = default;
    exception(const std::string& message);
    virtual ~exception() override = default;
    const char* what() const noexcept;
private:
    typedef std::exception parent_type;
    std::string message;
};


#define THROW(message) \
    throw exception(std::string("Error at ") + __FILE__ + \
        ":" + std::to_string(__LINE__) + ": " + std::string(message));

#define ASSERT(expr, message) \
    if ((expr) == false) {\
        THROW(message)\
    }

#endif // CORE_EXCEPTION_H
