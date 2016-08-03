#include "Game/Level/level.h"
#include "GameEngine/game_engine.h"


using namespace TD;

enum class GE::ComponentIDs : GE::TComponentID {
    _min = 0,

    CustomDataComponent = _min,
    CustomLogicsComponent,

    _max,
    _count = _max - _min
};

class CustomDataComponent :
    public GE::CDataComponent
{
public:
    struct Parameters : GE::TComponentCreateArgs
    {
        int value;
    };

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args_)
    {
        const auto* args = dynamic_cast<const Parameters*>(args_);
        return std::unique_ptr<GE::TComponent>(new CustomDataComponent(args));
    }

    CustomDataComponent(const Parameters* parameters);

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override { /* none */ }
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override {
        return forward_list<GE::TMessage::ID>();
    }

    int GetValue() const {
        return value;
    }

    void SetValue(int value) {
        this->value = value;
    }

protected:
    int value;
};

namespace GE {
template<>
struct ComponentID< CustomDataComponent > {
    static const ComponentIDs value;
};
const ComponentIDs ComponentID<CustomDataComponent>::value =
    ComponentIDs::CustomDataComponent;

template<>
struct ComponentClass< CustomDataComponent > {
    static const ComponentSystem value;
};
const ComponentSystem ComponentClass<CustomDataComponent>::value =
    ComponentSystem::data;
} //namespace GE

CustomDataComponent::CustomDataComponent(const Parameters* parameters) :
    CDataComponent(GE::ComponentID<CustomDataComponent>::value),
    value(0)
{
    if (parameters != nullptr) {
        value = parameters->value;
    }
}

class CustomLogicsComponent :
    public GE::CLogicsComponent
{
public:
    struct Parameters : GE::TComponentCreateArgs
    {
        TD::TLevelScene::ComponentPath dataComponentPath;
    };

    static std::unique_ptr<GE::TComponent> Create(
        const GE::TComponentCreateArgs* args_)
    {
        const auto* args = dynamic_cast<const Parameters*>(args_);
        return std::unique_ptr<GE::TComponent>(new CustomLogicsComponent(args));
    }

    CustomLogicsComponent(const Parameters* parameters);

    virtual void HandleMessage(const GE::TMessage& message,
        Context& context) override { /* none */ }
    virtual forward_list<GE::TMessage::ID> GetAcceptedMessages() const override {
        return forward_list<GE::TMessage::ID>();
    }

    virtual void Update(const GE::TTime& step, Context& context) override {
        if (dataComponentHandle.IsNull() == true) {
            dataComponentHandle = context.scene->FindComponent(dataComponentPath);
        }

        if (dataComponentHandle.IsNull() == false) {
            const auto* data = context.scene->GetComponent<CustomDataComponent>(
                dataComponentHandle);
            ASSERT(data != nullptr,
                "Unexpected comoponent class of data component");
            std::cout << data->GetValue() << std::endl;
        } else {
            std::cout << "Can not find component '"
                << dataComponentPath.first << ":"
                << dataComponentPath.second << "'" << std::endl;
        }
    }

private:
    TD::TLevelScene::ComponentHandle dataComponentHandle;
    TD::TLevelScene::ComponentPath dataComponentPath;
};

namespace GE {
template<>
struct ComponentID<CustomLogicsComponent> {
    static const ComponentIDs value;
};
const ComponentIDs ComponentID<CustomLogicsComponent>::value =
    ComponentIDs::CustomLogicsComponent;

template<>
struct ComponentClass<CustomLogicsComponent> {
    static const ComponentSystem value;
};
const ComponentSystem ComponentClass<CustomLogicsComponent>::value =
    ComponentSystem::logics;
} //namespace GE

CustomLogicsComponent::CustomLogicsComponent(const Parameters* parameters) :
    CLogicsComponent(GE::ComponentID<CustomLogicsComponent>::value),
    dataComponentHandle(),
    dataComponentPath()
{
    if (parameters != nullptr) {
        dataComponentPath = parameters->dataComponentPath;
    }
}


TD::TLevel::Parameters createLevelParameters() {
    TD::TLevel::Parameters parameters;
    parameters.common.levelCode = "";
    parameters.common.levelType = TD::TLevel::LevelType::Free;

    TD::TLevelScene::Parameters::ObjectInfo object1;
    object1.name = "object1";

    TD::TComponentInfo component1;
    component1.id = GE::ComponentID<CustomDataComponent>::value;
    component1.name = "custom1";
    component1.parameters = nullptr;
    object1.components.push_back(component1);

    TD::TComponentInfo component2;
    component2.id = GE::ComponentID<CustomLogicsComponent>::value;
    component2.name = "custom2";
    std::unique_ptr<CustomLogicsComponent::Parameters> component2parameters(
        new CustomLogicsComponent::Parameters);
    component2parameters->dataComponentPath = {object1.name, component1.name};
    component2.parameters = std::move(component2parameters);
    object1.components.push_back(component2);

    parameters.scene.objects.push_back(object1);

    return parameters;
}

int main(int argc, char ** argv) {
    UNUSED(argc);
    UNUSED(argv);

    GE::TGameEngine engine;

    GE::TComponentRegistry::Entry entry;
    entry.create = &CustomDataComponent::Create;
    entry.system = GE::ComponentClass<CustomDataComponent>::value;
    engine.GetComponentRegistry().Register(
        GE::ComponentID<CustomDataComponent>::value, entry);

    entry.create = &CustomLogicsComponent::Create;
    entry.system = GE::ComponentClass<CustomLogicsComponent>::value;
    engine.GetComponentRegistry().Register(
        GE::ComponentID<CustomLogicsComponent>::value, entry);

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
