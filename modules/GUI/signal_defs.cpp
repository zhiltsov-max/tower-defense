#include "signal_defs.h"

BEGIN_GUI

const SignalID DefaultSignalID::ObjectVisibilityChanged = "vc";
const SignalID DefaultSignalID::ObjectShown = "sh";
const SignalID DefaultSignalID::ObjectHidden = "hid";

const SignalID DefaultSignalID::ObjectTextChanged = "otc";
const SignalID DefaultSignalID::ObjectPositionChanged = "mov";
const SignalID DefaultSignalID::ObjectSizeChanged = "siz";
const SignalID DefaultSignalID::ObjectParentChanged = "opc";

const SignalID DefaultSignalID::ObjectEnabled = "ena";
const SignalID DefaultSignalID::ObjectDisabled = "dis";

const SignalID DefaultSignalID::MouseEntered = "men";
const SignalID DefaultSignalID::MouseLeave = "mou";
const SignalID DefaultSignalID::MouseClick = "mcl";
const SignalID DefaultSignalID::MouseButtonDown = "mdn";
const SignalID DefaultSignalID::MouseButtonUp = "mup";
const SignalID DefaultSignalID::MouseMoved = "mmo";

const std::vector<SignalID>& DefaultSignalID::enumerate() {
    static const std::vector<SignalID> _enumeration {
        ObjectVisibilityChanged,
        ObjectShown,
        ObjectHidden,

        /*ObjectTextChanged*/
        ObjectPositionChanged,
        ObjectSizeChanged,
        ObjectParentChanged,

        MouseEntered,
        MouseLeave,
        MouseClick,
        MouseButtonDown,
        MouseButtonUp,
        MouseMoved
    };
    return _enumeration;
}

END_GUI
