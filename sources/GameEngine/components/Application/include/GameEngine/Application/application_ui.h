#ifndef GAME_ENGINE_APPLICATION_UI_H
#define GAME_ENGINE_APPLICATION_UI_H

#include <memory>

#include "GameEngine/Infrastructure/graphics_device.h"
#include "GameEngine/Infrastructure/window.h"


namespace GE {

namespace GUI {
class TUIParent;
}

class TApplicationUI
{
public:
    struct TParameters {
        uint windowWidth;
        uint windowHeight;
    };
    TApplicationUI(const TParameters& parameters);

    std::shared_ptr<const GUI::TUIParent> getUIParent() const;
    std::shared_ptr<GUI::TUIParent> getUIParent();

    void handleEvent(const TWindowEvent& event);
    void update();
    void draw(IO::TGraphicsDevice& device);

private:
    using UIParent = std::shared_ptr<GUI::TUIParent>;
    UIParent uiParent;
};

} // namespace GE

#endif // GAME_ENGINE_APPLICATION_UI_H
