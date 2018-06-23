#ifndef GAME_ENGINE_EXCEPTION_H
#define GAME_ENGINE_EXCEPTION_H

#include <exception>

#include "GameEngine/Utility/common.h"
#include "GameEngine/Infrastructure/string.h"


GE_BEGIN_ENGINE_NAMESPACE

class exception : public std::exception {
public:
    exception() = default;
    exception(const TString& message);
    virtual ~exception() override = default;
    const char* what() const noexcept override;

private:
    using parent_type = std::exception;

    TString message;
};

GE_END_ENGINE_NAMESPACE

#endif // GAME_ENGINE_EXCEPTION_H
