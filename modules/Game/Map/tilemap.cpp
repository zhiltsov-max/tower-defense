#include "tilemap.h"
#include "tilemaplayer.h"
#include <memory>
#include "../../../Application/application.h"


TTileMap::TTileMap() :
	layers(nullptr),
	tileset()
{}

TTileMap::TTileMap(const TTileMapInfo& source)
{
	loadData(source);
}

TTileMap::TTileMap(const TTileMap& other) :
	width(other.width),
	height(other.height),
	tileSize(other.tileSize),
	tileset(other.tileset),
    layers(new TTileMapLayer[Layer::_count])
{
    std::memcpy(layers, other.layers, Layer::_count * sizeof(TTileMapLayer));
}

TTileMap& TTileMap::operator=(const TTileMap& other) {
	if (this != &other) {
		if (layers == nullptr) {
            layers = new TTileMapLayer[Layer::_count];
		}
		width = other.width;
		height = other.height;
        std::memcpy(layers, other.layers, Layer::_count * sizeof(TTileMapLayer));
	}
	return *this;
}

TTileMap::~TTileMap()
{
	if (layers != nullptr) {
		delete[] layers;
	}
}
		
void TTileMap::updateData(const TTileMapInfo& source) {
    loadData(source);
}
	
uint TTileMap::getWidth() const {
	return width;
}	
uint TTileMap::getHeight() const {
    return height;
}

Vec2ui TTileMap::getSize() const {
    return Vec2ui(width, height);
}

uint TTileMap::getTileSize() const {
    return tileSize;
}
		
bool TTileMap::isTileBuildable(uint x, uint y) const {
	for(TTileMapLayer const* layer = layers; layer != layers + TileMapLayer::_count; ++layer) {
        const auto id = layer->getTile(x, y);
        if (tileset.GetTileAltitude(id) != Altitude::Ground) {
			continue;
		}
        if (tileset.GetTileBuildability(id) == false) {
			return false;
		}
	}
	return true;
}
	
int TTileMap::getTileWeight(uint x, uint y, const Altitude& altitude) const {
    PassWeight res = PassWeight::Max;
		
	for(TTileMapLayer const* layer = layers; layer != layers + TileMapLayer::_count; ++layer) {
		ushort id = layer->getTile(x, y);
		if (id == 0) {
			continue;
		}
			
        int tileAppearance = tileset.GetTileAltitude(id);
        if (altitude < tileAppearance) {
			res = PassWeight::CanNotPass;
			break;
		}
			
        int weight = tileset.GetTilePassWeight(id);
							
        switch (altitude) {
		case MobAppearance::Ground:
				if (isTileBuildable(x, y) == true) {
					if (TBuildingController::isTileTaken(x, y) == true) {
						weight = PassWeight::CanNotPass;
					}
				}
                break;
	
        case MobAppearance::Air:   /*none*/
        case MobAppearance::Water: /*none*/
				
		default:
			{	
                Throw("Unexpected appearance " + std::to_string(altitude), "TTileMap::getTileWeight");
				break;
			}
		}
			
		if (weight < res) {
			res = weight;
		}
	}

	return res;
}
	
	
void TTileMap::draw(Graphics::TRenderTarget& target) {
	for(TTileMapLayer const* layer = layers; layer != layers + TileMapLayer::_count; ++layer) {
        drawLayer(target, layer);
	}
}

void TTileMap::drawLayer(Graphics::TRenderTarget& target, TTileMapLayer const* layer) {

    for(auto y = 0; y != height; ++y) {
        for(auto x = 0; x != width; ++x) {
            const auto tileId = layer->getTile(x, y);
            if (tileId != 0) {
                sf::Sprite sprite = tileset.getImage(tileId - 1);
                sprite.setPosition(x * tileSize, y * tileSize);
                target.draw(sprite);
            }
        }
    }
}


void TTileMap::loadData(const TTileMapInfo& source) {
	if (source.empty() == true) {
        Throw("Unable to load tile map: source is empty.", "TTileMap::loadData");
	}
	
    width  = std::stoi(source[StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::Size] + source.keySep() + "width"]);
	height = std::stoi(source[StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::Size] + source.keySep() + "height"]);
	if ((width == 0) || (height == 0)) {
        Throw("Unable to load tileMap: wrong size.", "TTileMap::loadData");
	}
		
	layers = new TTileMapLayer[TileMapLayer::_count];
		
	int layerCount = std::stoi(source[StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::Layers] + source.keySep() + "count"]);
	if ((layerCount <= 0) || (TileMapLayer::_count < layerCount)) {
        Throw("Unable to load tileMap: wrong layer count.", "TTileMap::loadData");
	}
				
	for(int i = 0; i != layerCount; ++i) {
		layers[i] = TTileMapLayer(source.slice(
            StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::Layers] + source.keySep() + std::to_string(i)),
			width, height);
	}

    tileSize = GameMechanics::TILE_SIZE;

    TTilesetInfo tilesetInfo;
    tilesetInfo.info = source["tileset"];
    if (tilesetInfo.info.empty() == true) {
		throw_("Unable to load tile map: tileset data was not found.", "TTileMap::loadData");
    }
    source.resources->loadResource(source["tiles"]);
    tilesetInfo.texture = source.resources->getResource(source["tiles"]);
    tileset = TTileset(tilesetInfo);
}
