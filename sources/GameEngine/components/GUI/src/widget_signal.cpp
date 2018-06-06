#include "widget_signal.h"
#include "widget_slot.h"



BEGIN_GUI


TWidgetSignal::TWidgetSignal(const SignalID& id) :
    id(id),
    listeners()
{}

const SignalID& TWidgetSignal::GetID() const {
    return id;
}

void TWidgetSignal::Send(const Args& args) {
    for(auto it = listeners.begin(), iend = listeners.end();
        it != iend; ++it)
    {
        if (exists(*it) == true) {
            (*it).Invoke(args);
        } else {
#if defined(_DEBUG)
            GUI_WARNING("Listener '" + (*it).GetID() +
                "' is automatically removed from '" +
                id + "' listeners list.");
#endif // _DEBUG

            it = listeners.erase(it, ++Listeners::iterator(it));
            iend = listeners.end();
        }
    }
}


void TWidgetSignal::AddListener(const Slot& listener) {
    auto it = find(listener);
    if (it != listeners.cend()) {
#if defined(_DEBUG)
        GUI_WARNING("Signal '" + id + "' already contains this listener.");
#endif //DEBUG
        return;
    }

    listeners.emplace_back(listener);
}

void TWidgetSignal::RemoveListener(const Slot& listener) {
    auto it = find(listener);
    if (it == listeners.cend()) {
#if defined(_DEBUG)
        GUI_WARNING("Signal '" + id + "' does not contain this listener.");
#endif //DEBUG
        return;
    }

    listeners.erase(it);
}

bool TWidgetSignal::HasListener(const Slot& listener) const {
    return find(listener) != listeners.cend();
}

void TWidgetSignal::RemoveListeners() {
    listeners.clear();
}

TWidgetSignal::Listeners::const_iterator
TWidgetSignal::find(const Slot& listener) const {
    if (exists(listener) == false) {
        return listeners.cend();
    }
    return std::find_if(listeners.cbegin(), listeners.cend(),
        [&] (const Slot& elem) {
            return (exists(elem) == true) && (elem == listener);
        }
    );
}

TWidgetSignal::Listeners::iterator
TWidgetSignal::find(const Slot& listener) {
    if (exists(listener) == false) {
        return listeners.end();
    }
    return std::find_if(listeners.begin(), listeners.end(),
        [&] (const Slot& elem) {
            return (exists(elem) == true) && (elem == listener);
        }
    );
}

bool TWidgetSignal::exists(const Slot& listener) const {
    return listener.HasPtr() == true;
}


END_GUI
