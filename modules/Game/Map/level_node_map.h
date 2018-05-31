#ifndef LEVEL_NODE_MAP_H
#define LEVEL_NODE_MAP_H

#include "Core/core.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "Game/Components/td_components_list.h"
#include "Game/ComponentSystems/td_component_systems_list.h"
#include "Game/Level/level_scene.h"


namespace TD {

class TLevelNodeMap
{
public:
    struct Parameters;
    using Node = Vec2ui;
    using Path = vector<Node>;
    using Index = size_t;

    TLevelNodeMap() = default;
    TLevelNodeMap(const Parameters& parameters);

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
    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    void checkData(const Parameters& source);
    void checkNode(const Node& node, const Vec2ui& mapSize);
};

struct TLevelNodeMap::Parameters
{
    vector<Path> pathes;
    vector<Node> enters;
    vector<Node> exits;

    Vec2ui size;
};

} // namespace TD


TD_DECLARE_COMPONENT_CLASS(CLevelNodeMap,
    GE::ComponentIDs::LevelNodeMap, GE::ComponentSystem::Map)


namespace TD {

struct CLevelNodeMap : GE::TComponent
{
    struct Parameters;
    using NodeMap = TLevelNodeMap;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMap(const Parameters* source = nullptr);

    NodeMap nodeMap;

private:
    using parent_type = GE::TComponent;
};

struct CLevelNodeMap::Parameters : GE::TComponentCreateArgs
{
    NodeMap::Parameters nodeMap;
};

} // namespace TD


TD_DECLARE_COMPONENT_CLASS(CLevelNodeMapView,
    GE::ComponentIDs::LevelNodeMapView, GE::ComponentSystem::Graphics)


namespace TD {

struct CLevelNodeMapView : GE::TComponent // TODO: maybe it is Presenter
{
    struct Parameters;

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args = nullptr);

    CLevelNodeMapView(const Parameters* source = nullptr);

private:
    using parent_type = GE::TComponent;

};

struct CLevelNodeMapView::Parameters : GE::TComponentCreateArgs
{};

} // namespace TD

#endif // LEVEL_NODE_MAP_H
