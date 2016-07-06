#ifndef APPLICATION_TASK_H
#define APPLICATION_TASK_H

#include "Game/Application/td_application.h"


namespace TD {

using TApplicationStateTypeID = uchar;
enum class ApplicationState : TApplicationStateTypeID {
    Exit = 0,
    Menu,
    Game
};

class TApplicationTask /*Abstract*/
{
public:
    virtual ~TApplicationTask() = default;

    virtual void Update() = 0;
    virtual void Draw(Graphics::TRenderTarget& target) = 0;
    virtual void HandleEvent(const TApplication::Event& event) = 0;

    virtual const ApplicationState& GetCode() const = 0;

    void SetApplication(TTowerDefenseApplication* instance);

protected:
    using PApplication = TTowerDefenseApplication *;
    PApplication app;

    TApplicationTask(TTowerDefenseApplication* app = nullptr);
};

} // namespace TD

#endif //APPLICATION_TASK_H
