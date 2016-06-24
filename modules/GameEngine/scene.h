#ifndef SCENE_H
#define SCENE_H

#include "Core/core.h"
#include "GameEngine/scene_resources.h"
#include "GameEngine/scene_object_container.h"


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

template< class T >
T* TScene::GetComponent(const TScene::ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} //namespace GE

#endif // SCENE_H
