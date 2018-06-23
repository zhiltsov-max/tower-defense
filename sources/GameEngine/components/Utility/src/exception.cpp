#include "GameEngine/Utility/exception.h"


GE_BEGIN_ENGINE_NAMESPACE

exception::exception(const TString& message) :
    parent_type(),
    message(message)
{}

const char* exception::what() const noexcept {
    return message.c_str();
}

GE_END_ENGINE_NAMESPACE