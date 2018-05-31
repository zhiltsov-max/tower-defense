#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <functional>
#include "GameEngine/component_systems_manager.h"
#include "GameEngine/free_list_allocator.h"
#include "GameEngine/observable_interface.h"


namespace GE {

struct TSceneObjectMessage;

class TSceneObject
{
public:
    using ComponentHandle = TComponentHandle;
    using ComponentName = string;
    using Entry = std::pair<ComponentName, ComponentHandle>;
private:
    using ComponentsAllocator = FreelistAllocator<Entry>;
public:
    using EntryHandle = ComponentsAllocator::Handle;
private:
    using NameMapping = std::map<ComponentName, EntryHandle>;
public:
    static const EntryHandle HandleUndefined;
    using EntryConstRange = std::pair<
        NameMapping::const_iterator,
        NameMapping::const_iterator
    >;
    using EntryRange = std::pair<NameMapping::iterator, NameMapping::iterator>;
    class Observable;

    TSceneObject();
    TSceneObject(const TSceneObject& other) = delete; // can't copy ownership
    TSceneObject& operator = (
        const TSceneObject& other) = delete; // can't copy ownership
    TSceneObject(TSceneObject&& other);
    TSceneObject& operator = (TSceneObject&& other);
    ~TSceneObject();

    const ComponentHandle& operator [] (const ComponentName& name) const;
    const ComponentHandle& operator [] (const EntryHandle& handle) const;

    EntryHandle GetHandle(const ComponentName& name) const;

    EntryHandle AddComponent(const ComponentName& name,
        const ComponentHandle& component);

    ComponentHandle RemoveComponent(const ComponentName& name);
    ComponentHandle RemoveComponent(const EntryHandle& handle);

    bool HasComponent(const ComponentName& name) const;
    bool HasComponent(const EntryHandle& handle) const;
    bool HasComponents() const;

    EntryConstRange EnumerateEntries() const;
    EntryRange EnumerateEntries();

    const Observable& AsObservable() const;
    Observable& AsObservable();

private:
    NameMapping nameMapping;
    ComponentsAllocator componentsAllocator;

public:
    class Observable :
        public IObservable<TSceneObjectMessage>
    {
    public:
        using ObserverNotifierFunction = void (const TSceneObjectMessage&);
        using ObserverNotifier = std::function<ObserverNotifierFunction>;

        Observable(TSceneObject* owner = nullptr);
        void SetOwner(TSceneObject* instance);

        void SetObserver(const ObserverNotifier& instance);
        void SetObserver(ObserverNotifier&& instance);

        virtual void Notify(const TSceneObjectMessage& message) override;

    private:
        using PSceneObject = TSceneObject*;
        PSceneObject owner;
        ObserverNotifier observerNotifierInstance;

        void handleObserverChange();
    };
private:
    Observable observable;

    void notifyComponentHandleAdded(const ComponentHandle& handle,
        const EntryHandle& entry);
    void notifyComponentHandleDeleted(const ComponentHandle& handle);
};

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
        TSceneObject::EntryHandle entry;
    };

    struct ComponentRemovedMessage {
        TComponentHandle component;
    };

    union {
        ComponentAddedMessage componentAdded;
        ComponentRemovedMessage componentRemoved;
    };

    TSceneObjectMessage(Type type = Type::Undefined) :
        type(type)
    {}
};

} // namespace GE

#endif // SCENE_OBJECT_H
