#ifndef SCENE_H
#define SCENE_H

#include "Core/core.h"
#include "scene_resources.h"
#include "scene_object_container.h"



namespace GE {


class TScene
{
public:
    using SceneObjects = TSceneObjectContainer;
    using Resources = TSceneResources;
    using Handle = TSceneObject::ComponentHandle;


    virtual ~TScene() = default;

    const Resources& GetResources() const;
    Resources& GetResources();

    const SceneObjects& GetObjects() const;
    SceneObjects& GetObjects();

    Handle CreateComponent(
        const TComponent::ID& id,
        const ComponentSystem& componentClass,
        const TComponentCreateArgs* args = nullptr
    );
    template< class Component >
    Handle CreateComponent(TComponentCreateArgs* args);

    void RemoveComponent(const Handle& handle);

    TComponent* GetComponent(const Handle& handle);

    void SetGameEngine(TGameEngine* instance);

private:
    SceneObjects sceneObjects;
    Resources resources;

    using PGameEngine = TGameEngine *;
    PGameEngine engine;

};


template< class Component >
TScene::Handle TScene::CreateComponent(TComponentCreateArgs* args) {
    return CreateComponent(
        (uint)  ComponentID< Component >::value,
        ComponentClass< Component >::value,
        args
    );
}


} //namespace GE

#endif // SCENE_H
