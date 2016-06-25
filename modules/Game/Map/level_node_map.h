#ifndef LEVEL_NODE_MAP_H
#define LEVEL_NODE_MAP_H

#include "Core/core.h"
#include "Game/Components/components_list.h"
#include "GameEngine/component_systems.h"
#include "Game/Level/level_scene.h"


namespace TD {

class CLevelNodeMap :
    public GE::CDataComponent
{
public:
    using Node = Vec2ui;
    using Path = vector<Node>;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMap(const Parameters* source = nullptr);

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

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;
    virtual void Subscribe(GE::TComponentSystem& system) override;
    virtual void Unsubscribe(GE::TComponentSystem& system) override;
private:
    using parent_type = GE::CDataComponent;

    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    void checkData(const CLevelNodeMap::Parameters& source);
    void checkNode(const Node& node, const Vec2ui& mapSize);
};

template<>
struct GE::ComponentID<CLevelNodeMap>
{
    static constexpr GE::ComponentIDs value = GE::ComponentIDs::LevelNodeMap;
};

struct CLevelNodeMap::Parameters : GE::TComponentCreateArgs
{
    vector<Node> pathes;
    vector<Node> enters;
    vector<Node> exits;

    Vec2ui size;
};


class CLevelNodeMapView :
    public GE::CGraphicsComponent
{
public:
    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMapView(const Parameters* source = nullptr);

    virtual void Update(const GE::TTime& step, Context& context) override;
    virtual void HandleMessage(const TMessage& message,
        Context& context) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    void SetScene(TLevelScene* instance);
    void SetNodeMap(const TLevelScene::ComponentHandle& handle);
private:
    using parent_type = GE::CGraphicsComponent;

    TLevelScene* scene;
    TLevelScene::ComponentPath nodeMapComponent;
};

template<>
struct GE::ComponentID<CLevelNodeMapView>
{
    static constexpr GE::ComponentIDs value =
        GE::ComponentIDs::LevelNodeMapView;
};

struct CLevelNodeMapView::Parameters : GE::TComponentCreateArgs
{
    TLevelScene::ComponentPath nodeMapComponent;
};

} // namespace TD

#endif // LEVEL_NODE_MAP_H
