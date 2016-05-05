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


    Resource& LoadResource(
        const ID& id,
        const Resource::TypeID& type,
        const TSceneResourceCreateArgs* args = nullptr
    );
    void UnloadResource(const ID& id);

    const Resource& GetResource(const ID& id) const;
    Resource& GetResource(const ID& id);

    void Clear();
    bool Empty() const;
    bool IsResourceLoaded(const ID& id) const;

    const TSceneResourceRegistry& GetRegistry() const;
    TSceneResourceRegistry& GetRegistry();

private:
    using Resources = std::map<ID, std::unique_ptr<Resource>>;
    Resources resources;

    using Registry = TSceneResourceRegistry;
    Registry registry;
};


} //namespace GE

#endif //SCENE_RESOURCES_H
