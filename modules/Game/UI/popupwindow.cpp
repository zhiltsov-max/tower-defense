#include "popupwindow.h"

BEGIN_GAME_GUI

static const wchar_t* TPopUpWindow::MESSAGE_MULTIPLE_SELECTION = TEXT("Multiple selection.");

TPopUpWindow::TPopUpWindow(const TPopUpWindowSource &source_) :
    parent_type(source_)
{}

void TPopUpWindow::Initialize(const TPopUpWindowSource& source_) {
    TPopUpWindowSource source = source_;
    source.upgradeButtonSource.name = "Upgrade";
    AddChild(std::make_shared< ::GUI::TPushButton >(source.upgradeButtonSource));

    source.sellButtonSource.name = "Sell";
    AddChild(std::make_shared< ::GUI::TPushButton >(source.sellButtonSource));

    source.textBoxSource.name = "Text";
    AddChild( std::make_shared< ::GUI::TRichTextBox >(source.textBoxSource));
}

void TPopUpWindow::_update() {
    auto buildings = TBuildingController::GetSelectedBuildings();

    auto turret = TTurret(buildings.first());
    if ((buildings.empty() == true) || (turret == nullptr)) {
        colorModifier.a = 0u;
        return;
    }

    auto textBox = FindChild< ::GUI::TAbstractTextBox >("Text");
    if (buildings.size() == 1) {
        auto textStrings = _parseTurretDescription(turret);
        TextString text;
        for(const auto& str : textStrings) {
            text.append(std::endl + str);
        }
        textBox->SetText(text);
        FindChild("Upgrade")->Show();
        FindChild("Sell")->Show();
        colorModifier.a = (uchar) maxOpacity * 255.0;
    } else {
        textBox->SetText(MESSAGE_MULTIPLE_SELECTION);
        FindChild("Upgrade")->Hide();
        FindChild("Sell")->Show();
    }
    textBox->Show();
}

END_GAME_GUI
