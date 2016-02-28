#include "okdialog.h"



BEGIN_GUI


const char* TOkDialog::SLOT_NAME_OkButtonClicked = "OkButtonClicked";

TOkDialog::TOkDialog(const TOkDialogSource& source) :
    parent_type(source)
{}

void TOkDialog::Initialize(const TOkDialogSource& source) {
    parent_type::Initialize(source);
    TPushButtonSource buttonsSource = source.buttonsSource;
    buttonsSource.name = "Ok";
    buttonsSource.enabled = true;
    buttonsSource.text = TEXT("Ok");
    TWidgetRef okButton(new TPushButton(buttonsSource));

    Connect(okButton, okButton->GetSignal(DefaultSignalID::MouseClick),
        shared_from_this(), GetSlot(SLOT_NAME_OkButtonClicked));
}

std::list<TWidget::Slot> TOkDialog::_enumSlots() const {
    auto slots = parent_type::_enumSlots();

    slots.emplace_back(
        std::const_pointer_cast<TWidget>(shared_from_this()),
        SLOT_NAME_OkButtonClicked,
        slot_OkButtonClicked
    );

    return slots;
}


const TPushButton& TOkDialog::GetOkButton() const {
    return *FindChild<TPushButton>("Ok").lock();
}

TOkDialog::Style TOkDialog::GetStyle() const {
    return Style::OkDialog;
}

void TOkDialog::slot_OkButtonClicked(TWidget* this__, void** args) {
    UNUSED(args)
    TOkDialog* this_ = dynamic_cast<TOkDialog*>(this__);
    ASSERT(this_ != nullptr, "Slot owner is not an instance of TOkDialog.")

    this_->Hide();
    this_->parent.lock()->RemoveChild(this_->GetName());
}

TPushButton& TOkDialog::GetOkButton() {
    return *FindChild<TPushButton>("Ok").lock();
}


END_GUI
