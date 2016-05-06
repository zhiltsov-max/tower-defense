#include "application_ui.h"
#include "application.h"
#include "GUI/uiparent.h"



TApplicationUI::TApplicationUI(const TApplicationInfo& info) :
    uiParent()
{
    GUI::TUIParentSource src;
    src.margin = GUI::TPadding();
    src.position = GUI::TCoordinate();
    src.show = true;
    src.size = GUI::TSize(info.windowWidth, info.windowHeight);

    uiParent.reset(new GUI::TUIParent(src));
    uiParent->Initialize();
}


std::shared_ptr<const GUI::TUIParent> TApplicationUI::getUIParent() const {
    return std::dynamic_pointer_cast<const GUI::TUIParent>(uiParent);
}
std::shared_ptr<GUI::TUIParent> TApplicationUI::getUIParent() {
    return std::dynamic_pointer_cast<GUI::TUIParent>(uiParent);
}

void TApplicationUI::handleEvent(const TApplication::Event& event) {
    if (uiParent != nullptr) {
        uiParent->SendEvent(event);
    }
}

void TApplicationUI::update() {
    uiParent->Update();
}

void TApplicationUI::draw() {
    uiParent->Draw(*GUI::IO::GetGraphicsDevice());
}
