#include "gtest/gtest.h"
#include "Game/Map/level_node_map.h"
#include "Game/Map/level_passability_map.h"
#include "Game/Map/level_tile_map.h"
#include "Game/Map/level_tile_map_tileset.h"


using namespace TD;

// === CLevelTileMap tests ===

class TestCLevelTileMap :
    public ::testing::Test
{
protected:
    static CLevelTileMap::Parameters generateParameters() {
        CLevelTileMap::Parameters parameters;
        parameters.size = CLevelTileMap::Size(4, 5);
        const CLevelTileMap::Tilesets tilesets{1};
        for (size_t layerIndex = 0;
            layerIndex < static_cast<uchar>(CLevelTileMap::Layer::_count);
            ++layerIndex)
        {
            CLevelTileMap::LayerParameters layer;
            for (size_t y = 0; y < parameters.size.y; ++y) {
                for (size_t x = 0; x < parameters.size.x; ++x) {
                    CLevelTileMap::TileParameters tile;
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


TEST(CLevelTileMapTest, ctor_with_default_args_correct) {
    ASSERT_NO_THROW(CLevelTileMap(nullptr));
}

TEST_F(TestCLevelTileMap, ctor_with_custom_args_correct) {
    const auto parameters = generateParameters();
    const CLevelTileMap::Tilesets tilesets{1};

    const CLevelTileMap tileMap(&parameters);

    EXPECT_EQ(parameters.size, tileMap.GetSize());
    EXPECT_GE(parameters.layers.size(), tileMap.GetLayerCount());
    for (size_t layerIndex = 0; layerIndex < parameters.layers.size();
        ++layerIndex)
    {
        size_t tileIndex = 0;
        const auto layer = tileMap.GetLayer(
            static_cast<CLevelTileMap::Layer>(layerIndex));
        for (auto it = layer.first; it != layer.second; ++it) {
            EXPECT_EQ(parameters.layers[layerIndex].tiles[tileIndex].index,
                (*it).index);
            ++tileIndex;
        }
    }
    EXPECT_EQ(tilesets, tileMap.GetTilesets());
}

TEST(CLevelTileMapTest, create_with_default_args_correct) {
    std::unique_ptr<GE::TComponent> component;
    ASSERT_NO_THROW(component = std::move(CLevelTileMap::Create(nullptr)));
    EXPECT_NE(nullptr, component);
}

TEST(CLevelTileMapTest, create_with_wrong_args_fails) {
    const GE::TComponentCreateArgs args;

    ASSERT_ANY_THROW(CLevelTileMap::Create(&args));
}

TEST_F(TestCLevelTileMap, get_size) {
    const auto parameters = generateParameters();
    const CLevelTileMap tileMap(&parameters);

    ASSERT_EQ(parameters.size, tileMap.GetSize());
}

TEST_F(TestCLevelTileMap, set_size_nonzero_accepted) {
    const CLevelTileMap::Size size(3, 5);
    CLevelTileMap tileMap;

    tileMap.SetSize(size);

    EXPECT_EQ(size, tileMap.GetSize());
}

TEST_F(TestCLevelTileMap, set_size_zero_width_failure) {
    const CLevelTileMap::Size size(0, 5);
    CLevelTileMap tileMap;

    ASSERT_ANY_THROW(tileMap.SetSize(size));
}

TEST_F(TestCLevelTileMap, set_size_zero_height_failure) {
    const CLevelTileMap::Size size(3, 0);
    CLevelTileMap tileMap;

    ASSERT_ANY_THROW(tileMap.SetSize(size));
}

TEST_F(TestCLevelTileMap, get_tilesets) {
    const auto parameters = generateParameters();
    const CLevelTileMap::Tilesets tilesets{1};
    const CLevelTileMap tileMap(&parameters);

    ASSERT_EQ(tilesets, tileMap.GetTilesets());
}

TEST_F(TestCLevelTileMap, get_layer) {
    const auto parameters = generateParameters();
    const CLevelTileMap tileMap(&parameters);

    for (size_t layerIndex = static_cast<size_t>(CLevelTileMap::Layer::_min);
        layerIndex < static_cast<size_t>(CLevelTileMap::Layer::_count);
        ++layerIndex)
    {
        ASSERT_NO_THROW(tileMap.GetLayer(
            static_cast<CLevelTileMap::Layer>(layerIndex)));
    }
}

TEST_F(TestCLevelTileMap, get_layer_count) {
    const CLevelTileMap tileMap;

    ASSERT_EQ(static_cast<uchar>(CLevelTileMap::Layer::_count),
        tileMap.GetLayerCount());
}


// === CLevelNodeMap tests ===

class TestCLevelNodeMap :
    public ::testing::Test
{
protected:
    static CLevelNodeMap::Parameters generateParameters() {
        CLevelNodeMap::Parameters parameters;
        parameters.size = Vec2ui(3, 4);
        parameters.enters.push_back(Vec2ui(1, 1));
        parameters.enters.push_back(Vec2ui(2, 3));
        parameters.exits.push_back(Vec2ui(1, 3));
        CLevelNodeMap::Path path1 { {1, 1}, {1, 3} };
        CLevelNodeMap::Path path2 { {2, 3}, {2, 0}, {0, 0}, {0, 2}, {1, 2} };
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

TEST(CLevelNodeMapTest, ctor_with_default_args_correct) {
    ASSERT_NO_THROW(CLevelNodeMap(nullptr));
}

TEST(CLevelNodeMapTest, create_with_default_args_correct) {
    std::unique_ptr<GE::TComponent> component;
    ASSERT_NO_THROW(component = std::move(CLevelNodeMap::Create(nullptr)));
    EXPECT_NE(nullptr, component);
}

TEST(CLevelNodeMapTest, create_with_wrong_args_fails) {
    const GE::TComponentCreateArgs args;

    ASSERT_ANY_THROW(CLevelNodeMap::Create(&args));
}

TEST_F(TestCLevelNodeMap, ctor_with_custom_args_correct) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

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

TEST_F(TestCLevelNodeMap, get_enter_count) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.enters.size(), nodeMap.GetEnterCount());
}

TEST_F(TestCLevelNodeMap, get_enter) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.enters.size(); ++i) {
        EXPECT_EQ(parameters.enters[i], nodeMap.GetEnter(i));
    }
}

TEST_F(TestCLevelNodeMap, get_exit_count) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.exits.size(), nodeMap.GetExitCount());
}

TEST_F(TestCLevelNodeMap, get_exit) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.exits.size(); ++i) {
        EXPECT_EQ(parameters.exits[i], nodeMap.GetExit(i));
    }
}

TEST_F(TestCLevelNodeMap, get_path_count) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    ASSERT_EQ(parameters.pathes.size(), nodeMap.GetPathCount());
}

TEST_F(TestCLevelNodeMap, get_path) {
    const auto parameters = generateParameters();

    const CLevelNodeMap nodeMap(&parameters);

    for (size_t i = 0; i < parameters.pathes.size(); ++i) {
        EXPECT_EQ(parameters.pathes[i], nodeMap.GetPath(i));
    }
}

TEST_F(TestCLevelNodeMap, add_path) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Path path {
        nodeMap.GetEnter(0), nodeMap.GetExit(1)
    };

    nodeMap.AddPath(path);

    EXPECT_EQ(path, nodeMap.GetPath(nodeMap.GetPathCount() - 1));
}

TEST_F(TestCLevelNodeMap, add_enter_unexisting_success) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node enter{0, 0};

    nodeMap.AddEnter(enter);

    EXPECT_EQ(enter, nodeMap.GetEnter(nodeMap.GetEnterCount() - 1));
}

TEST_F(TestCLevelNodeMap, add_enter_existing_failure) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node enter{0, 0};

    nodeMap.AddEnter(enter);
    ASSERT_ANY_THROW(nodeMap.AddEnter(enter));
}

TEST_F(TestCLevelNodeMap, add_exit_unexisting_success) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node exit{0, 0};

    nodeMap.AddExit(exit);

    EXPECT_EQ(exit, nodeMap.GetExit(nodeMap.GetEnterCount() - 1));
}

TEST_F(TestCLevelNodeMap, add_exit_existing_failure) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node exit{0, 0};

    nodeMap.AddExit(exit);
    ASSERT_ANY_THROW(nodeMap.AddExit(exit));
}

TEST_F(TestCLevelNodeMap, find_nearest_exit_existing) {
    const auto parameters = generateParameters();
    CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.enters[1];

    const auto result = nodeMap.FindNearestExit(node.x, node.y);

    ASSERT_EQ(0u, result);
}

TEST_F(TestCLevelNodeMap, find_nearest_exit_unexisting) {
    CLevelNodeMap::Parameters parameters;
    parameters.size = Vec2ui(3, 4);
    parameters.enters = { {1, 1} };
    const CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.enters[0];

    const auto result = nodeMap.FindNearestExit(node.x, node.y);

    ASSERT_EQ(-1u, result);
}

TEST_F(TestCLevelNodeMap, is_enter_enter_if_enter) {
    const auto parameters = generateParameters();
    const CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.enters[0];

    ASSERT_TRUE(nodeMap.IsEnter(node));
}

TEST_F(TestCLevelNodeMap, is_enter_not_enter_if_not_enter) {
    const auto parameters = generateParameters();
    const CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.exits[0];

    ASSERT_FALSE(nodeMap.IsEnter(node));
}

TEST_F(TestCLevelNodeMap, is_exit_exit_if_exit) {
    const auto parameters = generateParameters();
    const CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.exits[0];

    ASSERT_TRUE(nodeMap.IsExit(node));
}

TEST_F(TestCLevelNodeMap, is_exit_not_exit_if_not_exit) {
    const auto parameters = generateParameters();
    const CLevelNodeMap nodeMap(&parameters);
    const CLevelNodeMap::Node node = parameters.enters[0];

    ASSERT_FALSE(nodeMap.IsExit(node));
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
