#include <iostream>
#include "source.cpp"
#include <bitset>

using namespace std;

int main() {
	cout << boolalpha;
	int test1 = 0b01101;
	//string e1 = "   00110         ";
	char e1[] = "   00110         ";
	Emplace(&e1[0], &test1);
	bitset<32> bity1 = test1;
	cout << bity1 << endl;

	int test2 = 0b00000;
	char e2[] = " 00011   00010     11111   00110    11110 00100 00001    00000";
	cout << "card=" << Cardinality(test2) << endl;
	char in2[] = "        00011  ";
	cout << "member=" << Member(&in2[0], test2) << endl;
	Insert(&e2[0], &test2);
	cout << "card=" << Cardinality(test2) << endl;
	cout << "member=" << Member(&in2[0], test2) << endl;
	bitset<32> bity2 = test2;
	cout << bity2 << endl;

	char e3[1000];
	Print(test2, &e3[0]);
	cout << e3 << endl;


	int test3 = 0b00010;
	cout << Emptiness(test3) << endl;
	cout << Nonempty(test3) << endl;
	bitset<32> bity3 = test3;
	cout << bity3 << endl;

	int test4 = 0b011;
	cout << Emptiness(test4) << endl;
	cout << Nonempty(test4) << endl;
	bitset<32> bity4 = test4;
	cout << bity4 << endl;
	char e4[1000];
	Print(test4, &e4[0]);
	cout << e4 << endl;

	int test5 = -1;
	bitset<32> bity5 = test5;
	cout << bity5 << endl;
	char e5[1000];
	Print(test5, &e5[0]);
	cout << e5 << endl;

	int test6 = 0b010;
	int test7 = 0b101;
	int test8 = 0b100;
	cout << Disjoint(test6, test7) << endl;
	cout << Disjoint(test7, test8) << endl;
	
	cout << endl;
	int test9 = 0b01111;
	char in9[] = "00011        00001   00000 00010";
	Erase(&in9[0], &test9);
	char out9[1000];
	Print(test9, &out9[0]);
	cout << out9 << endl;
	bitset<32> bity9 = test9;
	cout << bity9 << endl;

	cout << endl;
	int test10 = 0b1100011;
	cout << "card=" << Cardinality(test10) << endl;
	test10 = -1;
	char out10[1000];
	//char in10[] = "00001";
	//char in10[] = " 11111  00000";
	//char in10[] = "11111  00000 ";
	cout << "card=" << Cardinality(test10) << endl;
	char in10[] = "00000";
	Erase(&in10[0], &test10);
	Print(test10, &out10[0]);
	cout << out10 << endl;
	bitset<32> bity10 = test10;
	cout << bity10 << endl;
	cout << "card=" << Cardinality(test10) << endl;

	cout << endl;
	int test11 = 10001;
	int test12 = 110;
	cout << LessThen(test11, test12) << endl;
	cout << LessEqual(test11, test12) << endl;
	cout << GreatThen(test11, test12) << endl;
	cout << GreatEqual(test11, test12) << endl;

	std::cout << LessThen( 0b1010, 0b1010) << ", ";
	std::cout << LessEqual(0b1010, 0b1010) << "\n";
	std::cout << LessThen( 0b1001, 0b1010) << ", ";
	std::cout << LessEqual(0b1001, 0b1010) << '\n';
	std::cout << LessThen( 0b1010, 0b1001) << ", ";
	std::cout << LessEqual(0b1010, 0b1001) << '\n';
	std::cout << LessThen( 0b10000000000000000000000000000000, 0b10000000000000000000000000000000) << ", ";
	std::cout << LessEqual(0b10000000000000000000000000000000, 0b10000000000000000000000000000000) << "\n";
	std::cout << LessThen( 0b11000000000000000000000000000000, 0b10100000000000000000000000000000) << ", ";
	std::cout << LessEqual(0b11000000000000000000000000000000, 0b10100000000000000000000000000000) << "\n";
	std::cout << LessThen( 0b10100000000000000000000000000000, 0b11000000000000000000000000000000) << ", ";
	std::cout << LessEqual(0b10100000000000000000000000000000, 0b11000000000000000000000000000000) << "\n";
	std::cout << LessThen( 0b01000000000000000000000000000000, 0b10000000000000000000000000000000) << ", ";
	std::cout << LessEqual(0b01000000000000000000000000000000, 0b10000000000000000000000000000000) << "\n";
	
}
