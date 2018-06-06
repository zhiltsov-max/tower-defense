#include "widget_slot.h"



BEGIN_GUI


TWidgetSlot::TWidgetSlot(const Owner& owner,
    const SlotID& id,
    const Method& pointer
) :
    owner(owner),
    name(id),
    ptr(pointer)
{}

bool TWidgetSlot::operator == (const TWidgetSlot& other) const {
    return (ptr.target<Method>() == other.ptr.target<Method>()) &&
        (owner.lock().get() == other.owner.lock().get()) &&
        (name == other.name);
}

bool TWidgetSlot::operator !=(const TWidgetSlot& other) const {
    return !operator == (other);
}


void TWidgetSlot::Invoke(const Args& args) const {
    if (ptr) {
        ptr(owner.lock().get(), args);
    }
}

const SlotID& TWidgetSlot::GetID() const {
    return name;
}

const TWidgetSlot::Method& TWidgetSlot::GetPtr() const {
    return ptr;
}

bool TWidgetSlot::HasPtr() const {
    return ptr != false;
}

const TWidgetSlot::Owner& TWidgetSlot::GetOwner() const {
    return owner;
}

void TWidgetSlot::SetOwner(const Owner& value) {
    owner = value;
}


END_GUI
