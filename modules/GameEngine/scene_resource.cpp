#include "scene_resource.h"
#include "scene_resource_loader.h"



const TSceneResource::TypeID& TSceneResource::GetType() const {
	return type;
}

const TSceneResource::Metadata& TSceneResource::GetMetadata() const {
    return metadata;
}

TSceneResource::PCData TSceneResource::GetData() const {
    return data;
}

TSceneResource::PData TSceneResource::GetData() {
    return data;
}

void TSceneResource::Load(const string& source) {
    Loader loader;
    loader.Load(source, *this);
}
