#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <ctime>
#include <conio.h>
#include "info.h"
#include "decision_tree.h"
using namespace std;

static const string delim = "\n\n======================================\n\n";

class bashe {
private:
	int amount;
	int M;
	void Computer(info& Game, int level);
	void ComputerEasy(info& Game);
	void ComputerMedium(info& Game);
	void ComputerHard(info& Game);
public:
	bashe();
	void Fill(int& amount, int& M, bool& user);
	int Play(info& Game);
	void PlayGame(info& Game, int level);
	void PrintRankTable(info& Game);
};

inline bashe::bashe() {
	amount = 0;
	M = 0;
}
inline void bashe::ComputerEasy(info& Game) {
	int taken = 0;
	if (amount - M >= 0) {
		taken = rand()% M+1;
	}
	else {
		taken = rand() % amount+1;
	}
	amount -= taken;
	cout << "Computer has taken " << taken << " stones\n" << endl;
	Game.PrintStones(amount);
}
inline void bashe::ComputerMedium(info& Game) {
	if (rand() % 2) ComputerEasy(Game);
	else ComputerHard(Game);
}
inline void bashe::ComputerHard(info& Game) {
	decision_tree tree(amount, M);
	tree.Fill();
	int max = 0;
	tree.Modify();
	int taken = tree.FindBestVariant();
	amount -= taken;
	cout << "Computer has taken " << taken << " stones\n" << endl;
	Game.PrintStones(amount);
}
inline void bashe::Computer(info& Game, int level) {
	if (level == 1) ComputerEasy(Game);
	if (level == 2) ComputerMedium(Game);
	if (level == 3) ComputerHard(Game);
}
inline void bashe::Fill(int& amount, int& M, bool& user) {
	cout << "Enter the amount of stones: ";
	cin >> amount;
	cout << "Enter the amount of max stones could be taken in 1 round: ";
	cin >> M;
	cout << "\nEnter '1' if you want to go first" << endl;
	cout << "Enter '0' if you want to go second" << endl;
	cout << "Your answer: ";
	cin >> user;
	cout << endl;
}
inline void bashe::PrintRankTable(info& Game) {
	cout << delim;
	
	int counter = 0;
	rsize_t length_num = to_string(static_cast<int>(Game.ranks.size())).length();
	rsize_t length_name = 4;
	
	for (const auto& name : Game.ranks) {
		if (name.first.length() > length_name) length_name = name.first.length();
	}
	cout << setw(length_num) << " " << "  " << setw(length_name) << "Name" << "   " << setw(length_num) << "W" << " - " << setw(length_num) << "L" << endl;
	
	for (const auto& person : Game.ranks) {
		cout << setw(length_num) << ++counter << ") " << setw(length_name) << person.first << " : " << setw(length_num) << person.second.first << " - " << setw(length_num) << person.second.second << endl;
	}

	cout << delim;
	
	cout << "Press any key to continue...";
	char garbage = _getch();
}
inline int bashe::Play(info& Game) {
	int variant = Game.GameStart();
	if (variant == 1) {
		Game.NewPlayer();
		cout << "Press '1' if you'd like to select \"easy\"" << endl;
		cout << "Press '2' if you'd like to select \"medium\"" << endl;
		cout << "Press '3' if you'd like to select \"hard\"" << endl;
		cout << "Select the level of difficulty: ";
		int level = 0;
		cin >> level;
		cout << endl;
		PlayGame(Game, level);
	}
	else if(variant == 2) {
		PrintRankTable(Game);
	}
	else if(variant == 3) {
		cout << "Thanks for playing!!!" << endl;
	}
	return variant;
}
inline void bashe::PlayGame(info& Game, int level) {
	bool user = 0;
	Fill(amount, M, user);

	while (amount > 0) {
		Game.NewTurn(user);
		if (!user) {
			Computer(Game, level);
			user = !user;
			continue;
		}
		cout << "Enter how many stones out of " << M << " you'd like to take: ";
		int taken = 0;
		cin >> taken;
		cout << endl;
		while (taken > M && amount-taken < 0) {
			if (amount - taken >= 0) {
				cout << "The entered value is bigger than " << M << "!\nReenter the value: ";
				cin >> taken;
				cout << endl;
			}
			else {
				cout << "The entered value is bigger than the amount of stones left in the heap!\nReenter the value: ";
				cin >> taken;
				cout << endl;
			}
		}
		amount -= taken;
		Game.PrintStones(amount);
		user = !user;
	}
	if (amount == 0 && user) {
		Game.EndGame(0);
	}
	else if (amount == 0 && !user) {
		Game.EndGame(1);
	}

	cout << "Press any key to continue...";
	char garbage = _getch();
}

int main() {
	info Game;
	int playing = 0;
	while (playing != 3) {
		bashe game;
		playing = game.Play(Game);
		system("cls");
	}
	return 0;
}
