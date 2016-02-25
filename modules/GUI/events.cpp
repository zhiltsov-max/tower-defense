#include "events.h"

BEGIN_GUI

bool TMenuObjectEvents::HasSignal(const SignalID& signal) const {
    return (m_signals.count(signal) != 0);
}

bool TMenuObjectEvents::HasSlot(const SignalID& slot) const {
    return (m_slots.count(slot) != 0);
}

const TMenuObjectEvents::Signal& TMenuObjectEvents::GetSignal(const SignalID& name) const {
    return m_signals.at(name);
}
TMenuObjectEvents::Signal& TMenuObjectEvents::GetSignal(const SignalID& name) {
    return m_signals.at(name);
}

const TMenuObjectEvents::Slot& TMenuObjectEvents::GetSlot(const SignalID& name) const {
    return m_slots.at(name);
}
TMenuObjectEvents::Slot& TMenuObjectEvents::GetSlot(const SignalID& name) {
    return m_slots.at(name);
}

void TMenuObjectEvents::AddSignal(Signal&& signal) {
#if defined(_DEBUG)
    GUI_ASSERT(HasSignal(signal.GetID()) == false,
        string("Warning: Signal '") + signal.GetID() + string("' already exists."));
#endif
    m_signals.emplace(signal.GetID(), std::move(signal));
}

void TMenuObjectEvents::AddSlot(Slot&& slot) {
#if defined(_DEBUG)
    GUI_ASSERT(HasSlot(slot->GetID()) == false,
        string("Warning: Slot '") + slot->GetID() + string("' already exists."));
#endif
    m_slots.emplace(slot->GetID(), std::move(slot));
}

const TMenuObjectEvents::Slots& TMenuObjectEvents::GetSlots() const {
    return m_slots;
}
TMenuObjectEvents::Slots& TMenuObjectEvents::GetSlots() {
    return m_slots;
}

const TMenuObjectEvents::Signals& TMenuObjectEvents::GetSignals() const {
    return m_signals;
}
TMenuObjectEvents::Signals& TMenuObjectEvents::GetSignals() {
    return m_signals;
}


END_GUI
