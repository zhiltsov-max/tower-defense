#include "level_clock.h"


namespace TD {


TLevelClock::TLevelClock(const Rate& rate) :
    rate(rate),
    clock(0)
{}

void TLevelClock::Update() {
    clock += tick();
}

void TLevelClock::SetRate(const Rate& value) {
    rate = value;
}

const TLevelClock::Rate& TLevelClock::GetRate() const {
    return rate;
}

const TLevelClock::Time& TLevelClock::Get() const {
    return clock;
}

} // namespace TD
