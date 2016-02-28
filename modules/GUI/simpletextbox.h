#ifndef SIMPLETEXTBOX_H
#define SIMPLETEXTBOX_H

#include "gui_main.h"
#include "abstracttextbox.h"

BEGIN_GUI

struct TSimpleTextBoxSource : TAbstractTextBoxSource
{};

class TSimpleTextBox : public TAbstractTextBox
{
public:
    TSimpleTextBox(const TSimpleTextBoxSource& source);
    TSimpleTextBox(const TSimpleTextBox& other) = delete;
    TSimpleTextBox& operator=(const TSimpleTextBox& other) = delete;
    ~TSimpleTextBox() = default;

    virtual void SetEditable(bool value) override;
private:
    typedef TAbstractTextBox parent_type;
};


END_GUI


#endif // SIMPLETEXTBOX_H
