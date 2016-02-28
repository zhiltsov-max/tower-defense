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

    static const SignalID ObjectEnabled;
    static const SignalID ObjectDisabled;

    static const SignalID MouseEntered;
    static const SignalID MouseLeave;
    static const SignalID MouseClick;
    static const SignalID MouseDown;
    static const SignalID MouseUp;

    static const std::vector<SignalID>& enumerate();

private:
    static const std::vector<SignalID> _enumeration;
};

END_GUI

#endif // SIGNAL_DEFS_H
