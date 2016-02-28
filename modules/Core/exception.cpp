#include "exception.h"


exception::exception(const std::string &message) :
    parent_type(),
    message(message)
{}

const char* exception::what() const noexcept {
    return message.c_str();
}
