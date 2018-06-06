#include "uiparent.h"


BEGIN_GUI

TUIParent::TUIParent(const TUIParentSource& source) :
    parent_type(source)
{}

bool TUIParent::IsVisible() const {
    return visible;
}

void TUIParent::SetParent(const TWidgetWeakRef& value) {
#if defined(_DEBUG)
    GUI_WARNING("Attempt to set a parent for UIParent object.");
#endif // _DEBUG

    UNUSED(value)
}

void TUIParent::SetChildrenVisibility(bool value) const {
    for(auto& child : children) {
        child.second->SetVisibility(value);
    }
}
void TUIParent::ShowChildren() {
    SetChildrenVisibility(true);
}
void TUIParent::HideChildren() {
    SetChildrenVisibility(false);
}

bool TUIParent::IsMouseOver() const {
    return _isMouseOverChild();
}

void TUIParent::SendEvent(const TEvent& event) {
    bool consumed = false;
    _sendEvent(event, consumed);
}

void TUIParent::_draw(TRenderTarget&) { /*none*/ }
void TUIParent::_update() { /*none*/ }

void GUI::TUIParent::_handleEvent(const TEvent&, bool&) {
    return;
}

END_GUI
