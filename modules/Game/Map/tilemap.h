#ifndef TILEMAP_H
#define TILEMAP_H

#include "tileset.h"
#include "../Scene/scene_resources.h"


struct TTileMapInfo
{
    TNamedData<string> info;
    TSceneResources* resources;
};

class TTileMap
{
public:
	TTileMap();
    TTileMap(const TTileMapInfo& source);
	TTileMap(const TTileMap& other);
	TTileMap& operator=(const TTileMap& other);
	~TTileMap();
		
    void updateData(const TTileMapInfo& source);
		
	uint getWidth() const;
	uint getHeight() const;
    Vec2ui getSize() const;

    uint getTileSize() const;
		
    bool isTileBuildable(uint x, uint y) const;
    int getTileWeight(uint x, uint y, const Altitude& altitude) const;

    void draw(Graphics::TRenderTarget& target);

private:
    enum class Layer {
        _min = 0,

        Ground = 0,
        GroundEffects = 1,
        Objects = 2,
        ObjectEffects = 3,

        _count
    };


    TTileMapLayer* layers;
    uint width;
    uint height;
    TTileset tileset;
    uint tileSize;


    void loadData(const TTileMapInfo& source);

    void drawLayer(Graphics::TRenderTarget& target, TTileMapLayer const* layer);
};

#endif //TILEMAP_H
