#ifndef GAME_ENGINE_APPLICATION_UI_H
#define GAME_ENGINE_APPLICATION_UI_H

#include <memory>

#include "GameEngine/Application/application.h"



namespace GUI {
class TUIParent;
}

class TApplicationUI
{
public:
    TApplicationUI(const TApplicationInfo& info);

    std::shared_ptr<const GUI::TUIParent> getUIParent() const;
    std::shared_ptr<GUI::TUIParent> getUIParent();

    void handleEvent(const TWindowEvent& event);
    void update();
    void draw();

private:
    using UIParent = std::shared_ptr<GUI::TUIParent>;
    UIParent uiParent;
};

#endif // GAME_ENGINE_APPLICATION_UI_H
