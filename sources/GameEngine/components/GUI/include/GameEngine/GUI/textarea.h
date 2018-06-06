#ifndef TEXT_AREA_H
#define TEXT_AREA_H

#include "abstracttextarea.h"



BEGIN_GUI


struct TTextAreaSource : TAbstractTextAreaSource { /*none*/ };


class TTextArea : public TAbstractTextArea
{
private:
    typedef TAbstractTextArea parent_type;

public:
    TTextArea(const TTextAreaSource& source, const Parent& parent) :
        parent_type(source, parent)
    {}
};


END_GUI

#endif // TEXT_AREA_H
