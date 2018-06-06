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
    buttonsSource.textArea.text = TEXT("Ok");
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

void TOkDialog::slot_OkButtonClicked(TWidget* widget, const void* args) {
    TOkDialog* dialog = dynamic_cast<TOkDialog*>(widget);
    ASSERT(dialog != nullptr, "Slot owner is not an instance of TOkDialog.")

    dialog->Hide();
    dialog->parent.lock()->RemoveChild(dialog->GetName());
}

TPushButton& TOkDialog::GetOkButton() {
    return *FindChild<TPushButton>("Ok").lock();
}


END_GUI
