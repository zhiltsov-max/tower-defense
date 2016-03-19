#include "gtest/gtest.h"
#include "GameEngine/registry.h"
#include "GameEngine/component.h"
#include "GameEngine/component_systems.h"
#include "GameEngine/engine_messages.h"



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


// ### COMPONENT TESTS ###
enum class ComponentIDs : TComponentID {
    _min = 0,

    TestComponent,

    _max,
    _count = _max - _min
};

enum class MessageID : TMessageID {
    _min = static_cast<TMessageID>(DefaultMessageID::_max) + 1,

    CustomMessage,
    CustomUnexpectedMessage,

    _max,
    _count = _max - _min
};

class TestComponent;

template<>
struct ComponentID< TestComponent > {
    static const TComponent::ID value;
};
const TComponent::ID ComponentID< TestComponent >::value =
    ComponentIDs::TestComponent;

template<>
struct ComponentClass< TestComponent > {
    static const ComponentSystem value;
};
const ComponentSystem ComponentClass< TestComponent >::value =
    ComponentSystem::_undefined;

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
    virtual void TearDown() override {
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

    ASSERT_NO_THROW(HandleMessage(message));

    EXPECT_EQ(handledMessage, message.what());
}

TEST_F(TestComponent, message_handling_unexpected) {
    CustomUnexpectedMessage message;

    ASSERT_NO_THROW(HandleMessage(message));

    EXPECT_TRUE(handledMessage.empty());
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
