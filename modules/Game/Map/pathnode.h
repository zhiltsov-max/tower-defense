#ifndef PATHNODE_H
#define PATHNODE_H

#include "..\..\..\Core\core.h"


class TPathNode
{
public:
	TPathNode();
	TPathNode(const Point2ui& position);
	TPathNode(uint x, uint y);
	
	bool operator==(const TPathNode& other) const;

	const Point2ui& getPos() const;	
	float getSize() const;
	const Point2ui& absPos() const;		
	
#if _DEBUG_
    void draw(Graphics::TRenderTarget& target);
#endif

private:
    Point2ui pos; //Tile coordinates

	const float size;
	
#if _DEBUG_
    static const Graphics::ARGB color = 0xCCC8C800;

	void checkPosition() const;
#endif
};

#endif // PATHNODE_H
