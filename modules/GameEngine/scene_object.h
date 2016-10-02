#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <functional>
#include "GameEngine/component_systems_manager.h"
#include "GameEngine/free_list_allocator.h"
#include "GameEngine/observable_interface.h"


namespace GE {

struct TSceneObjectMessage
{
    enum class Type : uchar
    {
        Undefined = 0,
        ComponentAdded,
        ComponentRemoved,

        _max,
        _min = 0,
        _count = _max - _min
    };
    Type type;

    struct ComponentAddedMessage {
        TComponentHandle component;
    };

    struct ComponentRemovedMessage {
        TComponentHandle component;
    };

    union {
        ComponentAddedMessage componentAdded;
        ComponentRemovedMessage componentRemoved;
    };

    TSceneObjectMessage(TSceneObjectMessage::Type type = TSceneObjectMessage::Type::Undefined) :
        type(type)
    {}
};

class TSceneObject :
    public IObservable<TSceneObjectMessage>
{
private:
    struct Entry;
    using ComponentsAllocator = FreelistAllocator<Entry>;

public:
    using EntryHandle = ComponentsAllocator::Handle;
    static const EntryHandle HandleUndefined;
    using ComponentHandle = TComponentHandle;
    using ComponentName = string;

    TSceneObject();

    const ComponentHandle& operator [] (const ComponentName& name) const;
    ComponentHandle& operator [] (const ComponentName& name);

    const ComponentHandle& operator [] (const EntryHandle& handle) const;
    ComponentHandle& operator [] (const EntryHandle& handle);

    EntryHandle GetHandle(const ComponentName& name) const;

    EntryHandle AddComponent(const ComponentName& name,
        const ComponentHandle& component);

    ComponentHandle RemoveComponent(const ComponentName& name);
    ComponentHandle RemoveComponent(const EntryHandle& handle);

    bool HasComponent(const ComponentName& name) const;
    bool HasComponent(const EntryHandle& handle) const;
    bool HasComponents() const;

private:
    using NameMapping = std::map<ComponentName, EntryHandle>;
    NameMapping nameMapping;
    ComponentsAllocator componentsAllocator;

    // IObservable<TSceneObjectMessage> interface
public:
    virtual void Notify(const TSceneObjectMessage& message) override;
    using ObserverNotifier = std::function<void (const TSceneObjectMessage&)>;
    void SetObserver(ObserverNotifier instance);

private:
    ObserverNotifier observerNotifierInstance;
};

struct TSceneObject::Entry
{
    ComponentName name;
    ComponentHandle component;

    Entry(const ComponentName& name = ComponentName(),
        const ComponentHandle& handle = ComponentHandle::Undefined);
};

} // namespace GE

#endif // SCENE_OBJECT_H
