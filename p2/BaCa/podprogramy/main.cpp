#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <cstdarg>
#include "source.cpp"

TEST(csum2, SumOfPositiveNumbers) {
	EXPECT_EQ(csum2("2137", "54"), "2191");
	EXPECT_NE(csum2("2137", "54"), " 2191");
	EXPECT_NE(csum2("2137", "54"), "2191 ");
	EXPECT_NE(csum2("2137", "54"), " 2191 ");
	EXPECT_EQ(csum2("100", "1"), "101");
	EXPECT_EQ(csum2("1", "1"), "2");
	EXPECT_EQ(csum2("5", "5"), "10");
	EXPECT_EQ(csum2("9", "9"), "18");
	EXPECT_EQ(csum2("99", "99"), "198");
	EXPECT_EQ(csum2("9999", "9999"), "19998");
	EXPECT_EQ(csum2("9999", "999"), "10998");
	EXPECT_EQ(csum2("9999", "99"), "10098");
	EXPECT_EQ(csum2("48", "62"), "110");
}

// TEST(MathTest, TwoPlusTwoEqualsFour) {
//     EXPECT_EQ(2 + 2, 4);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );

	Sum(3, "witam", "pozdrawiam", "miłego dnia");

    return RUN_ALL_TESTS();
}
