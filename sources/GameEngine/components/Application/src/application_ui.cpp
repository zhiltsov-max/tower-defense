#include "GameEngine/Application/application_ui.h"
#include "GameEngine/GUI/uiparent.h"


GE_BEGIN_ENGINE_NAMESPACE

TApplicationUI::TApplicationUI(const TParameters& parameters) :
    uiParent()
{
    GUI::TUIParentSource src;
    src.margin = GUI::TPadding();
    src.position = GUI::TCoordinate();
    src.show = true;
    src.size = GUI::TSize(parameters.windowWidth, parameters.windowHeight);

    uiParent.reset(new GUI::TUIParent(src));
    uiParent->Initialize();
}


std::shared_ptr<const GUI::TUIParent> TApplicationUI::getUIParent() const {
    return std::dynamic_pointer_cast<const GUI::TUIParent>(uiParent);
}
std::shared_ptr<GUI::TUIParent> TApplicationUI::getUIParent() {
    return std::dynamic_pointer_cast<GUI::TUIParent>(uiParent);
}

void TApplicationUI::handleEvent(const TWindowEvent& event) {
    if (uiParent != nullptr) {
        uiParent->SendEvent(event);
    }
}

void TApplicationUI::update() {
    uiParent->Update();
}

void TApplicationUI::draw(IO::TGraphicsDevice& device) {
    uiParent->Draw(device);
}

GE_END_ENGINE_NAMESPACE