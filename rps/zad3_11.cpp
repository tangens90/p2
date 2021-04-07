#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>

using namespace std;

int getRand(int size) {
	return (rand() % size);
}

void getRandPair(int size, int& a, int& b) {
	a = getRand(size);
	do {
		b = getRand(size);
	} while (a == b);
}

struct Player {
	int default_tokens;
	int tokens;
	int wins;

	void resetTokens() {
		tokens = default_tokens;
	}

	Player() {
		wins = 0;
	}
};

int found_winner(Player* players, int r, int tokens_sum) {
	for (int i = 0; i < r; i++) {
		if (players[i].tokens == tokens_sum) {
			return i;
		}
	}
	return -1;
}

void simulate(Player* players, int r, vector<int>& active_players, int tokens_sum) {
	int winner;
	while ((winner = found_winner(players, r, tokens_sum)) == -1) {
		int a, b;
		getRandPair(active_players.size(), a, b);
		int result = getRand(2);
		int toRemove = result == 0 ? a : b;
		int toAdd = result == 0 ? b : b;
		players[active_players[toRemove]].tokens--;
		players[active_players[toAdd]].tokens++;
		if (players[active_players[toRemove]].tokens <= 0)
			active_players.erase(active_players.begin() + toRemove);
	}

	players[winner].wins++;
}

int main() {
	srand(time(NULL));
	// n - ilość symulacji
	// r - ilość graczy
	int n, r;
	int tokens_sum = 0;
	cin >> n >> r;
	Player* players = new Player[r];
	for (int i = 0; i < r; i++) {
		cin >> players[i].default_tokens;
		tokens_sum += players[i].default_tokens;
	}
	
	for (int i = 0; i < n; i++) {
		vector<int> active_players;
		for (int j = 0; j < r; j++) {
			active_players.push_back(j);
			players[j].resetTokens();
		}
		simulate(players, r, active_players, tokens_sum);
	}

	for (int i = 0; i < r; i++) {
		cout << i << ":\twins=" << players[i].wins << "\t" << (int)((double)players[i].wins / (double)n * 100.0) << "%" << endl;
	}

	delete[] players;
}
