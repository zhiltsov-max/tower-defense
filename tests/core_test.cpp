#include "gtest.h"

#include "Core/core.h"


// ### SPLIT TESTS ###
TEST(splitTest, split_string_by_string_1) {
    const string s("del 10del 20del 30del 40del 502387del del del 7del 0del ");
    const string sep("del ");

    vector<string> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(11u, res.size());
}

TEST(splitTest, split_string_by_string_1_2) {
    const string s("del 10del 20");
    const string sep("del ");

    vector<string> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(3u, res.size());
}

TEST(splitTest, split_string_by_1b_char_1) {
    const string s("del 10dddel d20deld");
    const char sep('d');

    vector<string> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(8u, res.size());
}

TEST(splitTest, split_string_by_1b_char_2) {
    const string s("del 10dddel123");
    const char sep('d');

    vector<string> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(5u, res.size());
}

TEST(splitTest, split_string_by_length_1) {
    const string str = "1234567";
    const size_t partSize = 3;
    vector<string> res;
    EXPECT_NO_THROW(res = String::splitByLength(str, partSize));
    EXPECT_EQ(3u, res.size());
    EXPECT_EQ("123", res[0]);
    EXPECT_EQ("456", res[1]);
    EXPECT_EQ("7", res[2]);
}


#if defined(UNICODE)

TEST(splitTest, split_wstring_by_wstring) {
    const wstring s(L"dфl фбв10dфl 2вуап0dфl 3ывп0dфl 4фы0dфl ыфва502387dфl ываdфl dфlыв7dфl 0dфl ");
    const wstring sep(L"dфl ");

    vector<wstring> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(10u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_1) {
    const wstring s(L"ф фбв10del 2вуапфф");
    const wchar_t sep(L'ф');

    vector<wstring> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(5u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_2) {
    const wstring s(L"ф фбв10dфa");
    const wchar_t sep(L'ф');

    vector<wstring> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(4u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_3) {
    const wstring s(L"正體字體體/繁體字體");
    const wchar_t sep(L'體');

    vector<wstring> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(6u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_4) {
    const wstring s(L"");
    const wchar_t sep(L'體');

    vector<wstring> res;
    ASSERT_NO_THROW(res = String::split(s, sep));
    ASSERT_EQ(1u, res.size());
}

TEST(splitTest, split_wstring_by_length_1) {
    const wstring str = L"фывапрол";
    const size_t partSize = 3;
    vector<wstring> res;
    EXPECT_NO_THROW(res = String::splitByLength(str, partSize));
    EXPECT_EQ(3u, res.size());
    EXPECT_EQ(L"фыв", res[0]);
    EXPECT_EQ(L"апр", res[1]);
    EXPECT_EQ(L"ол", res[2]);
}
#endif //UNICODE



//### JOIN TESTS ###
TEST(joinTest, join_string_without_glue) {
    const vector<string> parts = {
        "123", "456", "789"
    };
    string res;
    ASSERT_NO_THROW(res = String::join(parts));
    ASSERT_EQ("123456789", res);
}

TEST(joinTest, join_string_with_glue_1) {
    const vector<string> parts = {
        "123", "456", "789"
    };
    const string glue("abc");
    string res;
    ASSERT_NO_THROW(res = String::join(parts, glue));
    ASSERT_EQ("123abc456abc789", res);
}

TEST(joinTest, join_string_with_glue_2) {
    const vector<string> parts = {
        "123", "456", "789"
    };
    const char glue('a');
    string res;
    ASSERT_NO_THROW(res = String::join(parts, glue));
    ASSERT_EQ("123a456a789", res);
}


#if defined(UNICODE)

TEST(joinTest, join_wstring_without_glue) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };
    wstring res;
    ASSERT_NO_THROW(res = String::join(parts));
    ASSERT_EQ(L"123456789", res);
}

TEST(joinTest, join_wstring_with_glue_1) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };
    const wstring glue(L"體аб正 ");
    wstring res;
    ASSERT_NO_THROW(res = String::join(parts, glue));
    ASSERT_EQ(L"123體аб正 456體аб正 789", res);
}

TEST(joinTest, join_wstring_with_glue_2) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };
    const wchar_t glue(L'體');
    wstring res;
    ASSERT_NO_THROW(res = String::join(parts, glue));
    ASSERT_EQ(L"123體456體789", res);
}

#endif //UNICODE


//### OTHER TESTS ###
//=== STARTS WITH ===
TEST(startsWith, string_1) {
    const string str("abcd");
    const string prefix("ab");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, string_2) {
    const string str("abcd");
    const string prefix("");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, string_3) {
    const string str("cd");
    const string prefix("ab");
    EXPECT_FALSE(String::startsWith(str, prefix));
}


#if defined(UNICODE)

TEST(startsWith, wstring_1) {
    const wstring str(L"體фcd");
    const wstring prefix(L"體ф");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, wstring_2) {
    const wstring str(L"cd");
    const wstring prefix(L"體b");
    EXPECT_FALSE(String::startsWith(str, prefix));
}

#endif //UNICODE


//=== ENDS WITH ===
TEST(endsWith, string_1) {
    const string str("abcd");
    const string ending("cd");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, string_2) {
    const string str("abcd");
    const string ending("");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, string_3) {
    const string str("ab");
    const string ending("cd");
    EXPECT_FALSE(String::endsWith(str, ending));
}


#if defined(UNICODE)

TEST(endsWith, wstring_1) {
    const wstring str(L"cdf體ф");
    const wstring ending(L"體ф");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, wstring_2) {
    const wstring str(L"cd");
    const wstring ending(L"體b");
    EXPECT_FALSE(String::endsWith(str, ending));
}

#endif //UNICODE



//=== RIGHT ===
TEST(rightTest, string_1) {
    const string str = "123456";
    const size_t pos = 0;
    string res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_EQ("123456", res);
}

TEST(rightTest, string_2) {
    const string str = "123456";
    const size_t pos = 4;
    string res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_EQ("56", res);
}

TEST(rightTest, string_3) {
    const string str = "123456";
    const size_t pos = 8;
    string res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_TRUE(res.empty());
}


#if defined(UNICODE)

TEST(rightTest, wstring_1) {
    const wstring str = L"123456";
    const size_t pos = 0;
    wstring res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_EQ(L"123456", res);
}

TEST(rightTest, wstring_2) {
    const wstring str = L"123456";
    const size_t pos = 4;
    wstring res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_EQ(L"56", res);
}

TEST(rightTest, wstring_3) {
    const wstring str = L"123456";
    const size_t pos = 8;
    wstring res;
    EXPECT_NO_THROW(res = String::right(str, pos));
    EXPECT_TRUE(res.empty());
}

#endif //UNICODE


//=== LEFT ===
TEST(leftTest, string_1) {
    const string str = "123456";
    const size_t pos = 0;
    string res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_TRUE(res.empty());
}

TEST(leftTest, string_2) {
    const string str = "123456";
    const size_t pos = 4;
    string res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_EQ("1234", res);
}

TEST(leftTest, string_3) {
    const string str = "123456";
    const size_t pos = 8;
    string res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_EQ("123456", res);
}


#if defined(UNICODE)

TEST(leftTest, wstring_1) {
    const wstring str = L"фывапр";
    const size_t pos = 0;
    wstring res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_TRUE(res.empty());
}

TEST(leftTest, wstring_2) {
    const wstring str = L"фывапр";
    const size_t pos = 4;
    wstring res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_EQ(L"фыва", res);
}

TEST(leftTest, wstring_3) {
    const wstring str = L"фывапр";
    const size_t pos = 8;
    wstring res;
    EXPECT_NO_THROW(res = String::left(str, pos));
    EXPECT_EQ(L"фывапр", res);
}

#endif //UNICODE


// To lower
TEST(toLowerTest, string_1) {
    const string str = "ABC";
    EXPECT_EQ("abc", String::toLower(str));
}


#if defined(UNICODE)

TEST(toLowerTest, wstring_1) {
    const wstring str = L"ФЫВ";
    setlocale(LC_ALL, "Russian");
    const std::locale loc("");
    EXPECT_EQ(L"фыв", String::toLower(str, loc));
}

#endif //UNICODE


// To wide
#if defined(UNICODE)

TEST(toWide, wstring_1) {
    const string str = "abc";
    wstring res;
    EXPECT_NO_THROW(res = String::toWide(str));
    EXPECT_EQ(L"abc", res);
}

#endif //UNICODE


//### PARSER TESTS ###
TEST(parserTest, parse_test_1) {
    const string fileData = "{map:{size:{width:16;height:12;};layers:{count:4;0:{tiles:[1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1];};1:{tiles:[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,3,3,3,4,0,0,0,0,0,0,3,3,4,0,0,2,0,0,0,7,4,0,0,0,0,0,0,0,2,0,0,2,0,0,0,0,2,0,0,0,0,0,0,0,7,3,3,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];};2:[];3:[];};nodes:{enters:{count:1;0:[0,3];};exits:{count:1;0:[10,5];};pathes:{count:1;0:{count:17;enter:0;0:[1,3];1:[2,3];2:[2,4];3:[2,5];4:[3,5];5:[4,5];6:[5,5];7:[5,4];8:[5,3];9:[5,2];10:[6,2];11:[7,2];12:[8,2];13:[9,2];14:[9,3];15:[10,3];16:[10,4];exit:0;};};};gameObjects:{count:2;0:{type:building;id:-1;x:10.5;y:5.5;};1:{type:building;id:4;x:2.5;y:6;messageBubbleName:MessageBubble;};};tileset:Data/Levels/tileData.dat;};scripts:{pathes:[scriptCore.lua,level1.lua];};stages:{mobs:{healthGrowth:1.1;rewardGrowth:1.3;speedGrowth:1.1;};count:5;0:{buildings:{-1:{repairable:1;};};quests:{2:[1,1];};scripts:{_:1;};};1:{quests:{3:[1,1];};};2:{quests:{4:[1,1];};};3:{quests:{5:[1,1];};};4:{quests:{6:[1,1];};mobs:{1:{health:10;};};};};player:{credits:2000;};resources:{gameObjects:{mobs:{id:[1,3];};buildings:{id:[-1,1,2,3,4];};};tileset:I64,64,Data/Levels/Tiles.png,0,128;};};";
    std::stringstream ss;
    ss << fileData;

    TNamedData<string> parsed;
    EXPECT_NO_THROW(parsed = std::move(ParseData(ss)));
    TNamedData<string> expectation {
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
    TNamedData<string> res;
    EXPECT_NO_THROW(res = std::move(parsed.slice(string("map") + parsed.keySep() + "nodes")));
    EXPECT_EQ(expectation, res);
}

TEST(parserTest, parse_test_unexpected_eof) {
    const string fileData = "{2352:1234;";
    std::stringstream ss;
    ss << fileData;

    TMyON_DataReader parser(ss);
    EXPECT_TRUE(parser.parse());
    EXPECT_EQ("Unexpected file end: closing parenthesis was not found.", parser.getError());
}

TEST(parserTest, parse_test_unexpected_value) {
    const string fileData = "{:2134;";
    std::stringstream ss;
    ss << fileData;

    TMyON_DataReader parser(ss);
    EXPECT_TRUE(parser.parse());
    EXPECT_EQ("Empty key for value at pos 2.", parser.getError());
}


//### POINT TESTS ###
TEST(pointTest, arihmetics_and_logics_operators) {
    using Point = Point2i;

    Point p1(10, 15);
    Point p2(4, 5);

    EXPECT_TRUE(p1 > p2);
    EXPECT_FALSE(p1 < p2);
    EXPECT_FALSE(p1 == p2);
    EXPECT_TRUE(p1 != p2);

    EXPECT_EQ(Point(14, 20), p1 + p2);
    EXPECT_EQ(Point(6, 10), p1 - p2);
    EXPECT_EQ(Point(20, 45), p1 * Point(2, 3));
    EXPECT_EQ(Point(2, 3), p1 / Point(5, 5));

    EXPECT_EQ(Point(50, 75), p1 * 5);
    EXPECT_EQ(Point(2, 3), p1 / 5);
    EXPECT_EQ(Point(12, 17), p1 + 2);
    EXPECT_EQ(Point(8, 13), p1 - 2);

    EXPECT_NO_THROW(p1 += p2);
    EXPECT_EQ(Point(14, 20), p1);

#if defined(_DEBUG)
    EXPECT_ANY_THROW(p1[3]);
#else
    EXPECT_NO_THROW(p1[3]);
#endif
}

TEST(pointTest, operations) {
    using Point = Point2i;

    EXPECT_DOUBLE_EQ(5.0, norm(Point(3, 4)));
    EXPECT_DOUBLE_EQ(25.0, norm(Point(3, 4), NormType::NORM_SQUARED));

    EXPECT_EQ(Point(1, 2), abs(Point(-1, 2)));


    EXPECT_TRUE(Point(1, 2).isInRect(
            Point(0, 1), Point(2, 3)
        ));
    EXPECT_TRUE(Point(1, 2).isInRect(
            Point(2, 3), Point(0, 1)
        ));

    EXPECT_FALSE(Point(1, 2).isInRect(
            Point(1, 3), Point(2, 3)
        ));
    EXPECT_FALSE(Point(1, 2).isInRect(
            Point(2, 3), Point(1, 3)
        ));
}

TEST(pointTest, serialization) {
    using Point = Point<double, 5>;
    Point point;
    point[0] = 4.0;
    point[1] = 2.0;
    point[2] = 1.0;
    point[3] = 1.0;
    point[4] = 6.0;

    EXPECT_FALSE(string(point).empty());

#if defined(UNICODE)
    EXPECT_FALSE(wstring(point).empty());
#endif
}




int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
