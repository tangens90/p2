#include <iostream>
#include <string>

using namespace std;

int main() {
	int n;
	cin >> n;
	string* nazwiska = new string[n];
	for (int i = 0; i < n; i++) {
		string tmp;
		cin >> tmp;
		nazwiska[i] = tmp;
	}

	cout << endl;

	for (int i = 0; i < n; i++) {
		cout << nazwiska[i] << endl;
	}

	delete[] nazwiska;
}
