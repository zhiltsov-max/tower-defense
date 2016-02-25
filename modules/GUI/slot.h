#ifndef SLOT_H
#define SLOT_H

#include "gui_main.h"
#include "signal.h"


BEGIN_GUI

class TMenuObject;

class TMenuObjectSlot
{
public:
    using Args = void**;
    using Method = void (*)(TMenuObject*, Args);


    TMenuObjectSlot(TMenuObject* owner, const SignalID& name,
        Method pointer);

    TMenuObjectSlot(const TMenuObjectSlot& other) = default;
    TMenuObjectSlot(TMenuObjectSlot&& other) = default;
    ~TMenuObjectSlot() = default;
    TMenuObjectSlot& operator=(const TMenuObjectSlot& other) = delete;
    TMenuObjectSlot& operator=(TMenuObjectSlot&& other) = delete;


    void Invoke(Args args = nullptr) const;

    const SignalID& GetID() const;
    const Method& GetPtr() const;    

    TMenuObject const* GetOwner() const;
    void SetOwner(TMenuObject* value);

private:
    const SignalID name;
    TMenuObject* owner;
    Method ptr;
};

END_GUI

#endif // SLOT_H
