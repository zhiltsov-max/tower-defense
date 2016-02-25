#ifndef EVENTS_H
#define EVENTS_H

#include "gui_main.h"
#include "signal.h"
#include "slot.h"

BEGIN_GUI

class TMenuObjectEvents
{
public:
    typedef TMenuObjectSignal Signal;
    typedef std::shared_ptr<TMenuObjectSlot> Slot;
    typedef std::map<string, Signal> Signals;
    typedef std::map<string, Slot> Slots;

    TMenuObjectEvents() = default;
    TMenuObjectEvents(const TMenuObjectEvents& other) = delete; //too difficult
    TMenuObjectEvents(TMenuObjectEvents&& other) = default;
    TMenuObjectEvents& operator=(const TMenuObjectEvents& other) = delete; //too difficult
    TMenuObjectEvents& operator=(TMenuObjectEvents&& other) = default;
    ~TMenuObjectEvents() = default;

    bool HasSignal(const SignalID& signal) const;
    bool HasSlot(const SignalID& slot) const ;

    const Signal& GetSignal(const SignalID& name) const;
    Signal& GetSignal(const SignalID& name);

    const Slot& GetSlot(const SignalID& name) const;
    Slot& GetSlot(const SignalID& name);

    const Slots& GetSlots() const;
    Slots& GetSlots();

    const Signals& GetSignals() const;
    Signals& GetSignals();

    void AddSignal(Signal&& signal);
    void AddSlot(Slot&& slot);
private:
    Signals m_signals;
    Slots m_slots;

    void swap(TMenuObjectEvents& other);
};

END_GUI

#endif // EVENTS_H
