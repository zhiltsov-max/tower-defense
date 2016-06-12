#include "gtest/gtest.h"
#include "GameEngine/registry.h"
#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"
#include "GameEngine/engine_messages.h"
#include "GameEngine/scene_object.h"
#include "GameEngine/scene_object_container.h"
#include "GameEngine/scene_resources.h"



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

TEST_F(TestRegistry, registration_and_access) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;

    ASSERT_NO_THROW(registry.Register(id, entry));

    EXPECT_TRUE(registry.IsRegistered(id));
    EXPECT_EQ(entry, registry[id]);
}

TEST_F(TestRegistry, existing_item_registration) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;

    ASSERT_NO_THROW(registry.Register(id, entry));
    ASSERT_ANY_THROW(registry.Register(id, entry));
}

TEST_F(TestRegistry, unregistration) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;
    ASSERT_NO_THROW(registry.Register(id, entry));

    ASSERT_NO_THROW(registry.Unregister(id));

    EXPECT_FALSE(registry.IsRegistered(id));
}

TEST_F(TestRegistry, unexisting_item_unregistration) {
    Registry registry;
    ID id = 4;
    Entry entry = -10;

    ASSERT_NO_THROW(registry.Register(id, entry));
    ASSERT_NO_THROW(registry.Unregister(id));
    ASSERT_ANY_THROW(registry.Unregister(id));
}

TEST_F(TestRegistry, isempty_test) {
    Registry registry;
    ID id = 6;
    Entry entry = 100500;

    ASSERT_TRUE(registry.IsEmpty());

    registry.Register(id, entry);

    ASSERT_FALSE(registry.IsEmpty());

    registry.Unregister(id);

    ASSERT_TRUE(registry.IsEmpty());
}

TEST_F(TestRegistry, size) {
    Registry registry;
    const size_t count = 4;
    ID ids[count] = {5, 6, 10, 12};
    Entry entries[count] = {-10, 1, 50, 7};

    ASSERT_EQ(0u, registry.Size());

    for(size_t i = 0; i < count; ++i) {
        registry.Register(ids[i], entries[i]);
    }

    ASSERT_EQ(count, registry.Size());
}

TEST_F(TestRegistry, clear) {
    Registry registry;
    const size_t count = 4;
    ID ids[count] = {5, 6, 10, 12};
    Entry entries[count] = {-10, 1, 50, 7};
    for(size_t i = 0; i < count; ++i) {
        registry.Register(ids[i], entries[i]);
    }

    ASSERT_NO_THROW(registry.Clear());

    EXPECT_TRUE(registry.IsEmpty());
}


// ### COMPONENT SYSTEM TESTS ###

enum class GE::ComponentIDs : TComponentID {
    _min = 0,

    TestComponent,
    CustomComponent,

    _max,
    _count = _max - _min
};

enum class GE::MessageID : TMessageID {
    _min = static_cast<TMessageID>(DefaultMessageID::_max) + 1,

    CustomMessage,
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


// === Component Tests ===

class TestComponent :
    public ::testing::Test,
    protected TComponent
{
public:
    TestComponent();

protected:
    class CustomMessage;
    class CustomUnexpectedMessage;


    string handledMessage;


    virtual void Update() override;

    virtual void HandleMessage(const TMessage& message) override;
    virtual void Subscribe(TComponentSystem& system) override;
    virtual void Unsubscribe(TComponentSystem& system) override;

    virtual void SetUp() override {
        handledMessage.clear();
    }
};

class TestComponent::CustomMessage :
    public TMessage
{
public:
    CustomMessage(const string& message) :
        TMessage(static_cast<ID>(MessageID::CustomMessage)),
        message(message)
    {}

    const string& what() const {
        return message;
    }
private:
    string message;
};

class TestComponent::CustomUnexpectedMessage :
    public TMessage
{
public:
    CustomUnexpectedMessage() :
        TMessage(MessageID::CustomUnexpectedMessage)
    {}
};

namespace GE {
template<>
struct ComponentID< TestComponent > {
    static const TComponent::ID value;
};
const TComponent::ID ComponentID<TestComponent>::value =
    ComponentIDs::TestComponent;

template<>
struct ComponentClass< TestComponent > {
    static const ComponentSystem value;
};
const ComponentSystem ComponentClass<TestComponent>::value =
    ComponentSystem::_undefined;
} //namespace GE

TestComponent::TestComponent() :
    ::testing::Test(),
    TComponent(ComponentID<TestComponent>::value)
{}

void TestComponent::Update() { /*none*/ }

void TestComponent::HandleMessage(const TMessage& message) {
    switch (message.GetID()) {
    case MessageID::CustomMessage:
        handledMessage = static_cast<const CustomMessage&>(message).what();
        break;

    default:
        handledMessage.clear();
        break;
    }
}

void TestComponent::Subscribe(TComponentSystem& system) {
    system.Subscribe(this, MessageID::CustomMessage);
}

void TestComponent::Unsubscribe(TComponentSystem& system) {
    system.Unsubscribe(this, MessageID::CustomMessage);
}


TEST_F(TestComponent, initialization) {
    EXPECT_EQ(ComponentID<TestComponent>::value, GetID());
}

TEST_F(TestComponent, message_handling_expected) {
    CustomMessage message("123");

    HandleMessage(message);

    EXPECT_EQ(message.what(), handledMessage);
}

TEST_F(TestComponent, message_handling_unexpected) {
    CustomUnexpectedMessage message;

    HandleMessage(message);

    EXPECT_TRUE(handledMessage.empty());
}


// === ComponentSystem Tests ===

class CustomComponent :
    public TComponent
{
public:
    static std::unique_ptr<TComponent> Create(const TComponentCreateArgs*) {
        return std::unique_ptr<TComponent>(new CustomComponent);
    }


    CustomComponent();


    virtual void Update() override { /*none*/ }
    virtual void HandleMessage(const TMessage& message) override { /* none */ }
    virtual void Subscribe(TComponentSystem& system) override {
        system.Subscribe(this, MessageID::CustomMessage);
    }
    virtual void Unsubscribe(TComponentSystem& system) override {
        system.Unsubscribe(this, MessageID::CustomMessage);
    }
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
    ComponentSystem::input;
} //namespace GE

CustomComponent::CustomComponent() :
    TComponent(ComponentID<CustomComponent>::value)
{}


class TestComponentSystem :
    public ::testing::Test,
    public TComponentSystem
{
protected:
    virtual void SetUp() override {
        SetRegistry(nullptr);

        testRegistry.Clear();

        testRegistry.Register(ComponentIDs::CustomComponent,
            &CustomComponent::Create);

        SetRegistry(&testRegistry);
    }

    bool HasSubscription(const TComponent* component,
        const TMessage::ID& id) const
    {
        return (listeners.count(id) != 0) &&
            (std::find(listeners.at(id).cbegin(), listeners.at(id).cend(),
                component) != listeners.at(id).cend());
    }

private:
    TComponentRegistry testRegistry;
};


TEST_F(TestComponentSystem, create_component_positive) {
    auto component = CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    EXPECT_NE(HandleUndefined, component);
}

TEST_F(TestComponentSystem, create_component_negative) {
    EXPECT_ANY_THROW(CreateComponent(ComponentIDs::_count, nullptr));
}

TEST_F(TestComponentSystem, remove_component) {
    auto component = CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    RemoveComponent(component);

    EXPECT_EQ(0u, components.size());
}

TEST_F(TestComponentSystem, get_component) {
    auto component = CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    EXPECT_NE(nullptr, GetComponent(component));
}

TEST_F(TestComponentSystem, subscribe_component) {
    auto component = CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    // automatic subscription in CreateComponent()

    EXPECT_TRUE(HasSubscription(GetComponent(component),
        MessageID::CustomMessage));
}

TEST_F(TestComponentSystem, unsubscribe_component) {
    auto component = CreateComponent(
        ComponentID<CustomComponent>::value, nullptr);

    Unsubscribe(GetComponent(component), MessageID::CustomMessage);

    EXPECT_FALSE(HasSubscription(GetComponent(component),
        MessageID::CustomMessage));
}


// ### SCENE TESTS ###
// === SceneObject Tests ===

TEST(SceneObjectTest, add_component_success) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_TRUE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, add_component_failure_empty_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name;
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, add_component_failure_empty_component) {
    const TSceneObject::ComponentHandle handle;
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, add_component_failure_duplicate) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, handle);

    ASSERT_ANY_THROW(sceneObject.AddComponent(name, handle));
}

TEST(SceneObjectTest, has_component_with_handle_positive) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_TRUE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, has_component_with_handle_negative_unknown_handle) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, fakeHandle);

    EXPECT_FALSE(sceneObject.HasComponent(100));
}

TEST(SceneObjectTest, has_component_with_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    EXPECT_FALSE(sceneObject.HasComponent(name));

    sceneObject.AddComponent(name, handle);

    EXPECT_TRUE(sceneObject.HasComponent(name));
}

TEST(SceneObjectTest, has_components) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    EXPECT_FALSE(sceneObject.HasComponents());

    sceneObject.AddComponent(name, handle);

    EXPECT_TRUE(sceneObject.HasComponents());
}

TEST(SceneObjectTest, remove_component_with_handle_success) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    sceneObject.RemoveComponent(handle);

    EXPECT_FALSE(sceneObject.HasComponent(handle));
}

TEST(SceneObjectTest, remove_component_with_name_success) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, handle);

    sceneObject.RemoveComponent(name);

    EXPECT_FALSE(sceneObject.HasComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_unknown_component) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_empty_name) {
    const TSceneObject::ComponentHandle handle(1, ComponentSystem::logics);
    const TSceneObject::Name name;
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, remove_component_with_name_failure_unknown_handle) {
    const TSceneObject::ComponentHandle handle;
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;

    ASSERT_ANY_THROW(sceneObject.RemoveComponent(name));
}

TEST(SceneObjectTest, get_component_handle_by_handle) {
    const TSceneObject::ComponentHandle fakeComponentHandle(
        1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeComponentHandle);

    EXPECT_EQ(fakeComponentHandle, sceneObject[handle]);
}

TEST(SceneObjectTest, get_component_handle_by_name) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    sceneObject.AddComponent(name, fakeHandle);

    EXPECT_EQ(fakeHandle, sceneObject[name]);
}

TEST(SceneObjectTest, get_handle_by_name) {
    const TSceneObject::ComponentHandle fakeHandle(1, ComponentSystem::logics);
    const TSceneObject::Name name = "component";
    TSceneObject sceneObject;
    const auto handle = sceneObject.AddComponent(name, fakeHandle);

    EXPECT_EQ(handle, sceneObject.GetHandle(name));
}


TEST(SceneObject_ComponentHandleTest, get_value) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::logics;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleValue, handle.GetValue());
}

TEST(SceneObject_ComponentHandleTest, get_system) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::logics;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleSystem, handle.GetSystem());
}

TEST(SceneObject_ComponentHandleTest, explicit_conversion_to_handle) {
    const size_t handleValue = 1;
    const auto handleSystem = ComponentSystem::logics;
    const TSceneObject::ComponentHandle handle(handleValue, handleSystem);

    EXPECT_EQ(handleValue, static_cast<size_t>(handle));
}

TEST(SceneObject_ComponentHandleTest, operator_equals_positive) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::logics);
    const TSceneObject::ComponentHandle handle2(0, ComponentSystem::logics);

    EXPECT_TRUE(handle1 == handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_equals_negative) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::logics);
    const TSceneObject::ComponentHandle handle2(1, ComponentSystem::logics);

    EXPECT_FALSE(handle1 == handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_not_equals_positive) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::logics);
    const TSceneObject::ComponentHandle handle2(1, ComponentSystem::logics);

    EXPECT_TRUE(handle1 != handle2);
}

TEST(SceneObject_ComponentHandleTest, operator_not_equals_negative) {
    const TSceneObject::ComponentHandle handle1(0, ComponentSystem::logics);
    const TSceneObject::ComponentHandle handle2(0, ComponentSystem::logics);

    EXPECT_FALSE(handle1 != handle2);
}

TEST(SceneObject_ComponentHandleTest, initial_value_is_undefined) {
    const TSceneObject::ComponentHandle handle;

    EXPECT_EQ(TSceneObject::ComponentHandle::Undefined, handle);
}


// === SceneObjectContainer Tests ===

TEST(SceneObjectContainerTest, add_object_success) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;

    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, add_object_rvalue_success) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;

    const auto handle = container.AddSceneObject(name, std::move(TSceneObject()));

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, add_object_failure_empty_name) {
    const TSceneObjectContainer::Name name;
    TSceneObjectContainer container;

    ASSERT_ANY_THROW(container.AddSceneObject(name, TSceneObject()));
}

TEST(SceneObjectContainerTest, add_object_failure_duplicate) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;

    container.AddSceneObject(name, TSceneObject());
    ASSERT_ANY_THROW(container.AddSceneObject(name, TSceneObject()));
}

TEST(SceneObjectContainerTest, has_object_with_handle_positive) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, has_object_with_handle_negative_unknown_handle) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    EXPECT_FALSE(container.HasObject(100));
}

TEST(SceneObjectContainerTest, has_object_with_name) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;

    EXPECT_FALSE(container.HasObject(name));

    container.AddSceneObject(name, TSceneObject());

    EXPECT_TRUE(container.HasObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_success) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    container.RemoveSceneObject(handle);

    EXPECT_FALSE(container.HasObject(handle));
}

TEST(SceneObjectContainerTest, remove_object_with_name_success) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    container.RemoveSceneObject(name);

    EXPECT_FALSE(container.HasObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_name_failure_empty_name) {
    const TSceneObjectContainer::Name name;
    TSceneObjectContainer container;

    ASSERT_ANY_THROW(container.RemoveSceneObject(name));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_failure_unknown_handle) {
    const TSceneObjectContainer::Handle handle = 42;
    TSceneObjectContainer container;

    ASSERT_ANY_THROW(container.RemoveSceneObject(handle));
}

TEST(SceneObjectContainerTest, remove_object_with_handle_failure_undefined_handle) {
    const auto handle = TSceneObjectContainer::HandleUndefined;
    TSceneObjectContainer container;

    ASSERT_ANY_THROW(container.RemoveSceneObject(handle));
}

TEST(SceneObjectContainerTest, get_object_by_handle_positive) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    ASSERT_NO_THROW(container[handle]);
}

TEST(SceneObjectContainerTest, get_object_by_name) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    ASSERT_NO_THROW(container[name]);
}

TEST(SceneObjectContainerTest, get_handle_by_name) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    const auto handle = container.AddSceneObject(name, TSceneObject());

    EXPECT_EQ(handle, container.GetHandle(name));
}

TEST(SceneObjectContainerTest, is_empty) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;

    EXPECT_TRUE(container.IsEmpty());

    container.AddSceneObject(name, TSceneObject());

    EXPECT_FALSE(container.IsEmpty());
}

TEST(SceneObjectContainerTest, clear) {
    const TSceneObjectContainer::Name name = "object";
    TSceneObjectContainer container;
    container.AddSceneObject(name, TSceneObject());

    container.Clear();

    EXPECT_TRUE(container.IsEmpty());
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

TEST_F(TestSceneResources, empty_empty_collection_is_empty) {
    ASSERT_TRUE(Empty());
}

TEST_F(TestSceneResources, empty_not_empty_collection_is_not_empty) {
    LoadResource("testID", TTestResource::typeID);

    ASSERT_FALSE(Empty());
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

TEST_F(TestSceneResources, clear) {
    static const TSceneResources::ID id = "testID";
    LoadResource(id, TTestResource::typeID);
    Clear();

    ASSERT_TRUE(Empty());
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
