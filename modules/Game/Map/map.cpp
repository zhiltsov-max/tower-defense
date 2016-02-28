#include "map.h"


TLevelMap::TLevelMap(const TLevelMapInfo& source) :
    parent_type(),
    m_tileMap(source.info.slice(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::TileMap]))
{
    m_nodeMap = std::move(TNodeMap(m_tileMap.getSize(),
        source.info.slice(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::NodeMap])
        ));
}
	
void TLevelMap::updateData(const TLevelMapInfo& source) {
    if (source.info.empty() == true) {
		return;
	}
		
    if (source.info.contains(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::TileMap]) == true) {
        TTileMapInfo info;
        info.info = source.info.slice(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::TileMap]);
        info.resources = getSceneResources();
        m_tileMap.updateData(info);
	}
	
    if (source.info.contains(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::NodeMap]) == true) {
        m_nodeMap.updateData(source.slice(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::NodeMap]));
	}
/*  TO DO: fill scene
	if (source.contains(StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::GameObjects]) == true) {
		gameObjects.updateData(source.slice(
            StageInfo::Category_Map_Value[StageInfo::Category_Map_Entry::GameObjects]
        ));
    }
*/
}

const TPassabilityMap& TLevelMap::getPassabilityMap(const Altitude& altitude) const {
    return TPassabilityMap(getSize(), m_tileMap, altitude);
}

TPassabilityMap& TLevelMap::getPassabilityMap(const Altitude& altitude) {
    return TPassabilityMap(getSize(), m_tileMap, altitude);
}

const TTileMap& TLevelMap::getTileMap() const {
    return m_tileMap;
}
TTileMap& TLevelMap::getTileMap() {
    return m_tileMap;
}
	
const TNodeMap& TLevelMap::getNodeMap() const {
    return m_nodeMap;
}
TNodeMap& TLevelMap::getNodeMap() {
    return m_nodeMap;
}

const TLevelMap::Size& TLevelMap::getSize() const {
    return m_tileMap.getSize();
}
		
bool TLevelMap::isTileBuildable(uint x, uint y) const {
    return m_tileMap.isTileBuildable(x, y);
}	
	
#if _DEBUG_
void TLevelMap::showBuildingZones(Graphics::TRenderTarget& target) const {
    for(uint x = 0; x != getSize().x; ++x) {
        for(uint y = 0; y != getSize().y; ++y) {
            sf::RectangleShape rect(m_tileMap.getTileSize() - 2, m_tileMap.getTileSize() - 2);
            rect.setPosition(x * m_tileMap.getTileSize() + 1, y * m_tileMap.getTileSize() + 1);
            if ((m_tileMap.isTileBuildable(x, y) == true) && (e_buildingsController->isTileTaken(x, y) == false)) {
                rect.setFillColor(Graphics::ARGB(0x4C00C800));
			} else {
                rect.setFillColor(Graphics::ARGB(0x4CC80000));
            }
            target.draw(rect);
		}
	}
}
/*	
Method TLevelMap::ShowWaypoints()
	} GetGame().GetType()
		Case GameType.Normal
				number:Short = 0
			for(  path:TNodePath = EachIn nodeMap.pathes
				for(  node:TNode = EachIn path.path
					node.Draw()
						
					} (number = 0 Or number = path.GetLength())
						Graphics::SetColor($66C8C800)
					} else {
						Graphics::SetColor($FFFFFFFF)
					}
					DrawText(number, node.absx() - 2, node.absy() - 2)
						
					number:+1
				Next
			Next
			
		Case GameType.Free
			for(  mob:TMob = EachIn TMobController.GetAllMobs()
					
				} (mob.path.path = nullptr)
					Continue
				}
					
					number:Short = 0
					
				for(  node:TNode = EachIn mob.path.path.path
					Graphics::SetColor($44FF5050)
					DrawRect(node.x + 1 - GameMechanics.TILE_SIZE * 0.5, node.y + 1 - GameMechanics.TILE_SIZE * 0.5, GameMechanics.TILE_SIZE - 2, GameMechanics.TILE_SIZE - 2)
						
					node.Draw()
						
					Graphics::SetColor($FFFFFFFF)
					DrawText(number, node.x - 2, node.y - 2)
						
					number:+1
				Next
			Next
			
		Default
			throw_("Wrong game type: " + GetGame().GetType() + ".", "TLevelMap::ShowWaypoints")
	}
}
	
void TLevelMap::showWalktroubles() const {
		map:Byte[,] = nodeMap.GetPassabilityMap().ForMob()
	for(  x:Short = 0 Until GetWidth()
		for(  y:Short = 0 Until GetHeight()
			Graphics::SetColor($4C0000C8)
			DrawRect(x * GameMechanics.TILE_SIZE + 1, y * GameMechanics.TILE_SIZE + 1, GameMechanics.TILE_SIZE - 2, GameMechanics.TILE_SIZE - 2)
			Graphics::SetColor($FFFFFFFF)
			DrawText(map[x, y], (x + 0.5) * GameMechanics.TILE_SIZE, (y + 0.5) * GameMechanics.TILE_SIZE)
		Next
	Next
}
*/
#endif

	
void TLevelMap::draw(Graphics::TRenderTarget& target) {
    m_tileMap.draw(target);

#if _DEBUG_
	if (GameDebugTools::ShowBZ == true) { ShowBuildingZones(); }
	//if (GameDebugTools::ShowWP == true) { ShowWaypoints(); }
	//if (GameDebugTools::ShowWT == true) { ShowWalktroubles(); }
#endif
}
	
void TLevelMap::update() {
    //m_tileMap.update();
}

	
int TLevelMap::getZIndex() const {
	return GraphicsZIndexes::Ground;
}


list<string> LevelMapResources::get(const TNamedData<string>& source) {
    list<string> res;
    res.push_back(source["tileset"]);
    resourceHash = res.back();

    return res;
}
