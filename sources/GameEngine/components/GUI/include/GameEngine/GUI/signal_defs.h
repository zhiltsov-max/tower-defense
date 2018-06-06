#ifndef SIGNAL_DEFS_H
#define SIGNAL_DEFS_H

#include "gui_core.h"
#include "widget_signal.h"

BEGIN_GUI

class DefaultSignalID
{
public:
    DefaultSignalID() = delete;

    static const SignalID ObjectVisibilityChanged;
    static const SignalID ObjectShown;
    static const SignalID ObjectHidden;

    static const SignalID ObjectTextChanged;
    static const SignalID ObjectPositionChanged;
    static const SignalID ObjectSizeChanged;
    static const SignalID ObjectParentChanged;

    static const SignalID ObjectEnabled;
    static const SignalID ObjectDisabled;

    static const SignalID MouseEntered;
    static const SignalID MouseLeave;
    static const SignalID MouseClick;
    static const SignalID MouseButtonDown;
    static const SignalID MouseButtonUp;
    static const SignalID MouseMoved;


    static const std::vector<SignalID>& enumerate();
};

END_GUI

#endif // SIGNAL_DEFS_H
