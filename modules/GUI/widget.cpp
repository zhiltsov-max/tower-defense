#include "widget.h"
#include <limits>


BEGIN_GUI

TWidgetSource::TWidgetSource() :
    name(),
    position(),
    size(),
    margin(),
    show(false)
{}

TWidget::TWidget(const TWidgetSource& source) :
    parent_type(),
    name(source.name),
    parent(),
    children(),
    position(source.position),
    size(source.size),
    margin(source.margin),
    renderImage(source.size),
    mouseOver(false),
    visible(source.show),
    eventSystem(),
    clicked(false),
    needsRedraw(true)
{}


TWidget::TWidget(const TWidget& other) :
    parent_type(other),
    name(other.name),
    parent(), // copy have no parent
    children(other.children),
    position(other.position),
    size(other.size),
    margin(other.margin),
    renderImage(other.size),
    mouseOver(false),
    visible(other.visible),
    eventSystem(other.eventSystem),
    clicked(false),
    needsRedraw(true)
{
    for (auto& signal : eventSystem.GetSignals()) {
        signal.second.RemoveListeners();
    }
    for (auto& slot : eventSystem.GetSlots()) {
        slot.second.SetOwner(shared_from_this());
    }
}


TWidget::TWidget(TWidget&& prot) :
    parent_type(std::move(prot)),
    name(std::move(prot.name)),
    parent(prot.parent),
    children(std::move(prot.children)),
    position(std::move(prot.position)),
    size(std::move(prot.size)),
    margin(std::move(prot.margin)),
    renderImage(std::move(prot.renderImage)),
    mouseOver(prot.mouseOver),
    visible(prot.visible),
    eventSystem(std::move(prot.eventSystem)),
    clicked(prot.clicked),
    needsRedraw(prot.needsRedraw)
{
    for (auto& slot : eventSystem.GetSlots()) {
        slot.second.SetOwner(shared_from_this());
    }
}


TWidget& TWidget::operator = (const TWidget& other) {
    if (this != &other) {
        parent_type::operator = (other);
        name = other.name;
        parent.reset();
        children = other.children;
        position = other.position;
        size = other.size;
        margin = other.margin;
        renderImage = std::move(TRenderObject(other.size));
        mouseOver = false;
        visible = other.visible;
        eventSystem = other.eventSystem;
        clicked = false;
        needsRedraw = true;

        for (auto& signal : eventSystem.GetSignals()) {
            signal.second.RemoveListeners();
        }
        for (auto& slot : eventSystem.GetSlots()) {
            slot.second.SetOwner(shared_from_this());
        }
    }
    return *this;
}


TWidget& TWidget::operator = (TWidget&& prot) {
    if (this != &prot) {
        parent_type::operator = (std::move(prot));
        name = std::move(prot.name);
        parent = std::move(prot.parent);
        children = std::move(prot.children);
        position = std::move(prot.position);
        size = std::move(prot.size);
        margin = std::move(prot.margin);
        renderImage = std::move(prot.renderImage);
        mouseOver = std::move(prot.mouseOver);
        visible = std::move(prot.visible);
        eventSystem = std::move(prot.eventSystem);
        clicked = std::move(prot.clicked);
        needsRedraw = std::move(prot.needsRedraw);

        for (auto& slot : eventSystem.GetSlots()) {
            slot.second.SetOwner(shared_from_this());
        }
    }
    return *this;
}

void TWidget::Initialize() {
    _initializeEvents();
    _checkBorders();
}

TWidget::~TWidget() {
    if (parent.expired() == false) {
        auto p = parent.lock();
        if (p->HasChild(shared_from_this())) {
            p->RemoveChild(name);
        }
    }
}

void TWidget::_initializeEvents() {
    for(Signal& signal : _enumSignals()) {
        eventSystem.AddSignal(std::move(signal));
    }

    for(Slot& slot : _enumSlots()) {
        eventSystem.AddSlot(std::move(slot));
    }
}

bool TWidget::_isMouseOverChild() const {
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

TPadding TWidget::GetInnerBorder() const {
    return TPadding(0, 0, 0, 0);
}

void TWidget::_update() { /*none*/ }

void TWidget::_updateChildren() {
    for(auto& child : children) {
        child.second->Update();
    }
}

void TWidget::_drawChildren(TRenderTarget& target) {
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

void TWidget::_checkBorders() {
    const auto parent(this->parent.lock());
    float left = 0.f;
    float right = std::numeric_limits<float>::max();
    float top = 0.f;
    float bottom = std::numeric_limits<float>::max();
    if (parent != nullptr) {
        const TPadding parentBorder = std::move(parent->GetInnerBorder());
        left = margin.left;
        right = std::max(
            parent->GetOwnSize().x - parentBorder.right - GetWidth(), 0.f);
        top = margin.top;
        bottom = std::max(
            parent->GetOwnSize().y - parentBorder.bottom - GetHeight(), 0.f);
    }

    position.x = std::max(left, std::min(right, position.x));
    position.y = std::max(top, std::min(bottom, position.y));
}

void TWidget::_sendEvent(const TEvent& event, bool& consumed) {
    if (consumed == false) {
        _handleEvent(event, consumed);
    }

    if (consumed == false) {
        for (auto& child : children) {
            child.second->_sendEvent(event, consumed);
        }
    }
}

void TWidget::_handleEvent(const TEvent& event, bool& consume) {
    switch (event.type) {
    case TEvent::EventType::MouseMoved:
        _handle_mouseMove(event.mouseMove, consume);
        break;
    case TEvent::EventType::MouseButtonPressed:
        _handle_mouseButtonPressed(event.mouseButton, consume);
        break;
    case TEvent::EventType::MouseButtonReleased:
        _handle_mouseButtonReleased(event.mouseButton, consume);
        break;
    default: { /*none*/ }
    }
}

void TWidget::_handle_mouseButtonPressed(
    const TEvent_MouseClick& event, bool& consume
) {
    consume = false;

    if (IsVisible() == false) {
        return;
    }

    if ((mouseOver == true) && (_isMouseOverChild() == false)) {
        _OnMouseButtonDown(event);
        GetSignal(DefaultSignalID::MouseButtonDown).Send(&event);

        consume = true;
    }
}

void TWidget::_handle_mouseButtonReleased(
    const TEvent_MouseClick& event, bool& consume
) {
    consume = false;

    if (IsVisible() == false) {
        return;
    }

    if (clicked == true) {
        if ((mouseOver == true) && (_isMouseOverChild() == false)) {
            _OnClick();
            GetSignal(DefaultSignalID::MouseClick).Send();
        }

        _OnMouseButtonUp(event);
        GetSignal(DefaultSignalID::MouseButtonUp).Send(&event);
    }
}

void TWidget::_handle_mouseMove(const TEvent_MouseMoved& event, bool& consume) {
    consume = false;

    if (IsVisible() == false) {
        return;
    }

    const auto& mousePosition = event;
    const auto position = GetScreenPosition();
    const auto bounds = position + GetOwnSize();
    const bool isOver = IsVisible() &&
        isPointInRect(mousePosition.x, mousePosition.y,
            position.x, position.y, bounds.x, bounds.y);

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

void TWidget::_OnClick() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse click on object " + name);
#endif
    /*none*/
}
void TWidget::_OnHover() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse hover on object " + name);
#endif
    /*none*/
}
void TWidget::_OnMouseLeave() {
#if defined(_DEBUG)
    Debug::logMessage("Mouse left object " + name);
#endif
    /*none*/
}

void TWidget::_OnMouseButtonDown(const TEvent_MouseClick& event) {
    if (event.button == sf::Mouse::Button::Left) {
        clicked = true;
    }
}

void TWidget::_OnMouseButtonUp(const TEvent_MouseClick& event) {
    if (event.button == sf::Mouse::Button::Left) {
        clicked = false;
    }
}

void TWidget::_OnPositionChanged() { needsRedraw = true; }

void TWidget::_OnShown() { needsRedraw = true; }

void TWidget::_OnHidden() { /*none*/ }

void TWidget::_OnResized() {
    needsRedraw = true;
    _checkBorders();
    renderImage.resize(size);
}

void TWidget::_OnParentChanged() {
    _checkBorders();
}

bool TWidget::IsMouseOver() const {
    return IsVisible() && mouseOver;
}

bool TWidget::IsVisible() const {
    const auto parent(this->parent.lock());
    return visible && ((parent != nullptr) ? parent->IsVisible() : true);
}

bool TWidget::IsShown() const {
    return visible;
}

void TWidget::SetVisibility(bool value) {
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

void TWidget::Show() {
    SetVisibility(true);
}

void TWidget::Hide() {
    SetVisibility(false);
}


const TWidget::Name& TWidget::GetName() const {
    return name;
}


void TWidget::SetParent(const TWidgetWeakRef& value) {
    const auto currentParent = parent.lock();
    if (currentParent == value.lock()) {
        return;
    }

    Child me = shared_from_this();

    if (value.expired() == false) {
        auto newParent = value.lock();
        ASSERT(newParent->HasChild(name) == false,
           "Menu object '" + newParent->name + "' already contains "
           "child with name '" + name + "'.")

        newParent->children[name] = me;
    }

    if ((currentParent != nullptr) && (currentParent->HasChild(me) == true)) {
        currentParent->children.erase(name);
    }

    parent = value;
    _OnParentChanged();
    GetSignal(DefaultSignalID::ObjectParentChanged).Send();
}

TWidgetWeakRef TWidget::GetParent() const {
    return parent;
}

void TWidget::AddChild(const TWidgetRef& obj) {
    GUI_ASSERT(obj != nullptr,
        "Can not add null object as a child to '" + name + "'.")

    obj->SetParent(shared_from_this());
}

TWidget::Child TWidget::RemoveChild(const Name& name) {
    GUI_ASSERT(HasChild(name) == true,
        "Menu object '" + GetName() + "' does not contain "
        "child with name '" + name + "'.");

    Child child = children[name];
    children.erase(name);
    child->SetParent(TWidgetWeakRef());
    return child;
}

TWidget::Child TWidget::RemoveChild(const Child& obj) {
    return RemoveChild(obj->GetName());
}

bool TWidget::HasChild(const Name& name) const {
    return children.count(name) != 0;
}

bool TWidget::HasChild(const ChildRef& childRef) const {
    if (childRef.expired() == true) { return false; }
    const auto child = childRef.lock();
    return HasChild(child->name) && (child->parent.lock().get() == this);
}

void TWidget::RemoveChildren() {
    for (auto& entry : children) {
        RemoveChild(entry.first);
    }
}

bool TWidget::HasChildren() const {
    return (children.empty() == false);
}

TWidget::ConstChildRef TWidget::FindChild(const Name& key) const {
    const auto parts = String::split(key, keySep());
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
    if (currentObject.get() == this) {
        currentObject.reset();
    }
    return currentObject;
}

TWidget::ChildRef TWidget::FindChild(const Name& key) {
    const auto parts = String::split(key, keySep());
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
    if (currentObject.get() == this) {
        currentObject.reset();
    }
    return currentObject;
}

std::list<TWidget::ConstChildRef>
TWidget::FindChildren(const Name& name, bool recursievly) const
{
    std::list<ConstChildRef> result;

    if (children.count(name) != 0) {
        result.emplace_back(children.at(name));
    }

    if (recursievly == true) {
        for(const auto& currentObject : children) {
            auto currentObjectChildren =
                currentObject.second->FindChildren(name, true);

            result.insert(result.end(),
                currentObjectChildren.begin(),
                currentObjectChildren.end()
            );
        }
    }

    return result;
}

std::list<TWidget::ChildRef>
TWidget::FindChildren(const Name& name, bool recursievly)
{
    std::list<ChildRef> result;

    if (children.count(name) != 0) {
        result.emplace_back(children.at(name));
    }

    if (recursievly == true) {
        for(auto& currentObject : children) {
            auto currentObjectChildren =
                currentObject.second->FindChildren(name, true);

            result.insert(result.end(),
                currentObjectChildren.begin(),
                currentObjectChildren.end()
            );
        }
    }

    return result;
}

const TSize& TWidget::GetOwnSize() const {
    return size;
}

void TWidget::SetSize(const TSize& value) {
    if (size != value) {
        size = value;
        _OnResized();
    }
}

float TWidget::GetWidth() const {
    return size.x + margin.left + margin.right;
}

float TWidget::GetHeight() const {
    return size.y + margin.top + margin.bottom;
}

TSize TWidget::GetSize() const {
    return TSize(GetWidth(), GetHeight());
}


const TCoordinate& TWidget::GetPosition() const {
    return position;
}

TCoordinate TWidget::GetScreenPosition() const {
    const auto currentParent = parent.lock();
    if (currentParent != nullptr) {
        TPadding innerBorder = currentParent->GetInnerBorder();
        return position + currentParent->GetScreenPosition() +
               TCoordinate(innerBorder.left, innerBorder.top);
    } else {
        return position;
    }
}

void TWidget::SetPosition(const TCoordinate& temp) {
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

void TWidget::SetPosition(float x, float y) {
    SetPosition(TCoordinate(x, y));
}


const TPadding& TWidget::GetMargin() const {
    return margin;
}

void TWidget::SetMargin(const TPadding& value) {
    if (margin != value) {
        margin = value;
        _checkBorders();
        _OnPositionChanged();
    }
}


void TWidget::Update() {
    if (IsVisible() == false) {
        return;
    }
    _update();
    _updateChildren();
}

void TWidget::Draw(TRenderTarget& target) {
    if (IsVisible() == false) {
        return;
    }
    _draw(target);
    _drawChildren(target);
}


bool TWidget::HasSignal(const Signal& signal) const {
    return eventSystem.HasSignal(signal.GetID());
}
bool TWidget::HasSignal(const SignalID& signal) const {
    return eventSystem.HasSignal(signal);
}

bool TWidget::HasSlot(const Slot& slot) const {
    return eventSystem.HasSlot(slot.GetID());
}

bool TWidget::HasSlot(const SlotID& slot) const {
    return eventSystem.HasSlot(slot);
}

const TWidget::Signal& TWidget::GetSignal(const SignalID& name) const {
    return eventSystem.GetSignal(name);
}
TWidget::Signal& TWidget::GetSignal(const SignalID& name) {
    return eventSystem.GetSignal(name);
}

const TWidget::Slot& TWidget::GetSlot(const SlotID& name) const {
    return eventSystem.GetSlot(name);
}

TWidget::Slot& TWidget::GetSlot(const SlotID& name) {
    return eventSystem.GetSlot(name);
}

void TWidget::RegisterSignal(TWidgetSignal&& signal) {
    eventSystem.AddSignal(std::move(signal));
}

void TWidget::RegisterSignal(const TWidgetSignal& signal) {
    eventSystem.AddSignal(signal);
}

void TWidget::RegisterSlot(const TWidgetSlot& slot) {
    eventSystem.AddSlot(slot);
}

void TWidget::RegisterSlot(TWidgetSlot&& slot) {
    eventSystem.AddSlot(std::move(slot));
}

const list<TWidget::Signal>& TWidget::_basicSignals() {
    static const std::list<TWidget::Signal> _basicSignals_cache = [] {
        std::list<TWidget::Signal> cache;
        for (const auto& signalID : DefaultSignalID::enumerate()) {
            cache.emplace_back(signalID);
        }
        return cache;
    } ();
    return _basicSignals_cache;
}

std::list<TWidget::Signal> TWidget::_enumSignals() const {
    return _basicSignals();
}

std::list<TWidget::Slot> TWidget::_enumSlots() const {
    return std::list<Slot>();
}


void TWidget::Connect(const TWidgetWeakRef& signalOwnerRef,
    Signal& signal, const TWidgetWeakRef& slotOwnerRef, const Slot& slot)
{
    GUI_ASSERT(signalOwnerRef.expired() == false, "Signal owner is not specified.")
    GUI_ASSERT(slotOwnerRef.expired() == false, "Slot owner is not specified.")

    const auto signalOwner = signalOwnerRef.lock();
    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    const auto slotOwner = slotOwnerRef.lock();
    GUI_ASSERT(slotOwner->HasSlot(slot) == true,
        "Object '" + slotOwner->GetName() + "' does not have this slot.")

    signal.AddListener(slot);
}

void TWidget::Disconnect(const TWidgetWeakRef& signalOwnerRef,
    Signal& signal, const TWidgetWeakRef& slotOwnerRef, const Slot& slot)
{
    GUI_ASSERT(signalOwnerRef.expired() == false, "Signal owner is not specified.")
    GUI_ASSERT(slotOwnerRef.expired() == false, "Slot owner is not specified.")

    const auto signalOwner = signalOwnerRef.lock();
    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    const auto slotOwner = slotOwnerRef.lock();
    GUI_ASSERT(slotOwner->HasSlot(slot) == true,
        "Object '" + slotOwner->GetName() + "' does not have this slot.")

    signal.RemoveListener(slot);
}

void TWidget::Connect(const TWidgetWeakRef& signalOwnerRef,
    Signal& signal, const Slot& slot)
{
    GUI_ASSERT(signalOwnerRef.expired() == false, "Signal owner is not specified.")

    const auto signalOwner = signalOwnerRef.lock();
    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    signal.AddListener(slot);
}

void TWidget::Disconnect(const TWidgetWeakRef& signalOwnerRef,
    Signal& signal, const Slot& slot)
{
    GUI_ASSERT(signalOwnerRef.expired() == false, "Signal onwer is not specified.")

    const auto signalOwner = signalOwnerRef.lock();
    GUI_ASSERT(signalOwner->HasSignal(signal) == true,
        "Object '" + signalOwner->GetName() + "' does not send this signal.")

    signal.RemoveListener(slot);
}


END_GUI
