#include "signal.h"
#include "slot.h"

BEGIN_GUI

TMenuObjectSignal::TMenuObjectSignal(const SignalID& name_) :
    name(name_),
    listeners()
{}

TMenuObjectSignal::TMenuObjectSignal(const TMenuObjectSignal& other) :
    name(other.name),
    listeners(other.listeners)
{}

const SignalID& TMenuObjectSignal::GetID() const {
    return name;
}

void TMenuObjectSignal::Send(const Args& args) {
    for(auto it = listeners.begin(), iend = listeners.end(); it != iend; ++it) {
        if (exists(*it) == true) {
            (*it).lock()->Invoke(args);
        } else {
            it = listeners.erase(it, ++Listeners::iterator(it));
            iend = listeners.end();
        }
    }
}


void TMenuObjectSignal::AddListener(const Slot& listener) {
    auto it = std::move(find(listener));
    if (it != listeners.cend()) {
#if defined(_DEBUG)
        Debug::logMessage("Warning: Signal '" + name +
                "' already contains this listener.",
            "TMenuObject::AddListener",
            ::LogMessageImportance::Warning);
#endif //DEBUG
        return;
    }

    listeners.emplace_back(listener);
}

void TMenuObjectSignal::RemoveListener(const Slot& listener) {
    auto it = std::move(find(listener));
    if (it != listeners.cend()) {
#if defined(_DEBUG)
        Debug::logMessage("Warning: Signal '" + name +
                "' does not contain this listener.",
            "TMenuObject::RemoveListener",
            ::LogMessageImportance::Warning);
#endif //DEBUG
        return;
    }

    listeners.erase(it);
}

bool TMenuObjectSignal::HasListener(const Slot& listener) const {
    return find(listener) != listeners.cend();
}

TMenuObjectSignal::Listeners::const_iterator TMenuObjectSignal::find(const Slot& listener) const {
    if (exists(listener) == false) {
        return listeners.cend();
    }
    for(auto it = listeners.cbegin(), iend = listeners.cend(); it != iend; ++it) {
        if (exists(*it) == false) {
            continue;
        }
        if ((*it).lock() == listener.lock()) {
            return it;
        }
    }
    return listeners.cend();
}

TMenuObjectSignal::Listeners::iterator TMenuObjectSignal::find(const Slot& listener) {
    if (exists(listener) == false) {
        return listeners.end();
    }
    for(auto it = listeners.begin(), iend = listeners.end(); it != iend; ++it) {
        if (exists(*it) == false) {
            continue;
        }
        if ((*it).lock() == listener.lock()) {
            return it;
        }
    }
    return listeners.end();
}

bool TMenuObjectSignal::exists(const Slot& listener) const {
    return listener.expired() == false;
}


END_GUI
