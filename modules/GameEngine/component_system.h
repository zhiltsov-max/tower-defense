#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "GameEngine/engine_core.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/component.h"
#include "GameEngine/component_registry.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TComponentHandle;

class TComponentSystem /*Abstract*/
{
public:
    using Handle = size_t;
    static const Handle HandleUndefined;
    using Component = TComponent;
    using Context = TGameEngineContext;

    TComponentSystem();
    virtual ~TComponentSystem() = default;

    Handle CreateComponent(const TComponent::ID& typeID,
        const TComponentCreateArgs* args = nullptr);

    bool HasComponent(const Handle& handle) const;

    void RemoveComponent(const Handle& handle);

    const Component* GetComponent(const Handle& handle) const;
    Component* GetComponent(const Handle& handle);

    bool IsEmpty() const;
    void Clear();

    virtual void Update(const TTime& step, Context& context) = 0;

    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) = 0;

    void SetComponentRegistry(TComponentRegistry* instance);

protected:
    using ComponentRegistry = TComponentRegistry;
    using PComponentRegistry = ComponentRegistry *;
    PComponentRegistry componentRegistry;

    using PComponent = std::unique_ptr<Component>;
    vector<PComponent> components;
};

} // namespace GE

#endif // COMPONENT_SYSTEM_H
