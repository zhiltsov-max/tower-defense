#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include "gui_main.h"
#include "events.h"
#include "signal_defs.h"

BEGIN_GUI

class TMenuObject;
using TMenuObjectRef = std::shared_ptr<TMenuObject>;
using TMenuObjectConstRef = std::shared_ptr<const TMenuObject>;
using TMenuObjectWeakRef = std::weak_ptr<TMenuObject>;
using TMenuObjectConstWeakRef = std::weak_ptr<const TMenuObject>;

struct TMenuObjectSource
{
    //Main
    string name;
    //Graphics
    TCoordinate position;
    TSize size;
    TPadding margin;
    //Flags
    bool show;

    TMenuObjectSource();
};

class TMenuObject : public std::enable_shared_from_this<TMenuObject> /*Abstract*/
{
public:
    typedef string Key;
    typedef TMenuObjectRef Child;
    typedef TMenuObjectConstRef ConstChild;
    typedef TMenuObjectWeakRef ChildRef;
    typedef TMenuObjectConstWeakRef ConstChildRef;
    typedef std::map<Key, Child> Children;
    typedef TMenuObjectSignal Signal;
    typedef std::shared_ptr<TMenuObjectSlot> Slot;

    TMenuObject() = default;
    TMenuObject(const TMenuObjectSource& source);
    TMenuObject(const TMenuObject& other) = delete; /*since there is only single entry with given name in parent container*/
    TMenuObject& operator=(const TMenuObject& other) = delete; /*since there is only single entry with given name in parent container*/
    TMenuObject(TMenuObject&& prot) noexcept;
    virtual TMenuObject& operator=(TMenuObject&& prot) = default;
    virtual ~TMenuObject();

    virtual bool IsMouseOver() const;
    virtual bool IsVisible() const;
    virtual bool IsShown() const;

    virtual void SetVisibility(bool value);
    void Show(); /*wrapper*/
    void Hide(); /*wrapper*/

    const string& GetName() const;

    virtual void SetParent(const TMenuObjectWeakRef& value);
    virtual TMenuObjectWeakRef GetParent() const;

    virtual void AddChild(const TMenuObjectRef& obj);
    virtual Child RemoveChild(const string& name);
    virtual bool HasChild(const string& name) const;

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
    virtual ConstChildRef FindChild(const Key& key) const;

    /*
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    virtual ChildRef FindChild(const Key& key);

    /*
        Returns child and casts him to the const given type.
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    template< class T >
    std::weak_ptr<const T> FindChild(const Key& key) const;

    /*
        Returns child and casts him to the given type.
        Returns nullptr if child not found.
        For recursive search use '<parentName>keySep()<childName>...'.
    */
    template< class T >
    std::weak_ptr<T> FindChild(const Key& key);

    /*
        Returns a list with children of specified name.
    */
    virtual std::list<ConstChildRef> FindChildren(const string& name, bool recursievly = true) const;

    /*
        Returns a list with children of specified name.
    */
    virtual std::list<ChildRef> FindChildren(const string& name, bool recursievly = true);

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

    virtual const TPadding& GetMargin() const;
    virtual void SetMargin(const TPadding& value);

    virtual TPadding GetInnerBorder() const;

    virtual void Update() final;
    virtual void Draw(TRenderTarget& target) final;

    virtual bool HasSignal(const SignalID &signal) const final;
    virtual bool HasSlot(const SignalID& slot) const final;
    virtual bool HasSignal(const Signal &signal) const final;
    virtual bool HasSlot(const Slot& slot) const final;

    virtual const Signal& GetSignal(const string& name) const final;
    virtual Signal& GetSignal(const string& name) final;
    virtual const Slot& GetSlot(const string& name) const final;
    virtual Slot& GetSlot(const string& name) final;

    virtual void RegisterSignal(TMenuObjectSignal&& signal) final;
    virtual void RegisterSlot(TMenuObjectSlot&& slot) final;

    static void Connect(const TMenuObjectRef& signalOwner, Signal& signal, const TMenuObjectRef& slotOwner, const Slot& slot);
    static void Disconnect(const TMenuObjectRef& signalOwner, Signal& signal, const TMenuObjectRef& slotOwner, const Slot& slot);
private:
    typedef std::enable_shared_from_this<TMenuObject> parent_t;
protected:
    //Main
    string name;
    //Tree
    TMenuObjectWeakRef parent;
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
    TMenuObjectEvents events;
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
    virtual list<Signal> _enumSignals() const;
    static list<Signal>* _basicSignals_cache;

    /*
        Returns a list of common signals.
    */
    static const list<Signal>& _basicSignals();

    /*
        Returns a list of slots that have to be created.
    */
    virtual list<Slot> _enumSlots() const;
};


template< class T >
std::weak_ptr<const T> TMenuObject::FindChild(const Key& key) const {
    return std::dynamic_pointer_cast<const T>(FindChild(key).lock());
}

template< class T >
std::weak_ptr<T> TMenuObject::FindChild(const Key& key) {
    return std::dynamic_pointer_cast<T>(FindChild(key).lock());
}

END_GUI

#endif // MENUOBJECT_H
