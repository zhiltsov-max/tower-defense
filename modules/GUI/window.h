#ifndef WINDOW_H
#define WINDOW_H

#include "abstractwindow.h"

BEGIN_GUI

struct TWindowSource : TAbstractWindowSource
{ /*none*/ };

class TWindow : public TAbstractWindow
{
private:
    typedef TAbstractWindow parent_t;
public:
    TWindow(const TWindowSource& source) :
        parent_t(source)
    {}
    TWindow(const TWindow& other) = delete;
    TWindow& operator=(const TWindow& other) = delete;
    ~TWindow() = default;
};

END_GUI

#endif // WINDOW_H
