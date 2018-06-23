#include "GameEngine/Utility/exception.h"


GE_BEGIN_ENGINE_NAMESPACE

TException::TException(const TString& message) :
    parent_type(),
    message(message)
{}

const char* TException::what() const noexcept {
    return message.c_str();
}

GE_END_ENGINE_NAMESPACE