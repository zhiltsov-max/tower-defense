#ifndef SCENE_RESOURCES_H
#define SCENE_RESOURCES_H

#include "registry.h"
#include "scene_resource.h"



namespace GE {


using TSceneResourceID = string;

struct TSceneResourceCreateArgs
{
    virtual ~TSceneResourceCreateArgs() = default;
};

using TSceneResourceCreate =
    std::unique_ptr<TSceneResource> (*)(const TSceneResourceCreateArgs*);

using TSceneResourceRegistry =
    TRegistry< TSceneResourceCreate, TSceneResource::TypeID >;

class TSceneResources
{
public:
    using ID = TSceneResourceID;
    using Resource = TSceneResource;
    using PConstWeakResource = std::weak_ptr<const Resource>;
    using PWeakResource = std::weak_ptr<Resource>;


    PWeakResource LoadResource(
        const ID& id,
        const Resource::TypeID& type,
        const TSceneResourceCreateArgs* args = nullptr
    );
    void UnloadResource(const ID& id);

    PConstWeakResource GetResource(const ID& id) const;
    PWeakResource GetResource(const ID& id);

    void Clear();
    bool Empty() const;
    bool IsResourceLoaded(const ID& id) const;

    const TSceneResourceRegistry& GetRegistry() const;
    TSceneResourceRegistry& GetRegistry();

private:
    using PResource = std::shared_ptr<Resource>;
    using Resources = std::map<ID, PResource>;
    Resources resources;

    using Registry = TSceneResourceRegistry;
    Registry registry;
};


} //namespace GE

#endif //SCENE_RESOURCES_H
