#include "level_node_map.h"
#include <algorithm>


namespace TD {

std::unique_ptr<GE::TComponent>
CLevelNodeMap::Create(const GE::TComponentCreateArgs* args_) {
    return std::unique_ptr<GE::TComponent>(new CLevelNodeMap(args));
}

CLevelNodeMap::CLevelNodeMap(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelNodeMap>::value)
{
    if (source != nullptr) {
        checkDataSource(source);
        pathes = source->pathes;
        enters = source->enters;
        exits = source->exits;
    }
}

void CLevelNodeMap::checkNode(const Node& node, const Vec2ui& mapSize) {
    ASSERT((node.x < mapSize.x) && (node.y < mapSize.y),
        "Node is out of map.");
}

void CLevelNodeMap::checkData(const CLevelNodeMap::Parameters& source) {
    for (const auto& enter : source.enters) {
        checkNode(enter, source.size);
    }
    for (const auto& exit : source.exits) {
        checkNode(exit, source.size);
    }

    using std::find;
    for (const auto& path : source.pathes) {
        ASSERT(IsEnter(path[0]) == true, "Path begin is not found.");
        ASSERT(IsExit(path.back()) == true, "Path end is not found.");
        for (const auto& node : path) {
            checkNode(node, source.size);
        }
    }
}
	
void CLevelNodeMap::AddPath(const Path& path) {
    pathes.emplace_back(path);
}

void CLevelNodeMap::AddEnter(const Node& node) {
    ASSERT(IsEnter(node) == false, "Enter is already exists.");
    enters.emplace_back(node);
}

CLevelNodeMap::Node& CLevelNodeMap::addExit(const Node& node) {
    ASSERT(IsExit(node) == false, "Exit is already exists.");
    exits.emplace_back(node);
}	
	
const CLevelNodeMap::Node& CLevelNodeMap::GetEnter(size_t index) const {
	return enters[index];
}

CLevelNodeMap::Node& CLevelNodeMap::GetEnter(size_t index) {
    return enters[index];
}

const CLevelNodeMap::Node& CLevelNodeMap::GetExit(size_t index) const {
    return exits[index];
}

CLevelNodeMap::Node& CLevelNodeMap::GetExit(size_t index) {
    return exits[index];
}

const CLevelNodeMap::Path& CLevelNodeMap::GetPath(size_t index) const {
    return pathes[index];
}

CLevelNodeMap::Path& CLevelNodeMap::GetPath(size_t index) {
    return pathes[index];
}

size_t CLevelNodeMap::GetPathCount() const {
    return pathes.size();
}

size_t CLevelNodeMap::GetEnterCount() const {
    return enters.size();
}

size_t CLevelNodeMap::GetExitCount() const {
    return exits.size();
}

size_t CLevelNodeMap::FindNearestExit(uint x, uint y) const {
    if (exits.empty() == true) {
        return static_cast<size_t>(-1);
    }

    const auto* minNode = &exits.front();
    double minDist = std::pow<double>(x - (*minNode).x, 2) +
                     std::pow<double>(y - (*minNode).y, 2);

    for(const auto& node : exits) {
        const double curDist = std::pow<double>(x - node.x, 2) +
                               std::pow<double>(y - node.y, 2);
        if (curDist < minDist) {
            minNode = &node;
            minSq = curDist;
        }
    }
    return minNode - exits.front();
}

bool CLevelNodeMap::IsExit(const CLevelNodeMap::Node& node) const {
    return exits.cend() != std::find(exits.cbegin(), exits.cend(), node);
}
bool CLevelNodeMap::IsEnter(const CLevelNodeMap::Node& node) const {
    return enters.cend() != std::find(enters.cbegin(), enters.cend(), node);
}


std::unique_ptr<GE::TComponent>
CLevelNodeMapView::Create(const GE::TComponentCreateArgs* args_) {
    const auto* args = dynamic_cast<CLevelNodeMapView::Parameters*>(args_);
    return std::unique_ptr<GE::TComponent>(new CLevelNodeMapView(args));
}

CLevelNodeMapView::CLevelNodeMapView(const Parameters* source) :
    parent_type(GE::ComponentID<CLevelNodeMapView>::value)
{
    if (source != nullptr) {
        scene = source->scene;
        nodeMapComponentPath = source->nodeMapComponent;
    }
}

void CLevelNodeMapView::Update(const GE::TTime& step, Context& context) {
    //TODO: implementation
}

void CLevelNodeMapView::Render(Graphics::TRenderTarget& target) {
    //TODO: implementation
}

void CLevelNodeMapView::HandleMessage(const GE::TMessage& message,
    Context& context) { /*TODO:...*/ }

forward_list<GE::TMessage::ID> TD::CLevelNodeMapView::GetAcceptedMessages() {
    /*TODO:...*/
}

} // namespace TD
