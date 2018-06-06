#if !defined(SFML)
    #error "SFML have to be defined"
#endif //SFML

#include "GameEngine/Utility/core.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
    window.setVerticalSyncEnabled(true);
    window.setActive();

    sf::Clock timer;

    TImage img1;
    if (img1.loadFromFile("res/image1.jpg") == false) { std::cerr << "File image1 not found."; }
    TTexture tex1;
    tex1.loadFromImage(img1);
    TSprite spr1(tex1);

    TFont font;
    if (font.loadFromFile("res/calibri.ttf") == false) { std::cerr << "File calibri not found."; }

    // Create a new render-texture
    sf::RenderTexture texture;
    if (texture.create(100, 100) == false) {
        return -1;
    }

    sf::Sprite spr2;
    spr2.setPosition(400.f, 10.f);
    spr2.setOrigin(0.f, 100.f);
    spr2.setScale(1.f, -1.f);

    unsigned int frames = 0;
    unsigned int fps = 0;
    unsigned int prevTime = 0;

    while (window.isOpen()) {
        sf::Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == sf::Event::KeyPressed) {
                if (evt.key.code == sf::Keyboard::Escape) {
                    return EXIT_SUCCESS;
                }
            }
        }

        const auto time = timer.getElapsedTime();
        const auto dtime = time.asMilliseconds() - prevTime;
        if (dtime >= 1000) {
            fps = frames;
            frames = 0;
            prevTime = time.asMilliseconds();
        }

        spr1.setPosition( 50.d * cos(time.asMilliseconds() / 100.d), 50.d * sin(time.asMilliseconds() / 100.d) );

        texture.clear();
        TText text(std::to_string(fps), font);
        texture.draw(text);
        spr2.setTexture(texture.getTexture());

        window.clear();
        window.draw(spr1);
        window.draw(spr2);
        window.display();

        ++frames;
    }

    return 0;
}
