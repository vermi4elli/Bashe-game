#pragma once
#include <vector>
#include <set>


class node {
private:
	int value;
	int taken;
	int level;
	vector<node*> list_of_sons;
public:
	node();
	node(int taken, int value, int level);
	int GetValue() const;
	int GetTaken() const;
	int GetLevel() const;
	void SetValue(int value);
	vector<node*> GetSons();
	void SetSons(vector<node*> temp);
};

class decision_tree {
private:
	int M;
	int amount;
	node* top;
	void FillVector(node* temp, int amount_t);
	void PrintTree(vector<node*> x, int& tabs, set<int>& non);
	void ModifyTree(vector<node*> x);
public:
	decision_tree(int amount, int M);
	void Fill();
	node* GetTop() const;
	void Modify();
	int FindBestVariant();
};
