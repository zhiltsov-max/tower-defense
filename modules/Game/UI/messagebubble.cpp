#include "messagebubble.h"

BEGIN_GAME_GUI

TMessageBubble::TMessageBubble(const TMessageBubbleSource &source) :
    parent_type(source)
{}

void TMessageBubble::Initialize(const TMessageBubbleSource &source) {
    parent_type::Initialize(source);

    source.buttonsSource.name = CLOSE_BUTTON_NAME;
    source.buttonsSource.enabled = true;
    source.buttonsSource.text = "x";
    auto closeButton = std::make_shared< ::GUI::TPushButton >(source.buttonsSource);
    AddChild(closeButton);
    Connect(closeButton, closeButton->GetSignal(DefaultSignalName::MouseClick), shared_from_this(), GetSlot(SLOT_NAME_CloseButtonClicked));
}

std::list<TWidget::Slot> TMessageBubble::_enumSlots() const {
    auto slots = parent_type::_enumSlots();

    slots.push_back(std::make_shared< ::GUI::TWidgetSlot >(this, SLOT_NAME_CloseButtonClicked, slot_CloseButtonClicked));

    return slots;
}

void TMessageBubble::slot_CloseButtonClicked(TWidget *self_, void* args) {
    TMessageBubble* self = dynamic_cast<TMessageBubble>(self_);
    if (self != nullptr) {
        ::GUI::throw_("Slot owner is not an instance of TMessageBubble.", "TMessageBubble::slot_CloseButtonClicked");

    self->Hide();

    UNUSED(args)
}

END_GAME_GUI
