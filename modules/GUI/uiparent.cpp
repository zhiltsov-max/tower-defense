#include "uiparent.h"


BEGIN_GUI

TUIParent::TUIParent(const TUIParentSource& source) :
    parent_t(source)
{}

bool TUIParent::IsVisible() const {
    return visible;
}

void TUIParent::SetParent(const TMenuObjectWeakRef& value) {
#if defined(_DEBUG)
    throw_("Attempt to set parent of UIParent object.", "TUIParent::SetParent");
#endif
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

void TUIParent::_draw(TRenderTarget& target) { /*none*/ UNUSED(target) }
void TUIParent::_update() { /*none*/ }

END_GUI
