#ifndef __TILEMAPLAYER_H__
#define __TILEMAPLAYER_H__

#include "..\..\..\Core\core.h"
#include "map.h"

class TTileMapLayer
{
public:
	TTileMapLayer();	
	TTileMapLayer(const TNamedData<string>& source, ushort width_, ushort height_);
	TTileMapLayer(const TTileMapLayer& other);
	TTileMapLayer& operator=(const TTileMapLayer& other);
	~TTileMapLayer();
	
	ushort getTile(ushort x, ushort y) const;	
	void setTile(ushort x, ushort y, ushort tileId);
private:
	ushort* layer;
	uint width;
	uint height;
};


#endif