// Copyright (c) 2026 Shkelev Egor

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <set>
#include "textgen.h"

int CountWords(const std::string& s) {
    if (s.empty()) return 0;
    int count = 0;
    std::istringstream iss(s);
    std::string w;
    while (iss >> w) ++count;
    return count;
}

TEST(TextGeneratorTest, PrefixFormationFromNPREF) {
    TextGenerator gen("Hello my world");
    prefix firstPref = gen.getFirstPrefix();
    EXPECT_EQ(firstPref.size(), 2);
    EXPECT_EQ(firstPref[0], "hello");
    EXPECT_EQ(firstPref[1], "my");
}

TEST(TextGeneratorTest, PrefixSuffix) {
    TextGenerator gen("Hello my world");
    auto& table = gen.getStateTable();
    prefix curr = { "Hello", "my" };
    auto it = table.find(curr);
    ASSERT_NE(it, table.end());
    EXPECT_EQ(it->second.size(), 1);
    EXPECT_EQ(it->second[0], "world");
}

TEST(TextGeneratorTest, SingleSuffixSelection) {
    TextGenerator gen("Hello my world");
    std::string output = gen.Generate();
    EXPECT_EQ(output, "Hello my world");
}

TEST(TextGeneratorTest, MultipleSuffixes) {
    TextGenerator gen("Hello my world Hello my home");
    auto& table = gen.getStateTable();
    prefix curr = { "Hello", "my" };
    auto it = table.find(curr);
    ASSERT_NE(it, table.end());
    EXPECT_EQ(it->second.size(), 2);
    std::set<std::string> suffixes(it->second.begin(), it->second.end());
    EXPECT_TRUE(suffixes.count("world"));
    EXPECT_TRUE(suffixes.count("home"));
}

TEST(TextGeneratorTest, MultipleSuffixesSelection) {
    TextGenerator gen("Hello my world Hello my home");
    std::set<std::string> seen;
    bool flag1 = false, flag2 = false;
    while (!flag1 && !flag2) {
        std::string out = gen.Generate();
        std::istringstream iss(out);
        std::string w1, w2, w3;
        iss >> w1 >> w2 >> w3;
        if (w1 == "Hello" && w2 == "my") {
            if (w3 == "world") {
                flag1 = true;
            }
            if (w3 == "home") {
                flag2 = true;
            }
        }
    }
    EXPECT_TRUE(flag1);
    EXPECT_TRUE(flag2);
}

TEST(TextGeneratorTest, CheckMAXGEN) {
    std::string long_input;
    for (int i = 0; i < 1500; ++i) long_input += "word ";
    TextGenerator gen(long_input);
    std::string out = gen.Generate();
    int word_count = CountWords(out);
    EXPECT_LE(word_count, 1000);
}

TEST(TextGeneratorTest, GenerationLength) {
    TextGenerator gen("one two three four");
    std::string out = gen.Generate();
    EXPECT_EQ(CountWords(out), 4);
}

TEST(TextGeneratorTest, TerminationWhenNoSuffix) {
    TextGenerator gen("Hello my world");
    std::string out = gen.Generate();
    EXPECT_EQ(out, "Hello my world");
}

TEST(TextGeneratorTest, CheckNPREF1) {
    EXPECT_THROW(TextGenerator gen("Hello"), std::invalid_argument);
    EXPECT_THROW(TextGenerator gen(""), std::invalid_argument);
}

TEST(TextGeneratorTest, CheckNPREF2) {
    TextGenerator gen("Hello world");
    auto& table = gen.getStateTable();
    EXPECT_TRUE(table.empty());
    std::string out = gen.Generate();
    EXPECT_EQ(out, "");
}

TEST(TextGeneratorTest, FileConstructorWorks) {
    std::ofstream testFile("test_input.txt");
    testFile << "one two three four";
    testFile.close();
    std::ifstream file("test_input.txt");
    TextGenerator gen(file);
    file.close();
    std::remove("test_input.txt");
    prefix first = gen.getFirstPrefix();
    EXPECT_EQ(first.size(), 2);
    EXPECT_EQ(first[0], "one");
    EXPECT_EQ(first[1], "two");
}
