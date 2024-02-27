#pragma once
#include"Grammar.h"
#include<stack>
#include"Lexical.h"

/*属性文法
  A -> do{B}while{C}；{ if C.flag goto do.add else next }
  C -> E1 ROP E2      { C.flag := E1.val ROP.op E2.val }
  B -> S;B            { }
  B -> S;			  { }
  B -> A			  { }
  S -> i=E			  { i.val := E.val }
  E -> -E1			  { E.val := E1.val * (-1) }
  E -> F			  { E.val := F.val }
  E -> E1+F			  { E.val := E1.val + F.val }
  E -> E1-F			  { E.val := E1.val - F.val }
  F -> G			  { F.val := G.val }
  F -> F1*G		      { F.val := F1.val * G.val }
  F -> F1/G           { F.val := F1.val / G.val }
  G -> i              { G.val := i.val }
  G -> n              { G.val := n.val }
  G -> (E)            { G.val := E.val }
  ROP -> >            { ROP.op := > }
  ROP -> <            { ROP.op := < }
  ROP -> ==           { ROP.op := == }
  ROP -> >=           { ROP.op := >= }
  ROP -> <=           { ROP.op := <= }
*/

struct action {
	string act="-1";
	int gonum=0;
};

struct symbol {
	string name;//符号名
	string value;//符号值
	int pos;//符号表中的位置
};

struct item {//四元式
	string op;
	int A1index=-1;
	int A2index=-1;
	int resultindex=-1;
};

class Analysis {
public:
	Grammar G;
	Lexical L;
	void initialize();
	void analyze();
	void initialize_actionTable();
	void display_table();
	void display_siyuanshiTable();
private:	
	vector<symbol> symTable;//符号表
	vector<item> siyuanshiTable;

public:	void GEN(string op, int a1,int a2,int result);
	  symbol newType();
	
	void A_do_B_while_C();
	void  C_E1_ROP_E2();
	void B_S_B();
	void B_S();
	void B_A();
	void S_i_E();
	void E_neg_E1();
	void E_F();
	void E_E1_add_F();
	void E_E1_minus_F();
	void F_G();
	void F_F1_mul_G();
	void F_F1_div_G();
	void G_i();
	void G_n();
	void G_E();
	void ROP_larger ();
	void ROP_lower();
	void ROP_logical_equal ();
	void ROP_larger_equal();
	void ROP_lower_equal();
private:
	action actionTable[119][20];
	int gotoTable[119][9];
	int symbolnum;
    ;
	map<string, int> semantic_to_symbol;
	stack<int>statusStack;
	stack<symbol>symStack;
	stack<string>semanticStack;
};