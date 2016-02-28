#ifndef GAMEINFOWINDOW_H
#define GAMEINFOWINDOW_H

#include "../GUI/window.h"
#include "game_gui_main.h"

BEGIN_GAME_GUI

struct TGameInfoWindowSource : ::GUI::TWindowSource {
    TRichTextBoxSource textBoxSource;
};

class TGameInfoWindow : public TWindow
{
public:
    TGameInfoWindow(const TGameInfoWindowSource& source);
    void Initialize(const TWidgetSource& source);
private:
    typedef ::GUI::TWindow parent_type;

    static const char* DEFAULT_TEXTBOX_NAME;

    std::shared_ptr< ::GUI::TRichTextBox > _getText();
protected:
    virtual void _update() override;
};

END_GAME_GUI

#endif // GAMEINFOWINDOW_H
