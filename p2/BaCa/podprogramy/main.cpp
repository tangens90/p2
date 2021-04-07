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

TEST(Sum, SumOfMultiplePositiveNumbers) {
	string arr1[] = {"123", "345"};
	const string* txt1 = &arr1[0];
	EXPECT_EQ(Sum(2, txt1), "468");
	EXPECT_EQ(Sum(2, "123", "345"), "468");
	string output;
	Sum(&output, 2, txt1);
	EXPECT_EQ(output, "468");

	string arr2[] = {"123", "345", "999"};
	const string* txt2 = &arr2[0];
	EXPECT_EQ(Sum(3, txt2), "1467");
	EXPECT_EQ(Sum(3, "123", "345", "999"), "1467");

	string arr3[] = {"123", "345", "999", "0", "0"};
	const string* txt3 = &arr3[0];
	EXPECT_EQ(Sum(5, txt3), "1467");

	string arr4[] = {"123", "345", "999", "1000000", "1"};
	const string* txt4 = &arr4[0];
	EXPECT_EQ(Sum(5, txt4), "1001468");
}

TEST(Sum, OverloadingFunction) {
	string arr4[] = {"123", "345", "999", "1000000", "1"};
	const string* txt4 = &arr4[0];
	EXPECT_EQ(Sum(5, txt4), "1001468");
	EXPECT_EQ(Sum(5, "123", "345", "999", "1000000", "1"), "1001468");
	string output1;
	Sum(&output1, 5, txt4);
	EXPECT_EQ(output1, "1001468");
	string output2;
	Sum(&output2, 5, "123", "345", "999", "1000000", "1");
	EXPECT_EQ(output2, "1001468");
	string output3;
	Sum(output3, 5, txt4);
	EXPECT_EQ(output3, "1001468");
	string output4;
	Sum(output4, 5, "123", "345", "999", "1000000", "1");
	EXPECT_EQ(output4, "1001468");
}


 TEST(Sum, SumWithLeadingZeros) {
	GTEST_SKIP();

	string arr5[] = {"00000000000", "0"};
	const string* txt5 = &arr5[0];
	EXPECT_EQ(Sum(2, txt5), "0");

	string arr6[] = {"00000000000", "1"};
	const string* txt6 = &arr6[0];
	EXPECT_EQ(Sum(2, txt6), "1");

	string arr7[] = {"00000000001", "0"};
	const string* txt7 = &arr7[0];
	EXPECT_EQ(Sum(2, txt7), "1");

	string arr8[] = {"00000000001", "1"};
	const string* txt8 = &arr8[0];
	EXPECT_EQ(Sum(2, txt8), "2");
 }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
