#ifndef GAME_ENGINE_EXCEPTION_H
#define GAME_ENGINE_EXCEPTION_H

#include <exception>

#include "GameEngine/Infrastructure/string.h"


namespace GE {

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

} // namespace GE

#endif // GAME_ENGINE_EXCEPTION_H
