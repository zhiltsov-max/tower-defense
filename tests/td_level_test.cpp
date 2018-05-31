#include "gtest/gtest.h"
#include "GameEngine/game_engine.h"
#include "Game/Level/level.h"
#include "Game/Level/level_scene.h"


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

TEST_F(TestLevel, get_scene) {
    ASSERT_NO_THROW(level->GetScene());
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

    Custom = _min,

    _max,
    _count = _max - _min,

    _undefined
};

enum class GE::ComponentIDs : TComponentID {
    _min = 0,

    Custom = _min,

    _max,
    _count = _max - _min
};

class CustomComponent :
    public GE::TComponent
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


    int value;
};

namespace GE {
template<>
struct ComponentID< CustomComponent > {
    inline static const ComponentIDs value() { return ComponentIDs::Custom; }
};

template<>
struct ComponentClass< CustomComponent > {
    inline static const ComponentSystem value() {
        return ComponentSystem::Custom;
    }
};
} // namespace GE

class CSCustom :
    public GE::TComponentSystem
{
public:
    virtual void Update(const GE::TTime& step, Context& context) override
    { /*none*/ }

    virtual void HandleMessage(const GE::TMessage& message,
        const GE::TComponentHandle& sender, Context& context) override
    { /*none*/ }
};


CustomComponent::CustomComponent(const Parameters* parameters) :
    GE::TComponent(ComponentID<CustomComponent>::value()),
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
            AddSystem<CSCustom>(GE::ComponentSystem::Custom);

        GE::TComponentRegistry::Entry entry;
        entry.create = &CustomComponent::Create;
        entry.system = GE::ComponentClass<CustomComponent>::value();
        engine->GetComponentSystemsManager().GetComponentRegistry().
            Register(GE::ComponentID<CustomComponent>::value(), entry);

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
        GE::ComponentID<CustomComponent>::value(), nullptr));
}

TEST_F(TestLevelScene, create_component_with_custom_args_correct) {
    CustomComponent::Parameters parameters;
    parameters.value = 10;

    const auto handle = scene->CreateComponent(
        GE::ComponentID<CustomComponent>::value(), &parameters);

    ASSERT_FALSE(handle.IsNull());
    const auto* component = scene->GetComponent<CustomComponent>(handle);
    ASSERT_NE(nullptr, component);
    ASSERT_EQ(parameters.value, component->value);
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

    const auto handle = scene->CreateComponent<CustomComponent>(&parameters);

    ASSERT_FALSE(handle.IsNull());
    const auto* component = scene->GetComponent<CustomComponent>(handle);
    ASSERT_NE(nullptr, component);
    ASSERT_EQ(parameters.value, component->value);
}

TEST_F(TestLevelScene, remove_component_existing_component) {
    auto handle = scene->CreateComponent(
        GE::ComponentID<CustomComponent>::value(), nullptr);

    scene->RemoveComponent(handle);

    ASSERT_FALSE(scene->HasComponent(handle));
}

TEST_F(TestLevelScene, remove_component_unexisting_component_success) {
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
    struct OtherComponent : GE::TComponent {};
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

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
        ComponentID<CustomComponent>::value(), nullptr);
    const TLevelScene::ComponentPath path{"object1", "component1"};
    TLevelScene::Object object;
    object.AddComponent(path.second, handle);
    scene->AddSceneObject(path.first, std::move(object));

    ASSERT_EQ(handle, scene->FindComponent(path));
}

TEST_F(TestLevelScene, find_component_unexisting) {
    const TLevelScene::ComponentPath path{"object1", "component1"};

    ASSERT_EQ(TLevelScene::ComponentHandle::Undefined,
        scene->FindComponent(path));
}

TEST_F(TestLevelScene, find_scene_object_existing) {
    const auto name = "object1";
    const auto handle = scene->AddSceneObject(name);

    ASSERT_EQ(handle, scene->FindSceneObject(name));
}

TEST_F(TestLevelScene, find_scene_object_unexisting) {
    ASSERT_EQ(TLevelScene::ObjectHandle::Undefined,
        scene->FindSceneObject("1"));
}

TEST_F(TestLevelScene, get_scene_object_existing) {
    const auto handle = scene->AddSceneObject("object1");

    ASSERT_NO_THROW(scene->GetSceneObject(handle));
}

TEST_F(TestLevelScene, get_scene_object_unexisting) {
    ASSERT_ANY_THROW(scene->GetSceneObject(
        TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, find_scene_object_with_name_existing) {
    const auto name = "object1";
    scene->AddSceneObject(name);

    ASSERT_TRUE(scene->HasObject(name));
}

TEST_F(TestLevelScene, find_scene_object_with_name_unexisting) {
    ASSERT_FALSE(scene->HasObject("1"));
}

TEST_F(TestLevelScene, find_scene_object_with_handle_existing) {
    const auto name = "object1";
    const auto handle = scene->AddSceneObject(name);

    ASSERT_TRUE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, find_scene_object_with_handle_unexisting) {
    ASSERT_FALSE(scene->HasObject(TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, add_scene_object_with_unexisting_name) {
    const auto name = "object";

    const auto handle = scene->AddSceneObject(name);

    ASSERT_FALSE(handle.IsNull());
}

TEST_F(TestLevelScene, add_scene_object_with_existing_name_is_failure) {
    const auto name = "object";
    scene->AddSceneObject(name);

    ASSERT_ANY_THROW(scene->AddSceneObject(name));
}

TEST_F(TestLevelScene, add_scene_object_by_rvalue_success) {
    const auto name = "object";

    TLevelScene::Object object;
    scene->AddSceneObject(name, std::move(object));
}

TEST_F(TestLevelScene, remove_scene_object_by_handle_existing) {
    const auto name = "object";
    const auto handle = scene->AddSceneObject(name);

    scene->RemoveSceneObject(handle);

    ASSERT_FALSE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, remove_scene_object_by_handle_unexisting) {
    ASSERT_NO_THROW(scene->RemoveSceneObject(
        TLevelScene::ObjectHandle::Undefined));
}

TEST_F(TestLevelScene, remove_scene_object_by_name_existing) {
    const auto name = "object";
    const auto handle = scene->AddSceneObject(name);

    scene->RemoveSceneObject(handle);

    ASSERT_FALSE(scene->HasObject(handle));
}

TEST_F(TestLevelScene, remove_scene_object_by_name_unexisting) {
    ASSERT_NO_THROW(scene->RemoveSceneObject("name"));
}

TEST_F(TestLevelScene, clear_clears) {
    scene->CreateComponent(ComponentID<CustomComponent>::value(), nullptr);
    scene->AddSceneObject("object");

    scene->Clear();

    EXPECT_TRUE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_empty_when_empty) {
    ASSERT_TRUE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_not_empty_when_has_object) {
    scene->AddSceneObject("object");

    ASSERT_FALSE(scene->IsEmpty());
}

TEST_F(TestLevelScene, is_empty_not_empty_when_has_component) {
    scene->CreateComponent(ComponentID<CustomComponent>::value(), nullptr);

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
