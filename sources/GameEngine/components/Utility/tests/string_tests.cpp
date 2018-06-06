#include "gtest/gtest.h"

#include "GameEngine/Utility/data_structures.h"


using namespace GE;

TEST(splitTest, split_string_by_string_1) {
    const string s("del 10del 20del 30del 40del 502387del del del 7del 0del ");
    const string sep("del ");

    vector<string> res = String::split(s, sep);

    ASSERT_EQ(11u, res.size());
}

TEST(splitTest, split_string_by_string_1_2) {
    const string s("del 10del 20");
    const string sep("del ");

    vector<string> res = String::split(s, sep);

    ASSERT_EQ(3u, res.size());
}

TEST(splitTest, split_string_by_1b_char_1) {
    const string s("del 10dddel d20deld");
    const char sep('d');

    vector<string> res = String::split(s, sep);
    ASSERT_EQ(8u, res.size());
}

TEST(splitTest, split_string_by_1b_char_2) {
    const string s("del 10dddel123");
    const char sep('d');

    vector<string> res = String::split(s, sep);

    ASSERT_EQ(5u, res.size());
}

TEST(splitTest, split_string_by_length_1) {
    const string str = "1234567";
    const size_t partSize = 3;

    vector<string> res = String::splitByLength(str, partSize);

    EXPECT_EQ(3u, res.size());
    EXPECT_EQ("123", res[0]);
    EXPECT_EQ("456", res[1]);
    EXPECT_EQ("7", res[2]);
}


#if defined(UNICODE)

TEST(splitTest, split_wstring_by_wstring) {
    const wstring s(L"dфl фбв10dфl 2вуап0dфl 3ывп0dфl 4фы0dфl ыфва502387dфl ываdфl dфlыв7dфl 0dфl ");
    const wstring sep(L"dфl ");

    vector<wstring> res = String::split(s, sep);

    ASSERT_EQ(10u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_1) {
    const wstring s(L"ф фбв10del 2вуапфф");
    const wchar_t sep(L'ф');

    vector<wstring> res = String::split(s, sep);

    ASSERT_EQ(5u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_2) {
    const wstring s(L"ф фбв10dфa");
    const wchar_t sep(L'ф');

    vector<wstring> res = String::split(s, sep);

    ASSERT_EQ(4u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_3) {
    const wstring s(L"正體字體體/繁體字體");
    const wchar_t sep(L'體');

    vector<wstring> res = String::split(s, sep);

    ASSERT_EQ(6u, res.size());
}

TEST(splitTest, split_wstring_by_widechar_4) {
    const wstring s(L"");
    const wchar_t sep(L'體');

    vector<wstring> res = String::split(s, sep);

    ASSERT_EQ(1u, res.size());
}

TEST(splitTest, split_wstring_by_length_1) {
    const wstring str = L"фывапрол";
    const size_t partSize = 3;

    vector<wstring> res = String::splitByLength(str, partSize);

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

    string res = String::join(parts);

    ASSERT_EQ("123456789", res);
}

TEST(joinTest, join_string_with_glue_string) {
    const vector<string> parts = {
        "123", "456", "789"
    };
    const string glue{ "abc" };

    string res = String::join(parts, glue);

    ASSERT_EQ("123abc456abc789", res);
}

TEST(joinTest, join_string_with_glue_single_character) {
    const vector<string> parts = {
        "123", "456", "789"
    };
    const char glue{ 'a' };

    string res = String::join(parts, glue);

    ASSERT_EQ("123a456a789", res);
}


#if defined(UNICODE)

TEST(joinTest, join_wstring_without_glue) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };

    wstring res = String::join(parts);

    ASSERT_EQ(L"123456789", res);
}

TEST(joinTest, join_wstring_with_glue_string) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };
    const wstring glue{ L"體аб正 " };

    wstring res = String::join(parts, glue);

    ASSERT_EQ(L"123體аб正 456體аб正 789", res);
}

TEST(joinTest, join_wstring_with_glue_single_character) {
    const vector<wstring> parts = {
        L"123", L"456", L"789"
    };
    const wchar_t glue{ L'體' };

    wstring res = String::join(parts, glue);

    ASSERT_EQ(L"123體456體789", res);
}

#endif //UNICODE


//### OTHER TESTS ###
//=== STARTS WITH ===
TEST(startsWith, string_regular) {
    const string str("abcd");
    const string prefix("ab");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, string_empty) {
    const string str("abcd");
    const string prefix("");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, string_wrong) {
    const string str("cd");
    const string prefix("ab");
    EXPECT_FALSE(String::startsWith(str, prefix));
}


#if defined(UNICODE)

TEST(startsWith, wstring_regular) {
    const wstring str(L"體фcd");
    const wstring prefix(L"體ф");
    EXPECT_TRUE(String::startsWith(str, prefix));
}

TEST(startsWith, wstring_wrong) {
    const wstring str(L"cd");
    const wstring prefix(L"體b");
    EXPECT_FALSE(String::startsWith(str, prefix));
}

#endif //UNICODE


//=== ENDS WITH ===
TEST(endsWith, string_regular) {
    const string str("abcd");
    const string ending("cd");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, string_empty) {
    const string str("abcd");
    const string ending("");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, string_wrong) {
    const string str("ab");
    const string ending("cd");
    EXPECT_FALSE(String::endsWith(str, ending));
}


#if defined(UNICODE)

TEST(endsWith, wstring_regular) {
    const wstring str(L"cdf體ф");
    const wstring ending(L"體ф");
    EXPECT_TRUE(String::endsWith(str, ending));
}

TEST(endsWith, wstring_wrong) {
    const wstring str(L"cd");
    const wstring ending(L"體b");
    EXPECT_FALSE(String::endsWith(str, ending));
}

#endif //UNICODE



//=== RIGHT ===
TEST(rightTest, string_full) {
    const string str = "123456";
    const size_t pos = 0;

    string res = String::right(str, pos);

    EXPECT_EQ("123456", res);
}

TEST(rightTest, string_part) {
    const string str = "123456";
    const size_t pos = 4;

    string res = String::right(str, pos);

    EXPECT_EQ("56", res);
}

TEST(rightTest, string_out_of_bounds) {
    const string str = "123456";
    const size_t pos = 8;

    string res = String::right(str, pos);

    EXPECT_TRUE(res.empty());
}


#if defined(UNICODE)

TEST(rightTest, wstring_full) {
    const wstring str = L"123456";
    const size_t pos = 0;

    wstring res = String::right(str, pos);

    EXPECT_EQ(L"123456", res);
}

TEST(rightTest, wstring_part) {
    const wstring str = L"123456";
    const size_t pos = 4;

    wstring res = String::right(str, pos);

    EXPECT_EQ(L"56", res);
}

TEST(rightTest, wstring_out_of_bounds) {
    const wstring str = L"123456";
    const size_t pos = 8;

    wstring res = String::right(str, pos);

    EXPECT_TRUE(res.empty());
}

#endif //UNICODE


//=== LEFT ===
TEST(leftTest, string_empty) {
    const string str = "123456";
    const size_t pos = 0;

    string res = String::left(str, pos);

    EXPECT_TRUE(res.empty());
}

TEST(leftTest, string_part) {
    const string str = "123456";
    const size_t pos = 4;

    string res = String::left(str, pos);

    EXPECT_EQ("1234", res);
}

TEST(leftTest, string_out_of_bounds) {
    const string str = "123456";
    const size_t pos = 8;

    string res = String::left(str, pos);

    EXPECT_EQ("123456", res);
}


#if defined(UNICODE)

TEST(leftTest, wstring_empty) {
    const wstring str = L"фывапр";
    const size_t pos = 0;

    wstring res = String::left(str, pos);

    EXPECT_TRUE(res.empty());
}

TEST(leftTest, wstring_part) {
    const wstring str = L"фывапр";
    const size_t pos = 4;

    wstring res = String::left(str, pos);

    EXPECT_EQ(L"фыва", res);
}

TEST(leftTest, wstring_out_of_bounds) {
    const wstring str = L"фывапр";
    const size_t pos = 8;

    wstring res = String::left(str, pos);

    EXPECT_EQ(L"фывапр", res);
}

#endif //UNICODE


// To lower
TEST(toLowerTest, string_regular) {
    const string str = "ABC";
    EXPECT_EQ("abc", String::toLower(str));
}


#if defined(UNICODE)

TEST(toLowerTest, wstring_regular) {
    const wstring expected { L"asd" };
    const wstring str { L"ASD" };
    const std::locale loc { std::locale::classic() };

    ASSERT_EQ(expected, String::toLower(str, loc));
}

#endif //UNICODE


// To wide
#if defined(UNICODE)

TEST(toWide, wstring_regular) {
    const string str = "abc";
    wstring res;

    res = String::toWide(str);

    EXPECT_EQ(L"abc", res);
}

#endif //UNICODE