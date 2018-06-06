#include "Game/Level/level.h"
#include "GameEngine/game_engine.h"


using namespace TD;

enum class GE::ComponentSystem : GE::TComponentSystemTypeId {
    _min = 0,

    Custom = _min,

    _max,
    _count = _max - _min,

    _undefined
};


enum class GE::ComponentIDs : GE::TComponentID {
    _min = 0,

    CustomComponent = _min,

    _max,
    _count = _max - _min
};


struct CustomComponent : GE::TComponent
{
    struct Parameters : GE::TComponentCreateArgs
    {
        int value;
    };

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args_)
    {
        const auto* args = dynamic_cast<const Parameters*>(args_);
        return std::unique_ptr<GE::TComponent>(new CustomComponent(args));
    }

    CustomComponent(const Parameters* parameters);


    int value;
};

class CSCustom :
    public GE::TComponentSystem
{
public:
    virtual void Update(const GE::TTime& step, Context& context) override {
        for (auto& component : components) {
            ASSERT(component != nullptr, "Expected component.");
            ASSERT(component->GetID() == GE::ComponentIDs::CustomComponent,
                "Expected 'CustomComponent' component.");

            auto* customComponent =
                static_cast<CustomComponent*>(component.get());
            std::cout << customComponent->value << std::endl;
        }
    }

    virtual void HandleMessage(const GE::TMessage& message,
        const GE::TComponentHandle& sender, Context& context) override { /*none*/ }
};

namespace GE {
template<>
struct ComponentID< CustomComponent > {
    static const ComponentIDs value;
};
const ComponentIDs ComponentID<CustomComponent>::value =
    ComponentIDs::CustomComponent;

template<>
struct ComponentClass< CustomComponent > {
    static const ComponentSystem value;
};
const ComponentSystem ComponentClass<CustomComponent>::value =
    ComponentSystem::Custom;
} // namespace GE

CustomComponent::CustomComponent(const Parameters* parameters) :
    TComponent(GE::ComponentID<CustomComponent>::value),
    value(0)
{
    if (parameters != nullptr) {
        value = parameters->value;
    }
}


TD::TLevel::Parameters createLevelParameters() {
    TD::TLevel::Parameters parameters;
    parameters.common.levelCode = "";
    parameters.common.levelType = TD::TLevel::LevelType::Free;

    TD::TLevelScene::Parameters::ObjectInfo object1;
    object1.name = "object1";

    TD::TComponentInfo component1;
    component1.id = GE::ComponentID<CustomComponent>::value;
    component1.name = "custom1";
    component1.parameters = nullptr;
    object1.components.push_back(component1);

    parameters.scene.objects.push_back(object1);

    return parameters;
}

int main(int argc, char ** argv) {
    UNUSED(argc);
    UNUSED(argv);

    GE::TGameEngine engine;
    engine.GetComponentSystemsManager().
        AddSystem<CSCustom>(GE::ComponentSystem::Custom);

    GE::TComponentRegistry::Entry entry;
    entry.create = &CustomComponent::Create;
    entry.system = GE::ComponentClass<CustomComponent>::value;
    engine.GetComponentSystemsManager().GetComponentRegistry().
        Register(GE::ComponentID<CustomComponent>::value, entry);

    const TD::TLevel::Parameters levelParameters = createLevelParameters();
    TD::TLevel level(levelParameters, &engine);
    level.GetClock().SetRate(TD::TLevelClock::Rate::First);

    while (std::getchar() != 'q') {
        std::cout << "Update started:" << std::endl;
        level.Update();
        std::cout << "Update ended." << std::endl;
    }

    return 0;
}
