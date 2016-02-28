#include "pathnode.h"


TPathNode::TPathNode() :
	size(GameMechanics::TILE_SIZE * 0.1)
{}

TPathNode::TPathNode(const Point2ui& position) :
	pos(position),
	size(GameMechanics::TILE_SIZE * 0.1)
{
#if _DEBUG_
	checkPosition();
#endif
}
TPathNode::TPathNode(uint x, uint y) :
	pos(x, y),
	size(GameMechanics::TILE_SIZE * 0.1)
{
#if _DEBUG_
	checkPosition();
#endif
}

bool TPathNode::operator==(const TPathNode& other) const {
	return pos == other.pos;
}

const Point2ui& TPathNode::getPos() const {
	return pos;
}	
float TPathNode::getSize() const {
	return size;
}	
const Point2ui& TPathNode::absPos() const {
	return Point2ui(
		(pos[0] + 0.5) * GameMechanics::TILE_SIZE,
		(pos[1] + 0.5) * GameMechanics::TILE_SIZE
		);
}		

#if _DEBUG_
void TPathNode::draw(Graphics::TRenderTarget& target) {
    sf::CircleShape oval(size);
    oval.setFillColor(color);
    oval.setPosition(absPos());
    target.draw(oval);
}

void TPathNode::checkPosition() const {
	if (GetGame().GetLevel().GetScene().GetMap().GetWidth() < pos[0]) {
		throw_("Node is out of map: " + x + ", " + y, "TNode::_checkPosition");
	}
		
	if (GetGame().GetLevel().GetScene().GetMap().GetHeight() < pos[1]) {
		throw_("Node is out of map: " + x + ", " + y, "TNode::_checkPosition");
	}
}
#endif
