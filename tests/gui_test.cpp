#include "Application/application.h"
#include "GameEngine/GUI/gui_main.h"
#include "GameEngine/GUI/widget_event_system.h"
#include "GameEngine/GUI/widget.h"
#include "GameEngine/GUI/uiparent.h"
#include "gtest/gtest.h"



using namespace GUI;

// ### UIParent Tests ###
class TestUIParent :
	public ::testing::Test,
	public TUIParent
{
public:
	static const TUIParentSource source;

	TestUIParent() :
		::testing::Test(),
		TUIParent(source)
	{}

protected:
	virtual void SetUp() {
		Initialize();
	}
};

const TUIParentSource TestUIParent::source = [] {
	TUIParentSource source;
	source.size = TSize(30, 20);
	source.margin = TPadding(1, 2, 3, 4);
	source.show = true;
	source.position = TCoordinate(50, 20);
	return source;
} ();


TEST_F(TestUIParent, initialization) {
	EXPECT_EQ(source.size, GetOwnSize());
	EXPECT_EQ(source.size +
			TSize(source.margin.left + source.margin.right,
				source.margin.top + source.margin.bottom
			),
		GetSize());

	EXPECT_EQ(source.show, IsShown());
	EXPECT_EQ(source.margin, GetMargin());
	EXPECT_EQ(source.position, GetPosition());

    const string name = TGUISettings::DEFAULT_UIPARENT_NAME;
	EXPECT_EQ(name, GetName());
}

TEST_F(TestUIParent, set_parent) {
	EXPECT_NO_THROW(SetParent(TWidgetRef()));
}

TEST(UIParent_test, shared) {
	auto uiparent_storage = std::make_shared<TUIParent>(TestUIParent::source);
	auto& uiparent = *uiparent_storage;

    EXPECT_EQ(uiparent_storage, uiparent.shared_from_this());
}


// ### Signals and slots system ###
class TestSignal :
    public ::testing::Test,
    public TWidgetSignal
{
public:
    TestSignal() :
        ::testing::Test(),
        TWidgetSignal(testId)
    {}
protected:
    static const SignalID testId;
};
const SignalID TestSignal::testId = "testSignal";


TEST_F(TestSignal, get_id) {
    EXPECT_EQ(testId, GetID());
}

TEST_F(TestSignal, add_listener) {
    auto method = [] (TWidget*, const void *) {};
    TWidgetSlot slot(TWidgetWeakRef(), "testSlot", method);

    AddListener(slot);

    EXPECT_TRUE(HasListener(slot));
}

TEST_F(TestSignal, remove_listener) {
    TWidgetSlot slot(TWidgetWeakRef(), "testSlot", TWidgetSlot::Method());
    AddListener(slot);

    RemoveListener(slot);

    EXPECT_FALSE(HasListener(slot));
}


class TestSlot :
    public ::testing::Test,
    public TWidgetSlot
{
public:
    TestSlot() :
        ::testing::Test(),
        TWidgetSlot(testOwner, testId, testMethod)
    {}

protected:
    static const SlotID testId;
    static bool testMethodExecuted;
    static const Method testMethod;
    static const Owner testOwner;


    virtual void SetUp() override {
        testMethodExecuted = false;
    }
};

const SlotID TestSlot::testId = "testSlot";
bool TestSlot::testMethodExecuted = false;
const TestSlot::Method TestSlot::testMethod =
    [&] (TWidget*, const void*) { TestSlot::testMethodExecuted = true; };
const TestSlot::Owner TestSlot::testOwner {};


TEST_F(TestSlot, get_id) {
    EXPECT_EQ(testId, GetID());
}

TEST_F(TestSlot, get_method_ptr) {
    using TargetType = void (*)(TWidget*, void**);
    EXPECT_EQ(
        testMethod.target<TargetType>(),
        GetPtr().target<TargetType>()
    );
}

TEST_F(TestSlot, has_ptr) {
    EXPECT_TRUE(HasPtr());
}

TEST_F(TestSlot, get_owner) {
    EXPECT_EQ(testOwner.lock(), GetOwner().lock());
}

TEST_F(TestSlot, execution) {
    Invoke();

    EXPECT_TRUE(testMethodExecuted);
}

TEST_F(TestSlot, operator_equals) {
    TWidgetSlot other {testOwner, testId, testMethod};

    EXPECT_EQ(*this, other);
}

TEST_F(TestSlot, operator_not_equals) {
    const SlotID otherId = "testOtherSlot";
    TWidgetSlot other {testOwner, otherId, testMethod};

    EXPECT_NE(*this, other);
}


class TestEventSystem :
	public ::testing::Test,
	public TWidgetEventSystem
{};

TEST_F(TestEventSystem, add_signal) {
    const SignalID id = "testSignal";

    AddSignal(Signal(id));

    EXPECT_TRUE(HasSignal(id));
}

TEST_F(TestEventSystem, add_slot) {
    const SlotID id = "testSlot";

    AddSlot(Slot(TWidgetRef(), id, Slot::Method()));

    EXPECT_TRUE(HasSlot(id));
}

TEST_F(TestEventSystem, has_signal) {
    const SignalID id = "testSignal";

    EXPECT_FALSE(HasSignal(id));

    AddSignal(Signal(id));

    EXPECT_TRUE(HasSignal(id));
}

TEST_F(TestEventSystem, has_slot) {
    const SlotID id = "testSlot";

    EXPECT_FALSE(HasSlot(id));

    AddSlot(Slot(TWidgetRef(), id, Slot::Method()));

    EXPECT_TRUE(HasSlot(id));
}

TEST_F(TestEventSystem, get_signal) {
    const SignalID id = "testSignal";
    Signal signal(id);
    AddSignal(signal);

    auto& result = GetSignal(id);

    EXPECT_EQ(id, result.GetID());
}

TEST_F(TestEventSystem, get_slot) {
    const SlotID id = "testSlot";
    Slot slot(TWidgetRef(), id, Slot::Method());
    AddSlot(slot);

    auto& result = GetSlot(id);

    EXPECT_EQ(slot, result);
}

TEST_F(TestEventSystem, signals_and_slots_system) {
	const SignalID id = "testSignal";
    AddSignal(Signal(id));
	Signal& signal = GetSignal(id);

	bool methodExecuted = false;
    auto method = [&] (TWidget*, const void*) { methodExecuted = true; };
	Slot listener(TWidgetWeakRef(), id, method);
    signal.AddListener(listener);
    AddSlot(listener);

    signal.Send();

	EXPECT_TRUE(methodExecuted);
}


// ### Widget tests ###
class TestWidget :
	public ::testing::Test,
	public TWidget
{
public:
	TestWidget() :
		::testing::Test(),
		TWidget(source)
	{}
private:
	using parent_type = TWidget;

protected:
	static const TWidgetSource source;
	static const SignalID testSignal;
	static const SlotID testSlot;
	static int testSlotUseCount;
    static void slot_TestSlot(TWidget*, const void*) {
		++testSlotUseCount;
	}


	virtual void _draw(TRenderTarget&) override { /*none*/ }

	virtual std::list<Signal> _enumSignals() const override {
		auto signals = parent_type::_enumSignals();
		signals.emplace_back(testSignal);
		return signals;
	}

	virtual std::list<Slot> _enumSlots() const override {
		auto slots = parent_type ::_enumSlots();
		slots.emplace_back(TWidgetWeakRef(), testSlot, slot_TestSlot);
		return slots;
	}

	virtual void SetUp() override {
		Initialize();
	}
};

const SignalID TestWidget::testSignal = "testSignal";
const SlotID TestWidget::testSlot = "testSlot";
int TestWidget::testSlotUseCount = 0;

const TWidgetSource TestWidget::source = [] {
	TWidgetSource source;
	source.name = "TestWidget";
	source.position = TCoordinate(1, 2);
	source.show = false;
	source.size = TSize(3, 5);
	source.margin = TPadding(1, 2, 3, 4);
	return source;
} ();

TEST_F(TestWidget, get_name) {
	EXPECT_EQ(source.name, GetName());
}

TEST_F(TestWidget, get_position) {
	EXPECT_EQ(source.position, GetPosition());
}

TEST_F(TestWidget, is_shown) {
	EXPECT_EQ(source.show, IsShown());
}

TEST_F(TestWidget, get_margin) {
    EXPECT_EQ(source.margin, GetMargin());
}

TEST_F(TestWidget, get_own_size) {
	EXPECT_EQ(source.size, GetOwnSize());
}

TEST_F(TestWidget, get_size) {
	EXPECT_EQ(source.size +
			TSize(source.margin.left + source.margin.right,
				source.margin.bottom + source.margin.top),
        GetSize()
    );
}

TEST_F(TestWidget, is_signals_initialized_correctly) {
	EXPECT_EQ(eventSystem.GetSignals().size(), _enumSignals().size());
}

TEST_F(TestWidget, is_slots_initialized_correctly) {
	EXPECT_EQ(eventSystem.GetSlots().size(), _enumSlots().size());
}

TEST_F(TestWidget, has_signal) {
	EXPECT_TRUE(eventSystem.HasSignal(testSignal));
}

TEST_F(TestWidget, has_slot) {
	EXPECT_TRUE(eventSystem.HasSlot(testSlot));
}

TEST_F(TestWidget, set_margin) {
    SetMargin(TPadding(4, 3, 2, 1));

	EXPECT_EQ(TPadding(4, 3, 2, 1), GetMargin());
}

TEST_F(TestWidget, set_parent) {
    SetParent(TWidgetWeakRef());

	EXPECT_EQ(TWidgetWeakRef().lock(), GetParent().lock());
}

TEST_F(TestWidget, set_position) {
    SetPosition(TCoordinate(3, 3));

	EXPECT_EQ(TCoordinate(3, 3), GetPosition());
}

TEST_F(TestWidget, set_size) {
    SetSize(TSize(2, 2));

	EXPECT_EQ(TSize(2, 2), GetOwnSize());
}

TEST_F(TestWidget, set_visibility) {
    SetVisibility(true);

	EXPECT_EQ(true, IsShown());
}


class CustomWidget :
    public TWidget
{
public:
    CustomWidget(const TWidgetSource& source) :
        TWidget(source)
    {}
private:
    virtual void _draw(TRenderTarget&) override { /*none*/ }
};

TEST(WidgetTest, tree_operations_addition_as_child) {
	TWidgetSource source;
	source.name = "testRoot";
	source.size = TSize(1, 1);
	auto widget1 = std::make_shared<CustomWidget>(source);
	widget1->Initialize();

	source.name = "testChild";
	auto widget2 = std::make_shared<CustomWidget>(source);
	widget2->Initialize();

    widget1->AddChild(widget2);

	EXPECT_EQ(widget1.get(), widget2->GetParent().lock().get());
	EXPECT_TRUE(widget1->HasChild(widget2->GetName()));
	EXPECT_TRUE(widget1->HasChild(widget2));
	EXPECT_TRUE(widget1->HasChildren());
	EXPECT_EQ(widget2, widget1->FindChild(widget2->GetName()).lock());
	EXPECT_EQ(widget2, widget1->FindChild<CustomWidget>(widget2->GetName()).lock());
}

TEST(WidgetTest, tree_operations_addition_by_parent) {
    TWidgetSource source;
    source.name = "testRoot";
    source.size = TSize(1, 1);
    auto widget1 = std::make_shared<CustomWidget>(source);
    widget1->Initialize();

    source.name = "testChild";
    auto widget2 = std::make_shared<CustomWidget>(source);
    widget2->Initialize();

    widget2->SetParent(widget1);

    EXPECT_EQ(widget1, widget2->GetParent().lock());
    EXPECT_TRUE(widget1->HasChild(widget2->GetName()));
    EXPECT_TRUE(widget1->HasChild(widget2));
    EXPECT_TRUE(widget1->HasChildren());
    EXPECT_EQ(widget2, widget1->FindChild(widget2->GetName()).lock());
    EXPECT_EQ(widget2, widget1->FindChild<CustomWidget>(widget2->GetName()).lock());
}

TEST(WidgetTest, tree_operations_addition_with_equal_name_is_error) {
    TWidgetSource source;
    source.name = "testRoot";
    source.size = TSize(1, 1);
    auto widget1 = std::make_shared<CustomWidget>(source);
    widget1->Initialize();

    source.name = "testChild";
    auto widget2 = std::make_shared<CustomWidget>(source);
    widget2->Initialize();

    auto widget3 = std::make_shared<CustomWidget>(source);
    widget3->Initialize();

    widget1->AddChild(widget2);
    EXPECT_ANY_THROW(widget1->AddChild(widget3));
}

TEST(WidgetTest, tree_operations_deletion_as_child) {
	TWidgetSource source;
	source.name = "testRoot";
	source.size = TSize(1, 1);
	auto widget1 = std::make_shared<CustomWidget>(source);
	widget1->Initialize();

	source.name = "testChild";
	auto widget2 = std::make_shared<CustomWidget>(source);
	widget2->Initialize();

    widget1->AddChild(widget2);
    widget1->RemoveChild(widget2->GetName());

	EXPECT_FALSE(widget1->HasChild(widget2));
	EXPECT_EQ(TWidgetRef(), widget2->GetParent().lock());
	EXPECT_EQ(TWidgetRef(), widget1->FindChild(widget2->GetName()).lock());
}

TEST(WidgetTest, tree_operations_deletion_by_parent) {
	TWidgetSource source;
	source.name = "testRoot";
	source.size = TSize(1, 1);
	auto widget1 = std::make_shared<CustomWidget>(source);
	widget1->Initialize();

	source.name = "testChild";
	auto widget2 = std::make_shared<CustomWidget>(source);
	widget2->Initialize();

    widget2->SetParent(TWidgetRef());

	EXPECT_FALSE(widget1->HasChild(widget2));
	EXPECT_EQ(TWidgetRef(), widget2->GetParent().lock());
	EXPECT_EQ(TWidgetRef(), widget1->FindChild(widget2->GetName()).lock());
}

TEST(WidgetTest, tree_operations_group) {
	TWidgetSource source;
	source.name = "testRoot";
	source.size = TSize(1, 1);
	auto widget1 = std::make_shared<CustomWidget>(source);
	widget1->Initialize();

	source.name = "testChild1";
	auto widget2 = std::make_shared<CustomWidget>(source);
	widget2->Initialize();

	source.name = "testChild2";
	auto widget3 = std::make_shared<CustomWidget>(source);
	widget3->Initialize();

    widget1->AddChild(widget2);
    widget1->AddChild(widget3);
    widget1->RemoveChildren();

	EXPECT_FALSE(widget1->HasChildren());
}

TEST(WidgetTest, tree_operations_remove_removed_child) {
    TWidgetSource source;
    source.name = "testRoot";
    source.size = TSize(1, 1);
    auto widget1 = std::make_shared<CustomWidget>(source);
    widget1->Initialize();

    source.name = "testChild1";
    auto widget2 = std::make_shared<CustomWidget>(source);
    widget2->Initialize();
    widget1->AddChild(widget2);

    widget2.reset();
    widget1->RemoveChildren();

    EXPECT_FALSE(widget1->HasChildren());
}


int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
