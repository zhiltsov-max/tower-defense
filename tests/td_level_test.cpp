#include "gtest/gtest.h"
#include "Game/Level/level.h"


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

    std::unique_ptr<TLevel> level;
    ASSERT_NO_THROW(level.reset(new TLevel(info, &engine)));
}

TEST(LevelTest, ctor_with_null_engine_correct) {
    const TLevel::Parameters info{};

    std::unique_ptr<TLevel> level;
    ASSERT_NO_THROW(level.reset(new TLevel(info, nullptr)));
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
class TestLevelScene :
    ::testing::Test
{
    TestLevelScene() :
        ::testing::Test(),
        engine(nullptr),
        scene(nullptr)
    {}

    virtual void SetUp() override {
        engine.reset(new GE::TGameEngine);
        scene.reset(new TD::TLevelScene(generateInfo(), engine.get()));
    }

protected:
    static TLevel::Parameters generateInfo() {
        return TLevelScene::Parameters();
    }

    std::unique_ptr<GE::TGameEngine> engine;
    std::unique_ptr<TD::TLevelScene> scene;
}

TEST_F(LevelSceneTest, ctor) {

}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
