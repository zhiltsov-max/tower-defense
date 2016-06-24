#ifndef LEVEL_NODE_MAP_H
#define LEVEL_NODE_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "GameEngine/component_systems.h"
#include "Game/Level/level_scene.h"


namespace TD {

struct TLevelNodeMapInfo : GE::TComponentCreateArgs
{
    using Node = Vec2ui;
    using Path = vector<Node>;
    vector<Node> pathes;
    vector<Node> enters;
    vector<Node> exits;

    Vec2ui size;
};

class CLevelNodeMap :
    public GE::CDataComponent
{
public:
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMap(const TLevelNodeMapInfo* source = nullptr);

    using Path = TLevelNodeMapInfo::Path;
    using Node = TLevelNodeMapInfo::Node;
    void AddPath(const Path& path);
    void AddEnter(const Node& node);
    void AddExit(const Node& node);
	
    const Node& GetEnter(size_t index = 0) const;
    Node& GetEnter(size_t index = 0);

    const Node& GetExit(size_t index = 0) const;
    Node& GetExit(size_t index = 0);

    const Path& GetPath(size_t index = 0) const;
    Path& GetPath(size_t index = 0);

    size_t GetPathCount() const;
    size_t GetEnterCount() const;
    size_t GetExitCount() const;
	
    size_t FindNearestExit(uint x, uint y) const;
		
    bool IsExit(const Node& node) const;
    bool IsEnter(const Node& node) const;

    virtual void HandleMessage(const GE::TMessage& message) override;
    virtual void Subscribe(GE::TComponentSystem& system) override;
    virtual void Unsubscribe(GE::TComponentSystem& system) override;
private:
    using parent_type = GE::CDataComponent;

    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    void checkData(const TLevelNodeMapInfo& source);
    void checkNode(const Node& node, const Vec2ui& mapSize);
};

template<>
struct GE::ComponentID<CLevelNodeMap> {
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::LevelNodeMap;
};


struct TLevelNodeMapViewInfo : GE::TComponentCreateArgs
{
    TLevelScene* scene;
    TLevelScene::ComponentHandle nodeMapHandle;
};

class CLevelNodeMapView :
    public GE::CGraphicsComponent
{
public:
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMapView(const TLevelNodeMapViewInfo* source = nullptr);

    virtual void Update() override;
    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    void SetScene(TLevelScene* instance);
    void SetNodeMap(const TLevelScene::ComponentHandle& handle);
private:
    using parent_type = GE::CGraphicsComponent;

    TLevelScene* scene;
    TLevelScene::ComponentHandle nodeMapHandle;
};

template<>
struct GE::ComponentID<CLevelNodeMapView> {
    static constexpr GE::ComponentIDs value =
        GE::ComponentIDs::LevelNodeMapView;
};

} // namespace TD

#endif // LEVEL_NODE_MAP_H


/* TODO: ...
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
*/
