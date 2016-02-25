#include "slot.h"

BEGIN_GUI

TMenuObjectSlot::TMenuObjectSlot(
    TMenuObject* owner,
    const string& name,
    Method pointer
) :
    owner(owner),
    name(name),
    ptr(pointer)
{}


void TMenuObjectSlot::Invoke(Args args) const {
    ptr(owner, args);
}

const string& TMenuObjectSlot::GetID() const {
    return name;
}

const TMenuObjectSlot::Method& TMenuObjectSlot::GetPtr() const {
    return ptr;
}

TMenuObject const* TMenuObjectSlot::GetOwner() const {
    return owner;
}
void TMenuObjectSlot::SetOwner(TMenuObject* value) {
    owner = value;
}


END_GUI
