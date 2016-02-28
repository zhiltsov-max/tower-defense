#ifndef LEVEL_MAP_H
#define LEVEL_MAP_H

#include "../../../Core/core.h"
#include "../Scene/scene_object.h"
#include "tilemap.h"
#include "nodemap.h"
#include "passabilitymap.h"


struct TLevelMapInfo : TSceneObjectInfo
{
    TNamedData<string> info;
};

class LevelMapResources /*Abstract*/
{
public:
    static list<string> get(const TNamedData<string>& source);

	LevelMapResources() = delete;
	
	static string resourceHash;
};

class TLevelMap : public TSceneObject
{
public:
    using Size = Vec2ui;


    TLevelMap() = default;
    TLevelMap(const TLevelMapInfo& source);
	
    void updateData(const TLevelMapInfo& source);
			
	const TTileMap& getTileMap() const;
	TTileMap& getTileMap();
	
	const TNodeMap& getNodeMap() const;
	TNodeMap& getNodeMap();

    TPassabilityMap getPassabilityMap(const Altitude& altitude) const;
    TPassabilityMap getPassabilityMap(const Altitude& altitude);

    const Size& getSize() const;
	
    virtual void draw(Graphics::TRenderTarget& target) override;
    virtual void update() override;
	
    virtual int getZIndex() const override;

private:
    using parent_type = TSceneObject;


    TTileMap m_tileMap;
    TNodeMap m_nodeMap;


#if _DEBUG_
    void showBuildingZones(Graphics::TRenderTarget& target) const;
/*
    void showWaypoints() const;
    void showWalktroubles() const;
*/
#endif
};


#endif //LEVEL_MAP_H
