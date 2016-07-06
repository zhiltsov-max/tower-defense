#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "Core/core.h"


namespace TD {

class FPSCounter
{
public:
    static const int DEFAULT_FPS = 60;

    void update();
    double normalized() const;

private:
    using Clock = sf::Clock;
    Clock timer;
    unsigned int frames;
    unsigned int fps;
    unsigned int prevTime;
};

} // namespace TD

#endif // FPSCOUNTER_H
