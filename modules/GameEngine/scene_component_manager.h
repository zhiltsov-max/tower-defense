#ifndef SCENE_COMPONENT_MANAGER_H
#define SCENE_COMPONENT_MANAGER_H

#include "Core/core.h"
#include "GameEngine/scene_object.h"


namespace GE {

class TSceneComponentManager
{
public:
    using ComponentHandle = TSceneObject::ComponentHandle;

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
    using PGameEngine = TGameEngine *;
    PGameEngine engine;
};

template< class T >
T* TSceneComponentManager::GetComponent(
    const TSceneComponentManager::ComponentHandle& handle)
{
    return dynamic_cast<T*>(GetComponent(handle));
}

} //namespace GE

#endif // SCENE_COMPONENT_MANAGER_H
