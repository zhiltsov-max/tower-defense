#ifndef SCENE_RESOURCE_H
#define SCENE_RESOURCE_H

#include "Core/core.h"



namespace GE {


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


} //namespace GE

#endif //SCENE_RESOURCE_H
