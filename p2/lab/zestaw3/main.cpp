// link do repozytorium:
// https://github.com/tangens90/homework/tree/main/p2/lab/zestaw3

#include <regex>
#include <iostream>

using namespace std;

int main() {
	smatch dopasowania;
	string text = "Eternal eternal Elektryk elektryk Energia energia Ekran ekran Akwarium akwarium Dominika dominika Marmolada marmolada Wianek wianek Krzysztof krzysztof Waldek waldek Alergia alergia Ale ale";
	regex wzor(R"(\b([^\WeEa]\w*a\w*)\b|\b(a\w*)\b)");
	while (regex_search(text, dopasowania, wzor)) {
		cout << dopasowania.str(0) << endl;
		text = dopasowania.suffix().str();
	}
}
