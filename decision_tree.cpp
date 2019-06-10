#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <set>
#include "info.h"
#include "decision_tree.h"
using namespace std;

vector<int> FillValues(vector<node*> temp) {
	vector<int> result;
	for (const auto& x : temp) {
		result.push_back(x->GetValue());
	}
	return result;
}

decision_tree::decision_tree(int amount, int M) {
	this->amount = amount;
	this->M = M;
	top = nullptr;
}
void decision_tree::Fill() {
	top = new node();
	int amount_t = amount;
	FillVector(top, amount_t);
	/*int tabs = -1;
	cout << "\n\tPrinting tree:\n" << endl;
	set<int> non;
	PrintTree(top->GetSons(), tabs, non);
	cout << "\n" << endl;*/
}
void decision_tree::FillVector(node* x, int amount_t) {
	vector<node*> result;
	if (amount_t - M > 0) {
		for (int i = 1; i <= M; i++) {
			node* temp = new node(i, -1, x->GetLevel()+1);
			amount_t -= i;
			FillVector(temp, amount_t);
			amount_t += i;
			result.push_back(temp);
		}
	}
	else if (amount_t - M == 0) {
		for (int i = 1; i < M; i++) {
			node* temp = new node(i, -1, x->GetLevel() + 1);
			amount_t -= i;
			FillVector(temp, amount_t);
			amount_t += i;
			result.push_back(temp);
		}
		node* temp = new node(M, (x->GetLevel() + 1) % 2, x->GetLevel() + 1);
		result.push_back(temp);
	}
	else {
		for (int i = 1; i <= M; i++) {
			if (amount_t - i > 0) {
				node* temp = new node(i, -1, x->GetLevel() + 1);
				amount_t -= i;
				FillVector(temp, amount_t);
				amount_t += i;
				result.push_back(temp);
			}
			else if (amount_t - i == 0) {
				node* temp = new node(i, (x->GetLevel() + 1) % 2, x->GetLevel() + 1);
				result.push_back(temp);
			}
			else continue;
		}
	}
	x->SetSons(result);
}
void decision_tree::PrintTree(vector<node *> x, int& tabs, set<int>& non){
	tabs++;
	int counter = 1;
	int deleted = 0;
	for (const auto& y : x) {
		deleted = y->GetLevel();
		if(counter == x.size()) non.insert(deleted);
		for (int i = 1; i <= tabs; i++) {
			if (i == deleted && counter == x.size()) {
				cout << " \t";
				continue;
			}
			else if (non.find(i) != non.end()) {
				cout << " \t";
				continue;
			}
			cout << "|\t";
		}

		char temp = 45;
		cout << setfill(temp) << setw(7) << left << "|";
		cout << setfill(' ');

		cout << "[" << y->GetTaken() << "," << y->GetValue() << "]" << endl;
		

		PrintTree(y->GetSons(), tabs, non);
		++counter;
		if(non.find(deleted) != non.end()) non.erase(non.find(deleted));
	}
	tabs--;
	return;
}
void decision_tree::Modify() {
	ModifyTree(top->GetSons());
	/*int tabs = -1;
	set<int> non;
	PrintTree(top->GetSons(), tabs, non);*/
}
void decision_tree::ModifyTree(vector<node *> x) {
	for (const auto& y : x) {
		if (!y->GetSons().empty()) {
			ModifyTree(y->GetSons());
		}
		else {
			return;
		}

		vector<int> temp = FillValues(y->GetSons());
		sort(begin(temp), end(temp));
		if (y->GetLevel() % 2 == 0) {
			y->SetValue(temp[0]);
		}
		else {
			y->SetValue(temp[temp.size()-1]);
		}
	}
}
int decision_tree::FindBestVariant() {
	vector<node*> temp;
	if (top->GetSons().size() == 0) {
		return top->GetSons()[rand() % (top->GetSons().size() - 1)]->GetTaken();
		cout << "SELECTED RANDOMLY!!!" << endl;
	}
	for (const auto& x : top->GetSons()) {
		if (x->GetValue() == 1) temp.push_back(x);
	}
	sort(begin(temp), end(temp), [](const node* x, const node* y) {
		if (x->GetTaken() > y->GetTaken()) return true;
		return false;
	});
	return temp[0]->GetTaken();
}
node* decision_tree::GetTop() const {
	return top;
}

node::node() {
	this->value = -1;
	this->taken = -1;
	this->level = 0;
}
node::node(int taken, int value, int level) {
	this->value = value;
	this->taken = taken;
	this->level = level;
}
int node::GetValue() const {
	return this->value;
}
void node::SetValue(int value) {
	this->value = value;
}
int node::GetLevel() const {
	return level;
}
int node::GetTaken() const {
	return taken;
}
vector<node*> node::GetSons() {
	return this->list_of_sons;
}
void node::SetSons(vector<node*> temp) {
	this->list_of_sons = temp;
}
