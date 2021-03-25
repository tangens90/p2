// Jakub Parapura

#include <cmath>

using namespace std;

double findZero(
    double (*f)(double),  // funkcja której zera szukamy w [a, b] 
    double a,             // lewy koniec przedziału
    double b,             // prawy koniec przedziału
    int M,                // maksymalna dozwolona liczba wywołań funkcji f
    double eps,           // spodziewana dokładność zera
    double delta          // wystarczający błąd bezwzględny wyniku
) {
	double fa = f(a);
	double fb = f(b);
	double c = a;
	bool entered_secant = false;

	for (int i = 0; i < M; i++) {
		if (abs(fa) < eps)
			return a;

		if (abs(fb) < eps)
			return b;

		double e = b - a;
		e = e / 2;

		if (abs(b - a) < delta)
			return e;

		double fc;
		if (entered_secant == false && fa * fb <= 0 && abs(b - a) > 0.03) {
			// metoda bisekcji
			c = a + e;
			fc = f(c);
			if (abs(fc) < eps || abs(e) < delta)
				return c;

			if (fc * fa <= 0) {
				b = c;
				fb = fc;
			}
			else {
				a = c;
				fa = fc;
			}
		}
		else {
			// metoda siecznych
			entered_secant = true;
			double c = b - (b - a) * fb / (fb - fa);
			a = b;
			b = c;
			fa = fb;
			fb = f(c);
			fc = fb;

			if (abs(b - a) < delta || abs(fc) < eps)
				return c;
		}
	}

	return c;
}
