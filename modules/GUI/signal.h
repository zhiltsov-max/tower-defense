#ifndef SIGNAL_H
#define SIGNAL_H

#include "gui_main.h"

BEGIN_GUI

class TMenuObjectSlot;
using SignalID = string;

class TMenuObjectSignal
{
public:
    typedef std::weak_ptr<TMenuObjectSlot> Slot;
    typedef void** Args;

    TMenuObjectSignal(const SignalID& name_ = SignalID());
    TMenuObjectSignal(const TMenuObjectSignal& other);
    TMenuObjectSignal(TMenuObjectSignal&& other) = default;
    TMenuObjectSignal& operator=(const TMenuObjectSignal& other) = delete;
    TMenuObjectSignal& operator=(TMenuObjectSignal&& other) = delete;
    ~TMenuObjectSignal() = default;

    const SignalID& GetID() const;

    void Send(const Args& args = Args());

    void AddListener(const Slot& listener);
    void RemoveListener(const Slot& listener);
    bool HasListener(const Slot& listener) const;
private:
    const SignalID name;
    typedef std::list<Slot> Listeners;
    Listeners listeners;

    bool exists(const Slot& listener) const;

    Listeners::const_iterator find(const Slot &listener) const;
    Listeners::iterator find(const Slot& listener);
};


END_GUI

#endif // SIGNAL_H
