#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include "../GUI/transparentwindow.h"
#include "../GUI/pushbutton.h"
#include "../GUI/richtextbox.h"
#include "game_gui_main.h"

BEGIN_GAME_GUI

struct TPopUpWindowSource : ::GUI::TTransparentWindowSource {
    TPushButtonSource upgradeButtonSource;
    TPushButtonSource sellButtonSource;
    TRichTextBoxSource textBoxSource;
};

class TPopUpWindow : public ::GUI::TTransparentWindow
{
public:
    TPopUpWindow(const TPopUpWindowSource& source);
    void Initialize(const TPopUpWindowSource& source);

private:
    typedef ::GUI::TTransparentWindow parent_type;

    static const wchar_t* MESSAGE_MULTIPLE_SELECTION;

    std::vector<TextString> _parseTurretDescription(const TTurret& turret);

protected:
    virtual void _update() override;
};

END_GAME_GUI

#endif // POPUPWINDOW_H
