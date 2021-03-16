// Jakub Parapura

#include <iostream>
#include <cstdio>
#include <math.h>

using namespace std;

int main() {
	int z;
	cin >> z;
	while (z > 0) {
		z--;
		double x0, x1;
		int n;
		cin >> x0 >> x1 >> n;
		double A = (49 * x0 - 7 * x1) / 48.0;
		double B = (7 * x1 - x0) / 48.0;
		for (int i = 0; i < n; i++) {
			double k;
			cin >> k;
			double x = A * pow(7.0, -k) + B * pow(7.0, k);
			printf("%.15e\n", x);
		}
		if (z != 0)
			cout << endl;
	}
}
