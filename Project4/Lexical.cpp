#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<string>
#include"Lexical.h"
using namespace std;

int Lexical::getWordType(word w) {
	if (w.sym >= 0 && w.sym <= 34) {
		return 1;//关键字
	}
	else if (w.sym >= 35 && w.sym <= 66) {
		return 2;//运算符
	}
	else if (w.sym == 67) {
		return 3;//标识符
	}
	else return 4;//常数
}
void Lexical::printWord(word w) {
	switch (getWordType(w)) {
	case 2:
		cout << "( 操作符, ";
		break;
	case 1:
		cout << "( 关键字, ";
		break;
	case 4:
		cout << "( 常量, ";
		break;
	case 3:
		cout << "( 标识符, ";
		break;
	default:
		cout << "err input: ";
	}
	cout << w.sym << " , " << w.data << " )" << endl;
}
void Lexical::GetBC() {
	while ((ch == ' ') | (ch == '\t'|(ch=='\n'))) {
		GetChar();
	}
}
bool Lexical::IsLetter() {
	if (ch >= 'a' && ch <= 'z') {
		return true;
	}
	else if (ch >= 'A' && ch <= 'Z') {
		return true;
	}
	else return false;
}
bool Lexical::IsDigit() {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	else return false;
}
int Lexical::Reserse() {
	for (int i = 0; i < 35; i++) {
		if (strToken == k[i]) {
			return i;
		}
	}
	return -1;
}
int Lexical::Find_s() {
	for (int i = 0; i < 32; i++) {
		string temp(1, ch);
		if (temp == s[i]) {
			return i;
		}
	}
	return -1;
}
void  Lexical::Retract() {
	pint--;
	ch = ' ';
}
void Lexical::Concat() {
	strToken += ch;
}
void Lexical::InsertId() {
	word* w = new word();
	w->data = strToken;
	w->sym = ID;
	lexicalTable.push_back(*w);
	printWord(*w);
}
void Lexical::InsertConst() {
	word* w = new word();
	w->data = strToken;
	w->sym = CONST;
	lexicalTable.push_back(*w);
	printWord(*w);
}
void Lexical::Insertchar(int i) {
	word* w = new word();
	w->data = ch;
	w->sym = i + 35;
	lexicalTable.push_back(*w);
	printWord(*w);
}
void Lexical::Analyze() {
	bool ifhaspoint = false;
	bool ifwrongpoint = false;
	int code;
	bool isWrongInput = false;
	while (ch != '#' && pint < input.size() - 1) {
		GetChar();
		GetBC();
		if (IsLetter() | (ch == '_')) {//判断标识符，以字母或下划线开头
			while (IsLetter() | IsDigit() | (ch == '_')) {
				Concat();
				GetChar();
			}
			Retract();
			code = Reserse();//判断标识符是否key
			if (code == -1) {
				InsertId();
			}
			else {
				word* w = new word();
				w->data = k[code];
				w->sym = code;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
		}
		else if (IsDigit()) {//判断数字
			while (IsDigit() | (ch == '.')) {
				Concat();
				GetChar();
				if (IsLetter()) {
					cout << "wrong input" << endl;//数字开头，字母出现在后面，错误
					while (IsLetter() | IsDigit())GetChar();
					Retract();
					isWrongInput = true;
					break;
				}
				if (ch == '.') {
					if (ifhaspoint == true) {
						cout << "wrong input" << endl;
						while (IsDigit() | (ch == '.'))GetChar();
						Retract();
						ifwrongpoint = true;
						break;
					}
					ifhaspoint = true;
					continue;
				}
			}
			if (!isWrongInput && !ifwrongpoint) {
				Retract();
				InsertConst();
			}
			isWrongInput = false;
		}
		else switch (ch)//判断运算符和界符// { ',',';','(',')','{','}' ,'[', ']','+','-','>','<','=','/','*', '|','&','\'',':','%'};
		{
		case '+': {
			GetChar();
			if (ch == '+') {
				word* w = new word();
				w->data = "++";
				w->sym = 55;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else {
				Retract();
				ch = '+';
				Insertchar(Find_s());
			}
			break;
		}


		case '-': {
			GetChar();
			if (ch == '-') {
				word* w = new word();
				w->data = "--";
				w->sym = 61;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else {
				Retract();
				ch = '-';
				Insertchar(Find_s());
			}
			break;
		}
		case '*': Insertchar(Find_s()); break;
		case '/': {
			GetChar();
			if (ch == '/') {
				return;
			}
			else
				Retract();
			ch = '/'; Insertchar(Find_s());
			break;
		}
		case'=': Insertchar(Find_s());  break;
		case '(':Insertchar(Find_s()); break;
		case ')':Insertchar(Find_s()); break;
		case '[':Insertchar(Find_s()); break;
		case ']':Insertchar(Find_s()); break;
		case '{':Insertchar(Find_s()); break;
		case '}':Insertchar(Find_s()); break;
		case ';':Insertchar(Find_s()); break;
		case ',':Insertchar(Find_s());  break;
		case '|':Insertchar(Find_s()); break;
		case '&':Insertchar(Find_s());  break;

		case '<': {
			GetChar();
			if (ch == '=') {
				word* w = new word();
				w->data = "<=";
				w->sym = 64;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else if (ch == '<') {
				word* w = new word();
				w->data = "<<";
				w->sym = 62;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else {
				Retract();
				ch = '<'; Insertchar(Find_s());
			}
			break;
		}
		case '>': {
			GetChar();
			if (ch == '=') {
				word* w = new word();
				w->data = ">=";
				w->sym = 65;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else if (ch == '>') {
				word* w = new word();
				w->data = ">>";
				w->sym = 63;
				lexicalTable.push_back(*w);
				printWord(*w);
			}
			else {
				Retract();
				ch = '>'; Insertchar(Find_s());
			}
			break;
		}
		case ':': Insertchar(Find_s()); break;
		case '%': Insertchar(Find_s()); break;
		case '\'': Insertchar(Find_s()); break;
		case '$': return;
		case '#':Insertchar(Find_s()); return;

		default:cout << "wrong input" << endl;
		}
		strToken = "";
		ifhaspoint = false;
	}
}
void Lexical::run() {
	ifstream f;
	f.open("do_while.txt", ios::in);
	if (!f.is_open()) {
		cout << "error" << endl;
	}

	while (getline(f, input)) {
		input += "$";
		Analyze();
		pint = 0;
	}
	f.close();
}
void Lexical::displayLexicalTable() {
	for (auto i : lexicalTable) {
		cout << i.sym << " " << i.data << endl;
	}
}
