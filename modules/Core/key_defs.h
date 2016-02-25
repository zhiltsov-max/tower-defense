#ifndef CORE_IO_KEY_DEFS_H
#define CORE_IO_KEY_DEFS_H

#include <cstring>
#include <queue>


namespace IO {

enum class EventId : unsigned char {
    undefined = 0,
    KeyUp, KeyDown,                     /* Event value = key code */
    MouseUp, MouseDown,                 /* Event value = key code */
    MouseXmove, MouseYmove, MouseZmove, /* Event value = distance (px.) */
    _count
};

enum class MouseKey : unsigned char {
    Left = 0, Right, Middle,
    _count
};

enum class KeyState : unsigned char {
    Released = 0x0,
    Pressed  = 0x1,
    Hit      = 0x2
};

enum class KeyboardKey : short {
    Key_ESCAPE        = 0x01,
    Key_1             = 0x02,
    Key_2             = 0x03,
    Key_3             = 0x04,
    Key_4             = 0x05,
    Key_5             = 0x06,
    Key_6             = 0x07,
    Key_7             = 0x08,
    Key_8             = 0x09,
    Key_9             = 0x0A,
    Key_0             = 0x0B,
    Key_MINUS         = 0x0C,  /* - on main keyboard */
    Key_EQUALS        = 0x0D,
    Key_BACK          = 0x0E,  /* backspace */
    Key_TAB           = 0x0F,
    Key_Q             = 0x10,
    Key_W             = 0x11,
    Key_E             = 0x12,
    Key_R             = 0x13,
    Key_T             = 0x14,
    Key_Y             = 0x15,
    Key_U             = 0x16,
    Key_I             = 0x17,
    Key_O             = 0x18,
    Key_P             = 0x19,
    Key_LBRACKET      = 0x1A,
    Key_RBRACKET      = 0x1B,
    Key_RETURN        = 0x1C,  /* Enter on main keyboard */
    Key_LCONTROL      = 0x1D,
    Key_A             = 0x1E,
    Key_S             = 0x1F,
    Key_D             = 0x20,
    Key_F             = 0x21,
    Key_G             = 0x22,
    Key_H             = 0x23,
    Key_J             = 0x24,
    Key_K             = 0x25,
    Key_L             = 0x26,
    Key_SEMICOLON     = 0x27,
    Key_APOSTROPHE    = 0x28,
    Key_GRAVE         = 0x29,  /* accent grave */
    Key_LSHIFT        = 0x2A,
    Key_BACKSLASH     = 0x2B,
    Key_Z             = 0x2C,
    Key_X             = 0x2D,
    Key_C             = 0x2E,
    Key_V             = 0x2F,
    Key_B             = 0x30,
    Key_N             = 0x31,
    Key_M             = 0x32,
    Key_COMMA         = 0x33,
    Key_PERIOD        = 0x34,  /* . on main keyboard */
    Key_SLASH         = 0x35,  /* / on main keyboard */
    Key_RSHIFT        = 0x36,
    Key_MULTIPLY      = 0x37,  /* * on numeric keypad */
    Key_LMENU         = 0x38,  /* left Alt */
    Key_SPACE         = 0x39,
    Key_CAPITAL       = 0x3A,
    Key_F1            = 0x3B,
    Key_F2            = 0x3C,
    Key_F3            = 0x3D,
    Key_F4            = 0x3E,
    Key_F5            = 0x3F,
    Key_F6            = 0x40,
    Key_F7            = 0x41,
    Key_F8            = 0x42,
    Key_F9            = 0x43,
    Key_F10           = 0x44,
    Key_NUMLOCK       = 0x45,
    Key_SCROLL        = 0x46,  /* Scroll Lock */
    Key_NUMPAD7       = 0x47,
    Key_NUMPAD8       = 0x48,
    Key_NUMPAD9       = 0x49,
    Key_SUBTRACT      = 0x4A,  /* - on numeric keypad */
    Key_NUMPAD4       = 0x4B,
    Key_NUMPAD5       = 0x4C,
    Key_NUMPAD6       = 0x4D,
    Key_ADD           = 0x4E,  /* + on numeric keypad */
    Key_NUMPAD1       = 0x4F,
    Key_NUMPAD2       = 0x50,
    Key_NUMPAD3       = 0x51,
    Key_NUMPAD0       = 0x52,
    Key_DECIMAL       = 0x53,  /* . on numeric keypad */
    Key_OEM_102       = 0x56,  /* < > | on UK/Germany keyboards */
    Key_F11           = 0x57,
    Key_F12           = 0x58,

    Key_KANA          = 0x70,    /* (Japanese keyboard)            */
    Key_ABNT_C1       = 0x73,    /* / ? on Portugese (Brazilian) keyboards */
    Key_CONVERT       = 0x79,    /* (Japanese keyboard)            */
    Key_NOCONVERT     = 0x7B,    /* (Japanese keyboard)            */
    Key_YEN           = 0x7D,    /* (Japanese keyboard)            */
    Key_ABNT_C2       = 0x7E,    /* Numpad . on Portugese (Brazilian) keyboards */
    Key_NUMPADEQUALS  = 0x8D,    /* = on numeric keypad (NEC PC98) */
    Key_CIRCUMFLEX    = 0x90,    /* (Japanese keyboard)            */
    Key_AT            = 0x91,    /*                     (NEC PC98) */
    Key_COLON         = 0x92,    /*                     (NEC PC98) */
    Key_UNDERLINE     = 0x93,    /*                     (NEC PC98) */
    Key_KANJI         = 0x94,    /* (Japanese keyboard)            */
    Key_STOP          = 0x95,    /*                     (NEC PC98) */
    Key_AX            = 0x96,    /*                     (Japan AX) */
    Key_UNLABELED     = 0x97,    /*                        (J3100) */
    Key_NEXTTRACK     = 0x99,    /* Next Track */
    Key_NUMPADENTER   = 0x9C,    /* Enter on numeric keypad */
    Key_RCONTROL      = 0x9D,
    Key_MUTE	      = 0xA0,    /* Mute */
    Key_CALCULATOR    = 0xA1,    /* Calculator */
    Key_PLAYPAUSE     = 0xA2,    /* Play / Pause */
    Key_MEDIASTOP     = 0xA4,    /* Media Stop */
    Key_VOLUMEDOWN    = 0xAE,    /* Volume - */
    Key_VOLUMEUP      = 0xB0,    /* Volume + */
    Key_WEBHOME       = 0xB2,    /* Web home */
    Key_NUMPADCOMMA   = 0xB3,    /* , on numeric keypad (NEC PC98) */
    Key_DIVIDE        = 0xB5,    /* / on numeric keypad */
    Key_SYSRQ         = 0xB7,
    Key_RMENU         = 0xB8,     /* right Alt */
    Key_PAUSE         = 0xC5,    /* Pause */
    Key_HOME          = 0xC7,    /* Home on arrow keypad */
    Key_UP            = 0xC8,    /* UpArrow on arrow keypad */
    Key_PRIOR         = 0xC9,    /* PgUp on arrow keypad */
    Key_LEFT          = 0xCB,    /* LeftArrow on arrow keypad */
    Key_RIGHT         = 0xCD,    /* RightArrow on arrow keypad */
    Key_END           = 0xCF,    /* End on arrow keypad */
    Key_DOWN          = 0xD0,    /* DownArrow on arrow keypad */
    Key_NEXT          = 0xD1,    /* PgDn on arrow keypad */
    Key_INSERT        = 0xD2,    /* Insert on arrow keypad */
    Key_DELETE        = 0xD3,    /* Delete on arrow keypad */
    Key_LWIN          = 0xDB,    /* Left Windows key */
    Key_RWIN          = 0xDC,    /* Right Windows key */
    Key_APPS          = 0xDD,    /* AppMenu key */
    Key_POWER         = 0xDE,
    Key_SLEEP         = 0xDF,
    Key_WAKE          = 0xE3,    /* System Wake */
    Key_WEBSEARCH     = 0xE5,    /* Web Search */
    Key_WEBFAVORITES  = 0xE6,    /* Web Favorites */
    Key_WEBREFRESH    = 0xE7,    /* Web Refresh */
    Key_WEBSTOP       = 0xE8,    /* Web Stop */
    Key_WEBFORWARD    = 0xE9,    /* Web Forward */
    Key_WEBBACK       = 0xEA,    /* Web Back */
    Key_MYCOMPUTER    = 0xEB,    /* My Computer */
    Key_MAIL          = 0xEC,    /* Mail */
    Key_MEDIASELECT   = 0xED,    /* Media Select */

    Key_BACKSPACE     = Key_BACK,            /* backspace */
    Key_NUMPADSTAR    = Key_MULTIPLY,        /* * on numeric keypad */
    Key_LALT          = Key_LMENU,           /* left Alt */
    Key_CAPSLOCK      = Key_CAPITAL,         /* CapsLock */
    Key_NUMPADMINUS   = Key_SUBTRACT,        /* - on numeric keypad */
    Key_NUMPADPLUS    = Key_ADD,             /* + on numeric keypad */
    Key_NUMPADPERIOD  = Key_DECIMAL,         /* . on numeric keypad */
    Key_NUMPADSLASH   = Key_DIVIDE,          /* / on numeric keypad */
    Key_RALT          = Key_RMENU,           /* right Alt */
    Key_UPARROW       = Key_UP,              /* UpArrow on arrow keypad */
    Key_PGUP          = Key_PRIOR,           /* PgUp on arrow keypad */
    Key_LEFTARROW     = Key_LEFT,            /* LeftArrow on arrow keypad */
    Key_RIGHTARROW    = Key_RIGHT,           /* RightArrow on arrow keypad */
    Key_DOWNARROW     = Key_DOWN,            /* DownArrow on arrow keypad */
    Key_PGDN          = Key_NEXT,            /* PgDn on arrow keypad */
    _count = 256
};

struct TMouseDownEvent {
    unsigned char key;
    short x;
    short y;

    TMouseDownEvent(unsigned char key_, short x_, short y_) : key(key_), x(x_), y(y_) {}
};

struct TMouseUpEvent {
    unsigned char key;

    TMouseUpEvent(unsigned char key_) : key(key_) {}
};

struct TKeyDownEvent {
    unsigned char key;

    TKeyDownEvent(unsigned char key_) : key(key_) {}
};

struct TKeyUpEvent {
    unsigned char key;

    TKeyUpEvent(unsigned char key_) : key(key_) {}
};

struct Event {
    EventId id;
    union {
        unsigned char value;
        TMouseDownEvent mouseDown;
        TMouseUpEvent mouseUp;
        TKeyDownEvent keyDown;
        TKeyUpEvent keyUp;
    };

    Event(EventId id_, unsigned char value_) : id(id_), value(value_) {}
};

struct TKeyboardInfo
{
    bool isKeyDown(KeyboardKey key) const {
        return keyState[(unsigned char)key] == KeyState::Pressed;
    }
    bool isKeyHit(KeyboardKey key) {
        if (keyState[(unsigned char)key] == KeyState::Hit) {
            keyState[(unsigned char)key] = KeyState::Pressed;
            return true;
        }
        return false;
    }
    bool isKeyUp(KeyboardKey key) const {
        return keyState[(unsigned char)key] == KeyState::Released;
    }
    void clear() {
        while (events.empty() == false) { events.pop(); }
        memset(keyState, (int)KeyState::Released, sizeof(KeyState) * (int)KeyboardKey::_count);
    }


    KeyState keyState[(short)KeyboardKey::_count];

    typedef std::queue<Event> EventQueue;
    EventQueue events;
    static const int MAX_QUEUE_SIZE = 16;
};

struct TMouseInfo
{
    bool isKeyDown(MouseKey key) const {
        return keyState[(unsigned char)key] == KeyState::Pressed;
    }
    bool isKeyHit(MouseKey key) {
        if (keyState[(unsigned char)key] == KeyState::Hit) {
            keyState[(unsigned char)key] = KeyState::Pressed;
            return true;
        }
        return false;
    }
    bool isKeyUp(MouseKey key) const {
        return keyState[(unsigned char)key] == KeyState::Released;
    }
    int x() const {
        return axis[0];
    }
    int y() const {
        return axis[1];
    }
    int z() const {
        return axis[2];
    }
    int xSpeed() const {
        return speed[0];
    }
    int ySpeed() const {
        return speed[1];
    }
    int zSpeed() const {
        return speed[2];
    }
    void clear() {
        while (events.empty() == false) { events.pop(); }
        memset(axis, 0, sizeof(int) * AXISCOUNT);
        memset(speed, 0, sizeof(int) * AXISCOUNT);
        memset(keyState, (int)KeyState::Released, sizeof(KeyState) * (int)MouseKey::_count);
    }


    static const int AXISCOUNT = 3;

    KeyState keyState[(short)MouseKey::_count];
    int axis[AXISCOUNT] = {0};
    int speed[AXISCOUNT] = {0};

    typedef std::queue<Event> EventQueue;
    EventQueue events;
    static const int MAX_QUEUE_SIZE = 16;
};

} //namepace IO

#endif // __CORE_IO_KEY_DEFS_H__
