#include "scene_resources.h"


namespace GE {

TSceneResources::PWeakResource TSceneResources::LoadResource(
    const TSceneResources::ID& id, const TSceneResource::TypeID& type,
    const TSceneResourceCreateArgs* args
) {
    ASSERT(registry.IsRegistered(type) == true,
        "Failed to load resource: unknown type.");
    ASSERT(IsResourceLoaded(id) == false,
        "Failed to load resource: resource '" + id + "' is already loaded.");

    const auto& loader = registry[type];
    auto ptr = std::move(loader(args));
    if (ptr == nullptr) {
        THROW("Failed to load resource.");
    }

    PResource resource(ptr.release());
    return resources.emplace(id, std::move(resource)).first->second;
}

void TSceneResources::UnloadResource(const ID& id) {
    ASSERT(IsResourceLoaded(id) == true,
        "Failed to unload resource: resource is not loaded.");

    resources.erase(id);
}

void TSceneResources::Clear() {
    resources.clear();
}
	
bool TSceneResources::IsResourceLoaded(const ID& id) const {
    return resources.count(id) != 0;
}

const TSceneResourceRegistry& TSceneResources::GetRegistry() const {
    return registry;
}

TSceneResourceRegistry& TSceneResources::GetRegistry() {
    return registry;
}
	
TSceneResources::PConstWeakResource
TSceneResources::GetResource(const ID& id) const {
    return resources.at(id);
}

TSceneResources::PWeakResource TSceneResources::GetResource(const ID& id) {
    return resources.at(id);
}

bool TSceneResources::IsEmpty() const {
    return resources.empty();
}

} //namespace GE
