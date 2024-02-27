#include<algorithm>
#include<iomanip>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<stack>
#include"Grammar.h"
using namespace std;

/*ÎÄ·¨
1£©A -> do{B}while{C}£»

2£©C -> E ROP E

3£©B -> S;B | S; | A

4£©S -> i=E

5£©E -> -E | F | E+F | E-F | G

6£©F -> F*G | F/G

7£©G -> i | n | (E)

8£©ROP -> > | < | == | >= | <=

*/
void Grammar::initial_grammar() {

	production item = { "S'",{"S"} };
	all_production.push_back(item);
	item = { "S",{"i=E"} };
	all_production.push_back(item);
	item = { "A",{"do","{","B","}","while","{","C","}"}};
	all_production.push_back(item);
	item = { "C",{"E","ROP","E"}};
	all_production.push_back(item);
	item = { "B",{"S",";","B"}};
	all_production.push_back(item);
	item = { "B",{"S",";"}};
	all_production.push_back(item);
	item = { "B",{"A"} };
	all_production.push_back(item);
	item = { "E",{"E","+","F"}};
	all_production.push_back(item);
	item = { "E",{"E","-","F"} };
	all_production.push_back(item);
	item = { "E",{"F"} };	
	all_production.push_back(item);
	item = { "E",{"-","E"} };
	all_production.push_back(item);
	item = { "E",{"G"} };
	all_production.push_back(item);
	item = { "F",{"F","*","G"}};
	all_production.push_back(item);
	item = { "F",{"F","/","G"}};
	all_production.push_back(item);
	item = { "G",{"(","E",")"}};
	all_production.push_back(item);
	item = { "G",{"n"} };
	all_production.push_back(item);
	item = { "G",{"i"} };
	all_production.push_back(item);
	item = { "ROP",{">"} };
	all_production.push_back(item);
	item = { "ROP",{"<"} };
	all_production.push_back(item);
	item = { "ROP",{">="} };
	all_production.push_back(item);
	item = { "ROP",{"<="} };
	all_production.push_back(item);
	item = { "ROP",{"=="} };
	all_production.push_back(item);

	vnSet.insert("A");
	vnSet.insert("B");
	vnSet.insert("C");
	vnSet.insert("E");
	vnSet.insert("F");
	vnSet.insert("G");
	vnSet.insert("ROP");	
	vnSet.insert("S");
	vnSet.insert("S'");
	

	vtSet.insert("{");
	vtSet.insert("}");
	vtSet.insert("while");
	vtSet.insert("do");
	vtSet.insert(";");
	vtSet.insert("i");
	vtSet.insert("=");
	vtSet.insert("+");
	vtSet.insert("-");
	vtSet.insert("*");
	vtSet.insert("/");
	vtSet.insert("n");
	vtSet.insert(">");
	vtSet.insert("<");
	vtSet.insert("(");
	vtSet.insert(")");
	vtSet.insert(">=");
	vtSet.insert("<=");
	vtSet.insert("==");

	firstSet.insert(pair<string, set<string>>("S'", { "do" }));
	firstSet.insert(pair<string, set<string>>("A", { "do" }));
	firstSet.insert(pair<string, set<string>>("B", { "do", "i" }));
	firstSet.insert(pair<string, set<string>>("C", { "(","-","i","n" }));
	firstSet.insert(pair<string, set<string>>("S", { "i" }));
	firstSet.insert(pair<string, set<string>>("E", { "(","-","i","n" }));
	firstSet.insert(pair<string, set<string>>("F", { "i", "n", "(" }));
	firstSet.insert(pair<string, set<string>>("G", { "i", "n", "(" }));
	firstSet.insert(pair<string, set<string>>("ROP", { ">","<","==",">=","<=" }));


}
int Grammar::getVIndex(string V) {
	if (V == "#")return 0;
	else if (V == "(")return 1;
	else if (V == ")")return 2;
	else if (V == "*")return 3;
	else if (V == "+")return 4;
	else if (V == "-")return 5;
	else if (V == "/")return 6;
	else if (V == ";")return 7;
	else if (V == "<")return 8;
	else if (V == "<=")return 9;
	else if (V == "=")return 10;
	else if (V == "==")return 11;
	else if (V == ">")return 12;
	else if (V == ">=")return 13;


	else if (V == "do")return 14;
	else if (V == "i")return 15;
	else if (V == "n")return 16;
	else if (V == "while")return 17;
	else if (V == "{")return 18;
	else if (V == "}")return 19;
	else if (V == "A")return 20;
	else if (V == "B")return 21;
	else if (V == "C")return 22;
	else if (V == "E")return 23;
	else if (V == "F")return 24;
	else if (V == "G")return 25;
	else if (V == "ROP")return 26;
	else if (V == "S")return 27;
	else if (V == "S'")return 28;

	else return -1;
}
