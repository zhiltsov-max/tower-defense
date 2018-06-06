#ifndef LEVEL_CLOCK_H
#define LEVEL_CLOCK_H

#include "GameEngine/Utility/core.h"
#include "GameEngine/engine_core.h"


namespace TD {

/*
Game time controller.
*/
class TLevelClock
{
public:
    using Time = GE::TTime;

    static constexpr const Time tick() { return Time(0.01); }

    enum class Rate : uint {
        _min = 0,

        Pause = 0,
        First = 1,
        Second = 2,
        Four = 4,
        Eigth = 8,

        _max = 10
    };

    TLevelClock(const Rate& rate = Rate::_min);

    void Update();

    void SetRate(const Rate& value);
    const Rate& GetRate() const;

    const Time& Get() const;

private:
    Time clock;
    Rate rate;
};

} // namespace TD

#endif // LEVEL_CLOCK_H
