#include <string>
#include <cstdarg>
#include <iostream>

using namespace std;

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

string Sum(int n, const string* args) {
	return " ";
}

void get_va_nums(va_list& args, string* nums, int n, int i) {
	if (i >= n)
		return;
	nums[i++] = va_arg(args, char*);
	get_va_nums(args, nums, n, i);
}

string Sum(int n, ...) {
	va_list args;
	va_start(args, n);

	string* nums = new string[n];
	get_va_nums(args, nums, n, 0);

	for (int i = 0; i < n; i++) {
		cout << nums[i] << " ";
	}
	cout << endl;
	va_end(args);
	return " ";
}
