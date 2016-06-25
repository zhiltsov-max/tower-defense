#ifndef SCENE_H
#define SCENE_H

#include "Core/core.h"
#include "GameEngine/game_engine.h"
#include "GameEngine/scene_component_manager.h"
#include "GameEngine/scene_object_container.h"
#include "GameEngine/scene_resources.h"


namespace GE {

class TScene
{
public:
    using ComponentManager = TSceneComponentManager;
    using ObjectManager = TSceneObjectContainer;
    using ResourceManager = TSceneResources;

    using Object = ObjectManager::SceneObject;
    using ObjectName = ObjectManager::SceneObjectName;
    using ObjectHandle = ObjectManager::ObjectHandle;
    using ComponentHandle = ComponentManager::ComponentHandle;
    using ComponentName = ObjectManager::SceneObject::ComponentName;
    using ComponentPath = std::pair<ObjectName, ComponentName>;

    ComponentHandle CreateComponent(const TComponent::ID& id,
        const ComponentSystem& system,
        const TComponentCreateArgs* args = nullptr
    );

    void RemoveComponent(const ComponentHandle& handle);

    ComponentHandle FindComponent(const ComponentPath& path) const;

    template <class T>
    T* GetComponent(const ComponentHandle& handle);
    TComponent* GetComponent(const ComponentHandle& handle);

    ObjectHandle FindSceneObject(const ObjectName& name) const;

    const Object& GetSceneObject(const ObjectHandle& handle) const;
    Object& GetSceneObject(const ObjectHandle& handle);

    bool HasObject(const ObjectName& name) const;
    bool HasObject(const ObjectHandle& handle) const;

    ObjectHandle GetHandle(const ObjectName& name) const;

    ObjectHandle AddSceneObject(const ObjectName& name,
        const Object& sceneObject);
    ObjectHandle AddSceneObject(const ObjectName& name, Object&& sceneObject);

    Object RemoveSceneObject(const ObjectName& name);
    Object RemoveSceneObject(const ObjectHandle& handle);

    void Clear();
    bool IsEmpty() const;

    void SetGameEngine(TGameEngine* instance);

    const ObjectManager& GetObjectManager() const;
    ObjectManager& GetObjectManager();

    const ComponentManager& GetComponentManager() const;
    ComponentManager& GetComponentManager();

    const ResourceManager& GetResourceManager() const;
    ResourceManager& GetResourceManager();

private:
    ComponentManager componentManager;
    ObjectManager objectManager;
    ResourceManager resourceManager;
};

template< class T >
T* TScene::GetComponent(const ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} //namespace GE

#endif // SCENE_H
