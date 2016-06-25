#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "GameEngine/component.h"
#include "GameEngine/scene.h"


namespace TD {

class TLevelScene
{
public:
    using Scene = GE::TScene;
    using Object = Scene::Object;
    using ObjectName = Scene::ObjectName;
    using ObjectHandle = Scene::ObjectHandle;
    using ComponentHandle = Scene::ComponentHandle;
    using ComponentName = Scene::ComponentName;
    using ComponentPath = Scene::ComponentPath;
    struct Parameters;

    TLevelScene(const Parameters& info, GE::GameEngine& engine);

    template<class Component>
    ComponentHandle CreateComponent(TComponentCreateArgs* args);
    ComponentHandle CreateComponent(const GE::TComponent::ID& id,
        const GE::TComponentCreateArgs* args = nullptr);
    void RemoveComponent(const ComponentHandle& handle);

    const TComponent* FindComponent(const ComponentPath& path) const;
    TComponent* FindComponent(const ComponentPath& path);

    template <class T>
    T* GetComponent(const ComponentHandle& handle);
    TComponent* GetComponent(const ComponentHandle& handle);

    const Object* FindSceneObject(const ObjectName& name) const;
    Object* FindSceneObject(const ObjectName& name);

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

    const Scene& GetRaw() const;
    Scene& GetRaw();

private:
    Scene scene;

    void loadResources(const Parameters& info);
    void loadObjects(const Parameters& info);
};

struct TLevelScene::Parameters
{
    struct ObjectInfo;
    vector<string> resources;
    vector<ObjectInfo> objects;
};

struct TComponentInfo
{
    TLevelScene::ComponentName name;
    GE::ComponentIDs id;
    std::unique_ptr<GE::TComponentCreateArgs> parameters;
};

struct TLevelScene::Parameters::ObjectInfo
{
    TLevelScene::ObjectName name;
    vector<TComponentInfo> components;
};


template<class Component>
TLevelScene::ComponentHandle
TLevelScene::CreateComponent(GE::TComponentCreateArgs* args) {
    return CreateComponent(static_cast<uint>(GE::ComponentID<Component>::value),
        args);
}

template<class T>
T* TLevelScene::GetComponent(const ComponentHandle& handle) {
    return dynamic_cast<T*>(GetComponent(handle));
}

} // namespace TD

#endif // LEVEL_SCENE_H
