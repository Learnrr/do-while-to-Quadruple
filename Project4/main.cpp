#include"Analyze.h"

using namespace std;

int main() {

	Analysis a;
	a.initialize();
	a.initialize_actionTable();
	a.display_table();
	a.analyze();
	a.display_siyuanshiTable();
}