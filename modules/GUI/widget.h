#ifndef WIDGET_H
#define WIDGET_H

#include "gui_main.h"
#include "widget_event_system.h"
#include "signal_defs.h"



BEGIN_GUI


class TWidget;
using TWidgetRef = std::shared_ptr<TWidget>;
using TWidgetConstRef = std::shared_ptr<const TWidget>;
using TWidgetWeakRef = std::weak_ptr<TWidget>;
using TWidgetConstWeakRef = std::weak_ptr<const TWidget>;

struct TWidgetSource
{
    //Main
    string name;
    //Graphics
    TCoordinate position;
    TSize size;
    TPadding margin;
    //Flags
    bool show;

    TWidgetSource();
};

class TWidget : public std::enable_shared_from_this<TWidget> /*Abstract*/
{
public:
    using Name = string;
    using Child = TWidgetRef;
    using ConstChild = TWidgetConstRef;
    using ChildRef = TWidgetWeakRef;
    using ConstChildRef = TWidgetConstWeakRef;
    using Children = std::map<Name, Child>;
    using Signal = TWidgetEventSystem::Signal;
    using Slot = TWidgetEventSystem::Slot;


    TWidget() = default;
    TWidget(const TWidgetSource& source);
    TWidget(const TWidget& other);
    virtual TWidget& operator = (const TWidget& other);
    TWidget(TWidget&& prot);
    virtual TWidget& operator = (TWidget&& prot);
    virtual ~TWidget();

    virtual void Initialize();

    virtual bool IsMouseOver() const;
    virtual bool IsVisible() const;
    virtual bool IsShown() const;

    virtual void SetVisibility(bool value);
    void Show(); /*wrapper*/
    void Hide(); /*wrapper*/

    const Name& GetName() const;

    virtual void SetParent(const TWidgetWeakRef& value);
    virtual TWidgetWeakRef GetParent() const;

    virtual void AddChild(const TWidgetRef& obj);
    virtual Child RemoveChild(const Name& name);
    virtual bool HasChild(const Name& name) const;

    /*
        True if has child with given name and child's parent is this.
    */
    virtual bool HasChild(const Child& child) const;

    virtual void RemoveChildren();
    virtual bool HasChildren() const;

    static constexpr char keySep() {
        return TGUISettings::DefaultKeySeparator;
    }

    /*
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    virtual ConstChildRef FindChild(const Name& key) const;

    /*
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    virtual ChildRef FindChild(const Name& key);

    /*
        Returns child and casts him to the const given type.
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    template< class T >
    std::weak_ptr<const T> FindChild(const Name& key) const;

    /*
        Returns child and casts him to the given type.
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    template< class T >
    std::weak_ptr<T> FindChild(const Name& key);

    /*
        Returns a list with children of specified name.
    */
    virtual std::list<ConstChildRef> FindChildren(const Name& name,
        bool recursievly = true) const;

    /*
        Returns a list with children of specified name.
    */
    virtual std::list<ChildRef> FindChildren(const Name& name,
        bool recursievly = true);

    /*
        Returns size without margin.
    */
    virtual const TSize& GetOwnSize() const;

    virtual void SetSize(const TSize& value);

    /*
        Returns full width with margin.
    */
    virtual float GetWidth() const;

    /*
        Returns full height with margin.
    */
    virtual float GetHeight() const;

    /*
        Returns full size with margin.
    */
    virtual TSize GetSize() const;

    virtual const TCoordinate& GetPosition() const;

    /*
        Returns position with respect to parent containers
    */
    virtual TCoordinate GetScreenPosition() const;

    virtual void SetPosition(const TCoordinate& value);
    virtual void SetPosition(float x, float y);

    /*
        Returns marign size of this object.
    */
    virtual const TPadding& GetMargin() const;
    virtual void SetMargin(const TPadding& value);

    /*
        Returns inner border size for this object
        with respect to padding.
    */
    virtual TPadding GetInnerBorder() const;

    virtual void Update() final;
    virtual void Draw(TRenderTarget& target) final;

    virtual bool HasSignal(const SignalID& signal) const final;
    virtual bool HasSignal(const Signal& signal) const final;

    virtual bool HasSlot(const SlotID& slot) const final;
    virtual bool HasSlot(const Slot& slot) const final;

    virtual const Signal& GetSignal(const SignalID& name) const final;
    virtual Signal& GetSignal(const SignalID& name) final;

    virtual const Slot& GetSlot(const SlotID& name) const final;
    virtual Slot& GetSlot(const SlotID& name) final;

    virtual void RegisterSignal(const TWidgetSignal& signal) final;
    virtual void RegisterSignal(TWidgetSignal&& signal) final;

    virtual void RegisterSlot(const TWidgetSlot& slot) final;
    virtual void RegisterSlot(TWidgetSlot&& slot) final;

    static void Connect(const TWidgetRef& signalOwner,
        Signal& signal, const TWidgetRef& slotOwner, const Slot& slot);

    static void Disconnect(const TWidgetRef& signalOwner,
        Signal& signal, const TWidgetRef& slotOwner, const Slot& slot);

private:
    using parent_type = std::enable_shared_from_this<TWidget>;

protected:
    //Main
    Name name;
    //Tree
    TWidgetWeakRef parent;
    Children children;
    //Graphics
    TCoordinate position;
    TSize size;
    TPadding margin;
    TRenderObject renderImage;
    //Flags
    bool mouseOver;
    bool visible;
    //Events
    TWidgetEventSystem eventSystem;
    //Temporary
    bool clicked;
    bool needsRedraw;


    virtual void _initializeEvents();

    virtual bool _isMouseOverChild() const;

    virtual void _updateMouse();
    virtual void _update();
    virtual void _updateChildren();

    virtual void _draw(TRenderTarget& target) = 0;
    virtual void _drawChildren(TRenderTarget& target);

    virtual void _checkBorders();

    virtual void _OnClick();
    virtual void _OnHover();
    virtual void _OnMouseLeave();
    virtual void _OnPositionChanged();
    virtual void _OnShown();
    virtual void _OnHidden();
    virtual void _OnMouseDown();
    virtual void _OnMouseUp();
    virtual void _OnResized();

    /*
        Returns a list of signals that have to be created.
    */
    virtual std::list<Signal> _enumSignals() const;

    static const std::list<Signal> _basicSignals_cache;

    /*
        Returns a list of common signals.
    */
    static const std::list<Signal>& _basicSignals();

    /*
        Returns a list of slots that have to be created.
    */
    virtual std::list<Slot> _enumSlots() const;
};


template< class T >
std::weak_ptr<const T> TWidget::FindChild(const Name& key) const {
    return std::dynamic_pointer_cast<const T>(FindChild(key).lock());
}

template< class T >
std::weak_ptr<T> TWidget::FindChild(const Name& key) {
    return std::dynamic_pointer_cast<T>(FindChild(key).lock());
}


END_GUI

#endif // WIDGET_H
