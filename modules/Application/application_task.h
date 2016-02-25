#ifndef APPLICATION_TASK_H
#define APPLICATION_TASK_H

#include "td_application.h"



enum class TDAppState : uchar {
    Exit = 0,
    Menu,
    Game
};


class TTowerDefenseApplication;

class TTDApplicationTask /*Abstract*/
{
public:
    TTDApplicationTask(TTowerDefenseApplication* app = nullptr);
    virtual ~TTDApplicationTask() = default;

    virtual void Update() = 0;
    virtual void Draw(Graphics::TRenderTarget& target) = 0;
    virtual void HandleEvent(const TApplication::Event& event) = 0;

    virtual const TDAppState& GetCode() const = 0;

    void SetApplication(TTowerDefenseApplication* instance);

protected:
    using PApplication = TTowerDefenseApplication *;
    PApplication app;
};

#endif //APPLICATION_TASK_H
