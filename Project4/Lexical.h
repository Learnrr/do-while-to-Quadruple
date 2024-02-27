#pragma once
#include<iomanip>
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#define ID 67
#define CONST 68
using namespace std;


struct word {
	int sym=-1;
	string data = "";
};

class Lexical {
public:
	int getWordType(word w);
	void printWord(word w);
	//读一个字符
	void GetChar() {
		ch = input[pint];
		pint++;
	}

	//删除空白字符
	void GetBC();
	//判断字母
	bool IsLetter();
	//判断数字
	bool IsDigit();
	//对strToekn中的单词查找关键字表,若找到返回种别码，未找到返回-1
	int Reserse();
	//对ch中的字符查找运算符表，若找到返回种别码，未找到返回-1
	int Find_s();

	//搜索指示器回调一个位置，将ch置为空白字符
	void  Retract();
	//将ch中字符连接到strToken后
	void Concat();
	//插入strToken中的标识符到标识符表
	void InsertId();
	//插入常数
	void InsertConst();
	//插入运算符
	void Insertchar(int i);
	//分析输入串
	void Analyze();
	void run();
	void displayLexicalTable();


	vector<word> lexicalTable;
private:
	//k 数组------关键字表，每个数组元素存放一个关键字
	string k[35] = { "if","while","cout","cin","do","else","main","return","int","enum","char","string","struct","class",
	"float","double","const","case","continue","break","delete","for","false","true","switch","this","new","long","template",
	"static","try","except","public","private","protected" };//种别码为0-34
//种别码为35-65
	string s[32] = { ",",";" ,"(",")","{","}" ,"[", "]","+","-",">","<","=","/","*","|","&","\'",":","%","++","==","+=","-=","/=","*=","--","<<",">>","<=",">=","#"};
	 //              35   36    37 38  39  40   41  42  43  44  45  46  47  48   49  50  51  52  53  54  55    56   57  58   59   60   61   62    63   64    65  66
	//搜索指示器，字符指针
	int pint = 0;

	//保存字符的数组
	string strToken;

	//保存当前读到的字符
	char ch;

	//input
	string input = "";

};


