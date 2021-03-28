#include <iostream>
#include "source.cpp"
#include <bitset>

using namespace std;

int main() {
	int test1 = 0b01101;
	//string e1 = "   00110         ";
	char e1[] = "   00110         ";
	Emplace(&e1[0], &test1);
	bitset<32> bity1 = test1;
	cout << bity1 << endl;

	int test2 = 0b00000;
	char e2[] = " 00011   00010     11111   00110    11110 00100 00001    00000";
	Insert(&e2[0], &test2);
	bitset<32> bity2 = test2;
	cout << bity2 << endl;

	char e3[1000];
	Print(test2, &e3[0]);
	cout << e3 << endl;


	int test3 = 0b00010;
	cout << boolalpha << Emptiness(test3) << endl;
	cout << boolalpha << Nonempty(test3) << endl;
	bitset<32> bity3 = test3;
	cout << bity3 << endl;

	int test4 = 0b011;
	cout << boolalpha << Emptiness(test4) << endl;
	cout << boolalpha << Nonempty(test4) << endl;
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
}
