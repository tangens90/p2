// link do repozytorium:
// https://github.com/tangens90/homework/tree/main/p2/lab/zestaw4

#include <iostream>
#include <fstream>

using namespace std;

enum LEVEL { 
	FINEST = 0, 
	FINER = 1, 
	FINE = 2, 
	CONFIG = 3, 
	INFO = 4, 
	WARNING = 5, 
	SEVERE = 6
};

class Dziennik {
public:
	void changeLevel(LEVEL lvl) {
		this->lvl = lvl;
	}

	Dziennik(int ot, LEVEL lvl) : outputTarget(ot), lvl(lvl) {}

	void print(std::string message, ofstream& fout) {
		std::string output;
		switch (lvl) {
			case FINEST:
				output += "[FINEST] ";
			case FINER:
				output += "[FINER] ";
			case FINE:
				output += "[FINE] ";
			case CONFIG:
				output += "[CONFIG] ";
			case INFO:
				output += "[INFO] ";
			case WARNING:
				output += "[WARNING] ";
			case SEVERE:
				output += "[SEVERE] ";
		}
		if (outputTarget == 0)
			std::cout << output << message << std::endl;
		else
			fout << output.c_str() << message << endl;
	}

	void finest(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void finer(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void fine(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void config(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void info(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void warning(string msg, ofstream& fout) {
		print(msg, fout);
	}

	void severe(string msg, ofstream& fout) {
		print(msg, fout);
	}

private:
	LEVEL lvl;
	int outputTarget;

};

int main() {
	cout << "0 = wypisywanie w konsoli" << endl;
	cout << "1 = wypisywanie w pliku" << endl;
	int op;
	cin >> op;
	ofstream fout("output.txt");
	Dziennik d(op, FINEST);
	d.changeLevel(FINEST);
	d.print("tekst", fout);
	d.changeLevel(FINER);
	d.print("tekst", fout);
	d.changeLevel(FINE);
	d.print("tekst", fout);
	d.changeLevel(CONFIG);
	d.print("tekst", fout);
	d.changeLevel(INFO);
	d.print("tekst", fout);
	d.changeLevel(WARNING);
	d.print("tekst", fout);
	d.warning("tekst 2", fout);
	d.changeLevel(SEVERE);
	d.print("tekst", fout);
	d.print("tekst", fout);
	return 0;
}
