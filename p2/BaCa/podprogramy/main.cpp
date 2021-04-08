#include <gtest/gtest.h>
#include <string>
#include <iostream>
#include <cstdarg>
#include "source.cpp"

TEST(HelperFunctions, cleanNumber) {
	EXPECT_EQ(cleanNumber("123"), "123");
	EXPECT_EQ(cleanNumber("+123"), "123");
	EXPECT_EQ(cleanNumber("-123"), "123");
	EXPECT_EQ(cleanNumber("00000000"), "0");
	EXPECT_EQ(cleanNumber("-0"), "0");
	EXPECT_EQ(cleanNumber("-0000000000"), "0");
	EXPECT_EQ(cleanNumber("000005"), "5");
	EXPECT_EQ(cleanNumber("0000050000"), "50000");
	EXPECT_EQ(cleanNumber("-000005"), "5");
	EXPECT_EQ(cleanNumber("-0000050000"), "50000");
}

TEST(HelperFunctions, twosComplement) {
	EXPECT_EQ(twosComplement("20"), "80");
	EXPECT_EQ(twosComplement("5"), "5");
	EXPECT_EQ(twosComplement("1"), "9");
	EXPECT_EQ(twosComplement("1234"), "8766");
	EXPECT_EQ(twosComplement("94"), "06");
	EXPECT_EQ(twosComplement("123"), "877");
}

TEST(HelperFunctions, csum2) {
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

TEST(HelperFunctions, ignoreFirstDigit) {
	EXPECT_EQ(ignoreFirstDigit("3111"), "111");
	EXPECT_EQ(ignoreFirstDigit("10"), "0");
	EXPECT_EQ(ignoreFirstDigit("0"), "");
}

TEST(HelperFunctions, numLessEqual) {
	EXPECT_TRUE(numLessEqual("1", "123"));
	EXPECT_FALSE(numLessEqual("123", "1"));
	EXPECT_TRUE(numLessEqual("1", "1"));
	EXPECT_TRUE(numLessEqual("456", "456"));
	EXPECT_TRUE(numLessEqual("12", "13"));
	EXPECT_TRUE(numLessEqual("4", "6"));
	EXPECT_TRUE(numLessEqual("04", "06"));
	EXPECT_TRUE(numLessEqual("04", "006"));
	EXPECT_FALSE(numLessEqual("2137", "1337"));
}

TEST(HelperFunctions, unsignNum) {
	EXPECT_EQ(unsignNum("001"), "001");
	EXPECT_EQ(unsignNum("+001"), "001");
	EXPECT_EQ(unsignNum("-001"), "001");
}

TEST(HelperFunctions, cmult2digit) {
	EXPECT_EQ(cmult2digit("2137", '5'), "10685");
	EXPECT_EQ(cmult2digit("2137", '4'), "8548");
	EXPECT_EQ(cmult2digit("2137", '1'), "2137");
	EXPECT_EQ(cmult2digit("100", '1'), "100");
	EXPECT_EQ(cmult2digit("1", '1'), "1");
	EXPECT_EQ(cmult2digit("5", '5'), "25");
	EXPECT_EQ(cmult2digit("9", '9'), "81");
	EXPECT_EQ(cmult2digit("99", '9'), "891");
	EXPECT_EQ(cmult2digit("9999", '9'), "89991");
	EXPECT_EQ(cmult2digit("48", '6'), "288");
	EXPECT_EQ(cmult2digit("48", '2'), "96");
 }

TEST(HelperFunctions, cmult2) {
	EXPECT_EQ(cmult2("2137", "54"), "115398");
	EXPECT_EQ(cmult2("100", "1"), "100");
	EXPECT_EQ(cmult2("1", "100"), "100");
	EXPECT_EQ(cmult2("1", "1"), "1");
	EXPECT_EQ(cmult2("5", "5"), "25");
	EXPECT_EQ(cmult2("9", "9"), "81");
	EXPECT_EQ(cmult2("99", "99"), "9801");
	EXPECT_EQ(cmult2("9999", "9999"), "99980001");
	EXPECT_EQ(cmult2("9999", "999"), "9989001");
	EXPECT_EQ(cmult2("9999", "99"), "989901");
	EXPECT_EQ(cmult2("48", "62"), "2976");
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

	string arr5[] = {"9999", "9999"};
	const string* txt5 = &arr5[0];
	EXPECT_EQ(Sum(2, txt5), "19998");
}

 TEST(Sum, SumWithLeadingZeros) {
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

TEST(Sum, SumOfNegativeNumbers) {
	string arr00[] {"-1", "-1", "-1", "-1"};
	const string* txt00 = &arr00[0];
	EXPECT_EQ(Sum(4, txt00), "-4");

	string arr01[] {"-9999", "-9999"};
	const string* txt01 = &arr01[0];
	EXPECT_EQ(Sum(2, txt01), "-19998");

	string arr02[] {"-00000000", "-0"};
	const string* txt02 = &arr02[0];
	EXPECT_EQ(Sum(2, txt02), "0");

	string arr03[] {"-0", "-0"};
	const string* txt03 = &arr03[0];
	EXPECT_EQ(Sum(2, txt03), "0");

	string arr04[] {"-0", "-0", "-15"};
	const string* txt04 = &arr04[0];
	EXPECT_EQ(Sum(3, txt04), "-15");

	EXPECT_EQ(Sum(2, "-999", "-0"), "-999");
}

TEST(Sum, SumOfPositiveAndNegativeNumbers) {
	//GTEST_SKIP();

	EXPECT_EQ(Sum(2, "000", "-000123"), "-123");
	EXPECT_EQ(Sum(2, "-15", "10"), "-5");
	EXPECT_EQ(Sum(2, "-999", "0"), "-999");
	EXPECT_EQ(Sum(2, "-0", "+0"), "0");
	EXPECT_EQ(Sum(2, "-0", "0"), "0");
	EXPECT_EQ(Sum(2, "+0", "-0"), "0");
	EXPECT_EQ(Sum(2, "-999", "1"), "-998");
	EXPECT_EQ(Sum(4, "-1", "1", "-1", "1"), "0");
	EXPECT_EQ(Sum(3, "-1", "1", "-1"), "-1");
	EXPECT_EQ(Sum(2, "-1234", "+1234"), "0");
	EXPECT_EQ(Sum(2, "-1234", "1234"), "0");
	EXPECT_EQ(Sum(2, "+001", "-0001112"), "-1111");
	EXPECT_EQ(Sum(2, "68", "-94"), "-26");
	EXPECT_EQ(Sum(2, "-68", "94"), "26");
	EXPECT_EQ(Sum(2, "94", "-68"), "26");
	EXPECT_EQ(Sum(2, "-94", "68"), "-26");
	EXPECT_EQ(Sum(2, "-94", "94"), "0");
	EXPECT_EQ(Sum(2, "94", "-94"), "0");
	EXPECT_EQ(Sum(3, "-68", "94", "-123"), "-97");
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

TEST(Mult, MultiplyingPositiveNumbers) {
	string arr0[] = {"123", "345", "1"};
	const string* txt0 = &arr0[0];
	EXPECT_EQ(Mult(3, txt0), "42435");

	EXPECT_EQ(Mult(2, "2137", "54"), "115398");
	EXPECT_EQ(Mult(2, "100", "1"), "100");
	EXPECT_EQ(Mult(2, "1", "100"), "100");
	EXPECT_EQ(Mult(2, "1", "1"), "1");
	EXPECT_EQ(Mult(2, "5", "5"), "25");
	EXPECT_EQ(Mult(2, "9", "9"), "81");
	EXPECT_EQ(Mult(2, "99", "99"), "9801");
	EXPECT_EQ(Mult(2, "9999", "9999"), "99980001");
	EXPECT_EQ(Mult(2, "9999", "999"), "9989001");
	EXPECT_EQ(Mult(2, "9999", "99"), "989901");
	EXPECT_EQ(Mult(2, "48", "62"), "2976");
}

TEST(Mult, OverloadingFunction) {
	string arr4[] = {"123", "345", "1"};
	const string* txt4 = &arr4[0];
	EXPECT_EQ(Mult(3, txt4), "42435");
	EXPECT_EQ(Mult(3, "123", "345", "1"), "42435");
	string output1;
	Mult(&output1, 3, txt4);
	EXPECT_EQ(output1, "42435");
	string output2;
	Mult(&output2, 3, "123", "345", "1");
	EXPECT_EQ(output2, "42435");
	string output3;
	Mult(output3, 3, txt4);
	EXPECT_EQ(output3, "42435");
	string output4;
	Mult(output4, 3, "123", "345", "1");
	EXPECT_EQ(output4, "42435");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
