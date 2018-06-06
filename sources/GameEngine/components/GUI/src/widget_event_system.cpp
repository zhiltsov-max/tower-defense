#include "widget_event_system.h"



BEGIN_GUI


bool TWidgetEventSystem::HasSignal(const SignalID& signal) const {
    return (signals.count(signal) != 0);
}

bool TWidgetEventSystem::HasSlot(const SlotID& slot) const {
    return (slots.count(slot) != 0);
}

const TWidgetEventSystem::Signal&
TWidgetEventSystem::GetSignal(const SignalID& name) const {
    return signals.at(name);
}

TWidgetEventSystem::Signal&
TWidgetEventSystem::GetSignal(const SignalID& name) {
    return signals.at(name);
}

const TWidgetEventSystem::Slot&
TWidgetEventSystem::GetSlot(const SlotID& name) const {
    return slots.at(name);
}

TWidgetEventSystem::Slot&
TWidgetEventSystem::GetSlot(const SlotID& name) {
    return slots.at(name);
}

void TWidgetEventSystem::AddSignal(const Signal& signal) {
#if defined(_DEBUG)
    if (HasSignal(signal.GetID()) == true) {
        GUI_WARNING(string("Signal '") + signal.GetID() +
            string("' already exists."));
    }
#endif // _DEBUG

    signals.emplace(signal.GetID(), signal);
}

void TWidgetEventSystem::AddSignal(Signal&& signal) {
#if defined(_DEBUG)
    if (HasSignal(signal.GetID()) == true) {
        GUI_WARNING(string("Signal '") + signal.GetID() +
            string("' already exists."));
    }
#endif // _DEBUG

    signals.emplace(signal.GetID(), std::move(signal));
}

void TWidgetEventSystem::AddSlot(const Slot& slot) {
#if defined(_DEBUG)
    if (HasSlot(slot.GetID()) == true) {
        GUI_WARNING(string("Slot '") + slot.GetID() +
            string("' already exists."));
    }
#endif // _DEBUG

    slots.emplace(slot.GetID(), slot);
}

void TWidgetEventSystem::AddSlot(Slot&& slot) {
#if defined(_DEBUG)
    if (HasSlot(slot.GetID()) == true) {
        GUI_WARNING(string("Slot '") + slot.GetID() +
            string("' already exists."));
    }
#endif // _DEBUG

    slots.emplace(slot.GetID(), std::move(slot));
}

const TWidgetEventSystem::Slots& TWidgetEventSystem::GetSlots() const {
    return slots;
}

TWidgetEventSystem::Slots& TWidgetEventSystem::GetSlots() {
    return slots;
}

const TWidgetEventSystem::Signals& TWidgetEventSystem::GetSignals() const {
    return signals;
}

TWidgetEventSystem::Signals& TWidgetEventSystem::GetSignals() {
    return signals;
}


END_GUI
