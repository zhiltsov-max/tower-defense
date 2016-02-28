#include "tilemaplayer.h"
#include <memory>


TTileMapLayer::TTileMapLayer() :
	layer(nullptr)
{}
	
TTileMapLayer::TTileMapLayer(const TNamedData<string>& source, ushort width_, ushort height_) :
	width(width_),
	height(height_)
{
	if (source.empty() == true) {
		throw_("Unable to load tileMap layer: source is empty.", "TTileMapLayer::TTileMapLayer");
	}

	layer = new ushort[height * width];
		
	string raw_tiles = source["tiles"];
	raw_tiles = raw_tiles.substr(2, raw_tiles.size() - 2);
	if (raw_tiles.empty() == true) {
		return;
	}
		
	std::vector<string> tiles_ = String::split(raw_tiles, ',');
	if (tiles_.size() != width * height) {
		throw_("Failed to create level layer: wrong count of tiles.", "TTileMapLayer::TTileMapLayer");
	}

	for(size_t i = 0; i != tiles_.size(); ++i) {
		ushort value = std::stoul(tiles_[i]);			
		layer[i] = value;
	}
}

TTileMapLayer::TTileMapLayer(const TTileMapLayer& other) :
	width(other.width),
	height(other.height)
{
	layer = new ushort[width * height];
	std::memcpy(layer, other.layer, width * height * sizeof(ushort));
}

TTileMapLayer& TTileMapLayer::operator=(const TTileMapLayer& other) {
	if (this != &other) {
		if (layer != nullptr) {
			if ((width != other.width) || (height != other.height)) {
				delete layer;
				layer = new ushort[other.width * other.height];
			}
		} else {
			layer = new ushort[other.width * other.height];
		}
		width = other.width;
		height = other.height;
		std::memcpy(layer, other.layer, width * height * sizeof(ushort));
	}
	return *this;
}
	
TTileMapLayer::~TTileMapLayer() {
	if (layer != nullptr) {
		delete layer;
	}
}
	

	
	
ushort TTileMapLayer::getTile(ushort x, ushort y) const {
#if (_DEBUG_ == true)
	if ((width <= x) || (height <= y)) {
		throw_("Point is out of bounds", "TTileMapLayer::getTile");
	}
#endif
	return layer[y * width + x];
}
	
void TTileMapLayer::setTile(ushort x, ushort y, ushort tileId) {
#if (_DEBUG_ == true)
	if ((width <= x) || (height <= y)) {
		throw_("Point is out of bounds", "TTileMapLayer::getTile");
	}
#endif
	layer[y * width + x] = id;
}
};