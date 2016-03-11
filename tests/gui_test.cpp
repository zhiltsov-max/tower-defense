#include "Application/application.h"
#include "GUI/gui_main.h"
#include "GUI/widget_event_system.h"
#include "GUI/widget.h"
#include "GUI/uiparent.h"
#include "gtest.h"



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

    string name = TGUISettings::DEFAULT_UIPARENT_NAME;
    EXPECT_EQ(name, GetName());
}

TEST_F(TestUIParent, modification) {
    EXPECT_NO_THROW(SetMargin(TPadding(3, 4, 5, 6)));
    EXPECT_NO_THROW(SetPosition(TCoordinate(30, 40)));
    EXPECT_NO_THROW(SetSize(TSize(10, 20)));
    EXPECT_NO_THROW(SetVisibility(false));
    EXPECT_NO_THROW(SetParent(TWidgetRef()));

    EXPECT_EQ(TSize(10 + 5 + 6, 20 + 3 + 4), GetSize());
    EXPECT_EQ(TPadding(3, 4, 5, 6), GetMargin());
    EXPECT_EQ(TCoordinate(30, 40), GetPosition());
    EXPECT_FALSE(IsShown());
}

TEST(UIParent_test, shared) {
    auto uiparent_storage = std::make_shared<TUIParent>(TestUIParent::source);
    auto& uiparent = *uiparent_storage;

    EXPECT_NO_THROW(uiparent.shared_from_this());
}


// ### Signals and slots system ###
TEST(SignalTest, initialization) {
    const SignalID id = "testSignal";

    TWidgetSignal signal(id);
    EXPECT_EQ(id, signal.GetID());
}

TEST(SlotTest, initialization_and_execution) {
    const SlotID id = "testSignal";
    bool methodExecuted = false;
    auto method = [&] (TWidget*, void**) {
        methodExecuted = true;
    };
    TWidgetSlot slot(TWidgetWeakRef(), id, method);
    EXPECT_EQ(id, slot.GetID());
    EXPECT_TRUE(slot.HasPtr());
    EXPECT_EQ(TWidgetRef(), slot.GetOwner().lock());

    EXPECT_NO_THROW(slot.Invoke());
    EXPECT_TRUE(methodExecuted);
}

class TestEventSystem :
    public ::testing::Test,
    public TWidgetEventSystem
{};

TEST_F(TestEventSystem, signals_and_slots_system) {
    const SignalID id = "testSignal";

    EXPECT_NO_THROW(AddSignal(Signal(id)));
    EXPECT_TRUE(HasSignal(id));
    Signal& signal = GetSignal(id);

    bool methodExecuted = false;
    auto method = [&] (TWidget* object, void** args) {
        methodExecuted = true;
        UNUSED(object)
        UNUSED(args)
    };
    Slot listener(TWidgetWeakRef(), id, method);
    EXPECT_NO_THROW(signal.AddListener(listener));
    EXPECT_TRUE(signal.HasListener(listener));

    EXPECT_NO_THROW(AddSlot(listener));
    EXPECT_TRUE(HasSlot(listener.GetID()));

    EXPECT_NO_THROW(signal.Send());
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
    static void slot_TestSlot(TWidget*, void*) {
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


TEST_F(TestWidget, initialization) {
    EXPECT_EQ(source.name, GetName());
    EXPECT_EQ(source.position, GetPosition());
    EXPECT_EQ(source.show, IsShown());
    EXPECT_EQ(source.margin, GetMargin());
    EXPECT_EQ(source.size, GetOwnSize());
    EXPECT_EQ(source.size +
            TSize(source.margin.left + source.margin.right,
                source.margin.bottom + source.margin.top),
        GetSize());

    EXPECT_EQ(eventSystem.GetSignals().size(), _enumSignals().size());
    EXPECT_EQ(eventSystem.GetSlots().size(), _enumSlots().size());

    EXPECT_TRUE(eventSystem.HasSignal(testSignal));
    EXPECT_TRUE(eventSystem.HasSlot(testSlot));
}

TEST_F(TestWidget, modification) {
    EXPECT_NO_THROW(SetMargin(TPadding(4, 3, 2, 1)));
    EXPECT_EQ(TPadding(4, 3, 2, 1), GetMargin());

    EXPECT_NO_THROW(SetParent(TWidgetWeakRef()));
    EXPECT_EQ(TWidgetWeakRef().lock(), GetParent().lock());

    EXPECT_NO_THROW(SetPosition(TCoordinate(3, 3)));
    EXPECT_EQ(TCoordinate(3, 3), GetPosition());

    EXPECT_NO_THROW(SetSize(TSize(2, 2)));
    EXPECT_EQ(TSize(2, 2), GetOwnSize());

    EXPECT_NO_THROW(SetVisibility(true));
    EXPECT_EQ(true, IsShown());
}

class CustomWidget : public TWidget
{
public:
    CustomWidget(const TWidgetSource& source) :
        TWidget(source)
    {}
private:
    virtual void _draw(TRenderTarget&) override {}
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

    EXPECT_NO_THROW(widget1->AddChild(widget2));
	EXPECT_ANY_THROW(widget1->AddChild(widget2));

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
	
	EXPECT_NO_THROW(widget2->SetParent(widget1));

    EXPECT_EQ(widget1, widget2->GetParent().lock());
	EXPECT_TRUE(widget1->HasChild(widget2->GetName()));
	EXPECT_TRUE(widget1->HasChild(widget2));
	EXPECT_TRUE(widget1->HasChildren());
    EXPECT_EQ(widget2, widget1->FindChild(widget2->GetName()).lock());
    EXPECT_EQ(widget2, widget1->FindChild<CustomWidget>(widget2->GetName()).lock());
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

	EXPECT_NO_THROW(widget1->AddChild(widget2));
    EXPECT_NO_THROW(widget1->RemoveChild(widget2->GetName()));
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

	EXPECT_NO_THROW(widget2->SetParent(TWidgetRef()));

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

	EXPECT_NO_THROW(widget1->AddChild(widget2));
	EXPECT_NO_THROW(widget1->AddChild(widget3));
	EXPECT_NO_THROW(widget1->RemoveChildren());
	EXPECT_FALSE(widget1->HasChildren());
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
