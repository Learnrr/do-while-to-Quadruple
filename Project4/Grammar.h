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
	vector<production> all_production;//����ʽ����

	set<string> vnSet;//���ս����
	set<string> vtSet;//�ս����

	map<string, set<string>> firstSet;//first��
	map<string, set<string>> followSet;//follow��
public:
	void initial_grammar();
	int getVIndex(string V);
};