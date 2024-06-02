#pragma once
#include <iostream>
#include "Tbase.h"
#include <list>
#include <iterator>
template <typename T, typename K>
class Shtable: public Tbase<T, K> {
public:
	int size;
	int max;
	std::list<Element<T, K>>* array;
public:
	Shtable();
	void add(T element, K k) override;
	void del(K k)override;
	void print()override;
	T* search(K k)override;
	bool check(K k)override;
	size_t hash(K k);
	~Shtable();
};
template <typename T, typename K>
Shtable<T, K>::Shtable() {
	size = 0;
	max = 500;
	array = new std::list<Element<T, K>>[max];
}
template <typename T, typename K>
size_t
Shtable<T, K>::hash(K k) {
	return (max % k);
}
template<typename T, typename K>
void
Shtable<T, K>::print() {
	for (size_t i = 0; i < max; i++) {
		for (auto itr = array[i].begin(); itr != array[i].end(); itr++) {
			std::cout << (*itr).elem<<'\t'<<(*itr).key<<std::endl;
		}
	}
}
template <typename T, typename K>
void
Shtable<T, K>::del(K k) {
	size_t hasher = hash(k);
	if (array[hasher].size() != 0 && check(k)) {
		for (auto itr = array[hasher].begin(); itr != array[hasher].end(); itr++) {
			if ((*itr).key == k) {
				array[hasher].erase(itr);
			}
		}
	}

}
template <typename T, typename K>
T*
Shtable<T, K>::search(K k) {
	size_t hasher = hash(k);
	if (array[hasher].size() != 0) {
		for (auto itr = array[hasher].begin(); itr != array[hasher].end(); itr++) {
			if ((*itr).key == k) {
				return &((*itr).elem);
			}
		}
	}
	return nullptr;
}
template <typename T, typename K>
void
Shtable<T, K>::add(T element, K k) {
	size_t hasher = hash(k);
	Element<T, K> tmp;
	tmp.key = k;
	tmp.elem = element;
	if (!check(k)) {
		array[hasher].push_back(tmp);
		size++;
	}
	if (max < size * 0.75) {
		max *= 1.5;
		std::list<Element<T, K>>* ta = new std::list<Element<T, K>>[max];
		std::copy<array, array + max, ta>;
		array = new std::list<Element<T, K>>[max];
		std::copy<ta, ta + max, array>;
		delete[] ta;
	}
}
template <typename T, typename K>
bool
Shtable<T, K>::check(K k) {
	size_t hasher = hash(k);
	if (array[hasher].size() != 0) {
	}
	return false;
}
template <typename T, typename K>
Shtable<T, K>::~Shtable() {
	delete[] array;
}