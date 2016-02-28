#ifndef WIDGET_SLOT_H
#define WIDGET_SLOT_H

#include "gui_main.h"
#include "widget_signal.h"
#include <functional>



BEGIN_GUI


class TWidget;
using SlotID = SignalID;

class TWidgetSlot
{
public:
    using Args = void**;
    using Method = std::function<void (TWidget*, Args)>;
    using Owner = std::weak_ptr<TWidget>;


    TWidgetSlot(const Owner& owner, const SlotID& id,
        const Method& pointer);

    TWidgetSlot(const TWidgetSlot& other) = default;
    TWidgetSlot(TWidgetSlot&& other) = default;
    TWidgetSlot& operator = (const TWidgetSlot& other) = default;
    TWidgetSlot& operator = (TWidgetSlot&& other) = default;

    bool operator == (const TWidgetSlot& other) const;
    bool operator != (const TWidgetSlot& other) const;

    void Invoke(const Args& args = nullptr) const;

    const SlotID& GetID() const;

    const Method& GetPtr() const;
    bool HasPtr() const;

    const Owner& GetOwner() const;
    void SetOwner(const Owner& value);

private:
    const SlotID name;
    Owner owner;
    Method ptr;
};


END_GUI

#endif // WIDGET_SLOT_H
