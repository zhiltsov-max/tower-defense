#include "GameEngine/component_systems.h"
#include "GameEngine/game_engine.h"


namespace GE {

TComponentSystems::TComponentSystems(TGameEngine* engine) :
    engine(engine)
{}

void TComponentSystems::SetGameEngine(TGameEngine* instance) {
    engine = instance;
    for (auto& system : systems) {
        system.second->SetComponentRegistry(&instance->GetComponentRegistry());
    }
}

void TComponentSystems::Update(const TTime& step, Context& context) {
    for (auto& system : systems) {
        system.second->Update(step, context);
    }
}

TComponentSystem* TComponentSystems::AddSystem(const ID& id, PSystem&& system) {
    ASSERT(HasSystem(id) == false, "System already exists");
    auto* ptr = system.get();
    if (engine != nullptr) {
        system->SetComponentRegistry(&engine->GetComponentRegistry());
    }
    systems.emplace(id, std::move(system));
    return ptr;
}

bool TComponentSystems::HasSystem(const ID& id) const {
    return nullptr != FindSystem(id);
}

void TComponentSystems::RemoveSystem(const ID& id) {
    ASSERT(HasSystem(id) == true, "System does not exist");
    systems.erase(id);
}

const TComponentSystem* TComponentSystems::FindSystem(const ID& id) const {
    const auto it = systems.find(id);
    if (it != systems.cend()) {
        return (*it).second.get();
    } else {
        return nullptr;
    }
}

TComponentSystem* TComponentSystems::FindSystem(const ID& id) {
    const auto it = systems.find(id);
    if (it != systems.end()) {
        return (*it).second.get();
    } else {
        return nullptr;
    }
}

void TComponentSystems::SendMessage(const Message& message, Context& context) {
    for (auto& system : systems) {
        system.second->HandleMessage(message, context);
    }
}

const TComponentSystems::Systems& TComponentSystems::GetSystems() const {
    return systems;
}

TComponentSystems::Systems& TComponentSystems::GetSystems() {
    return systems;
}

} //namespace GE
