#include "menuobject.h"


BEGIN_GUI

TMenuObjectSource::TMenuObjectSource() :
    name(),
    position(),
    size(),
    margin(),
    show(false)
{}


TMenuObject::TMenuObject(const TMenuObjectSource& source) :
    parent_t(),
    name(source.name),
    parent(),
    children(),
    position(source.position),
    size(source.size),
    margin(source.margin),
    renderImage(source.size),
    mouseOver(false),
    visible(source.show),
    events(),
    clicked(false),
    needsRedraw(true)
{
    _checkBorders();
    _initializeEvents();
}

TMenuObject::TMenuObject(TMenuObject&& prot) noexcept :
    parent_t(std::move(prot)),
    name(std::move(prot.name)),
    parent(prot.parent),
    children(std::move(prot.children)),
    position(std::move(prot.position)),
    size(std::move(prot.size)),
    margin(std::move(prot.margin)),
    renderImage(std::move(prot.renderImage)),
    mouseOver(prot.mouseOver),
    visible(prot.visible),
    events(std::move(prot.events)),
    clicked(prot.clicked),
    needsRedraw(prot.needsRedraw)
{
    for (auto& slot : events.GetSlots()) {
        slot.second->SetOwner(this);
    }
}

TMenuObject::~TMenuObject() {
    if (parent.lock() != nullptr) {
        parent.lock()->RemoveChild(name);
    }
}

void TMenuObject::_initializeEvents() {
    for(Signal& signal : _enumSignals()) {
        events.AddSignal(std::move(signal));
    }

    for(Slot& slot : _enumSlots()) {
        events.AddSlot(std::move(slot));
    }
}

bool TMenuObject::_isMouseOverChild() const {
    if (children.empty() == true) {
        return false;
    }

    for(const auto& child : children) {
        if (child.second->IsMouseOver() == true) {
            return true;
        }
    }
    return false;
}

void TMenuObject::_updateMouse() {
    if (IO::IsMouseMoved() == true) {
        const TCoordinate position = GetScreenPosition();
        const bool isOver = IsVisible() &&
            IO::IsCursorInRect(position, position + GetOwnSize());

        if ((isOver == true) && (mouseOver == false)) {
            _OnHover();
            GetSignal(DefaultSignalID::MouseEntered).Send();
        } else if ((isOver == false) && (mouseOver == true)) {
            _OnMouseLeave();
            GetSignal(DefaultSignalID::MouseLeave).Send();
        } else {
            /*none*/
        }

        mouseOver = isOver;
    }

    if ((mouseOver == true) && (_isMouseOverChild() == false)) {
        if (IO::IsMouseHit(::IO::MouseKey::Left) == true) {
            clicked = true;
            _OnClick();
            GetSignal(DefaultSignalID::MouseClick).Send();
        }
    }

    if (clicked == true) {
        if (IO::IsMouseDown(::IO::MouseKey::Left) == true) {
            _OnMouseDown();
            GetSignal(DefaultSignalID::MouseDown).Send();
        } else {
            clicked = false;
            _OnMouseUp();
            GetSignal(DefaultSignalID::MouseUp).Send();
        }
    }
}

TPadding TMenuObject::GetInnerBorder() const {
    return TPadding(0, 0, 0, 0);
}

void TMenuObject::_update() {
    if (IsVisible() == true) {
        _updateMouse();
    }
}

void TMenuObject::_updateChildren() {
    for(auto& child : children) {
        child.second->Update();
    }
}

void TMenuObject::_drawChildren(TRenderTarget& target) {
    /*
        The use of reverse iterator intended to fix
        the problem of determining clicked object right.
        If children is updated in direct order,
        then the drawing will be in reversed order.
    */
    for(auto it = children.rbegin(), iend = children.rend(); it != iend; ++it) {
        (*it).second->Draw(target);
    }
}

void TMenuObject::_checkBorders() {
    const auto parent(this->parent.lock());
    float left = 0.f;
    float right = WindowWidth() - GetWidth();
    float top = 0.f;
    float bottom = WindowHeight() - GetHeight();
    if (parent != nullptr) {
        const TPadding parentBorder = std::move(parent->GetInnerBorder());
        left = margin.left;
        right = std::max(parent->GetOwnSize().x - parentBorder.right - GetWidth(), 0.f);
        top = margin.top;
        bottom = std::max(parent->GetOwnSize().y - parentBorder.bottom - GetHeight(), 0.f);
    }

    position.x = std::max(left, std::min(right, position.x));
    position.y = std::max(top, std::min(bottom, position.y));
}

void TMenuObject::_OnClick() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse click on object " + name);
#endif
    /*none*/
}
void TMenuObject::_OnHover() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse hover on object " + name);
#endif
    /*none*/
}
void TMenuObject::_OnMouseLeave() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse left object " + name);
#endif
    /*none*/
}
void TMenuObject::_OnPositionChanged() { needsRedraw = true; }
void TMenuObject::_OnShown() { needsRedraw = true; }
void TMenuObject::_OnHidden() { /*none*/ }
void TMenuObject::_OnMouseDown() { /*none*/ }
void TMenuObject::_OnMouseUp() { /*none*/ }
void TMenuObject::_OnResized() {
    needsRedraw = true;
    _checkBorders();
    renderImage.resize(size);
}

bool TMenuObject::IsMouseOver() const {
    return IsVisible() && mouseOver;
}

bool TMenuObject::IsVisible() const {
    const auto parent(this->parent.lock());
    return visible && ((parent != nullptr) ? parent->IsVisible() : true);
}

bool TMenuObject::IsShown() const {
    return visible;
}

void TMenuObject::SetVisibility(bool value) {
    if ((IsVisible() == false) && (value == true)) {
        _OnShown();
        GetSignal(DefaultSignalID::ObjectShown).Send();
        GetSignal(DefaultSignalID::ObjectVisibilityChanged).Send();
    } else if ((IsVisible() == true) && (value == false)) {
        _OnHidden();
        GetSignal(DefaultSignalID::ObjectHidden).Send();
        GetSignal(DefaultSignalID::ObjectVisibilityChanged).Send();
    } else {
        /*none*/
    }

    visible = value;
}

void TMenuObject::Show() {
    SetVisibility(true);
}

void TMenuObject::Hide() {
    SetVisibility(false);
}


const string& TMenuObject::GetName() const {
    return name;
}


void TMenuObject::SetParent(const TMenuObjectWeakRef& value) {
    const auto currentParent = parent.lock();
    if ((currentParent != nullptr) && (currentParent == value.lock())) {
        return;
    }

    if (value.lock() != nullptr) {
        if (value.lock()->HasChild(name) == false) {
            Child child = currentParent ?
                std::move(currentParent->RemoveChild(name)) :
                shared_from_this();

            value.lock()->children[name] = std::move(child);
        }
    }
    parent = value;
}

TMenuObjectWeakRef TMenuObject::GetParent() const {
    return parent;
}

void TMenuObject::AddChild(const TMenuObjectRef& obj) {
    GUI_ASSERT(obj != nullptr, "Can not add null object as a child to '" + name + "'.")

    const auto objCurrentParent = obj->parent.lock();

    GUI_ASSERT( (
            (HasChild(obj->name) == true) &&
            (objCurrentParent.get() != this)
        ) == false,
        "Menu object '" + name + "' already contains "
        "child with name '" + obj->name + "'.")

    if ((objCurrentParent.get() != this) &&
        (objCurrentParent != nullptr))
    {
        if (objCurrentParent->HasChild(obj->name) == true) {
            objCurrentParent->children.erase(obj->name); //since obj in the same group of shared_ptrs
        }
    }

    obj->parent = shared_from_this();
    children[obj->name] = obj;
}

TMenuObject::Child TMenuObject::RemoveChild(const string& name) {
    GUI_ASSERT(HasChild(name) == true,
        "Menu object '" + GetName() + "' does not contain "
        "child with name '" + name + "'.");

    Child child = children[name];
    children.erase(name);
    child->parent.reset();
    return child;
}

bool TMenuObject::HasChild(const string& name) const {
    return children.count(name) != 0;
}

bool TMenuObject::HasChild(const Child& child) const {
    if (child == nullptr) { return false; }
    return HasChild(child->name) && (child->parent.lock().get() == this);
}

void TMenuObject::RemoveChildren() {
    children.clear();
}

bool TMenuObject::HasChildren() const {
    return (children.empty() == false);
}

/*
    Returns nullptr if child not found.
    For recursive search use '<parentName>keySep()<childName>...'.
*/
TMenuObject::ConstChildRef TMenuObject::FindChild(const Key& key) const {
    const auto parts = std::move(String::split(key, keySep()));
    ConstChild currentObject = shared_from_this();
    for(const auto& part : parts) {
        if (currentObject == nullptr) {
            break;
        }
        if (currentObject->children.count(part) == 0) {
            currentObject.reset();
        } else {
            currentObject = currentObject->children.at(part);
        }
    }
    return currentObject;
}

/*
    Returns nullptr if child not found.
    For recursive search use '<parentName>keySep()<childName>...'.
*/
TMenuObject::ChildRef TMenuObject::FindChild(const Key& key) {
    const auto parts = std::move(String::split(key, keySep()));
    Child currentObject = shared_from_this();
    for(const auto& part : parts) {
        if (currentObject == nullptr) {
            break;
        }
        if (currentObject->children.count(part) == 0) {
            currentObject.reset();
        } else {
            currentObject = currentObject->children.at(part);
        }
    }
    return currentObject;
}

/*
    Returns a list with children of specified name.
*/
list<TMenuObject::ConstChildRef> TMenuObject::FindChildren(const string& name, bool recursievly) const {
    list<ConstChildRef> result;

    if (children.count(name) != 0) {
        result.emplace_back(children.at(name));
    }

    if (recursievly == true) {
        for(const auto& currentObject : children) {
            auto currentObjectChildren = std::move(currentObject.second->FindChildren(name, true));
            result.insert(result.end(), currentObjectChildren.cbegin(), currentObjectChildren.cend());
        }
    }

    return result;
}
/*
    Returns a list with children of specified name.
*/
list<TMenuObject::ChildRef> TMenuObject::FindChildren(const string& name, bool recursievly) {
    list<ChildRef> result;

    if (children.count(name) != 0) {
        result.emplace_back(children.at(name));
    }

    if (recursievly == true) {
        for(auto& currentObject : children) {
            auto currentObjectChildren = std::move(currentObject.second->FindChildren(name, true));
            result.insert(result.end(), currentObjectChildren.cbegin(), currentObjectChildren.cend());
        }
    }

    return result;
}



const TSize& TMenuObject::GetOwnSize() const {
    return size;
}

void TMenuObject::SetSize(const TSize& value) {
    if (size != value) {
        size = value;
        _OnResized();
    }
}

float TMenuObject::GetWidth() const {
    return size.x + margin.left + margin.right;
}

float TMenuObject::GetHeight() const {
    return size.y + margin.top + margin.bottom;
}

TSize TMenuObject::GetSize() const {
    return TSize(GetWidth(), GetHeight());
}


const TCoordinate& TMenuObject::GetPosition() const {
    return position;
}

TCoordinate TMenuObject::GetScreenPosition() const {
    const auto currentParent = parent.lock();
    if (currentParent != nullptr) {
        TPadding innerBorder = std::move(currentParent->GetInnerBorder());
        return position + currentParent->GetScreenPosition() +
               TCoordinate(innerBorder.left, innerBorder.top);
    } else {
        return position;
    }
}

void TMenuObject::SetPosition(const TCoordinate& temp) {
    TCoordinate value(
        std::max(0.f, temp.x),
        std::max(0.f, temp.y)
    );

    if (position != value) {
        position = std::move(value);
        _checkBorders();
        _OnPositionChanged();
        GetSignal(DefaultSignalID::ObjectPositionChanged).Send();
    }
}

void TMenuObject::SetPosition(float x, float y) {
    SetPosition(TCoordinate(x, y));
}


const TPadding& TMenuObject::GetMargin() const {
    return margin;
}

void TMenuObject::SetMargin(const TPadding& value) {
    if (margin != value) {
        margin = value;
        _checkBorders();
        _OnPositionChanged();
    }
}


void TMenuObject::Update() {
    if (IsVisible() == false) {
        return;
    }
    _update();
    _updateChildren();
}

void TMenuObject::Draw(TRenderTarget& target) {
    if (IsVisible() == false) {
        return;
    }
    _draw(target);
    _drawChildren(target);
}


bool TMenuObject::HasSignal(const Signal& signal) const {
    return events.HasSignal(signal.GetID());
}
bool TMenuObject::HasSignal(const SignalID& signal) const {
    return events.HasSignal(signal);
}

bool TMenuObject::HasSlot(const Slot& slot) const {
    return events.HasSlot(slot->GetID());
}
bool TMenuObject::HasSlot(const SignalID& slot) const {
    return events.HasSlot(slot);
}

const TMenuObject::Signal& TMenuObject::GetSignal(const string& name) const {
    return events.GetSignal(name);
}
TMenuObject::Signal& TMenuObject::GetSignal(const string& name) {
    return events.GetSignal(name);
}

const TMenuObject::Slot& TMenuObject::GetSlot(const string& name) const {
    return events.GetSlot(name);
}
TMenuObject::Slot &TMenuObject::GetSlot(const string& name) {
    return events.GetSlot(name);
}

void TMenuObject::RegisterSignal(TMenuObjectSignal&& signal) {
    events.AddSignal(std::move(signal));
}

void TMenuObject::RegisterSlot(TMenuObjectSlot&& slot) {
    events.AddSlot(std::make_shared<TMenuObjectSlot>(std::move(slot)));
}


std::list<TMenuObject::Signal>* TMenuObject::_basicSignals_cache = nullptr;
/*
    Returns a list of common signals.
*/
const list<TMenuObject::Signal>& TMenuObject::_basicSignals() {
    if (_basicSignals_cache == nullptr) {
        _basicSignals_cache = new std::list<Signal>();
        for (const auto& signalID : DefaultSignalID::enumerate()) {
            _basicSignals_cache->emplace_back(signalID);
        }
    }
    return *_basicSignals_cache;
}

std::list<TMenuObject::Signal> TMenuObject::_enumSignals() const {
    return _basicSignals();
}

std::list<TMenuObject::Slot> TMenuObject::_enumSlots() const {
    return std::list<Slot>();
}


void TMenuObject::Connect(const TMenuObjectRef &signalOwner, Signal& signal, const TMenuObjectRef& slotOwner, const Slot& slot) {
    GUI_ASSERT(signalOwner && slotOwner, "Signal or slot is null.")

    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    GUI_ASSERT(slotOwner->HasSlot(slot) == true,
        "Object '" + slotOwner->GetName() + "' does not have this slot.")

    signal.AddListener(slot);
}

void TMenuObject::Disconnect(const TMenuObjectRef& signalOwner, Signal& signal, const TMenuObjectRef& slotOwner, const Slot& slot) {
    GUI_ASSERT(signalOwner && slotOwner, "Signal or slot is null.")

    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    GUI_ASSERT(slotOwner->HasSlot(slot) == true,
        "Object '" + slotOwner->GetName() + "' does not have this slot.")

    signal.RemoveListener(slot);
}


END_GUI
