#pragma once
#include <iostream>
#include "MCtables.h"
class tables_test {
public:
	MCtables<std::string, int> mc;
	int key;
	std::string elem;
	tables_test();
	void add();
	void print();
	void del();
	void search();
};