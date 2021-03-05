// link do repozytorium
// https://github.com/tangens90/p2

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int main() {
	int n;
	cin >> n;
	const char** nazwiska = new const char*[n];

	for (int i = 0; i < n; i++) {
		char* tmp;
		// %ms powoduje sparsowanie napisu i alokacje takiej
		// ilości pamięci, żeby zmieścić podany napis, znak
		// \0 i nic więcej.
		scanf("%ms", &tmp);
		nazwiska[i] = tmp;
	}

	for (int i = 0; i < n; i++) {
		cout << nazwiska[i] << " " << strlen(nazwiska[i]) << endl;
	}


	for (int i = 0; i < n; i++) {
		delete[] nazwiska[i];
	}

	delete[] nazwiska;
}
