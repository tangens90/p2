// link do repozytorium
// https://github.com/tangens90/p2

#include <iostream>

using namespace std;

// kategoria cenowa filmu może się zmieniać w czasie
// jeśli na przykład film przestanie być tak często
// wypożyczany, wypożyczalnia może zdecydować się na
// obniżenie kategorii cenowej a przez to ceny, aby 
// zachęcić klientów. Również wiele filmów może 
// należeć do tej samej kategorii cenowej
struct KategoriaCenowa {
	char nazwa;
	double cena;

	KategoriaCenowa(char nazwa, double cena) : nazwa(nazwa), cena(cena) {}
};

struct Film_z_wypozyczalni {
	string tytul;
	int rokProdukcji;
	KategoriaCenowa* kat;

	Film_z_wypozyczalni(string tytul, int rokProdukcji, KategoriaCenowa* kat) 
		: tytul(tytul), rokProdukcji(rokProdukcji), kat(kat) {}
};
	
int main() {
	KategoriaCenowa* katA = new KategoriaCenowa('A', 24.99);
	KategoriaCenowa* katB = new KategoriaCenowa('B', 12.99);
	
	Film_z_wypozyczalni* nietykalni = new Film_z_wypozyczalni("Nietykalni", 2009, katB);
	Film_z_wypozyczalni* whiplash = new Film_z_wypozyczalni("Whiplash", 2014, katB);
	Film_z_wypozyczalni* joker = new Film_z_wypozyczalni("Joker", 2019, katA);

	cout << joker->kat->nazwa << endl;

	// Joker już nie jest najnowszym filmem. Ktoś
	// może zdecydować, że czas obniżyć jego cenę.
	joker->kat = katB;
	cout << joker->kat->nazwa << endl;

	delete katA;
	delete katB;
	delete nietykalni;
	delete whiplash;
	delete joker;
}
