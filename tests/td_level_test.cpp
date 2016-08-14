#include "gtest/gtest.h"
#include "GameEngine/game_engine.h"
#include "Game/Level/level.h"
#include "Game/Level/level_scene.h"
#include "GameEngine/ComponentSystems/component_system_data.h"


using namespace GE;
using namespace TD;

// ### Level tests ###

class TestLevel :
    public ::testing::Test
{
public:
    TestLevel() :
        ::testing::Test(),
        engine(nullptr),
        level(nullptr)
    {}

    virtual void SetUp() override {
        engine.reset(new GE::TGameEngine);
        level.reset(new TD::TLevel(generateInfo(), engine.get()));
    }

protected:
    static TLevel::Parameters generateInfo() {
        return TLevel::Parameters();
    }

    std::unique_ptr<GE::TGameEngine> engine;
    std::unique_ptr<TD::TLevel> level;
};


TEST(LevelTest, ctor_correct) {
    const TLevel::Parameters info{};
    TGameEngine engine;

    ASSERT_NO_THROW(TLevel(info, &engine));
}

TEST(LevelTest, ctor_with_null_engine_correct) {
    const TLevel::Parameters info{};

    ASSERT_NO_THROW(TLevel(info, nullptr));
}

TEST_F(TestLevel, get_clock) {
    ASSERT_NO_THROW(level->GetClock());
}

TEST_F(TestLevel, get_clock_const) {
    ASSERT_NO_THROW(const_cast<const TD::TLevel*>(level.get())->GetClock());
}

TEST_F(TestLevel, get_scene) {
    ASSERT_NO_THROW(level->GetScene());
}

TEST_F(TestLevel, get_clock_scene) {
    ASSERT_NO_THROW(const_cast<const TD::TLevel*>(level.get())->GetScene());
}

TEST_F(TestLevel, set_game_engine) {
    ASSERT_NO_THROW(level->SetGameEngine(engine.get()));
}

TEST_F(TestLevel, set_game_engine_with_null) {
    ASSERT_NO_THROW(level->SetGameEngine(nullptr));
}

TEST_F(TestLevel, update_0_tick) {
    level->GetClock().SetRate(TLevelClock::Rate::Pause);
    ASSERT_NO_THROW(level->Update());
}

TEST_F(TestLevel, update_1_tick) {
    level->GetClock().SetRate(TLevelClock::Rate::First);
    ASSERT_NO_THROW(level->Update());
}

TEST_F(TestLevel, update_max_tick) {
    level->GetClock().SetRate(TLevelClock::Rate::_max);
    ASSERT_NO_THROW(level->Update());
}


// ### LevelScene tests ###

enum class GE::ComponentSystem : GE::TComponentSystemTypeId {
    _min = 0,

    Data = _min,

    _max,
    _count = _max - _min,

    _undefined
};

enum class GE::ComponentIDs : TComponentID {
    _min = 0,

    CustomComponent = _min,

    _max,
    _count = _max - _min
};

class CustomComponent :
    public GE::CDataComponent
{
public:
    struct Parameters : GE::TComponentCreateArgs
    {
        int value;
    };

    static std::unique_ptr<GE::TComponent> Create(
        const TComponentCreateArgs* args_)
    {
        const auto* args = dynamic_cast<const Parameters*>(args_);
        return std::unique_ptr<GE::TComponent>(new CustomComponent(args));
    }

    CustomComponent(const Parameters* parameters);

    virtual void HandleMessage(const TMessage& message,
        Context& context) override { /* none */ }
    virtual forward_list<TMessage::ID> GetAcceptedMessages() const override {
        return forward_list<TMessage::ID>();
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
    ComponentSystem::Data;
} //namespace GE

CustomComponent::CustomComponent(const CustomComponent::Parameters* parameters) :
    GE::CDataComponent(ComponentID<CustomComponent>::value),
    value(0)
{
    if (parameters != nullptr) {
        value = parameters->value;
    }
}


class TestLevelScene :
    public ::testing::Test
{
public:
    TestLevelScene() :
        ::testing::Test(),
        engine(nullptr),
        scene(nullptr)
    {}

    virtual void SetUp() override {
        engine.reset(new GE::TGameEngine());
        engine->GetComponentSystemsManager().
            AddSystem<GE::CSDataSystem>(GE::ComponentSystem::Data);

        GE::TComponentRegistry::Entry entry;
        entry.create = &CustomComponent::Create;
        entry.system = GE::ComponentClass<CustomComponent>::value;
        engine->GetComponentSystemsManager().GetComponentRegistry().
            Register(GE::ComponentID<CustomComponent>::value, entry);

        scene.reset(new TD::TLevelScene(generateInfo(), engine.get()));
    }

protected:
    static TLevelScene::Parameters generateInfo() {
        return TLevelScene::Parameters();
    }

    std::unique_ptr<GE::TGameEngine> engine;
    std::unique_ptr<TD::TLevelScene> scene;
};

TEST(LevelSceneTest, ctor_correct) {
    GE::TGameEngine engine;
    ASSERT_NO_THROW(TD::TLevelScene(TLevelScene::Parameters(), &engine));
}

TEST(LevelSceneTest, ctor_with_null_engine_correct) {
    ASSERT_NO_THROW(TD::TLevelScene(TLevelScene::Parameters(), nullptr));
}

TEST_F(TestLevelScene, create_component_with_default_args_correct) {
    ASSERT_NO_THROW(scene->CreateComponent(
        GE::ComponentID<CustomComponent>::value, nullptr));
}

TEST_F(TestLevelScene, create_component_with_custom_args_correct) {
    CustomComponent::Parameters parameters;
    parameters.value = 10;

    TLevelScene::ComponentHandle handle;
    ASSERT_NO_THROW(handle = scene->CreateComponent(
        GE::ComponentID<CustomComponent>::value, &parameters));

    const auto* component = scene->GetComponent<CustomComponent>(handle);
    EXPECT_NE(nullptr, component);
    EXPECT_EQ(parameters.value, component->GetValue());
}

TEST_F(TestLevelScene, create_component_unregistered_incorrect) {
    ASSERT_ANY_THROW(scene->CreateComponent(GE::ComponentIDs::_count, nullptr));
}

TEST_F(TestLevelScene, create_component_by_template_with_default_args_correct) {
    ASSERT_NO_THROW(scene->CreateComponent<CustomComponent>(nullptr));
}

TEST_F(TestLevelScene, create_component_by_template_with_custom_args_correct) {
    CustomComponent::Parameters parameters;
    parameters.value = 10;

    TLevelScene::ComponentHandle handle;
    ASSERT_NO_THROW(
        handle = scene->CreateComponent<CustomComponent>(&parameters));

    const auto* component = scene->GetComponent<CustomComponent>(handle);
    EXPECT_NE(nullptr, component);
    EXPECT_EQ(parameters.value, component->GetValue());
}

TEST_F(TestLevelScene, remove_component_existing_component) {
    const auto handle = scene->CreateComponent(
        GE::ComponentID<CustomComponent>::value, nullptr);

    ASSERT_NO_THROW(scene->RemoveComponent(handle));
    EXPECT_FALSE(scene->HasComponent(handle));
}

TEST_F(TestLevelScene, remove_component_unexisting_component) {
    const auto handle = TLevelScene::ComponentHandle::Undefined;

    ASSERT_NO_THROW(scene->RemoveComponent(handle));
}

TEST_F(TestLevelScene, get_component_and_cast_existing) {
    const auto handle = scene->CreateComponent<CustomComponent>(nullptr);

    ASSERT_NE(nullptr, scene->GetComponent<CustomComponent>(handle));
}

TEST_F(TestLevelScene, get_component_and_cast_unexisting_handle) {
    const auto handle = TLevelScene::ComponentHandle::Undefined;

    ASSERT_EQ(nullptr, scene->GetComponent<CustomComponent>(handle));
}

TEST_F(TestLevelScene, get_component_and_cast_wrong_class) {
    class OtherComponent : GE::TComponent {
        virtual void HandleMessage(const GE::TMessage& message,
            Context& context) override {}
        virtual forward_list<GE::TMessage::ID>
            GetAcceptedMessages() const override
        {
            return forward_list<GE::TMessage::ID>();
        }
    };
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    ASSERT_EQ(nullptr, scene->GetComponent<OtherComponent>(handle));
}

TEST_F(TestLevelScene, get_component_existing) {
    const auto handle = scene->CreateComponent<CustomComponent>(nullptr);

    ASSERT_NE(nullptr, scene->GetComponent(handle));
}

TEST_F(TestLevelScene, get_component_unexisting_handle) {
    const auto handle = TLevelScene::ComponentHandle::Undefined;

    ASSERT_EQ(nullptr, scene->GetComponent(handle));
}

TEST_F(TestLevelScene, find_component_existing) {
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);
    const TLevelScene::ComponentPath path{"object1", "component1"};
    TLevelScene::Object object;
    object.AddComponent(path.second, handle);
    scene->AddSceneObject(path.first, object);

    ASSERT_EQ(handle, scene->FindComponent(path));
}

TEST_F(TestLevelScene, find_component_unexisting) {
    const TLevelScene::ComponentPath path{"object1", "component1"};

    ASSERT_EQ(TLevelScene::ComponentHandle::Undefined,
        scene->FindComponent(path));
}

TEST_F(TestLevelScene, find_scene_object_existing) {
    const auto name = "object1";
    TLevelScene::Object object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_EQ(handle, scene->FindSceneObject(name));
}

TEST_F(TestLevelScene, find_scene_object_unexisting) {
    ASSERT_EQ(TLevelScene::ObjectHandle::Undefined,
        scene->FindSceneObject("1"));
}

TEST_F(TestLevelScene, get_scene_object_existing) {
    TLevelScene::Object object;
    const auto handle = scene->AddSceneObject("object1", object);

    ASSERT_NO_THROW(scene->GetSceneObject(handle));
}

TEST_F(TestLevelScene, get_scene_object_unexisting) {
    ASSERT_ANY_THROW(scene->GetSceneObject(
        TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, find_scene_object_with_name_existing) {
    const auto name = "object1";
    TLevelScene::Object object;
    scene->AddSceneObject(name, object);

    ASSERT_TRUE(scene->HasObject(name));
}

TEST_F(TestLevelScene, find_scene_object_with_name_unexisting) {
    ASSERT_FALSE(scene->HasObject("1"));
}

TEST_F(TestLevelScene, find_scene_object_with_handle_existing) {
    const auto name = "object1";
    TLevelScene::Object object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_TRUE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, find_scene_object_with_handle_unexisting) {
    ASSERT_FALSE(scene->HasObject(TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, add_scene_object_with_unexisting_name) {
    const auto name = "object";
    TLevelScene::Object object;
    TLevelScene::ObjectHandle handle;

    ASSERT_NO_THROW(handle = scene->AddSceneObject(name, object));

    EXPECT_TRUE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, add_scene_object_with_existing_name_is_failure) {
    const auto name = "object";
    TLevelScene::Object object;

    scene->AddSceneObject(name, object);
    ASSERT_ANY_THROW(scene->AddSceneObject(name, object));
}

TEST_F(TestLevelScene, add_scene_object_by_rvalue) {
    const auto name = "object";
    TLevelScene::Object object;

    ASSERT_NO_THROW(scene->AddSceneObject(name, std::move(object)));
}

TEST_F(TestLevelScene, remove_scene_object_by_handle_existing) {
    const auto name = "object";
    TLevelScene::Object object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_NO_THROW(scene->RemoveSceneObject(handle));
    EXPECT_FALSE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, remove_scene_object_by_handle_unexisting) {
    ASSERT_NO_THROW(scene->RemoveSceneObject(
        TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, remove_scene_object_by_name_existing) {
    const auto name = "object";
    TLevelScene::Object object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_NO_THROW(scene->RemoveSceneObject(handle));
    EXPECT_FALSE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, remove_scene_object_by_name_unexisting) {
    ASSERT_NO_THROW(scene->RemoveSceneObject("name"));
}

TEST_F(TestLevelScene, clear_clears) {
    scene->CreateComponent(ComponentID<CustomComponent>::value, nullptr);
    scene->AddSceneObject("object", TLevelScene::Object());

    scene->Clear();

    EXPECT_TRUE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_empty_when_empty) {
    ASSERT_TRUE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_not_empty_when_has_object) {
    scene->AddSceneObject("object", TLevelScene::Object());

    ASSERT_FALSE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_not_empty_when_has_component) {
    scene->CreateComponent(ComponentID<CustomComponent>::value, nullptr);

    ASSERT_FALSE(scene->IsEmpty());
}

TEST(LevelSceneTest, set_game_engine) {
    GE::TGameEngine engine;
    TLevelScene scene(TLevelScene::Parameters(), &engine);

    EXPECT_NO_THROW(scene.SetGameEngine(&engine));
}

TEST(LevelSceneTest, set_game_engine_with_nullptr) {
    TLevelScene scene(TLevelScene::Parameters(), nullptr);

    EXPECT_NO_THROW(scene.SetGameEngine(nullptr));
}

TEST_F(TestLevelScene, update) {
    ASSERT_NO_THROW(scene->Update(TLevelClock::tick()));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
