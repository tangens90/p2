// link do repozytorium
// https://github.com/tangens90/p2

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

int main() {
	int n;
	cin >> n;

	// instrukcja ponizej przechwyci znak nowej linii wstawiany
	// zawsze po wprowadzeniu liczby n. ten znak jest nam zbędny
	// (i powoduje błędne działanie programu)
	fgetc(stdin);

	char** nazwiska = (char**)malloc(n * sizeof(char*));

	for (int i = 0; i < n; i++) {
		char* tmp;
		char c;
		size_t length = 0; // ilość znaków zapisanych w tmp
		size_t size = 2;   // obecny rozmiar tmp
		tmp = (char*)malloc(sizeof(*tmp) * size);
		while ((c = fgetc(stdin)) != EOF && c != '\n') {
			tmp[length++] = c;
			if (size == length) {
				tmp = (char*)realloc(tmp, sizeof(*tmp) * (size += 4));
			}
		}
		tmp[length++] = '\0';
		tmp = (char*)realloc(tmp, sizeof(*tmp) * length);
		nazwiska[i] = tmp;
	}

	for (int i = 0; i < n; i++) {
		cout << nazwiska[i] << " " << strlen(nazwiska[i]) << endl;
	}

	for (int i = 0; i < n; i++) {
		free(nazwiska[i]);
	}

	free(nazwiska);
}
