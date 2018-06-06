#ifndef WIDGET_EVENT_SYSTEM_H
#define WIDGET_EVENT_SYSTEM_H

#include "gui_main.h"
#include "widget_signal.h"
#include "widget_slot.h"



BEGIN_GUI


class TWidgetEventSystem
{
public:
    using Signal = TWidgetSignal;
    using Signals = std::map<SignalID, Signal>;
    using Slot = TWidgetSlot;
    using Slots = std::map<SlotID, Slot>;


    bool HasSignal(const SignalID& signal) const;
    bool HasSlot(const SlotID& slot) const ;

    const Signal& GetSignal(const SignalID& name) const;
    Signal& GetSignal(const SignalID& name);

    const Slot& GetSlot(const SlotID& name) const;
    Slot& GetSlot(const SlotID& name);

    const Slots& GetSlots() const;
    Slots& GetSlots();

    const Signals& GetSignals() const;
    Signals& GetSignals();

    void AddSignal(const Signal& signal);
    void AddSignal(Signal&& signal);

    void AddSlot(const Slot& slot);
    void AddSlot(Slot&& slot);

private:
    Signals signals;
    Slots slots;
};

using TEvent = sf::Event;
using TEvent_MouseClick = sf::Event::MouseButtonEvent;
using TEvent_MouseMoved = sf::Event::MouseMoveEvent;


END_GUI

#endif // WIDGET_EVENT_SYSTEM_H
