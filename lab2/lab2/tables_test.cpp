#include <iostream>
#include "tables_test.h"
tables_test::tables_test() {
	key = 0;
	elem = "";
}
void
tables_test::add() {
	std::cout << "Eneter the element: ";
	std::cin >> elem;
	std::cout << std::endl << "Enter the key: ";
	std::cin >> key;
	std::cout << std::endl;
	mc.add(elem, key);
	std::cin.clear();
}
void
tables_test::del() {
	std::cout << std::endl << "Enter the key: ";
	std::cin >> key;
	mc.del(key);
	std::cout << std::endl;
	std::cin.clear();
}
void
tables_test::print() {
	mc.active_table();
	mc.print();
}
void
tables_test::search() {
	std::cout << std::endl << "Enter the key: ";
	std::cin >> key;
	std::cout << mc.search(key)<< std::endl;
	std::cin.clear();
}