#include "level_map.h"


namespace TD {

const string TLevelMap::DEFAULT_OBJECT_NAME = "map";

TLevelMap::TLevelMap(const TLevelInfoMap& source) :
    scene(source.scene)
{
    ASSERT(scene != nullptr, "Scene is not set.");

    GE::TSceneObject sceneObject;
    tileMapHandle = scene->GetRaw().CreateComponent<CLevelTileMap>(
        &source.tileMap);
    sceneObject.AddComponent("tileMap", tileMapHandle);

    nodeMapHandle = scene->GetRaw().CreateComponent<CLevelNodeMap>(
        &source.nodeMap);
    sceneObject.AddComponent("nodeMap", nodeMapHandle);

    passabilityMapHandle = scene->GetRaw().CreateComponent<CPassabilityMap>();
    GetPassabilityMap().SetNodeMap(&nodeMap);
    sceneObject.AddComponent("passabilityMap", passabilityMapHandle);

    sceneObjectHandle = scene->AddSceneObject(DEFAULT_OBJECT_NAME, sceneObject);
}

const CLevelPassabilityMap& TLevelMap::GetPassabilityMap() const {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<const CLevelPassabilityMap>(
        passabilityMapHandle);
}

CLevelPassabilityMap& TLevelMap::GetPassabilityMap() {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<CLevelPassabilityMap>(
        passabilityMapHandle);
}

const CLevelTileMap& TLevelMap::GetTileMap() const {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<const CLeveltileMap>(tileMapHandle);
}

CLevelTileMap& TLevelMap::GetTileMap() {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<CLeveltileMap>(tileMapHandle);
}
	
const CLevelNodeMap& TLevelMap::GetNodeMap() const {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<const CLevelNodeMap>(
        nodeMapHandle);
}

CLevelNodeMap& TLevelMap::GetNodeMap() {
    ASSERT(scene != nullptr, "Scene is not set.");
    return *scene->GetRaw().GetComponent<CLevelNodeMap>(
        nodeMapHandle);
}

} // namespace TD
