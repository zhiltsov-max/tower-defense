#ifndef OKDIALOG_H
#define OKDIALOG_H

#include "messagebox.h"



BEGIN_GUI


struct TOkDialogSource : TMessageBoxSource
{ /*none*/ };

class TOkDialog : public TMessageBox
{
public:
    static const char* SLOT_NAME_OkButtonClicked;

    TOkDialog(const TOkDialogSource& source);
    TOkDialog(const TOkDialog& other) = delete;
    TOkDialog& operator=(const TOkDialog& other) = delete;
    ~TOkDialog() = default;

    virtual void Initialize(const TOkDialogSource& source);

    const TPushButton& GetOkButton() const;

    virtual Style GetStyle() const override;

private:
    using parent_type = TMessageBox;

protected:
    /*
        Returns a list of slots that have to be created.
    */
    virtual std::list<Slot> _enumSlots() const override;

    static void slot_OkButtonClicked(TWidget* widget, const void* args);

    TPushButton& GetOkButton();
};


END_GUI

#endif // OKDIALOG_H
