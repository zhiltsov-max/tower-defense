#include "gtest/gtest.h"
#include "GameEngine/game_engine.h"
#include "GameEngine/registry.h"
#include "GameEngine/engine_message.h"
#include "GameEngine/component.h"
#include "GameEngine/component_systems_manager.h"
#include "GameEngine/engine_messages.h"
#include "GameEngine/scene_object.h"
#include "GameEngine/scene_object_container.h"
#include "GameEngine/scene_resources.h"
#include "GameEngine/scene.h"


using namespace GE;

// ### REGISTRY TESTS ###

class TestRegistry :
    public ::testing::Test
{
protected:
    using Entry = int;
    using ID = int;
    using Registry = TRegistry<Entry, ID>;
};

TEST_F(TestRegistry, register_unexisting_item) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;

    ASSERT_NO_THROW(registry.Register(id, entry));

    EXPECT_TRUE(registry.IsRegistered(id));
    EXPECT_EQ(entry, registry[id]);
}

TEST_F(TestRegistry, register_existing_item) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;
    registry.Register(id, entry);

    ASSERT_ANY_THROW(registry.Register(id, entry));
}

TEST_F(TestRegistry, unregister_existing_item) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;
    registry.Register(id, entry);

    ASSERT_NO_THROW(registry.Unregister(id));

    EXPECT_FALSE(registry.IsRegistered(id));
}

TEST_F(TestRegistry, unregister_unexisting_item) {
    Registry registry;

    ASSERT_ANY_THROW(registry.Unregister(100));
}

TEST_F(TestRegistry, is_empty_empty_when_empty) {
    Registry registry;

    ASSERT_TRUE(registry.IsEmpty());
}

TEST_F(TestRegistry, is_empty_not_empty_when_not_empty) {
    Registry registry;
    ID id = 6;
    Entry entry = 100500;
    registry.Register(id, entry);

    ASSERT_FALSE(registry.IsEmpty());
}

TEST_F(TestRegistry, size_zero_when_empty) {
    Registry registry;

    ASSERT_EQ(0u, registry.Size());
}

TEST_F(TestRegistry, size_not_zero_when_not_empty) {
    Registry registry;
    const size_t count = 4;
    ID ids[count] = {5, 6, 10, 12};
    Entry entries[count] = {-10, 1, 50, 7};
    for(size_t i = 0; i < count; ++i) {
        registry.Register(ids[i], entries[i]);
    }

    ASSERT_EQ(count, registry.Size());
}

TEST_F(TestRegistry, clear_clears) {
    Registry registry;
    const size_t count = 4;
    ID ids[count] = {5, 6, 10, 12};
    Entry entries[count] = {-10, 1, 50, 7};
    for(size_t i = 0; i < count; ++i) {
        registry.Register(ids[i], entries[i]);
    }

    registry.Clear();

    EXPECT_TRUE(registry.IsEmpty());
}

// ### COMPONENT SYSTEM TESTS ###

enum class GE::ComponentSystem : TComponentSystemTypeId {
    _min = 0,

    Custom = _min,

    _max,
    _count = _max - _min,

    _undefined
};

enum class GE::ComponentIDs : TComponentID {
    _min = 0,

    TestComponent = _min,
    CustomComponent,

    _max,
    _count = _max - _min
};

enum class GE::MessageID : TMessageID {
    _min = static_cast<TMessageID>(DefaultMessageID::_max) + 1,

    CustomMessage = _min,
    CustomUnexpectedMessage,
    TestMessage,

    _max,
    _count = _max - _min
};

// === Message Tests ===

class TestMessage :
    public ::testing::Test,
    protected TMessage
{
public:
    TestMessage() :
        ::testing::Test(),
        TMessage(MessageID::TestMessage)
    {}
};

TEST_F(TestMessage, get_id) {
    EXPECT_EQ(MessageID::TestMessage, GetID());
}

// === MessageSystem Tests ===

class TestMessageSystem :
    public ::testing::Test,
    protected TMessageSystem
{
protected:
    bool HasSubscription(const ComponentHandle& source,
        const ComponentHandle& listener) const
    {
        return (routingTable.count(source) != 0) &&
            (FindListener(routingTable.at(source), listener)
                != routingTable.at(source).cend());
    }

    bool HasSubscription(const ComponentHandle& source,
        const ComponentHandle& listener, const MessageID& messageId) const
    {
        if (HasSubscription(source, listener) == false) {
            return false;
        } else {
            const auto& subscriptions = FindListener(
                routingTable.at(source), listener)->second;
            return subscriptions.cend() !=
                FindSubscription(subscriptions, messageId);
        }
    }
};

TEST_F(TestMessageSystem, subscribe_component_to_other) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender(10, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};

    Subscribe(sender, listener, message, handler);

    EXPECT_TRUE(HasSubscription(sender, listener, message));
}

TEST_F(TestMessageSystem, subscribe_component_to_other_without_callback_failure) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender(10, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    MessageCallback handler;

    ASSERT_ANY_THROW(Subscribe(sender, listener, message, handler));
}

TEST_F(TestMessageSystem, subscribe_component_to_global) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender = ComponentHandle::Undefined;
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};

    Subscribe(sender, listener, message, handler);

    EXPECT_TRUE(HasSubscription(sender, listener, message));
}

TEST_F(TestMessageSystem, unsubscribe_component_from_other_message) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender(10, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};
    Subscribe(sender, listener, message, handler);

    Unsubscribe(sender, listener, message);

    EXPECT_FALSE(HasSubscription(sender, listener, message));
}

TEST_F(TestMessageSystem, unsubscribe_component_from_other) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender(10, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};
    Subscribe(sender, listener, message, handler);

    Unsubscribe(sender, listener);

    EXPECT_FALSE(HasSubscription(sender, listener));
}

TEST_F(TestMessageSystem, unsubscribe_component_from_all) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender1(10, ComponentSystem::Custom);
    const ComponentHandle sender2(15, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};
    Subscribe(sender1, listener, message, handler);
    Subscribe(sender2, listener, message, handler);

    Unsubscribe(listener);

    EXPECT_FALSE(HasSubscription(sender1, listener));
    EXPECT_FALSE(HasSubscription(sender2, listener));
}

TEST_F(TestMessageSystem, unsubscribe_all_from_component) {
    const auto message = MessageID::TestMessage;
    const ComponentHandle sender(10, ComponentSystem::Custom);
    const ComponentHandle listener(20, ComponentSystem::Custom);
    auto handler = [] (const ComponentHandle&, const TMessage&, Context&) {};
    Subscribe(sender, listener, message, handler);

    UnsubscribeFrom(sender);

    EXPECT_FALSE(HasSubscription(sender, listener));
}

// === Component Tests ===

struct TestComponent : TComponent
{
    TestComponent();
};

namespace GE {
template <>
struct ComponentID<TestComponent>
{
    inline static constexpr ComponentIDs value() {
        return ComponentIDs::TestComponent;
    }
};
} // namespace GE
TestComponent::TestComponent() :
    TComponent(ComponentID<TestComponent>::value())
{}


TEST(ComponentTest, ctor) {
    const auto id = ComponentIDs::TestComponent;

    const TestComponent component;

    EXPECT_EQ(id, component.GetID());
}

TEST(ComponentTest, get_id) {
    const auto id = ComponentIDs::TestComponent;
    const TestComponent component;

    ASSERT_EQ(id, component.GetID());
}

TEST(ComponentTest, operator_print_to_stream) {
    const ComponentIDs id = ComponentIDs::TestComponent;
    std::stringstream ss;

    ss << id;

    ASSERT_FALSE(ss.str().empty());
}

// === ComponentSystem Tests ===

struct CustomComponent : TComponent
{
    struct Parameters : GE::TComponentCreateArgs
    {
        int value;
    };

    static std::unique_ptr<TComponent> Create(
        const TComponentCreateArgs* args_)
    {
        const auto* args = dynamic_cast<const Parameters*>(args_);
        return std::unique_ptr<TComponent>(new CustomComponent(args));
    }

    CustomComponent(const Parameters* parameters);


    int value;
};

namespace GE {
template<>
struct ComponentID< CustomComponent > {
    inline static const ComponentIDs value() {
        return ComponentIDs::CustomComponent;
    }
};

template<>
struct ComponentClass< CustomComponent > {
    inline static const ComponentSystem value() {
        return ComponentSystem::Custom;
    }
};
} // namespace GE

CustomComponent::CustomComponent(const Parameters* parameters) :
    TComponent(ComponentID<CustomComponent>::value()),
    value(0)
{
    if (parameters != nullptr) {
        value = parameters->value;
    }
}


class TestComponentSystem :
    public ::testing::Test,
    public TComponentSystem
{
protected:
    virtual void SetUp() override {
        SetComponentRegistry(nullptr);

        testRegistry.Clear();

        TComponentRegistry::Entry customComponentEntry;
        customComponentEntry.create = &CustomComponent::Create;
        customComponentEntry.system = ComponentClass<CustomComponent>::value();
        testRegistry.Register(ComponentIDs::CustomComponent,
            customComponentEntry);

        SetComponentRegistry(&testRegistry);
    }

    virtual void Update(const TTime& step,
        Context& context) override { /*none*/ }
    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) override { /*none*/ }

private:
    TComponentRegistry testRegistry;
};


TEST_F(TestComponentSystem, create_component_positive) {
    ASSERT_NO_THROW(CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr));
}

TEST_F(TestComponentSystem, create_component_negative) {
    ASSERT_ANY_THROW(CreateComponent(ComponentIDs::_count, nullptr));
}

TEST_F(TestComponentSystem, has_component_existing) {
    const auto handle = CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_TRUE(HasComponent(handle));
}

TEST_F(TestComponentSystem, has_component_unexisting) {
    ASSERT_FALSE(HasComponent(HandleUndefined));
}

TEST_F(TestComponentSystem, remove_component_existing) {
    const auto handle = CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_NO_THROW(RemoveComponent(handle));

    EXPECT_EQ(0u, components.size());
}

TEST_F(TestComponentSystem, remove_component_unexisting) {
    ASSERT_NO_THROW(RemoveComponent(HandleUndefined));
}

TEST_F(TestComponentSystem, get_component_existing) {
    const auto handle = CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_NE(nullptr, GetComponent(handle));
}

TEST_F(TestComponentSystem, get_component_unexisting) {
    ASSERT_EQ(nullptr, GetComponent(HandleUndefined));
}

TEST_F(TestComponentSystem, clear_clears) {
    CreateComponent(ComponentID<CustomComponent>::value(), nullptr);

    Clear();

    EXPECT_TRUE(IsEmpty());
}

TEST_F(TestComponentSystem, is_empty_empty_when_empty) {
    ASSERT_TRUE(IsEmpty());
}

TEST_F(TestComponentSystem, is_empty_not_empty_when_not_empty) {
    CreateComponent(ComponentID<CustomComponent>::value(), nullptr);
    ASSERT_FALSE(IsEmpty());
}

// === ComponentSystemsManager Tests ===

class CustomComponentSystem : public TComponentSystem
{
public:
    virtual void Update(const TTime& step, Context& context) { /*none*/ }
    virtual void HandleMessage(const TMessage& message,
        const TComponentHandle& sender, Context& context) override { /*none*/ }
};


TEST(ComponentSystemsManagerTest, add_system) {
    std::unique_ptr<TComponentSystem> system(new CustomComponentSystem);
    const auto* ptr = system.get();
    TComponentSystemsManager systems;

    ASSERT_EQ(ptr, systems.AddSystem(
        ComponentSystem::Custom, std::move(system)));
}

TEST(ComponentSystemsManagerTest, add_system_by_template) {
    TComponentSystemsManager systems;

    ASSERT_NE(nullptr, systems.AddSystem<CustomComponentSystem>(
        ComponentSystem::Custom));
}

TEST(ComponentSystemsManagerTest, remove_system_existing) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;
    systems.AddSystem<CustomComponentSystem>(id);

    ASSERT_NO_THROW(systems.RemoveSystem(id));

    EXPECT_FALSE(systems.HasSystem(id));
}

TEST(ComponentSystemsManagerTest, remove_system_unexisting_failure) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;

    ASSERT_ANY_THROW(systems.RemoveSystem(id));
}

TEST(ComponentSystemsManagerTest, has_system_has_existing) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;
    systems.AddSystem<CustomComponentSystem>(id);

    ASSERT_TRUE(systems.HasSystem(id));
}

TEST(ComponentSystemsManagerTest, has_system_has_not_unexisting) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;

    ASSERT_FALSE(systems.HasSystem(id));
}

TEST(ComponentSystemsManagerTest, find_system_existing_success) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;
    const auto* ptr = systems.AddSystem<CustomComponentSystem>(id);

    ASSERT_EQ(ptr, systems.FindSystem(id));
}

TEST(ComponentSystemsManagerTest, find_system_unexisting_failure) {
    const auto id = ComponentSystem::Custom;
    TComponentSystemsManager systems;

    ASSERT_EQ(nullptr, systems.FindSystem(id));
}

TEST(ComponentSystemsManagerTest, send_message_with_sender) {
    class CustomMessage : public TMessage {
    public:
        CustomMessage() : TMessage(MessageID::CustomMessage) {}
    };
    CustomMessage message;
    TGameEngine engine;
    TScene scene;
    TGameEngineContext context{&engine, &scene};
    TComponentSystemsManager::ComponentHandle sender{10, ComponentSystem::Custom};
    TComponentSystemsManager systems;

    ASSERT_NO_THROW(systems.SendMessage(message, context, sender));
}

TEST(ComponentSystemsManagerTest, send_message_without_sender) {
    class CustomMessage : public TMessage {
    public:
        CustomMessage() : TMessage(MessageID::CustomMessage) {}
    };
    CustomMessage message;
    TGameEngine engine;
    TScene scene;
    TGameEngineContext context{&engine, &scene};
    TComponentSystemsManager systems;

    ASSERT_NO_THROW(systems.SendMessage(message, context));
}

// ### SCENE TESTS ###
// === SceneObject Tests ===

TEST(SceneObjectTest, add_component_success) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_TRUE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, add_component_failure_empty_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name;
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, add_component_failure_empty_component) {
    const TSceneObject::ComponentHandle handle;
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, add_component_failure_duplicate) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, handle);

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, has_component_with_handle_positive) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_TRUE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, has_component_with_handle_negative_unknown_handle) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, fakeHandle);

    EXPECT_FALSE(sceneObject.HasComponent(100));
}

TEST(SceneObjectTest, has_component_with_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    EXPECT_FALSE(sceneObject.HasComponent(name));

    sceneObject.AddComponent(name, handle);

    EXPECT_TRUE(sceneObject.HasComponent(name));
}

TEST(SceneObjectTest, has_components) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    EXPECT_FALSE(sceneObject.HasComponents());

    sceneObject.AddComponent(name, handle);

    EXPECT_TRUE(sceneObject.HasComponents());
}

TEST(SceneObjectTest, remove_component_with_handle_success) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    sceneObject.RemoveComponent(handle);

    EXPECT_FALSE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, remove_component_with_name_success) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, handle);

    sceneObject.RemoveComponent(name);

    EXPECT_FALSE(sceneObject.HasComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_unknown_component) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_empty_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name;
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_unknown_handle) {
    const TSceneObject::ComponentHandle handle;
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, get_component_handle_by_handle) {
    const TSceneObject::ComponentHandle fakeComponentHandle(
        1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeComponentHandle);

    EXPECT_EQ(fakeComponentHandle, sceneObject[handle]);
}

TEST(SceneObjectTest, get_component_handle_by_name) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, fakeHandle);

    EXPECT_EQ(fakeHandle, sceneObject[name]);
}

TEST(SceneObjectTest, get_handle_by_name) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::Custom);
    const TSceneObject::ComponentName name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_EQ(handle, sceneObject.GetHandle(name));
}


TEST(SceneObject_ComponentHandleTest, get_value) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::Custom;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleValue, handle.GetValue());
}

TEST(SceneObject_ComponentHandleTest, get_system) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::Custom;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleSystem, handle.GetSystem());
}

TEST(SceneObject_ComponentHandleTest, explicit_conversion_to_handle) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::Custom;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleValue, static_cast<size_t>(handle));
}

TEST(SceneObject_ComponentHandleTest, operator_equals_positive) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::Custom);
    const TSceneObject::ComponentHandle handle2(0, ComponentSystem::Custom);

    EXPECT_TRUE(handle1 == handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_equals_negative) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::Custom);
    const TSceneObject::ComponentHandle handle2(1, ComponentSystem::Custom);

    EXPECT_FALSE(handle1 == handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_not_equals_positive) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::Custom);
    const TSceneObject::ComponentHandle handle2(1, ComponentSystem::Custom);

    EXPECT_TRUE(handle1 != handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_not_equals_negative) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::Custom);
    const TSceneObject::ComponentHandle handle2(0, ComponentSystem::Custom);

    EXPECT_FALSE(handle1 != handle2);
}

TEST(SceneObject_ComponentHandleTest, initial_value_is_undefined) {
    const TSceneObject::ComponentHandle handle;

    EXPECT_EQ(TSceneObject::ComponentHandle::Undefined, handle);
}


// === SceneObjectContainer Tests ===

TEST(SceneObjectContainerTest, add_object_success) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;

    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, add_object_rvalue_success) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;

    const auto handle = container.AddSceneObject(name, std::move(TSceneObject()));

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, add_object_failure_empty_name) {
    const TSceneObjectContainer::SceneObjectName name;
    TSceneObjectContainer container;

    ASSERT_ANY_THROW(container.AddSceneObject(name, TSceneObject()));
}

TEST(SceneObjectContainerTest, add_object_failure_duplicate) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;

    container.AddSceneObject(name, TSceneObject());
    ASSERT_ANY_THROW(container.AddSceneObject(name, TSceneObject()));
}

TEST(SceneObjectContainerTest, has_object_with_handle_positive) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, has_object_with_handle_negative_unknown_handle) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    EXPECT_FALSE(container.HasObject(100));
}

TEST(SceneObjectContainerTest, has_object_with_name) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;

    EXPECT_FALSE(container.HasObject(name));

    container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_success) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    container.RemoveSceneObject(handle);

    EXPECT_FALSE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, remove_object_with_name_success) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    container.RemoveSceneObject(name);

    EXPECT_FALSE(container.HasObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_name_failure_empty_name) {
    const TSceneObjectContainer::SceneObjectName name;
    TSceneObjectContainer container;

    ASSERT_NO_THROW(container.RemoveSceneObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_failure_unknown_handle) {
    const TSceneObjectContainer::ObjectHandle handle = 42;
    TSceneObjectContainer container;

    ASSERT_NO_THROW(container.RemoveSceneObject(handle));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_failure_undefined_handle) {
    const auto handle = TSceneObjectContainer::ObjectHandle::Undefined;
    TSceneObjectContainer container;

    ASSERT_NO_THROW(container.RemoveSceneObject(handle));
}

TEST(SceneObjectContainerTest, get_object_by_handle_positive) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    ASSERT_NO_THROW(container[handle]);
}

TEST(SceneObjectContainerTest, get_object_by_name) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    ASSERT_NO_THROW(container[name]);
}

TEST(SceneObjectContainerTest, get_handle_by_name) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_EQ(handle, container.GetHandle(name));
}

TEST(SceneObjectContainerTest, is_empty) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;

    EXPECT_TRUE(container.IsEmpty());

    container.AddSceneObject(name, TSceneObject());

    EXPECT_FALSE(container.IsEmpty());
}

TEST(SceneObjectContainerTest, clear) {
    const TSceneObjectContainer::SceneObjectName name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    container.Clear();

    EXPECT_TRUE(container.IsEmpty());
}

// === Scene Tests ===
class TestScene :
    public ::testing::Test
{
public:
    TestScene() :
        ::testing::Test(),
        engine(nullptr),
        scene(nullptr)
    {}

    virtual void SetUp() override {
        engine.reset(new GE::TGameEngine());
        engine->GetComponentSystemsManager().
            AddSystem<CustomComponentSystem>(GE::ComponentSystem::Custom);

        TComponentRegistry::Entry entry;
        entry.create = &CustomComponent::Create;
        entry.system = ComponentClass<CustomComponent>::value();
        engine->GetComponentSystemsManager().GetComponentRegistry().
            Register(ComponentID<CustomComponent>::value(), entry);

        scene.reset(new TScene());
        scene->SetGameEngine(engine.get());
    }

protected:
    std::unique_ptr<TGameEngine> engine;
    std::unique_ptr<TScene> scene;
};

TEST(SceneTest, ctor_correct) {
    ASSERT_NO_THROW(TScene());
}

TEST_F(TestScene, create_component_with_default_args_correct) {
    ASSERT_NO_THROW(scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr));
}

TEST_F(TestScene, create_component_with_custom_args_correct) {
    CustomComponent::Parameters parameters;
    parameters.value = 10;

    TScene::ComponentHandle handle;
    ASSERT_NO_THROW(handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), &parameters));

    const auto* component = scene->GetComponent<CustomComponent>(handle);
    EXPECT_NE(nullptr, component);
    EXPECT_EQ(parameters.value, component->value);
}

TEST_F(TestScene, create_component_unregistered_incorrect) {
    ASSERT_ANY_THROW(scene->CreateComponent(ComponentIDs::_count, nullptr));
}

TEST_F(TestScene, remove_component_existing_component) {
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_NO_THROW(scene->RemoveComponent(handle));
    EXPECT_FALSE(scene->HasComponent(handle));
}

TEST_F(TestScene, remove_component_unexisting_component) {
    const auto handle = TScene::ComponentHandle::Undefined;

    ASSERT_NO_THROW(scene->RemoveComponent(handle));
}

TEST_F(TestScene, get_component_and_cast_existing) {
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_NE(nullptr, scene->GetComponent<CustomComponent>(handle));
}

TEST_F(TestScene, get_component_and_cast_unexisting_handle) {
    const auto handle = TScene::ComponentHandle::Undefined;

    ASSERT_EQ(nullptr, scene->GetComponent<CustomComponent>(handle));
}

TEST_F(TestScene, get_component_and_cast_wrong_class) {
    struct OtherComponent : TComponent {};
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_EQ(nullptr, scene->GetComponent<OtherComponent>(handle));
}

TEST_F(TestScene, get_component_existing) {
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_NE(nullptr, scene->GetComponent(handle));
}

TEST_F(TestScene, get_component_unexisting_handle) {
    const auto handle = TScene::ComponentHandle::Undefined;

    ASSERT_EQ(nullptr, scene->GetComponent(handle));
}

TEST_F(TestScene, find_component_existing) {
    const auto handle = scene->CreateComponent(
        ComponentID<CustomComponent>::value(), nullptr);
    const TScene::ComponentPath path{"object1", "component1"};
    TSceneObject object;
    object.AddComponent(path.second, handle);
    scene->AddSceneObject(path.first, object);

    ASSERT_EQ(handle, scene->FindComponent(path));
}

TEST_F(TestScene, find_component_unexisting) {
    const TScene::ComponentPath path{"object1", "component1"};

    ASSERT_EQ(TScene::ComponentHandle::Undefined, scene->FindComponent(path));
}

TEST_F(TestScene, find_scene_object_existing) {
    const auto name = "object1";
    TSceneObject object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_EQ(handle, scene->FindSceneObject(name));
}

TEST_F(TestScene, find_scene_object_unexisting) {
    ASSERT_EQ(TScene::ObjectHandle::Undefined, scene->FindSceneObject("1"));
}

TEST_F(TestScene, get_scene_object_existing) {
    TSceneObject object;
    const auto handle = scene->AddSceneObject("object1", object);

    ASSERT_NO_THROW(scene->GetSceneObject(handle));
}

TEST_F(TestScene, get_scene_object_unexisting) {
    ASSERT_ANY_THROW(scene->GetSceneObject(TScene::ObjectHandle::Undefined));
}

TEST_F(TestScene, find_scene_object_with_name_existing) {
    const auto name = "object1";
    TSceneObject object;
    scene->AddSceneObject(name, object);

    ASSERT_TRUE(scene->HasObject(name));
}

TEST_F(TestScene, find_scene_object_with_name_unexisting) {
    ASSERT_FALSE(scene->HasObject("1"));
}

TEST_F(TestScene, find_scene_object_with_handle_existing) {
    const auto name = "object1";
    TSceneObject object;
    const auto handle = scene->AddSceneObject(name, object);

    ASSERT_TRUE(scene->HasObject(handle));
}

TEST_F(TestScene, find_scene_object_with_handle_unexisting) {
    ASSERT_FALSE(scene->HasObject(TScene::ObjectHandle::Undefined));
}

TEST_F(TestScene, add_scene_object_with_unexisting_name) {
    const auto name = "object";
    TSceneObject object;
    TScene::ObjectHandle handle;

    ASSERT_NO_THROW(handle = scene->AddSceneObject(name, object));

    EXPECT_TRUE(scene->HasObject(handle));
}

TEST_F(TestScene, add_scene_object_with_existing_name_is_failure) {
    const auto name = "object";
    TSceneObject object;

    scene->AddSceneObject(name, object);
    ASSERT_ANY_THROW(scene->AddSceneObject(name, object));
}

TEST_F(TestScene, add_scene_object_by_rvalue) {
    const auto name = "object";
    TSceneObject object;

    ASSERT_NO_THROW(scene->AddSceneObject(name, std::move(object)));
}

TEST_F(TestScene, remove_scene_object_by_handle_existing) {
    const auto name = "object";
    TSceneObject object;
    TScene::ObjectHandle handle = scene->AddSceneObject(name, object);

    ASSERT_NO_THROW(scene->RemoveSceneObject(handle));
    EXPECT_FALSE(scene->HasObject(handle));
}

TEST_F(TestScene, remove_scene_object_by_handle_unexisting) {
    ASSERT_NO_THROW(scene->RemoveSceneObject(TScene::ObjectHandle::Undefined));
}

TEST_F(TestScene, remove_scene_object_by_name_existing) {
    const auto name = "object";
    TSceneObject object;
    TScene::ObjectHandle handle = scene->AddSceneObject(name, object);

    ASSERT_NO_THROW(scene->RemoveSceneObject(handle));
    EXPECT_FALSE(scene->HasObject(handle));
}

TEST_F(TestScene, remove_scene_object_by_name_unexisting) {
    const auto name = "object";
    ASSERT_NO_THROW(scene->RemoveSceneObject(name));
}

TEST_F(TestScene, clear_clears) {
    scene->CreateComponent(ComponentID<CustomComponent>::value(), nullptr);
    scene->AddSceneObject("object", TSceneObject());

    scene->Clear();

    EXPECT_TRUE(scene->IsEmpty());
}

TEST_F(TestScene, is_empty_empty_when_empty) {
    ASSERT_TRUE(scene->IsEmpty());
}

TEST_F(TestScene, is_empty_not_empty_when_has_object) {
    scene->AddSceneObject("object", TSceneObject());

    ASSERT_FALSE(scene->IsEmpty());
}

TEST_F(TestScene, is_empty_not_empty_when_has_component) {
    scene->CreateComponent(ComponentID<CustomComponent>::value(), nullptr);

    ASSERT_FALSE(scene->IsEmpty());
}

TEST(SceneTest, set_game_engine) {
    TGameEngine engine;
    TScene scene;

    EXPECT_NO_THROW(scene.SetGameEngine(&engine));
}

TEST(SceneTest, set_game_engine_with_nullptr) {
    TScene scene;

    EXPECT_NO_THROW(scene.SetGameEngine(nullptr));
}

TEST_F(TestScene, get_component_manager) {
    EXPECT_NO_THROW(scene->GetComponentManager());
}

TEST_F(TestScene, get_object_manager) {
    EXPECT_NO_THROW(scene->GetObjectManager());
}

TEST_F(TestScene, get_resource_manager) {
    EXPECT_NO_THROW(scene->GetResourceManager());
}


// ### SCENE RESOURCES TESTS ###

enum class GE::SceneResourceTypeID : TSceneResourceTypeID {
    Unknown,
    TestResource,

    _count
};

class TestSceneResources :
    public ::testing::Test,
    public TSceneResources
{
protected:
    class TTestResource : public TSceneResource {
    public:
        static const SceneResourceTypeID typeID;

        static std::unique_ptr<TSceneResource> Create(
            const TSceneResourceCreateArgs*
        );

        TTestResource();

    private:
        using parent_type = TSceneResource;
    };

    virtual void SetUp() override;
};

const SceneResourceTypeID TestSceneResources::TTestResource::typeID =
    SceneResourceTypeID::TestResource;

std::unique_ptr<TSceneResource>
TestSceneResources::TTestResource::Create(const TSceneResourceCreateArgs*) {
    return std::unique_ptr<TSceneResource>(new TTestResource);
}

TestSceneResources::TTestResource::TTestResource() :
    parent_type(typeID)
{}

void TestSceneResources::SetUp() {
    GetRegistry().Clear();
    GetRegistry().Register(TTestResource::typeID, TTestResource::Create);
}

TEST_F(TestSceneResources, is_empty_empty_collection_is_empty) {
    ASSERT_TRUE(IsEmpty());
}

TEST_F(TestSceneResources, is_empty_not_empty_collection_is_not_empty) {
    LoadResource("testID", TTestResource::typeID);

    ASSERT_FALSE(IsEmpty());
}

TEST_F(TestSceneResources, load_resource_success) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);

    ASSERT_TRUE(IsResourceLoaded(id));
}

TEST_F(TestSceneResources, load_resource_failure_existing_id) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);
    ASSERT_ANY_THROW(LoadResource(id, TTestResource::typeID));
}

TEST_F(TestSceneResources, load_resource_failure_unexpected_type) {
    ASSERT_ANY_THROW(LoadResource("testID", SceneResourceTypeID::Unknown));
}

TEST_F(TestSceneResources, unload_resource_success) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);
    UnloadResource(id);

    ASSERT_FALSE(IsResourceLoaded(id));
}

TEST_F(TestSceneResources, unload_resource_failure_unexisting_resource) {
    ASSERT_ANY_THROW(UnloadResource("testID"));
}

TEST_F(TestSceneResources, clear_clears) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);
    Clear();

    ASSERT_TRUE(IsEmpty());
}

TEST_F(TestSceneResources, is_resource_loaded_is_true_success) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);

    ASSERT_TRUE(IsResourceLoaded(id));
}

TEST_F(TestSceneResources, is_resource_loaded_is_false_success) {
    ASSERT_FALSE(IsResourceLoaded("anyID"));
}

TEST_F(TestSceneResources, get_resource_success) {
    static const TSceneResources::ID id = "testID";
    const auto resource = LoadResource(id, TTestResource::typeID);

    ASSERT_EQ(resource.lock(), GetResource(id).lock());
    EXPECT_FALSE(resource.expired());
}

TEST_F(TestSceneResources, get_registry_success) {
    ASSERT_NO_THROW(GetRegistry());
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
