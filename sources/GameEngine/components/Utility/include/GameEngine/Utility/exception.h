#ifndef GAME_ENGINE_EXCEPTION_H
#define GAME_ENGINE_EXCEPTION_H

#include <exception>
#include <string>


namespace GE {

class exception : public std::exception {
public:
    exception() = default;
    exception(const std::string& message);
    virtual ~exception() override = default;
    const char* what() const noexcept override;

private:
    using parent_type = std::exception;

    std::string message;
};

} // namespace GE

#endif // GAME_ENGINE_EXCEPTION_H
