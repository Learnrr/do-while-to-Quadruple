#include<iostream>
#include"Analyze.h"
#include<fstream>
#include<string>
#include <sstream>
using namespace std;
void Analysis::initialize_actionTable() {
	ifstream in;
	string temp;
	in.open("analysisTable.txt");
	if (!in.is_open()) {
		abort();
	}
	for (int i = 0; i < 119; i++) {

		for (int j = 0; j < 20; j++) {
			in >> temp;
			if (temp[0] == 'S') {
				actionTable[i][j].act="S";
				string s = temp.substr(1);
				std::istringstream ss(s);
				ss >> actionTable[i][j].gonum;
			}
			else if (temp == "acc") {
				actionTable[i][j].act = "acc";
			}
			else if (temp[0] == 'r') {
				actionTable[i][j].act = "r";
				string s = temp.substr(1);
				std::istringstream ss(s);
				ss >> actionTable[i][j].gonum;
			}
		}
		for (int j = 20; j < 29; j++) {
			in >> temp;
			std::istringstream ss(temp);
			ss >> gotoTable[i][j-20];
		}
	}
	in.close();
}

void Analysis::display_table() {
	for (int i = 0; i < 119; i++) {
		for (int j = 0; j < 20; j++) {

				if (actionTable[i][j].act == "-1")
					cout << "-1" << " ";
				else cout << actionTable[i][j].act << actionTable[i][j].gonum << " ";
		}
		for (int j = 20; j < 29; j++) {
			cout << gotoTable[i][j-20] << " ";
		}
		cout << endl;
	}
}
symbol Analysis::newType() {
	symbol T;
	T.name = "T" + to_string(symbolnum);
	T.pos = symTable.size();
	symTable.push_back(T);
	semantic_to_symbol[T.name] = T.pos;
	symbolnum++;
	return T;
}
void Analysis::GEN(string op, int A1index,int A2index, int resultindex) {
	item new_item;
	if (op == "neg") {
		symTable[resultindex].value = "-" + symTable[A1index].value;
	}
	if (op == "+") {
		symTable[resultindex].value = to_string(stoi(symTable[A1index].value) + stoi(symTable[A2index].value));
	}
	else if (op == "-") {
		symTable[resultindex].value = to_string(stoi(symTable[A1index].value) - stoi(symTable[A2index].value));
	}
	else if (op == "*") {
		symTable[resultindex].value = to_string(stoi(symTable[A1index].value) * stoi(symTable[A2index].value));
	}
	else if (op == "/") {
		if (stoi(symTable[A2index].value) == 0) {
			cout << "Integer division by zero。" << endl;            // 除 0 err
			return;
		}
		symTable[resultindex].value = to_string(stoi(symTable[A1index].value) / stoi(symTable[A2index].value));
	}
	else if (op == "=") {
		symTable[resultindex].value = symTable[A1index].value;
	}
	else if (op == "==") {
		symTable[resultindex].value;
	}
	new_item.op = op;
	new_item.A1index = A1index;
	new_item.A2index = A2index;
	new_item.resultindex = resultindex;
	siyuanshiTable.push_back(new_item);
}
void Analysis::A_do_B_while_C() {
	symbol DO, B, C;
	symStack.pop();
	symStack.pop();
	C = symStack.top();
	symStack.pop();
	symStack.pop();
	symStack.pop();
	symStack.pop();
	B = symStack.top();
	symStack.pop();
	symStack.pop();
	DO = symStack.top();
	symStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();

	symStack.push(symbol{"A"});
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][0]);
	semanticStack.pop();
	semanticStack.pop();
	DO.value = symTable[semantic_to_symbol[semanticStack.top()]].value;
	semanticStack.pop();
	int A1index = C.pos;
	siyuanshiTable.push_back(item{ "j_true",A1index,-1,stoi(DO.value) });
}
void Analysis::B_A() {
	symbol A = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "B" });
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][1]);
}
void Analysis::B_S() {
	symStack.pop();
	symbol S = symStack.top();
	
	symStack.pop();
	symStack.push(symbol{ "B" });
	statusStack.pop();
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][1]);
}
void Analysis::B_S_B() {
	symbol B = symStack.top();
	symStack.pop();
	symStack.pop();
	symStack.pop();
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "B" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][1]);
}
void Analysis::C_E1_ROP_E2() {
	symbol E1, E2, ROP;
	E2 = symStack.top();
	symStack.pop();
	ROP = symStack.top();
	symStack.pop();
	E1 = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "C" });

	statusStack.pop();
	statusStack.pop();
	statusStack.pop();

	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][2]);
	symbol T = newType();

	GEN(ROP.value, E1.pos, E2.pos, T.pos);
	semanticStack.pop();
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}

void Analysis::E_E1_add_F() {
	symbol F, E1;
	F=symStack.top();
	symStack.pop();
	symStack.pop();
	E1=symStack.top();
	symStack.pop();
	symStack.push(symbol{ "E" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][3]);

	symbol T = newType();
	GEN("+", E1.pos, F.pos, T.pos);
	semanticStack.pop();
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}
void Analysis::E_E1_minus_F() {
	symbol F, E1;
	F = symStack.top();
	symStack.pop();
	symStack.pop();
	E1 = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "E" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][3]);

	symbol T = newType();
	GEN("-", E1.pos, F.pos, T.pos);
	semanticStack.pop();
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}
void Analysis::E_F() {
	symbol F = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "E" });
	statusStack.pop();
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][3]);
	symStack.top().pos = semantic_to_symbol[semanticStack.top()];
}
void Analysis::E_neg_E1() {
	symbol E1 = symStack.top();
	symStack.pop();
	symStack.pop();
	symStack.push(symbol{ "E" });
	statusStack.pop();
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][3]);

	symbol T = newType();
	GEN("neg", E1.pos, -1, T.pos);
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}
void Analysis::F_F1_div_G() {
	symbol F1, G;
	 G= symStack.top();
	symStack.pop();
	symStack.pop();
	F1 = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "F" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][4]);

	symbol T = newType();
	GEN("/", F1.pos, G.pos, T.pos);
	semanticStack.pop();
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}
void Analysis::F_F1_mul_G() {
	symbol F1, G;
	G = symStack.top();
	symStack.pop();
	symStack.pop();
	F1 = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "F" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	int curStatus = statusStack.top();
	statusStack.push(gotoTable[curStatus][4]);

	symbol T = newType();
	GEN("*", F1.pos, G.pos, T.pos);
	semanticStack.pop();
	semanticStack.pop();
	semanticStack.push(T.name);
	symStack.top().pos = T.pos;
	symStack.top().value = T.value;
}
void Analysis::F_G() {
	symbol G = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "F" });
	statusStack.pop();
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][4]);
	symStack.top().pos = semantic_to_symbol[semanticStack.top()];
}
void Analysis::G_E() {	
	symStack.pop();
	symbol E = symStack.top();
	symStack.pop();
	symStack.pop();
	symStack.push(symbol{ "G" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][5]);
	symStack.top().pos = semantic_to_symbol[semanticStack.top()];

}
void Analysis::G_i() {
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "G" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][5]);
	symStack.top().pos = semantic_to_symbol[semanticStack.top()];//将语义值和G关联
}
void Analysis::G_n() {
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "G" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][5]);
	symStack.top().pos = semantic_to_symbol[semanticStack.top()];
}
void Analysis::ROP_larger() {
	symbol r = symStack.top();
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "ROP" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][6]);
	symStack.top().value = r.name;
}
void Analysis::ROP_lower() {
	symbol r = symStack.top();
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "ROP" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][6]);
	symStack.top().value = r.name;
}
void Analysis::ROP_larger_equal() {
	symbol r = symStack.top();
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "ROP" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][6]);
	symStack.top().value = r.name;
}
void Analysis::ROP_lower_equal() {
	symbol r = symStack.top();
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "ROP" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][6]);
	symStack.top().value = r.name;
}
void Analysis::ROP_logical_equal() {
	symbol r = symStack.top();
	symStack.pop();
	statusStack.pop();
	symStack.push(symbol{ "ROP" });
	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][6]);
	symStack.top().value = r.name;
}
void Analysis::S_i_E() {
	symbol E,i;
	E = symStack.top();
	symStack.pop();
	symStack.pop();
	i = symStack.top();
	symStack.pop();
	symStack.push(symbol{ "S" });
	statusStack.pop();
	statusStack.pop();
	statusStack.pop();

	int curstatus = statusStack.top();
	statusStack.push(gotoTable[curstatus][7]);

	semanticStack.pop();
	i.name = semanticStack.top();
	semanticStack.pop();
	GEN("=", E.pos, -1, semantic_to_symbol[i.name]);
}
void Analysis::initialize() {
	symbolnum = 0;
	symTable.clear();
	siyuanshiTable.clear();
	semantic_to_symbol.clear();
	if (!statusStack.empty()) {
		statusStack.pop();
	}
	if (!semanticStack.empty()) {
		semanticStack.pop();
	}
	if (!symStack.empty()) {
		symStack.pop();
	}
}
void Analysis::analyze() {
	int pointer = 0;
	string cursymbol;
	word curword;
	L.run();//分析输入串得到LexicalTable
	statusStack.push(0);
	symStack.push(symbol{ "#" });
	int doindex = 0;
	while (!symStack.empty()) {
		if (pointer < L.lexicalTable.size()) {
			curword = L.lexicalTable[pointer];
			cursymbol = curword.data;
			if (L.getWordType(curword) == 3) {//标识符
				cursymbol = "i";
				semanticStack.push(curword.data);
				symbol s;
				s.name = curword.data;
				s.value = "0";//还未赋值，在规约时赋值
				s.pos = symTable.size();
				symTable.push_back(s);
				semantic_to_symbol[s.name] = s.pos;
			}
			else if (L.getWordType(curword) == 4) {//常量
				cursymbol = "n";
				semanticStack.push(curword.data);
				symbol s;
				s.name = curword.data;
				s.value = curword.data;
				s.pos = symTable.size();
				symTable.push_back(s);
				semantic_to_symbol[s.name] = s.pos;
			}
			else if (curword.sym == 4) {//do
				semanticStack.push(curword.data + to_string(doindex));
				symbol s;
				s.name = curword.data + to_string(doindex);
				s.value = to_string(siyuanshiTable.size());//记录当前四元式位置
				s.pos = symTable.size();
				symTable.push_back(s);
				semantic_to_symbol[s.name] = s.pos;
				doindex++;
			}
			else if (G.getVIndex(cursymbol) == -1) {
				cout << "wrong" << endl;
				return;
			}
		}
		int curstatus = statusStack.top();
		action curact = actionTable[curstatus][G.getVIndex(cursymbol)];
		if (curact.act == "S") {
			statusStack.push(curact.gonum);
			symStack.push({ cursymbol });
			pointer++;
		}
		else if (curact.act == "r") {
			int num = curact.gonum;
			switch (num) {
			case 1:
				A_do_B_while_C();      //
				break;
			case 2:
				C_E1_ROP_E2();         //
				break;
			case 3:
				B_S_B();            //
				break;
			case 4:
				B_S();              //
				break;
			case 5:
				B_A();              //
				break;
			case 6:
				S_i_E();            // S -> i=E 
				break;
			case 7:
				E_neg_E1();           // E-> -E
				break;
			case 8:
				E_F();              // E-> F
				break;
			case 9:
				E_E1_add_F();         // E->E+F
				break;
			case 10:
				E_E1_minus_F();        // E->E-F
				break;
			case 11:
				F_G();              // E->G
				break;
			case 12:
				F_F1_mul_G();          // E->F*G
				break;
			case 13:
				F_F1_div_G();         // E->F/G
				break;
			case 14:
				G_i();              // G->i
				break;
			case 15:
				G_n();              // G->n
				break;
			case 16:
				G_E();              // G->(E)
				break;
			case 17:
				ROP_larger();      //
				break;
			case 18:
				ROP_lower();     //
				break;
			case 19:
				ROP_logical_equal();     //
				break;
			case 20:
				ROP_larger_equal();       //
				break;
			case 21:
				ROP_lower_equal();       //
				break;
			default:
				cout << "wrong grammar index" << endl;
			}
			
		}
		else if (curact.act == "acc") {
			statusStack.pop();
			symStack.pop();
			statusStack.pop();
			symStack.pop();
		}
		else {
			cout << "分析错误" << endl;
			return;
		}
	}
}
void Analysis::display_siyuanshiTable() {
		
		for (auto iter : siyuanshiTable) {
			
			//cout << "(" << iter.op << "," << iter.A1index << "," << iter.A2index << "," << iter.resultindex << ")" << endl;
			cout << "(";
			cout << iter.op;
			cout << ";";
			if (iter.op[0] == 'j') {
				if (iter.A1index != -1)
					cout << symTable[iter.A1index].name;
				else
					cout << "-1";
				
				cout << ";-1" <<";"<< iter.resultindex;
			}
			else {
				if (iter.A1index != -1)
					cout << symTable[iter.A1index].name;
				else
					cout << "-1";
				if (iter.A2index != -1)
					cout << ";" << symTable[iter.A2index].name;
				else
					cout <<","<<"-1";
				if (iter.resultindex != -1)
					cout << "," << symTable[iter.resultindex].name;
				else
					cout << "," << "-1";
			}
			cout << ")";
			cout << endl;
		}
	
}
