#ifndef TILESET_H
#define TILESET_H

#include "../../../Core/core.h"
#include "passabilitymap.h"


struct TTilesetInfo
{
    string info;
    Graphics::TTexture* texture;
    int tileSize;
};

class TTileset
{
public:
    using TileID = uint;
    using TileFrame = sf::IntRect;
    using ImageInstance = Graphics::TTexture*;
    using TileImage = Graphics::TSprite;


    TTileset() = default;
    TTileset(const TTilesetInfo& source);

    const PassWeight& GetTilePassWeight(const TileID& id) const;
    const Altitude& GetTileAltitude(const TileID& id) const;
    bool GetTileBuildability(const TileID& id) const;
    TileImage GetTileImage(const TileID& id) const;

    void SetImageInstance(ImageInstance& value);
private:
    struct TileInfo {
        Altitude altitude;
        PassWeight weight;
        bool buildable;
        TileFrame frame;

        TileInfo(const Altitude& altitude_, const PassWeight& weight_, bool buildable_) :
            altitude(altitude_), weight(weight_), buildable(buildable_)
		{}
	};
    using Data = map<TileID, TileInfo>;

    Data m_info;

    ImageInstance e_image;
};

#endif //TILESET_H
