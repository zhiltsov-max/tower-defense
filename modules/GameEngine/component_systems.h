#ifndef COMPONENT_SYSTEMS_H
#define COMPONENT_SYSTEMS_H

#include "GameEngine/engine_message.h"
#include "GameEngine/component_system.h"
#include "GameEngine/game_engine_context.h"


namespace GE {

class TComponentSystems
{
public:
    using Message = TMessage;
    using ID = ComponentSystem;
    using Context = TGameEngineContext;
    using PSystem = std::unique_ptr<TComponentSystem>;

    TComponentSystems(TGameEngine* engine = nullptr);

    void SetGameEngine(TGameEngine* instance);

    void Update(const TTime& step, Context& context);

    TComponentSystem* AddSystem(const ID& id, PSystem&& system);

    template<class C>
    C* AddSystem(const ID& id);

    bool HasSystem(const ID& id) const;
    void RemoveSystem(const ID& id);

    const TComponentSystem* FindSystem(const ID& id) const;
    TComponentSystem* FindSystem(const ID& id);

    void SendMessage(const Message& message, Context& context);

public:
    //TODO: hide implementation
    using Systems = map<ID, PSystem>;
    const Systems& GetSystems() const;
    Systems& GetSystems();

private:
    using PGameEngine = TGameEngine *;
    PGameEngine engine;

    Systems systems;
};

template<class C>
C* TComponentSystems::AddSystem(const ID& id) {
    return dynamic_cast<C*>(AddSystem(id, std::move(PSystem(new C()))));
}

} //namespace GE

#endif // COMPONENT_SYSTEMS_H
