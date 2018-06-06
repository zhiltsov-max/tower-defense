#include "gameinfowindow.h"

BEGIN_GAME_GUI

static const char* TGameInfoWindow::DEFAULT_TEXTBOX_NAME = "Text";

TGameInfoWindow::TGameInfoWindow(const TGameInfoWindowSource& source) :
    parent_type(source)
{}

void TGameInfoWindow::Initialize(const TWidgetSource& source) {
    source.textBoxSource.name = DEFAULT_TEXTBOX_NAME;
    AddChild(std::make_shared< ::GUI::TRichTextBox >(source.textBoxSource));
}

std::shared_ptr<TRichTextBox> TGameInfoWindow::_getText() {
    return FindChild< ::GUI::TRichTextBox >(DEFAULT_TEXTBOX_NAME);
}

void TGameInfoWindow::_update() {
    TLevel& level = GetGame().GetLevel();

    int stage = level.GetStage().GetNumber();
    TextString info =
            "Level - " + level.GetCode() + ", stage - " + stage + "\n" +
            "Credits: " + level.GetProgress().GetCredits() + "\n" +
            "Health: " + int(level.GetStage().GetCastleHealth()) + "%" + "\n\n"
            "Game speed: " + level.GetGameSpeed() + "x";

    _getText()->SetText(info);
}

END_GAME_GUI
