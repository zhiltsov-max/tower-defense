#ifndef WIDGET_SIGNAL_H
#define WIDGET_SIGNAL_H

#include "gui_main.h"



BEGIN_GUI


class TWidgetSlot;
using SignalID = string;

class TWidgetSignal
{
public:
    using Slot = TWidgetSlot;
    using Args = void**;


    TWidgetSignal(const SignalID& id = SignalID());
    TWidgetSignal(const TWidgetSignal& other) = default;
    TWidgetSignal(TWidgetSignal&& other) = default;
    TWidgetSignal& operator = (const TWidgetSignal& other) = default;
    TWidgetSignal& operator = (TWidgetSignal&& other) = default;

    const SignalID& GetID() const;

    void Send(const Args& args = Args());

    void AddListener(const Slot& listener);
    void RemoveListener(const Slot& listener);
    bool HasListener(const Slot& listener) const;
    void RemoveListeners();
private:
    const SignalID id;
    using Listeners = list<Slot>;
    Listeners listeners;

    bool exists(const Slot& listener) const;

    Listeners::const_iterator find(const Slot& listener) const;
    Listeners::iterator find(const Slot& listener);
};


END_GUI

#endif // WIDGET_SIGNAL_H
