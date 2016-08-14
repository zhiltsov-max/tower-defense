#ifndef LEVEL_NODE_MAP_H
#define LEVEL_NODE_MAP_H

#include "Core/core.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"
#include "GameEngine/ComponentSystems/component_system_data.h"
#include "GameEngine/ComponentSystems/component_system_graphics.h"
#include "Game/Level/level_scene.h"


namespace TD {

class CLevelNodeMap :
    public GE::CDataComponent
{
public:
    using Node = Vec2ui;
    using Path = vector<Node>;
    using Index = size_t;
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMap(const Parameters* source = nullptr);

    void AddPath(const Path& path);
    void AddEnter(const Node& node);
    void AddExit(const Node& node);
	
    const Node& GetEnter(const Index& index = 0) const;
    Node& GetEnter(const Index& index = 0);

    const Node& GetExit(const Index& index = 0) const;
    Node& GetExit(const Index& index = 0);

    const Path& GetPath(const Index& index = 0) const;
    Path& GetPath(const Index& index = 0);

    size_t GetPathCount() const;
    size_t GetEnterCount() const;
    size_t GetExitCount() const;
	
    Index FindNearestExit(uint x, uint y) const;
		
    bool IsExit(const Node& node) const;
    bool IsEnter(const Node& node) const;

private:
    using parent_type = GE::CDataComponent;

    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    void checkData(const CLevelNodeMap::Parameters& source);
    void checkNode(const Node& node, const Vec2ui& mapSize);
};

struct CLevelNodeMap::Parameters : GE::TComponentCreateArgs
{
    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    Vec2ui size;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CLevelNodeMap>
{
    static const ComponentIDs value;
};

template<>
struct ComponentClass<TD::CLevelNodeMap>
{
    static const ComponentSystem value;
};

} // namespace GE


namespace TD {

class CLevelNodeMapView :
    public GE::CGraphicsComponent
{
public:
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMapView(const Parameters* source = nullptr);

    virtual void Update(const GE::TTime& step, Context& context) override;
    virtual void Render(Graphics::TRenderTarget& target) override;
    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override;

private:
    using parent_type = GE::CGraphicsComponent;

    TLevelScene::ComponentPath nodeMapComponentPath;
    TLevelScene::ComponentHandle nodeMapHandle;
};

struct CLevelNodeMapView::Parameters : GE::TComponentCreateArgs
{
    TLevelScene::ComponentPath nodeMapComponent;
};

} // namespace TD


namespace GE {

template<>
struct ComponentID<TD::CLevelNodeMapView>
{
    static const ComponentIDs value;
};

template<>
struct ComponentClass<TD::CLevelNodeMapView>
{
    static const ComponentSystem value;
};

} // namespace GE

#endif // LEVEL_NODE_MAP_H
