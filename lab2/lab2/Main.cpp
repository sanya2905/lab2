#pragma once
#include <iostream>
#include "tables_test.h"
int main() {
	tables_test t;
	t.add();
	t.add();
	t.add();
	t.print();
	t.del();
	t.print();
	t.search();
	return 0;
}