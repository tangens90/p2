#include <string>
#include <cstdarg>
#include <iostream>

using namespace std;

bool isNegative(const string a) {
	if (a[0] == '-')	return true;
	if (a[0] == '+')	return false;
	return false;
}

string cleanNumberRec(const string a, int i, bool beforeNum) {
	if (i == a.size())
		return "";

	switch (a[i]) {
		case '+':
		case '-':
			return cleanNumberRec(a, i + 1, beforeNum);
		case '0':
			if (beforeNum)
				return cleanNumberRec(a, i + 1, beforeNum);
			else
				return '0' + cleanNumberRec(a, i + 1, beforeNum);
		default:
			beforeNum = false;
			return a[i] + cleanNumberRec(a, i + 1, beforeNum);
	}
}

string cleanNumber(const string a) {
	string result = cleanNumberRec(a, 0, true);
	if (result.size() == 0)
		return "0";
	return result;
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
	string cleanA = cleanNumber(a);
	string cleanB = cleanNumber(b);
	if (isNegative(a) && isNegative(b)) {
		string temp = cleanNumber(csum2Rec(cleanA, cleanB, 0, 0));
		if (temp == "0")	return temp;
		else	return '-' + cleanNumber(csum2Rec(cleanA, cleanB, 0, 0));
	}
	else if ( (isNegative(a) && isNegative(b) == false) || 
			  (isNegative(a) == false && isNegative(b)) ) {
		
	}
	else {
		// a, b >= 0
		return cleanNumber(csum2Rec(cleanA, cleanB, 0, 0));
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
