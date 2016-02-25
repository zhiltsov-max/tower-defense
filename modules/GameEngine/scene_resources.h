#ifndef SCENE_RESOURCES_H
#define SCENE_RESOURCES_H

#include "Core/core.h"
#include "scene_resource.h"



class TSceneResources
{
public:
    using ID = string;
    using Resource = TSceneResource;


    Resource& LoadResource(const ID& id);
    void UnloadResource(const ID& id);
		
    const Resource& GetResource(const ID& id) const;
    Resource& GetResource(const ID& id);

    void Clear();
    bool Empty() const;
    bool IsResourceLoaded(const ID& name) const;

private:
    using Data = std::map<ID, Resource>;
    Data data;
};


#endif //SCENE_RESOURCES_H
