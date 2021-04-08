// Jakub Parapura

#include <string>
#include <cstdarg>
#include <iostream>

using namespace std;

string csum2(const string, const string); 
string csum2Rec(const string, const string, int, int);

bool isNegative(const string a) {
	if (a[0] == '-')	return true;
	if (a[0] == '+')	return false;
	return false;
}

string cleanNumberRec(const string a, int i, bool befNum) {
	if (i == a.size())
		return "";

	switch (a[i]) {
		case '+':
		case '-':
			return cleanNumberRec(a, i + 1, befNum);
		case '0':
			if (befNum)
				return cleanNumberRec(a, i + 1, befNum);
			else
				return '0' + cleanNumberRec(a, i + 1, befNum);
		default:
			befNum = false;
			return a[i] + cleanNumberRec(a, i + 1, befNum);
	}
}

string cleanNumber(const string a) {
	string result = cleanNumberRec(a, 0, true);
	if (result.size() == 0)
		return "0";
	return result;
}

string twosComplementRec(const string a, int i) {
	if (i == a.size()) return "";
	char beg = '9' - a[i] + '0';
	return beg + twosComplementRec(a, i + 1);
}

string twosComplement(const string a) {
	// NOTE kolejne miejsce, w którym wywołuje csum2Rec, 
	// żeby nie przejść przez cleanNumber
	return csum2Rec(twosComplementRec(a, 0), "1", 0, 0);
}

string ignoreFirstDigit(const string a) {
	return a.substr(1, a.size() - 1);
}

string unsignNum(const string a) {
	switch (a[0]) {
		case '+':
		case '-':
			return a.substr(1, a.size() - 1);
		default:
			return a;
	}
}

bool numLessEqualRec(const string a, const string b, int i) {
	// a.size() == b.size()
	if (a.size() <= i) return true; // bo są równe
	if (a[i] != b[i]) {
		return a[i] <= b[i];
	}
	return numLessEqualRec(a, b, i + 1);
}

bool numLessEqual(const string a, const string b) {
	string cleanA = cleanNumber(a);
	string cleanB = cleanNumber(b);
	if (cleanA.size() != cleanB.size()) return cleanA.size() <= cleanB.size();
	return numLessEqualRec(cleanA, cleanB, 0);
}

// ta funkcja przyjmuje tylko liczby dodatnie oraz bez znaków + i -
string csum2Rec(const string a, const string b, int i, int r) {
	int x = -1;
	int y = -1;
	if (i >= a.size()) x = 0;
	if (i >= b.size()) y = 0;
	if (i >= a.size() && i >= b.size() && r == 0)
		return "";

	x = x == -1 ? a[a.size() - 1 - i] - '0' : 0;
	y = y == -1 ? b[b.size() - 1 - i] - '0' : 0;	
	int result = x + y + r;
	int digit = result % 10;
	char digitChar = digit + '0';
	return csum2Rec(a, b, i + 1, result / 10) + digitChar;
}

string csum2(const string a, const string b) {
	// - + + itd.
	// NOTE założenie że b < a jest chyba niepotrzebne
	// TODO czyszczenie z +, - i niepotrzebnych zer
	// TODO ostateczne zwracanie liczby powinno czyścić liczbę ze znaków
	// oraz doklejać - jeśli to potrzebne
	string unsignA = unsignNum(a);
	string unsignB = unsignNum(b);
	if (isNegative(a) && isNegative(b)) {
		string temp = cleanNumber(csum2Rec(unsignA, unsignB, 0, 0));
		if (temp == "0")	return temp;
		else	return '-' + cleanNumber(csum2Rec(unsignA, unsignB, 0, 0));
	}
	else if ( (isNegative(a) && isNegative(b) == false) || 
			  (isNegative(a) == false && isNegative(b)) ) {
		string ujemna, dodatnia;
		if (isNegative(a)) {
			ujemna = unsignA;
			dodatnia = unsignB;
		}
		if (isNegative(b)) {
			ujemna = unsignB;
			dodatnia = unsignA;
		}
		
		//cout << "ujemna=" << ujemna << endl;
		//cout << "dodatnia=" << dodatnia << endl;
		string ujemnaU2 = twosComplement(ujemna);
		// NOTE wiemy, że ujemnaU2 i dodatnia nie mają + i - na początku
		// ale moga mieć niepotrzebne zera. żeby ich nie ucinać wywołuję
		// csum2Rec, które nie przechodzi przez cleanNumber
		string partial = csum2Rec(ujemnaU2, dodatnia, 0, 0);
		//string partial = csum2(ujemnaU2, dodatnia);
		//cout << "ujemnaU2=" << ujemnaU2 << endl;
		//cout << "partial=" << partial << endl;
		if (numLessEqual(ujemna, dodatnia)) {
			return cleanNumber(ignoreFirstDigit(partial));
		}
		else {
			return '-' + cleanNumber(twosComplement(partial));
		}
	}
	else {
		// a, b >= 0
		return cleanNumber(csum2Rec(unsignA, unsignB, 0, 0));
	}
	return "coś się zjebało";
}

string csumManyRec(int n, const string* args, int i) {
	if (i == n - 2)
		return csum2(args[i], args[i + 1]);
	return csum2(args[i], csumManyRec(n, args, i + 1));
}

void get_va_nums(va_list& args, string* nums, int n, int i) {
	if (i >= n)
		return;
	nums[i++] = va_arg(args, char*);
	get_va_nums(args, nums, n, i);
}

string Sum(int n, const string* args) {
	return csumManyRec(n, args, 0);
}

string Sum(int n, ...) {
	va_list args;
	va_start(args, n);

	string* nums = new string[n];
	get_va_nums(args, nums, n, 0);
	
	va_end(args);
	string result = Sum(n, nums);
	delete[] nums;
	return result;
}

void Sum(string* output, int n, const string* args) {
	*output = csumManyRec(n, args, 0);
}

void Sum(string* output, int n, ...) {
	va_list args;
	va_start(args, n);

	string* nums = new string[n];
	get_va_nums(args, nums, n, 0);
	
	va_end(args);
	
	*output = Sum(n, nums);
	delete[] nums;
}

void Sum(string& output, int n, const string* args) {
	output = csumManyRec(n, args, 0);
}

void Sum(string& output, int n, ...) {
	va_list args;
	va_start(args, n);

	string* nums = new string[n];
	get_va_nums(args, nums, n, 0);
	
	va_end(args);
	
	output = Sum(n, nums);
	delete[] nums;
}
