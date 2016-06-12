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
    using ComponentHandle = TSceneObject::ComponentHandle;


    virtual ~TScene() = default;

    const Resources& GetResources() const;
    Resources& GetResources();

    const SceneObjects& GetObjects() const;
    SceneObjects& GetObjects();

    ComponentHandle CreateComponent(
        const TComponent::ID& id,
        const ComponentSystem& componentClass,
        const TComponentCreateArgs* args = nullptr
    );
    template< class Component >
    ComponentHandle CreateComponent(TComponentCreateArgs* args);

    void RemoveComponent(const ComponentHandle& handle);

    TComponent* GetComponent(const ComponentHandle& handle);
    template <class T>
    T* GetComponent(const ComponentHandle& handle);

    void SetGameEngine(TGameEngine* instance);

private:
    SceneObjects sceneObjects;
    Resources resources;

    using PGameEngine = TGameEngine *;
    PGameEngine engine;

};


template< class Component >
TScene::ComponentHandle TScene::CreateComponent(TComponentCreateArgs* args) {
    return CreateComponent(
        static_cast<uint>(ComponentID<Component>::value),
        ComponentClass<Component>::value,
        args
    );
}

template< class T >
TScene::T* TScene::GetComponent(const TScene::ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} //namespace GE

#endif // SCENE_H
