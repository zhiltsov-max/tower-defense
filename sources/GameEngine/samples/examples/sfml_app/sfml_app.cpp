#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Title");
    window.setVerticalSyncEnabled(true);
    window.setActive();

    sf::Clock timer;

    sf::Image img1;
    if (img1.loadFromFile("resources/image.jpg") == false) { std::cerr << "File not found."; }
    sf::Text tex1;
    tex1.loadFromImage(img1);
    sf::Sprite spr1(tex1);

    sf::Font font;
    if (font.loadFromFile("resources/font.ttf") == false) { std::cerr << "File not found."; }

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
        sf::Text text(std::to_string(fps), font);
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
