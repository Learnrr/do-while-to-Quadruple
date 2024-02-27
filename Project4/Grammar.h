#pragma once
#include<iostream>
#include<vector>
#include<set>
#include<map>
using namespace std;
struct production {
	string left;
	vector<string>right;
};

class Grammar {
private:
	vector<production> all_production;//产生式集合

	set<string> vnSet;//非终结符集
	set<string> vtSet;//终结符集

	map<string, set<string>> firstSet;//first集
	map<string, set<string>> followSet;//follow集
public:
	void initial_grammar();
	int getVIndex(string V);
};