#include "scene_resources.h"


	
TSceneResource& TSceneResources::LoadResource(const ID& id) {
    if (IsResourceLoaded(id) == true) {
        return data.at(id);
	}
		
    TSceneResource resource;
    resource.Load(id);
    auto it = data.emplace(id, resource).first;
    return (*it).second;
}
	
void TSceneResources::UnloadResource(const ID& name) {
    if (IsResourceLoaded(name) == false) {
		return;
	}
    data.erase(name);
}

void TSceneResources::Clear() {
    data.clear();
}
	
bool TSceneResources::IsResourceLoaded(const ID& name) const {
    return data.count(name) != 0;
}
	
const TSceneResource& TSceneResources::GetResource(const ID& name) const {
    return data.at(name);
}

TSceneResource& TSceneResources::GetResource(const ID& name) {
    return data.at(name);
}

bool TSceneResources::Empty() const {
	return data.empty();
}
