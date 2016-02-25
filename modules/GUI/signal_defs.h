#ifndef SIGNAL_DEFS_H
#define SIGNAL_DEFS_H

#include "gui_core.h"
#include "signal.h"

BEGIN_GUI

class DefaultSignalID
{
public:
    DefaultSignalID() = delete;

    static SignalID ObjectVisibilityChanged;
    static SignalID ObjectShown;
    static SignalID ObjectHidden;

    static SignalID ObjectTextChanged;
    static SignalID ObjectPositionChanged;
    static SignalID ObjectSizeChanged;

    static SignalID ObjectEnabled;
    static SignalID ObjectDisabled;

    static SignalID MouseEntered;
    static SignalID MouseLeave;
    static SignalID MouseClick;
    static SignalID MouseDown;
    static SignalID MouseUp;

    static std::vector<SignalID> enumerate() {
        return {
           ObjectVisibilityChanged,
           ObjectShown,
           ObjectHidden,

           /*ObjectTextChanged*/
           ObjectPositionChanged,
           ObjectSizeChanged,

           MouseEntered,
           MouseLeave,
           MouseClick,
           MouseDown,
           MouseUp
         };
    }
};

END_GUI

#endif // SIGNAL_DEFS_H
