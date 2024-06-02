#pragma once
#include <iostream>
#include "Avl3.h"
#include "Ftable.h"
#include "Ltable.h"
#include "Orded.h"
#include "Fhtable.h"
#include "Shtable.h";
#include "Tbase.h"
#include "monom.h"
#include "list.h"
//Выдает непонятную ошибку при попытке подключить мой класс list, пришлось писать тесты для типов string, int
template<typename T, typename K>
class MCtables {
private:
	Tbase<T, K>* array[6];
	size_t active;
	T value;
public:
	MCtables();
	void add(T elem, K k);
	void del(K k);
	void active_table();
	void print();
	T search(K k);
};
template<typename T, typename K>
MCtables<T, K>::MCtables() {
	Ftable<T, K>* f = new Ftable<T, K>();
	Orded<T, K>* o = new Orded<T, K>();
	Ltable<T, K>* lst = new Ltable<T, K>();
	Fhtable<T, K>* fh = new Fhtable<T, K>();
	Shtable<T, K>* sht = new Shtable<T, K>();
	Avl3<T, K>* avl3 = new Avl3<T, K>();
	active = 0;
	array[0] = f;
	array[1] = o;
	array[2] = lst;
	array[3] = fh;
	array[4] = sht;
	array[5] = avl3;
}
template<typename T, typename K>
void
MCtables<T, K>::add(T elem, K k) {
	for (size_t i = 0; i < 6; i++) {
		(*array[i]).add(elem, k);
	}
}
template<typename T, typename K>
void
MCtables<T, K>::del(K k) {
	for (size_t i = 0; i < 6; i++) {
		(*array[i]).del(k);
	}
}
template<typename T, typename K>
void
MCtables<T, K>::active_table() {
	std::cout << "1.Ftable" << std::endl << "2.Orded" << std::endl << "3.Ltable" << std::endl << "4.Fhtable" << std::endl << "5.Shtable" << std::endl << "6.Avl3" << std::endl << "Take table: ";
	std::cin >> active;
	active--;
}
template<typename T, typename K>
void
MCtables<T, K>::print() {
	(*array[active]).print();
}
template<typename T, typename K>
T
MCtables<T, K>::search(K k) {
	active_table();
	value = *((*array[active]).search(k));
	return value;
}
