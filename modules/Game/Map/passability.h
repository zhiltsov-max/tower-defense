#ifndef PASSABILITY_H
#define PASSABILITY_H

enum class Altitude {
    _min = 0,

    Underground = 0,
    Water,
    Ground,
    Air,

    _count
};

enum class PassWeight : ushort {
    _min = 0,

    CanNotPass = 0,
    Min = 2,
    Low = 5,
    Medium = 10,
    Hard = 20,
    Max = 30,

    _max = Max
};

#endif // PASSABILITY_H
