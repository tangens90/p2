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
	EXPECT_EQ(Sum(2, "-0", "-0"), "0");
	EXPECT_EQ(Sum(2, "10", "-1"), "9");
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
	string arr01[] = { "+0000000000000000", "-00000000000000000", "+3333333333333333", "-234121212123", "-5298592312354352", "+99657452352300005403405349", "-1423900000000000000000000000000000000000000000000000000000000000000000"};
    string arr00[] = { "321312222", "-4234320000000", "+0000000000000"};
    const string* txt00 = &arr00[0];
	EXPECT_EQ(Sum(3, txt00), "-4233998687778");
    const string* txt01 = &arr01[0];
	EXPECT_EQ(Sum(7, txt01), "-1423899999999999999999999999999999999999999900342547649665487696827793");
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

TEST(Mult, MultOfNegativeNumbers) {
	EXPECT_EQ(Mult(2, "000", "-000123"), "0");
	EXPECT_EQ(Mult(2, "-15", "10"), "-150");
	EXPECT_EQ(Mult(2, "-999", "0"), "0");
	EXPECT_EQ(Mult(2, "-0", "+0"), "0");
	EXPECT_EQ(Mult(2, "-0", "0"), "0");
	EXPECT_EQ(Mult(2, "+0", "-0"), "0");
	EXPECT_EQ(Mult(2, "-999", "1"), "-999");
	EXPECT_EQ(Mult(4, "-1", "1", "-1", "1"), "1");
	EXPECT_EQ(Mult(3, "-1", "1", "-1"), "1");
	EXPECT_EQ(Mult(3, "-1", "-1", "-1"), "-1");
	EXPECT_EQ(Mult(2, "-1234", "+1234"), "-1522756");
	EXPECT_EQ(Mult(2, "-1234", "1234"), "-1522756");
	EXPECT_EQ(Mult(2, "+001", "-0001112"), "-1112");
	EXPECT_EQ(Mult(2, "68", "-94"), "-6392");
	EXPECT_EQ(Mult(2, "-68", "94"), "-6392");
	EXPECT_EQ(Mult(2, "94", "-68"), "-6392");
	EXPECT_EQ(Mult(2, "-94", "68"), "-6392");
	EXPECT_EQ(Mult(2, "-94", "94"), "-8836");
	EXPECT_EQ(Mult(2, "94", "-94"), "-8836");
	EXPECT_EQ(Mult(3, "-68", "94", "-123"), "786216");
	EXPECT_EQ(Mult(2, "0", "-3333333"), "0");
	EXPECT_EQ(Mult(2, "0", "3333333"), "0");
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

TEST(DC, TestyZDiscorda) {

	const string* napis; 
	
	
	string arr0[] = {"2386000", "000000000000006970000" };  
	napis = &arr0[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr1[] = {"-00000000000002862168", "-0000000000000000000000000000645268" };  
	napis = &arr1[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr2[] = {"-0000000000009615600", "000000000000942613" };  
	napis = &arr2[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr3[] = {"0000000000000009268733", "+0000000000000000000007009353" };  
	napis = &arr3[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr4[] = {"-07847168", "0000000000000000000007204296" };  
	napis = &arr4[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr5[] = {"+0000000002623285", "000000000000000008505699" };  
	napis = &arr5[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr6[] = {"00000000000000000000000009232190", "+0000000000000005211062" };  
	napis = &arr6[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr7[] = {"-0000000000000000000000009884374", "+0000000000000000000000000000005123623" };  
	napis = &arr7[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr8[] = {"-0000009958789", "0000000000000009843224" };  
	napis = &arr8[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr9[] = {"+000000008601067", "0000000005967869" };  
	napis = &arr9[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr10[] = {"000000000000000000000000007250418", "0003291052" };  
	napis = &arr10[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr11[] = {"000000000000000000006860647", "-0000000000000000000000000000003766544" };  
	napis = &arr11[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr12[] = {"-0000000000000000000000000000004848012", "+000000000000000000351156" };  
	napis = &arr12[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr13[] = {"-003326787", "0000000000000000000000009200629" };  
	napis = &arr13[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr14[] = {"+00000000000000000000000000005464560", "000000000000000004388852" };  
	napis = &arr14[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr15[] = {"-00000000000000000000000006917485", "0000000000005550544" };  
	napis = &arr15[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr16[] = {"0000000000000000000000000000003991481", "+00000000000000000000009170177" };  
	napis = &arr16[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr17[] = {"-00000000000000000000000000005258243", "0000000007570867" };  
	napis = &arr17[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr18[] = {"+0000000000000000000003506784", "000000000000000009753223" };  
	napis = &arr18[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr19[] = {"+0000000000000000001321230", "-00000000000007401996" };  
	napis = &arr19[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr20[] = {"+00000008630837", "0000000000000000000005766419" };  
	napis = &arr20[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr21[] = {"0000000000000000000000001763153", "-00000000000005104102" };  
	napis = &arr21[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr22[] = {"+0000000000000000000000000000001029323", "00000000000000000006374057" };  
	napis = &arr22[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr23[] = {"+00000000000000000000000003346605", "00000000000006531460" };  
	napis = &arr23[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr24[] = {"0000000000000003213001", "000000004182414" };  
	napis = &arr24[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr25[] = {"000000000000000003666294", "2129099" };  
	napis = &arr25[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr26[] = {"+000000000000000000000000009849278", "0000000000008373538" };  
	napis = &arr26[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr27[] = {"000009842271", "001810397" };  
	napis = &arr27[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr28[] = {"000000000009021643", "0000000000000005333547" };  
	napis = &arr28[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr29[] = {"+00000000000000000000007963682", "+0000000000000000000002849112" };  
	napis = &arr29[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr30[] = {"+000000000000000000000002331276", "+00000000000000000007174007" };  
	napis = &arr30[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr31[] = {"+007130796", "00003299627" };  
	napis = &arr31[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr32[] = {"0000000000000000006356747", "+00000000000000000001591900" };  
	napis = &arr32[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr33[] = {"+0345590", "00000006758793" };  
	napis = &arr33[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr34[] = {"-00000000000000003468653", "00078795" };  
	napis = &arr34[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr35[] = {"000000000000000001343848", "008867184" };  
	napis = &arr35[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr36[] = {"5169006", "0000000288907" };  
	napis = &arr36[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr37[] = {"00000000000000000000006381742", "000000000000000000000380925" };  
	napis = &arr37[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr38[] = {"-0000000000000000000001590234", "-000009436162" };  
	napis = &arr38[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr39[] = {"+00000000002911455", "00000000007857297" };  
	napis = &arr39[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr40[] = {"+0000002019129", "0000000000000000000000007506938" };  
	napis = &arr40[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr41[] = {"+00000000000000000000000003354120", "000000000000000005061651" };  
	napis = &arr41[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr42[] = {"03731504", "00000000000000000000000006702077" };  
	napis = &arr42[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr43[] = {"000000000005020849", "-07359939" };  
	napis = &arr43[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr44[] = {"-00000006217924", "-07377647" };  
	napis = &arr44[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr45[] = {"-0000000000009539936", "-00000000000007511327" };  
	napis = &arr45[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr46[] = {"000000000000000000000008022783", "-000000000000000000000000000008893526" };  
	napis = &arr46[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr47[] = {"+000000000000000693187", "0006381174" };  
	napis = &arr47[0]; 
	 cout << Sum(2, napis) << endl;  
	
	string arr48[] = {"+000000000000000000000000555555", "+0003573505" };  
	napis = &arr48[0]; 
	 cout << Sum(2, napis) << endl;  
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
