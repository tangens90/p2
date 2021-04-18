// TODO link do githuba

#include <regex>
#include <iostream>

using namespace std;

int main() {
	smatch dopasowania;
	string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
	regex wzor(R"([^\WeE]\w*a\w*)");
	while (regex_search(text, dopasowania, wzor)) {
		cout << dopasowania.str(0) << endl;
		text = dopasowania.suffix().str();
	}
}
