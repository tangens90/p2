#include <string>
#include <cstdarg>
#include <iostream>

using namespace std;

// ta funkcja przyjmuje tylko liczby dodatnie i bez znaków
string csum2Rec(const string a, const string b, int i, int r) {
	// b < a
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
	// b < a

	return csum2Rec(a, b, 0, 0);
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
