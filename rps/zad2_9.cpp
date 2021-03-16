#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int getRand() {
	return (rand() % 100) + 1;
}

int main() {
	int n;
	cin >> n;
	int x_wins = 0, y_wins = 0;
	srand(time(NULL));

	for (int i = 0; i < n; i++) {
		int S = 0;
		int x, y;
		while (S <= 100) {
			x = getRand();
			S += x;
		}
	
		while (S <= 200) {
			y = getRand();
			S += y;
		}
//		cout << S << endl;
//		cout << x << endl;
//		cout << y << endl;
//		cout << "---" << endl;
		if (y > x) {
			y_wins++;
			//cout << "y wygral" << endl;
		} else if (x > y) {
			x_wins++;
			//cout << "x wygral" << endl;
		}
		else { 
			//cout << "remis" << endl;
		}
	}

	cout << setprecision(3);  
	cout << "y: " << (double)y_wins / (double)n << endl;
	cout << "x: " << (double)x_wins / (double)n << endl;

}
