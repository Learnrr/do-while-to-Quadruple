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
	//��һ���ַ�
	void GetChar() {
		ch = input[pint];
		pint++;
	}

	//ɾ���հ��ַ�
	void GetBC();
	//�ж���ĸ
	bool IsLetter();
	//�ж�����
	bool IsDigit();
	//��strToekn�еĵ��ʲ��ҹؼ��ֱ�,���ҵ������ֱ��룬δ�ҵ�����-1
	int Reserse();
	//��ch�е��ַ���������������ҵ������ֱ��룬δ�ҵ�����-1
	int Find_s();

	//����ָʾ���ص�һ��λ�ã���ch��Ϊ�հ��ַ�
	void  Retract();
	//��ch���ַ����ӵ�strToken��
	void Concat();
	//����strToken�еı�ʶ������ʶ����
	void InsertId();
	//���볣��
	void InsertConst();
	//���������
	void Insertchar(int i);
	//�������봮
	void Analyze();
	void run();
	void displayLexicalTable();


	vector<word> lexicalTable;
private:
	//k ����------�ؼ��ֱ�ÿ������Ԫ�ش��һ���ؼ���
	string k[35] = { "if","while","cout","cin","do","else","main","return","int","enum","char","string","struct","class",
	"float","double","const","case","continue","break","delete","for","false","true","switch","this","new","long","template",
	"static","try","except","public","private","protected" };//�ֱ���Ϊ0-34
//�ֱ���Ϊ35-65
	string s[32] = { ",",";" ,"(",")","{","}" ,"[", "]","+","-",">","<","=","/","*","|","&","\'",":","%","++","==","+=","-=","/=","*=","--","<<",">>","<=",">=","#"};
	 //              35   36    37 38  39  40   41  42  43  44  45  46  47  48   49  50  51  52  53  54  55    56   57  58   59   60   61   62    63   64    65  66
	//����ָʾ�����ַ�ָ��
	int pint = 0;

	//�����ַ�������
	string strToken;

	//���浱ǰ�������ַ�
	char ch;

	//input
	string input = "";

};


