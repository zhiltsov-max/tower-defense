#include "gtest/gtest.h"
#include "Game/Map/level_node_map.h"
#include "Game/Map/level_passability_map.h"
#include "Game/Map/level_tile_map.h"
#include "Game/Map/level_tile_map_tileset.h"


using namespace TD;

// === TLevelTileMap tests ===

class TestTLevelTileMap :
    public ::testing::Test
{
protected:
    static TLevelTileMap::Parameters generateParameters() {
        TLevelTileMap::Parameters parameters;
        parameters.size = TLevelTileMap::Size(4, 5);
        const TLevelTileMap::Tilesets tilesets{1};
        for (size_t layerIndex = 0;
            layerIndex < static_cast<uchar>(TLevelTileMap::Layer::_count);
            ++layerIndex)
        {
            TLevelTileMap::LayerParameters layer;
            for (size_t y = 0; y < parameters.size.y; ++y) {
                for (size_t x = 0; x < parameters.size.x; ++x) {
                    TLevelTileMap::TileParameters tile;
                    tile.tile = 4;
                    tile.tileset = *tilesets.cbegin();
                    layer.tiles.push_back(tile);
                }
            }
            parameters.layers.push_back(layer);
        }
        return parameters;
    }
};


TEST(TLevelTileMapTest, ctor_with_default_args_correct) {
    ASSERT_NO_THROW(TLevelTileMap());
}

TEST_F(TestTLevelTileMap, ctor_with_custom_args_correct) {
    const auto parameters = generateParameters();
    const TLevelTileMap::Tilesets tilesets{1};
    const TLevelTileMap tileMap(&parameters);

    EXPECT_EQ(parameters.size, tileMap.GetSize());
    EXPECT_GE(parameters.layers.size(), tileMap.GetLayerCount());
    for (size_t layerIndex = 0; layerIndex < parameters.layers.size();
        ++layerIndex)
    {
        size_t tileIndex = 0;
        const auto layer = tileMap.GetLayer(
            static_cast<TLevelTileMap::Layer>(layerIndex));
        for (auto it = layer.first; it != layer.second; ++it) {
            EXPECT_EQ(parameters.layers[layerIndex].tiles[tileIndex].index,
                (*it).index);
            ++tileIndex;
        }
    }
    EXPECT_EQ(tilesets, tileMap.GetTilesets());
}

TEST_F(TestTLevelTileMap, get_size) {
    const auto parameters = generateParameters();
    const TLevelTileMap tileMap(&parameters);

    ASSERT_EQ(parameters.size, tileMap.GetSize());
}

TEST_F(TestTLevelTileMap, set_size_nonzero_accepted) {
    const TLevelTileMap::Size size(3, 5);
    TLevelTileMap tileMap;

    tileMap.SetSize(size);

    EXPECT_EQ(size, tileMap.GetSize());
}

TEST_F(TestTLevelTileMap, set_size_zero_width_failure) {
    const TLevelTileMap::Size size(0, 5);
    TLevelTileMap tileMap;

    ASSERT_ANY_THROW(tileMap.SetSize(size));
}

TEST_F(TestTLevelTileMap, set_size_zero_height_failure) {
    const TLevelTileMap::Size size(3, 0);
    TLevelTileMap tileMap;

    ASSERT_ANY_THROW(tileMap.SetSize(size));
}

TEST_F(TestTLevelTileMap, get_tilesets) {
    const auto parameters = generateParameters();
    const TLevelTileMap::Tilesets tilesets{1};
    const TLevelTileMap tileMap(&parameters);

    ASSERT_EQ(tilesets, tileMap.GetTilesets());
}

TEST_F(TestTLevelTileMap, get_layer) {
    const auto parameters = generateParameters();
    const TLevelTileMap tileMap(&parameters);

    for (size_t layerIndex = static_cast<size_t>(TLevelTileMap::Layer::_min);
        layerIndex < static_cast<size_t>(TLevelTileMap::Layer::_count);
        ++layerIndex)
    {
        ASSERT_NO_THROW(tileMap.GetLayer(
            static_cast<TLevelTileMap::Layer>(layerIndex)));
    }
}

TEST_F(TestTLevelTileMap, get_layer_count) {
    const TLevelTileMap tileMap;

    ASSERT_EQ(static_cast<uchar>(TLevelTileMap::Layer::_count),
        tileMap.GetLayerCount());
}

// === CLevelTileMap Tests ===

TEST(CLevelTileMapTest, create_with_default_args_correct) {
    std::unique_ptr<GE::TComponent> component;
    ASSERT_NO_THROW(component = std::move(CLevelTileMap::Create(nullptr)));
    EXPECT_NE(nullptr, component);
}

TEST(CLevelTileMapTest, create_with_wrong_args_fails) {
    const GE::TComponentCreateArgs args;

    ASSERT_ANY_THROW(CLevelTileMap::Create(&args));
}

// === TLevelNodeMap Tests ===

class TestTLevelNodeMap :
    public ::testing::Test
{
protected:
    static TLevelNodeMap::Parameters generateParameters() {
        TLevelNodeMap::Parameters parameters;
        parameters.size = Vec2ui(3, 4);
        parameters.enters.push_back(Vec2ui(1, 1));
        parameters.enters.push_back(Vec2ui(2, 3));
        parameters.exits.push_back(Vec2ui(1, 3));
        TLevelNodeMap::Path path1 { {1, 1}, {1, 3} };
        TLevelNodeMap::Path path2 { {2, 3}, {2, 0}, {0, 0}, {0, 2}, {1, 2} };
        parameters.pathes = { path1, path2 };
        /*
        [ v | < | < ]
        [ v | * | ^ ]
        [ > | v | ^ ]
        [ _ | o | * ]
        -------------
        <, v, >, ^ - direction of a path
        * - enter
        o - exit
        */
        return parameters;
    }
};

TEST(TLevelNodeMapTest, ctor_with_default_args_correct) {
    ASSERT_NO_THROW(TLevelNodeMap());
}

TEST_F(TestTLevelNodeMap, ctor_with_custom_args_correct) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    EXPECT_EQ(parameters.enters.size(), nodeMap.GetEnterCount());
    for (size_t i = 0; i < parameters.enters.size(); ++i) {
        EXPECT_EQ(parameters.enters[i], nodeMap.GetEnter(i));
    }

    EXPECT_EQ(parameters.exits.size(), nodeMap.GetExitCount());
    for (size_t i = 0; i < parameters.exits.size(); ++i) {
        EXPECT_EQ(parameters.exits[i], nodeMap.GetExit(i));
    }

    EXPECT_EQ(parameters.pathes.size(), nodeMap.GetPathCount());
    for (size_t i = 0; i < parameters.pathes.size(); ++i) {
        EXPECT_EQ(parameters.pathes[i], nodeMap.GetPath(i));
    }
}

TEST_F(TestTLevelNodeMap, get_enter_count) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.enters.size(), nodeMap.GetEnterCount());
}

TEST_F(TestTLevelNodeMap, get_enter) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.enters.size(); ++i) {
        EXPECT_EQ(parameters.enters[i], nodeMap.GetEnter(i));
    }
}

TEST_F(TestTLevelNodeMap, get_exit_count) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.exits.size(), nodeMap.GetExitCount());
}

TEST_F(TestTLevelNodeMap, get_exit) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.exits.size(); ++i) {
        EXPECT_EQ(parameters.exits[i], nodeMap.GetExit(i));
    }
}

TEST_F(TestTLevelNodeMap, get_path_count) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.pathes.size(), nodeMap.GetPathCount());
}

TEST_F(TestTLevelNodeMap, get_path) {
    const auto parameters = generateParameters();

    const TLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.pathes.size(); ++i) {
        EXPECT_EQ(parameters.pathes[i], nodeMap.GetPath(i));
    }
}

TEST_F(TestTLevelNodeMap, add_path) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Path path {
        nodeMap.GetEnter(0), nodeMap.GetExit(1)
    };

    nodeMap.AddPath(path);

    EXPECT_EQ(path, nodeMap.GetPath(nodeMap.GetPathCount() - 1));
}

TEST_F(TestTLevelNodeMap, add_enter_unexisting_success) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node enter{0, 0};

    nodeMap.AddEnter(enter);

    EXPECT_EQ(enter, nodeMap.GetEnter(nodeMap.GetEnterCount() - 1));
}

TEST_F(TestTLevelNodeMap, add_enter_existing_failure) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node enter{0, 0};

    nodeMap.AddEnter(enter);
    ASSERT_ANY_THROW(nodeMap.AddEnter(enter));
}

TEST_F(TestTLevelNodeMap, add_exit_unexisting_success) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node exit{0, 0};

    nodeMap.AddExit(exit);

    EXPECT_EQ(exit, nodeMap.GetExit(nodeMap.GetEnterCount() - 1));
}

TEST_F(TestTLevelNodeMap, add_exit_existing_failure) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node exit{0, 0};

    nodeMap.AddExit(exit);
    ASSERT_ANY_THROW(nodeMap.AddExit(exit));
}

TEST_F(TestTLevelNodeMap, find_nearest_exit_existing) {
    const auto parameters = generateParameters();
    TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.enters[1];

    const auto result = nodeMap.FindNearestExit(node.x, node.y);

    ASSERT_EQ(0u, result);
}

TEST_F(TestTLevelNodeMap, find_nearest_exit_unexisting) {
    TLevelNodeMap::Parameters parameters;
    parameters.size = Vec2ui(3, 4);
    parameters.enters = { {1, 1} };
    const TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.enters[0];

    const auto result = nodeMap.FindNearestExit(node.x, node.y);

    ASSERT_EQ(-1u, result);
}

TEST_F(TestTLevelNodeMap, is_enter_enter_if_enter) {
    const auto parameters = generateParameters();
    const TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.enters[0];

    ASSERT_TRUE(nodeMap.IsEnter(node));
}

TEST_F(TestTLevelNodeMap, is_enter_not_enter_if_not_enter) {
    const auto parameters = generateParameters();
    const TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.exits[0];

    ASSERT_FALSE(nodeMap.IsEnter(node));
}

TEST_F(TestTLevelNodeMap, is_exit_exit_if_exit) {
    const auto parameters = generateParameters();
    const TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.exits[0];

    ASSERT_TRUE(nodeMap.IsExit(node));
}

TEST_F(TestTLevelNodeMap, is_exit_not_exit_if_not_exit) {
    const auto parameters = generateParameters();
    const TLevelNodeMap nodeMap(&parameters);
    const TLevelNodeMap::Node node = parameters.enters[0];

    ASSERT_FALSE(nodeMap.IsExit(node));
}

// === CLevelNodeMap Tests ===

TEST(CLevelNodeMapTest, create_with_default_args_correct) {
    std::unique_ptr<GE::TComponent> component;
    ASSERT_NO_THROW(component = std::move(CLevelNodeMap::Create(nullptr)));
    EXPECT_NE(nullptr, component);
}

TEST(CLevelNodeMapTest, create_with_wrong_args_fails) {
    const GE::TComponentCreateArgs args;

    ASSERT_ANY_THROW(CLevelNodeMap::Create(&args));
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
