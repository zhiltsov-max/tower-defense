#include "scene_resource.h"



std::ostream&operator <<(std::ostream& os, const SceneResourceTypeID& id) {
    return os << static_cast<TSceneResourceTypeID>(id);
}

const TSceneResource::TypeID&TSceneResource::GetType() const {
    return type;
}

TSceneResource::TSceneResource(const TypeID& type) :
    type(type)
{}
