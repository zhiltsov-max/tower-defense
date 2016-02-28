#include "researches_tree_item_view.h"
#include "Application/application.h"
#include "Game/Player/player_progress.h"



namespace TD {


const TColorModifier TResearchesTreeItemView::COLOR_MODIFIER_ENABLED  { 1.0, 1.0, 1.0 };
const TColorModifier TResearchesTreeItemView::COLOR_MODIFIER_DISABLED { 0.7, 0.7, 0.7 };

const SignalID TResearchesTreeItemView::SIGNAL_ITEM_RESEARCHED = "_ir";

const SignalID TResearchesTreeItemView::SLOT_IMAGE_BOX_CLICKED = "_ibc";
const SignalID TResearchesTreeItemView::SLOT_PREV_ITEM_RESEARCHED = "_pir";
const SignalID TResearchesTreeItemView::SLOT_TRY_RESEARCH = "_tr";


TResearchesTreeItemView::TResearchesTreeItemView(const TResearchesTreeItemSource& source) :
    parent_type(source),
    m_state(State::Disabled),
    m_research(source.research),
    e_controller(source.controller),
    e_progress(source.progress)
{}

void TResearchesTreeItemView::Initialize(const TResearchesTreeItemSource& source) {
    source.button.text = std::to_wstring(_getResearch());
    auto button = std::make_shared<TPushButton>(source.button);
    AddChild(button);
    Connect(button, button->GetSignal(DefaultSignalID::MouseClick), shared_from_this(), GetSlot(SLOT_TRY_RESEARCH));

    auto imageBox = std::make_shared<TImageBox>(source.imageBox);
    Connect(imageBox, imageBox->GetSignal(DefaultSignalID::MouseClick), shared_from_this(), GetSlot(SLOT_IMAGE_BOX_CLICKED));

    /*TO DO: extract to creation code*/
    auto prev = _getPreviousItem();
    Connect(prev, prev->GetSignal(SIGNAL_ITEM_RESEARCHED), shared_from_this(), GetSlot(SLOT_PREV_ITEM_RESEARCHED));
}

list<TWidget::Signal> TResearchesTreeItemView::_enumSignals() const {
   auto signals = std::move(parent_type::_enumSignals());

   signals.emplace_back(DefaultSignalID::ObjectEnabled);
   signals.emplace_back(DefaultSignalID::ObjectDisabled);
   signals.emplace_back(SIGNAL_ITEM_RESEARCHED);

   return signals;
}

list<TWidget::Slot> TResearchesTreeItemView::_enumSlots() const {
    list<Slot> slots = std::move(parent_type::_enumSlots());

    slots.push_back(std::make_shared<TWidgetSlot>(this, SLOT_PREV_ITEM_RESEARCHED, slot_ItemResearched));
    slots.push_back(std::make_shared<TWidgetSlot>(this, SLOT_IMAGE_BOX_CLICKED, slot_ImageBoxClicked));
    slots.push_back(std::make_shared<TWidgetSlot>(this, SLOT_TRY_RESEARCH, slot_TryResearch));

    return slots;
}

void TResearchesTreeItemView::_draw(TRenderTarget& target) {
    if (needsRedraw == true) {
        TRenderTarget& localTarget = renderImage.getRenderTarget();
        localTarget.clear();
        _drawConnections(localTarget);

        renderImage.createDrawingObject();
        needsRedraw = false;
    }

    const auto position = std::move(GetScreenPosition());
    renderImage.getDrawingObject().setPosition(position);
    target.draw(renderImage.getDrawingObject());

#if defined(_DEBUG_)
    if (Debug::show_frames() == true) {
        sf::RectangleShape boundingRect(size);
        boundingRect.setFillColor(sf::Color::Transparent);
        boundingRect.setOutlineColor(sf::Color(0, 255 - 55 * mouseOver, 0, 128));
        boundingRect.setOutlineThickness(2.f);
        boundingRect.setPosition(position);
        target.draw(boundingRect);

        sf::Text rectText = TFont().createText(String::toWide(name));
        rectText.setPosition(position);
        target.draw(rectText);
    }
#endif
}

void TResearchesTreeItemView::_drawConnections(TRenderTarget& target) {
    const auto prevResearches = std::move(_getPreviousResearches());
    if (prevResearches.empty() == true) {
        return;
    }

    sf::Vertex line[2] = {
        sf::Vertex(std::move(GetScreenPosition()) + std::move(GetSize()) * 0.5f),
        sf::Vertex()
    };

    for (const auto& entry : prevResearches) {
        const auto research = std::move(entry.lock());

        if (research->_getResearch()->IsResearched() == true) {
            line[0].color = COLOR_LINE_BRIGHT;
            line[1].color = COLOR_LINE_BRIGHT;
        } else {
            line[0].color = COLOR_LINE_DARK;
            line[1].color = COLOR_LINE_DARK;
        }
        line[1].position = std::move(research->GetScreenPosition()) + std::move(research->GetSize()) * 0.5f;

        target.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

/*TO DO:*/
void TResearchesTreeItemView::_OnDisabled() {
    //_getImageBox().lock()->SetColorModifier(COLOR_MODIFIER_DISABLED); //?
    _getButton().lock()->Disable();
}

void TResearchesTreeItemView::_OnEnabled() {
    //_getImageBox().lock()->SetColorModifier(COLOR_MODIFIER_ENABLED); //?
    _getButton().lock()->Enable();
}

void TResearchesTreeItemView::_OnResearched() {
    const auto credits = obj_->_getProgress().GetCredits();
    const auto cost = obj->_getResearch().GetCost();
    obj->_getResearch().SetResearched(true);
    _getProgress()->SetCredits(credits - cost);

    auto button = _getButton().lock();
    if (button != nullptr) {
        button->Remove();
    }
}

bool TResearchesTreeItemView::_hasEnoughCredits() const {
    return _getResearch().GetCost() <= _getProgress().GetCredits();
}

std::weak_ptr<TAbstractButton> TResearchesTreeItemView::_getButton() {
    return FindChild<TAbstractButton>("Button");
}

std::weak_ptr<TImageBox> TResearchesTreeItemView::_getImageBox() {
    return FindChild<TImageBox>("ImageBox");
}

std::weak_ptr<TResearchesTree> TResearchesTreeItemView::_getTree() {
    return std::dynamic_pointer_cast<TResearchesTree>(parent);
}

const TResearches& TResearchesTreeItemView::_getController() const {
    return *e_controller;
}

const TResearch& TResearchesTreeItemView::_getResearch() const {
    return *m_research;
}

TResearch& TResearchesTreeItemView::_getResearch() {
    return *m_research;
}

list<std::weak_ptr<TResearchesTreeItemView> > TResearchesTreeItemView::_getPrevResearches() const {
    return _getController().GetTree().GetPrevResearches(_getResearch().GetID());
}

std::weak_ptr<const TResearchesTree> TResearchesTreeItemView::_getTree() const {
    return std::dynamic_pointer_cast<TResearchesTree>(parent);
}

std::weak_ptr<const TImageBox> TResearchesTreeItemView::_getImageBox() const {
    return FindChild<TImageBox>("ImageBox");
}

std::weak_ptr<const TAbstractButton> TResearchesTreeItemView::_getButton() const {
    return FindChild<TAbstractButton>("Button");
}

void TResearchesTreeItemView::slot_PrevItemResearched(TWidget* obj_, void* args) {
    auto obj = dynamic_cast<TUpgradesTreeItem*>(obj_);
    if (obj == nullptr) {
        throw_("Slot invoked for an object of wrong type.", "TUpgradesTreeItem::slot_ItemResearched");
    }
    obj->SetState(State::Enabled);

    UNUSED(args)
}

void TResearchesTreeItemView::slot_TryResearch(TWidget* obj_, void* args) {
    auto obj = dynamic_cast<TResearchesTreeItemView*>(obj_);
    if (obj == nullptr) {
        throw_("Slot invoked for an object of wrong type.", "TUpgrdesTreeItem::slot_TryResearch");
    }

    if (obj->GetState() == State::CanResearch) {
        obj->SetState(State::Researched);
    }

    UNUSED(args)
}

void TResearchesTreeItemView::slot_ImageBoxClicked(TWidget* obj_, void* args) {
    auto obj = dynamic_cast<TResearchesTreeItemView*>(obj_);
    if (obj != nullptr) {
        throw_("Slot invoked for an object of wrong type.", "TUpgradesTreeItem::slot_ImageBoxClicked");
    }

    obj->_OnClick();

    UNUSED(args)
}

const State& TResearchesTreeItemView::GetState() const {
    return m_state;
}

void TResearchesTreeItemView::SetState(const State& value) {
    if (m_state != value) {
        switch (value) {
        case State::Disabled:
            _OnDisabled();
            GetSignal(DefaultSignalID::ObjectDisabled).Send();
            break;

        case State::CanResearch:
            _OnEnabled();
            GetSignal(DefaultSignalID::ObjectEnabled).Send();
            break;

        case State::Researched:
            _OnResearched();
            GetSignal(SIGNAL_ITEM_RESEARCHED).Send();
            GetSignal(DefaultSignalID::ObjectDisabled).Send();
            break;

        case UpgradesTreeItemState.CanNotResearch:
            _OnDisabled();
            GetSignal(DefaultSignalID::ObjectDisabled).Send();

        case State::Enabled:
            _OnEnabled();
            GetSignal(DefaultSignalID::ObjectEnabled).Send();
            break;

        default: /* none */;
        }

        m_state = value;
    }
}

void TResearchesTreeItemView::SetControllerInstance(const TResearcesControllerInstance& value) {
    e_controller = value;
}

void TResearchesTreeItemView::SetProgressInstance(const TProgressInstance& value) {
    e_progress = value;
}


} // namespace TD
