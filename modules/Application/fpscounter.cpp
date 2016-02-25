#include "fpscounter.h"

void FPSCounter::update() {
    const auto current_time = timer.getElapsedTime().asMilliseconds();
    if (1000 <= current_time - prevTime) {
        fps = frames;
        frames = 0;
        prevTime = current_time;
    }
    ++frames;
}

double FPSCounter::normalized() const {
    return double(DEFAULT_FPS) / double(fps);
}

#if defined(SFML)
void FPSCounter::draw(Graphics::TRenderTarget& target) {
    sf::Text text(std::to_string(fps), sf::Font(), 20);
    target.draw(text);
}
#endif
