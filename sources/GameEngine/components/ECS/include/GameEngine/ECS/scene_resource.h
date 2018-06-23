#ifndef SCENE_RESOURCE_H
#define SCENE_RESOURCE_H

#include "GameEngine/utility.h"


GE_BEGIN_ENGINE_NAMESPACE

using TSceneResourceTypeID = uint;
enum class SceneResourceTypeID : TSceneResourceTypeID;

std::ostream& operator << (std::ostream& os, const SceneResourceTypeID& id);

class TSceneResource
{
public:
    using TypeID = SceneResourceTypeID;

    const TypeID& GetType() const;

    virtual ~TSceneResource() = default;

protected:
    TSceneResource(const TypeID& type);
    TSceneResource(const TSceneResource& other) = default;
    TSceneResource& operator = (const TSceneResource& other) = default;

private:
    TypeID type;
};

GE_END_ENGINE_NAMESPACE

#endif //SCENE_RESOURCE_H
