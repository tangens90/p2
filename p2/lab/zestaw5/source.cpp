// link do repozytorium:
// https://github.com/tangens90/homework/tree/main/p2/lab/zestaw5

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

class Kapitan {
private:
	string imie, nazwisko;
	int sluzba;
	bool emerytura;
public:
	Kapitan();
	Kapitan(string, string, int, bool);
	string get_imie() const;
};

Kapitan::Kapitan() {}

Kapitan::Kapitan(string im, string na, int sl, bool em) {
	imie = im;
	nazwisko = na;
	sluzba = sl;
	emerytura = em;
}

string Kapitan::get_imie() const {
	return imie;
}

class Statek {
private:
	Kapitan kapitan;
	string nazwa;
	int zaloga;
	int racje;
public:
	Statek();
	Statek(Kapitan, string, int, int);

	int get_zaloga() const;
	virtual int get_racje() const;
	void set_zaloga(int zaloga);
	void set_racje(int);
	void werbunek(int liczba);
	Kapitan get_kapitan() const;
	virtual void oblicz_zywnosc();
};

Statek::Statek() {
	this->kapitan = Kapitan("John", "Sheridan", 10, false);
	this->nazwa = "White Star";
	this->zaloga = 25;
	this->racje = 0;
}

Statek::Statek(Kapitan kapitan, std::string nazwa, int zaloga, int racje = 0) {
	this->kapitan = kapitan;
	this->nazwa = nazwa;
	this->zaloga = zaloga;
	this->racje = racje;
}

int Statek::get_zaloga() const { return zaloga; }
int Statek::get_racje() const { return racje; }
void Statek::set_zaloga(int zaloga) { this->zaloga = zaloga; }
void Statek::set_racje(int n) { this->racje = n; }

void Statek::werbunek(int liczba) {
	zaloga += liczba;
}

Kapitan Statek::get_kapitan() const {
	return kapitan;
}

void Statek::oblicz_zywnosc() {
	racje = 3 * zaloga;
}

class StatekPasazerski : public virtual Statek {
private:
	int pasazerowie;
public:
	StatekPasazerski();
	StatekPasazerski(int);
	int get_pasazerowie() const;
	void set_pasazerowie(int);
	int liczba_osob() const;
	void oblicz_zywnosc() override;
};

StatekPasazerski::StatekPasazerski() {
	pasazerowie = 5;
}

StatekPasazerski::StatekPasazerski(int n) {
	pasazerowie = n;
}

int StatekPasazerski::liczba_osob() const {
	return pasazerowie + get_zaloga();
}

int StatekPasazerski::get_pasazerowie() const {
	return pasazerowie;
}

void StatekPasazerski::set_pasazerowie(int p) {
	pasazerowie = p;
}

void StatekPasazerski::oblicz_zywnosc() {
	set_racje(3 * (get_zaloga() + pasazerowie));
}

class Mysliwiec : public virtual Statek {
private:
	int liczba_wiezyczek = 1;
public:
	int get_wiezyczki() const { return liczba_wiezyczek; };
};

class TransportowiecBojowy : public StatekPasazerski, public Mysliwiec {
};

TEST(Statek, Basic) {
	Statek s1;
	EXPECT_EQ(s1.get_zaloga(), 25);
	s1.werbunek(10);
	EXPECT_EQ(s1.get_zaloga(), 35);
	s1.set_zaloga(3);
	EXPECT_EQ(s1.get_zaloga(), 3);
	s1.oblicz_zywnosc();
	EXPECT_EQ(s1.get_racje(), 9);

	Kapitan k2("KKK", "UUU", 4, true);
	Statek s2(k2, "QWE", 1, 0);
	EXPECT_EQ(s2.get_zaloga(), 1);
}

TEST(StatekPasazerski, Basic) {
	StatekPasazerski liniowiec = StatekPasazerski{};
	EXPECT_EQ(liniowiec.liczba_osob(), 30);
	liniowiec.werbunek(16);
	EXPECT_EQ(liniowiec.liczba_osob(), 46);
	liniowiec.set_pasazerowie(4);
	EXPECT_EQ(liniowiec.liczba_osob(), 45);
	EXPECT_EQ(liniowiec.get_zaloga(), 41);

	EXPECT_EQ(liniowiec.get_kapitan().get_imie(), "John");
	liniowiec.oblicz_zywnosc();
	EXPECT_EQ(liniowiec.get_racje(), 135);
	
	StatekPasazerski sp_racje;
	EXPECT_EQ(sp_racje.liczba_osob(), 30);
	sp_racje.oblicz_zywnosc();
	EXPECT_EQ(sp_racje.get_racje(), 90);
	Statek statek_racje;
	EXPECT_EQ(sp_racje.get_zaloga(), 25);
	statek_racje.oblicz_zywnosc();
	EXPECT_EQ(statek_racje.get_racje(), 75);
}

TEST(TransportowiecBojowy, Basic) {
	TransportowiecBojowy trb;
	EXPECT_EQ(trb.get_wiezyczki(), 1);
}

TEST(Polimorfizm, Basic) {
	TransportowiecBojowy* trb = new TransportowiecBojowy();
	// Statek wiozący 100 pasażerów:
	StatekPasazerski* z_pasazerami = new StatekPasazerski(100);  
	Statek* tab_statki[] = { new Statek{}
		, new StatekPasazerski{}
		, new Statek(Kapitan("Susan", "Ivanova", 10, false), "Starfury", 1)
		, trb
		, z_pasazerami
	};
	
	for (Statek* statek : tab_statki) {
		statek->oblicz_zywnosc();
	}

	EXPECT_EQ(tab_statki[0]->get_racje(), 75);
	EXPECT_EQ(tab_statki[1]->get_racje(), 90);
	EXPECT_EQ(tab_statki[2]->get_racje(), 3);
	EXPECT_EQ(tab_statki[3]->get_racje(), 90);
	EXPECT_EQ(tab_statki[4]->get_racje(), 375);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
