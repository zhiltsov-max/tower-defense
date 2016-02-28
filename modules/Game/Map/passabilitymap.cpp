#include "passabilitymap.h"
#include "tilemap.h"


TPassabilityMap::TPassabilityMap(const Size& size, const TTileMap& tilemap, const Altitude& altitude) :
    m_size(size_),
    m_map(new Passability[m_size.x * m_size.y]),
    m_altitude(altitude)
{
    for(auto y = 0; y < m_size.height; ++y) {
        for(auto x = 0; x < m_size.width; ++x) {
            m_map[y][x] = tilemap.getTileWeight(x, y, m_altitude);
        }
    }
}

TPassabilityMap::TPassabilityMap(const TPassabilityMap& other) :
    m_size(other.m_size),
    m_map(new Passability[other.m_size.x * other.m_size.y]),
    m_altitude(other.m_altitude)
{
    memcpy(m_map, other.m_map, sizeof(Passability) * m_size.x * m_size.y);
}

TPassabilityMap& TPassabilityMap::operator=(const TPassabilityMap& other) {
	if (this != &other) {
        if (m_size != other.m_size) {
            m_size = other.m_size;

            if (m_map != nullptr) {
                delete[] m_map;
            }
            m_map = new Passability[m_size.x * m_size.y];
        }

        memcpy(m_map, other.m_map, sizeof(Passability) * m_size.x * m_size.y);
        m_altitude = other.m_altitude;
	}
	return *this;
}
	
TPassabilityMap::~TPassabilityMap()
{
    if (m_map != nullptr) {
        delete[] m_map;
    }
}

const Altitude& TPassabilityMap::getAltitude() const {
    return m_altitude;
}

const TPassabilityMap::Map& TPassabilityMap::raw() const {
    return m_map;
}

TPassabilityMap::Map& TPassabilityMap::raw() {
    return m_map;
}

const Size& TPassabilityMap::getSize() const {
    return m_size;
}
