#include <sstream>

#include "gtest/gtest.h"

#include "GameEngine/Utility/data_structures.h"


using namespace GE;

TEST(parserTest, parse_and_slice_difficult_correct) {
    const string fileData = "{map:{size:{width:16;height:12;};layers:{count:4;0:{tiles:[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1];};1:{tiles:[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,3,3,3,4,0,0,0,0,0,0,3,3,4,0,0,2,0,0,0,7,4,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];};2:[];3:[];};nodes:{enters:{count:1;0:[0,3];};exits:{count:1;0:[10,5];};pathes:{count:1;0:{count:17;enter:0;0:[1,3];1:[2,3];2:[2,4];3:[2,5];4:[3,5];5:[4,5];6:[5,5];7:[5,4];8:[5,3];9:[5,2];10:[6,2];11:[7,2];12:[8,2];13:[9,2];14:[9,3];15:[10,3];16:[10,4];exit:0;};};};gameObjects:{count:2;0:{type:building;id:-1;x:10.5;y:5.5;};1:{type:building;id:4;x:2.5;y:6;messageBubbleName:MessageBubble;};};tileset:Data/Levels/tileData.dat;};scripts:{pathes:[scriptCore.lua,level1.lua];};stages:{mobs:{healthGrowth:1.1;rewardGrowth:1.3;speedGrowth:1.1;};count:5;0:{buildings:{-1:{repairable:1;};};quests:{2:[1,1];};scripts:{_:1;};};1:{quests:{3:[1,1];};};2:{quests:{4:[1,1];};};3:{quests:{5:[1,1];};};4:{quests:{6:[1,1];};mobs:{1:{health:10;};};};};player:{credits:2000;};resources:{gameObjects:{mobs:{id:[1,3];};buildings:{id:[-1,1,2,3,4];};};tileset:I64,64,Data/Levels/Tiles.png,0,128;};};";
    std::stringstream ss;
    ss << fileData;

    const auto parsed = ParseData(ss);

    const TNamedData<string> expectation {
        {"map:nodes", ""},
        {"map:nodes:enters", ""},
        {"map:nodes:enters:0", "[0,3]"},
        {"map:nodes:enters:count", "1"},
        {"map:nodes:exits", ""},
        {"map:nodes:exits:0", "[10,5]"},
        {"map:nodes:exits:count", "1"},
        {"map:nodes:pathes", ""},
        {"map:nodes:pathes:0", ""},
        {"map:nodes:pathes:0:0", "[1,3]"},
        {"map:nodes:pathes:0:1", "[2,3]"},
        {"map:nodes:pathes:0:10", "[6,2]"},
        {"map:nodes:pathes:0:11", "[7,2]"},
        {"map:nodes:pathes:0:12", "[8,2]"},
        {"map:nodes:pathes:0:13", "[9,2]"},
        {"map:nodes:pathes:0:14", "[9,3]"},
        {"map:nodes:pathes:0:15", "[10,3]"},
        {"map:nodes:pathes:0:16", "[10,4]"},
        {"map:nodes:pathes:0:2", "[2,4]"},
        {"map:nodes:pathes:0:3", "[2,5]"},
        {"map:nodes:pathes:0:4", "[3,5]"},
        {"map:nodes:pathes:0:5", "[4,5]"},
        {"map:nodes:pathes:0:6", "[5,5]"},
        {"map:nodes:pathes:0:7", "[5,4]"},
        {"map:nodes:pathes:0:8", "[5,3]"},
        {"map:nodes:pathes:0:9", "[5,2]"},
        {"map:nodes:pathes:0:count", "17"},
        {"map:nodes:pathes:0:enter", "0"},
        {"map:nodes:pathes:0:exit", "0"},
        {"map:nodes:pathes:count", "1"}
    };
    const auto res = parsed.slice(string("map") + parsed.keySep() + "nodes");
    ASSERT_EQ(expectation, res);
}

TEST(parserTest, parse_unexpected_eof) {
    const string fileData = "{2352:1234;";
    std::stringstream ss;
    ss << fileData;

    TMyON_DataReader parser(ss);
    EXPECT_TRUE(parser.parse());
    EXPECT_EQ("Unexpected file end: closing parenthesis was not found.", parser.getError());
}

TEST(parserTest, parse_unexpected_value) {
    const string fileData = "{:2134;";
    std::stringstream ss;
    ss << fileData;

    TMyON_DataReader parser(ss);
    EXPECT_TRUE(parser.parse());
    EXPECT_EQ("Empty key for value at pos 2.", parser.getError());
}