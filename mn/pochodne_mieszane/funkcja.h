template <typename T>
T funkcja(const T& x, const T& y) {
	T wynik = sin(x*x - 2*(y+1))/exp(-y*y+cos(x*y));
	//T wynik = sin(x+y);
	//T wynik = sin((x-y)/(3*x+5));
	//T wynik = ((x+y)*(y-3))/(-y-x*y-2);
	//T wynik = x+y;
	//T wynik = x+x*y+y;
	//T wynik = 3.0+x+y+5.0;
	//T wynik = 3.0+x+y+5.0;
	//T wynik = (2 + x)/y;
	return wynik;

