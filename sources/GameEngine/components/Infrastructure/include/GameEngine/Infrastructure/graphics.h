#ifndef GAME_ENGINE_GRAPHICS_H
#define GAME_ENGINE_GRAPHICS_H

#include "SFML/Graphics.hpp"

#include "GameEngine/Utility/defs.h"
#include "GameEngine/Infrastructure/point.h"


namespace GE {

namespace Graphics {

using TColor = sf::Color;

struct ARGB {
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;


    constexpr ARGB(uint32_t value = 0xffffffff) :
        a(value >> 24),
        r(value >> 16),
        g(value >> 8),
        b(value)
    {}

    constexpr ARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) :
        a(a),
        r(r),
        g(g),
        b(b)
    {}

    constexpr ARGB(const TColor& color) :
        a(color.a),
        r(color.r),
        g(color.g),
        b(color.b)
    {}


    constexpr operator uint32_t() const {
        return
            (static_cast<uint32_t>(a) << 24) +
            (static_cast<uint32_t>(r) << 16) +
            (static_cast<uint32_t>(g) << 8) +
            (static_cast<uint32_t>(b));
    }

    operator TColor() const {
        return TColor(r, g, b, a);
    }

    bool operator == (const ARGB& other) const {
        return
            (a == other.a) &&
            (r == other.r) &&
            (g == other.g) &&
            (b == other.b);
    }
};


using TFont = sf::Font;
using TText = sf::Text;
using TImage = sf::Image;
using TTexture = sf::Texture;
using TSprite = sf::Sprite;

} // namespace Graphics

} // namespace GE

#endif // GAME_ENGINE_GRAPHICS_H
