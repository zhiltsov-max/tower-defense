#include "Game/Map/level_node_map.h"
#include <algorithm>


namespace TD {

TLevelNodeMap::TLevelNodeMap(const Parameters& parameters) :
    pathes(),
    enters(),
    exits()
{
    checkData(parameters);
    pathes = parameters.pathes;
    enters = parameters.enters;
    exits = parameters.exits;
}
	
void TLevelNodeMap::checkNode(const Node& node, const Vec2ui& mapSize) {
    ASSERT((node.x < mapSize.x) && (node.y < mapSize.y),
        "Node is out of map.");
}

void TLevelNodeMap::checkData(const Parameters& source) {
    for (const auto& enter : source.enters) {
        checkNode(enter, source.size);
    }
    for (const auto& exit : source.exits) {
        checkNode(exit, source.size);
    }

    using std::find;
    for (const auto& path : source.pathes) {
        ASSERT(source.enters.cend() !=
                find(source.enters.cbegin(), source.enters.cend(), path.front()),
            "Path begin is not found.");
        ASSERT(exits.cend() !=
                find(source.exits.cbegin(), source.exits.cend(), path.back()),
            "Path end is not found.");
        for (const auto& node : path) {
            checkNode(node, source.size);
        }
    }
}

void TLevelNodeMap::AddPath(const Path& path) {
    pathes.emplace_back(path);
}

void TLevelNodeMap::AddEnter(const Node& node) {
    ASSERT(IsEnter(node) == false, "Enter is already exists.");
    enters.emplace_back(node);
}

void TLevelNodeMap::AddExit(const Node& node) {
    ASSERT(IsExit(node) == false, "Exit is already exists.");
    exits.emplace_back(node);
}	
	
const TLevelNodeMap::Node& TLevelNodeMap::GetEnter(const Index& index) const {
	return enters[index];
}

TLevelNodeMap::Node& TLevelNodeMap::GetEnter(const Index& index) {
    return enters[index];
}

const TLevelNodeMap::Node& TLevelNodeMap::GetExit(const Index& index) const {
    return exits[index];
}

TLevelNodeMap::Node& TLevelNodeMap::GetExit(const Index& index) {
    return exits[index];
}

const TLevelNodeMap::Path& TLevelNodeMap::GetPath(const Index& index) const {
    return pathes[index];
}

TLevelNodeMap::Path& TLevelNodeMap::GetPath(const Index& index) {
    return pathes[index];
}

size_t TLevelNodeMap::GetPathCount() const {
    return pathes.size();
}

size_t TLevelNodeMap::GetEnterCount() const {
    return enters.size();
}

size_t TLevelNodeMap::GetExitCount() const {
    return exits.size();
}

TLevelNodeMap::Index TLevelNodeMap::FindNearestExit(uint x, uint y) const {
    if (exits.empty() == true) {
        return -1u;
    }

    auto minNode = exits.cbegin();
    double minDist = std::pow<double>(x - (*minNode).x, 2) +
                     std::pow<double>(y - (*minNode).y, 2);

    for (auto it = exits.cbegin(); it != exits.cend(); ++it) {
        const auto node = *it;
        const double curDist = std::pow<double>(x - node.x, 2) +
                               std::pow<double>(y - node.y, 2);
        if (curDist < minDist) {
            minNode = it;
            minDist = curDist;
        }
    }
    return std::distance(exits.cbegin(), minNode);
}

bool TLevelNodeMap::IsExit(const Node& node) const {
    return exits.cend() != std::find(exits.cbegin(), exits.cend(), node);
}
bool TLevelNodeMap::IsEnter(const Node& node) const {
    return enters.cend() != std::find(enters.cbegin(), enters.cend(), node);
}


std::unique_ptr<GE::TComponent>
CLevelNodeMap::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelNodeMap(args));
}

CLevelNodeMap::CLevelNodeMap(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelNodeMap>::value()),
    nodeMap((source != nullptr) ? source->nodeMap : NodeMap::Parameters())
{}


std::unique_ptr<GE::TComponent>
CLevelNodeMapView::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<const Parameters*>(args_);
    if ((args_ != nullptr) && (args == nullptr)) {
        THROW("Wrong args passed to function.");
    }
    return std::unique_ptr<GE::TComponent>(new CLevelNodeMapView(args));
}

CLevelNodeMapView::CLevelNodeMapView(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelNodeMapView>::value())
{}

} // namespace TD
