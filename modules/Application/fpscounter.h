#ifndef FPSCOUNTER_H
#define FPSCOUNTER_H

#include "application.h"



class FPSCounter
{
public:
    static const int DEFAULT_FPS = 60;

    void update();
    double normalized() const;

#if defined(SFML)
    void draw(Graphics::TRenderTarget& target);
#endif

private:
#if defined(SFML)
    sf::Clock timer;
#endif
    unsigned int frames;
    unsigned int fps;
    unsigned int prevTime;
};

#endif // FPSCOUNTER_H
