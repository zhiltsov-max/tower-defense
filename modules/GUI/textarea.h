#ifndef TEXTAREA_H
#define TEXTAREA_H

#include "abstracttextarea.h"

BEGIN_GUI

typedef TAbstractTextArea TTextArea;

/*
class TTextArea : public TAbstractTextArea
{
public:
    TTextArea(const TextString& text, const TCoordinate& position, TMenuObject* parent) :
        parent_t(text, position, parent)
    {}
};
*/
END_GUI

#endif // TEXTAREA_H
