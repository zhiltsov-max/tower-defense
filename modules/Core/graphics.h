#ifndef CORE_GRAPHICS_H
#define CORE_GRAPHICS_H

#include "checkdef.h"

#if !defined(SFML)
    #error Only SFML supported now
#endif //SFML

#include "defs.h"
#include "image.h"


namespace Graphics {

using TColor = sf::Color;

struct ARGB {
    uchar a;
    uchar r;
    uchar g;
    uchar b;


    constexpr ARGB(uint value = 0xffffffff) :
        a(value >> 24),
        r(value >> 16),
        g(value >> 8),
        b(value)
    {}

    constexpr ARGB(uchar r, uchar g, uchar b, uchar a = 255) :
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


    constexpr operator uint() const {
        return (static_cast<uint>(a) << 24) +
            (static_cast<uint>(r) << 16) +
            (static_cast<uint>(g) << 8) +
            (static_cast<uint>(b));
    }

    operator TColor() const {
        return TColor(r, g, b, a);
    }

    bool operator==(const ARGB& other) {
        return operator uint() == other.operator uint();
    }
	
};


using TRenderTarget = sf::RenderTarget;
using TFont = sf::Font;
using TText = sf::Text;

} //namespace Graphics

#endif //CORE_GRAPHICS_H
