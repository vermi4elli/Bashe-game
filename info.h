#pragma once
#include <map>
#include <string>
using namespace std;

class info {
private:
	string last_name;
	map<string, pair<int, int>> ranks;
	friend class bashe;
public:
	int GameStart();
	void NewPlayer();
	void PrintStones(int amount);
	void NewTurn(bool user);
	void EndGame(bool user_victory);
};
