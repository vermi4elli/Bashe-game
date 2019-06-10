#include <map>
#include <string>
#include <iostream>
#include "info.h"
using namespace std;

static const string delim = "\n\n======================================\n\n";

int info::GameStart() {
	cout << "\nBASHE GAME!!!";
	cout << delim;
	cout << "Press '1' if you'd like to begin a new game" << endl;
	cout << "Press '2' if you'd like to see a rank table" << endl;
	cout << "Press '3' if you'd like to exit the game" << endl;
	cout << "Your answer: ";
	int variant = 0;
	cin >> variant;
	cout << endl;
	return variant;
}
void info::NewPlayer() {
	cout << "Enter the new player's name: ";
	string name;
	cin >> name;
	last_name = name;
	cout << endl;
	if (ranks.find(last_name) == ranks.end()) {
		ranks[last_name].first = 0;
		ranks[last_name].second = 0;
	}
}
void info::PrintStones(int amount) {
	if (amount == 0) {
		cout << "No stones left!\n" << endl;
		return;
	}
	cout << "Stones:" << endl;
	for (int i = 0; i < amount; i++) {
		cout << "* ";
	}
	cout << "\n" << endl;
}
void info::NewTurn(bool user) {
	if (user) {
		cout << "It's now your turn, " << last_name << endl;
	}
	else {
		cout << "It's now computer's turn" << endl;
	}
}
void info::EndGame(bool user_victory) {
	if (user_victory) {
		cout << "YOU HAVE WON, CONGRATULATIONS!\n" << endl;
		ranks[last_name].first++;
	}
	else {
		cout << "COMPUTER HAS WON, AGAIN...\n" << endl;
		ranks[last_name].second++;
	}
}
