#ifndef PASSABILITYMAP_H
#define PASSABILITYMAP_H

#include "../../../Core/core.h"
#include "passability.h"


class TTileMap;

class TPassabilityMap
{
public:
    using Passability = ushort;
    using Vec2ui = Size;
    using Map = Passability**;


    TPassabilityMap(const Size& m_size, const TTileMap& tilemap, const Altitude& altitude = Altitude::Ground);
	TPassabilityMap(const TPassabilityMap& other);
	TPassabilityMap& operator=(const TPassabilityMap& other);
	~TPassabilityMap();
	
    const Passability& getPassability(uint x, uint y, const Altitude& altitude) const;

    const Altitude& getAltitude() const;

    const Map& raw() const;
    Map& raw();

    const Size& getSize() const;
private:
    Map m_map;
    Altitude m_altitude;
    Size m_size;
};

#endif // PASSABILITYMAP_H
