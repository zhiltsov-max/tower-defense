#ifndef MESSAGEBUBBLE_H
#define MESSAGEBUBBLE_H

#include "../GUI/messagebox.h"
#include "game_gui_main.h"

BEGIN_GAME_GUI

struct TMessageBubbleSource : ::GUI::TMessageBoxSource { /*none*/ };

class TMessageBubble : public ::GUI::TMessageBox
{
public:
    TMessageBubble(const TMessageBubbleSource& source);
    void Initialize(const TMessageBubbleSource& source);
private:
    typedef ::GUI::TMessageBox parent_type;

    static const string CLOSE_BUTTON_NAME = "Close";
    static const ::GUI::SignalID SLOT_NAME_CloseButtonClicked = "CloseButtonClicked";
protected:
    virtual std::list<Slot> _enumSlots() const override;

    static void slot_CloseButtonClicked(TWidget* self_, void* args);
};

END_GAME_GUI

#endif // MESSAGEBUBBLE_H
