// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>

TEST(TestPrefixCreating, Test1) {
	TextGenerator gen = TextGenerator("Hello world");
	EXPECT_EQ(gen.getFirstPrefix().size(), 2);
}

TEST(TestPrefixCreating, Test2) {
	EXPECT_THROW(TextGenerator("Hello"), invalid_argument);
}

TEST(TestInputFileOpening, Test1) {
	ifstream file = ifstream("wrong_name.txt");
	EXPECT_THROW(TextGenerator(file), runtime_error);
}

TEST(TestStateTab, Test1) {
	TextGenerator gen = TextGenerator();
	EXPECT_TRUE(gen.getStateTab().size() > 0);
}

TEST(TestStateTab, Test1) {
	TextGenerator gen = TextGenerator("Hello world");
	EXPECT_TRUE(gen.getStateTab().size() > 0);
}