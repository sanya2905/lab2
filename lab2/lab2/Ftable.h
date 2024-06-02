#pragma once
#include <iostream>
#include "Tbase.h"
template <typename T, typename K>
class Ftable : public Tbase<T, K> {
public:
	int size;
	int max;
	Element<T, K>* array;
public:
	Ftable();
	void add(T elem, K key) override;
	void del(K k) override;
	T* search(K key) override;
	void print() override;
	bool check(K k) override;
	~Ftable();
};
template <typename T, typename K>
Ftable<T, K>::Ftable() {
	size = 0;
	array = new Element<T, K>[20];
	max = 20;
}
template<typename T, typename K>
bool
Ftable<T, K>::check(K k) {
	for (size_t i = 0; i < size; i++) {
		if (array[i].key == k) {
			return true;
		}
	}
	return false;
}
template <typename T, typename K>
void
Ftable<T, K>::add(T el, K k) {
	if (size == 0) {
		size++;
		array[0].key = k;
		array[0].elem = el;
	}
	else {
		if (!check(k)) {
			if (size >= max) {
				max *= 1.5;
				Element<T, K>* ta = new Element<T, K>[max];
				std::copy<array, array + max, ta>;
				array = new Element<T, K>[max];
				std::copy<ta, ta + max, array>;
				delete[] ta;
			}
			array[size].elem = el;
			array[size].key = k;
			size++;
		}
	}

}
template<typename T, typename K>
void
Ftable<T, K>::del(K k) {
	if (size == 0 || !check(k)) {
		return;
	}
	for (size_t i = 0; i < size; i++) {
		if (array[i].key == k) {
			Element<T, K> tmp = array[i];
			array[i] = array[size - 1];
			array[size - 1] = tmp;
			array[size - 1].key = 0;
			size--;
		}
	}
}
template<typename T, typename K>
T*
Ftable<T, K>::search(K ke) {
	if (size == 0) {
		return nullptr;
	}
	for (size_t i = 0; i < size; i++) {
		if (array[i].key == ke) {
			return ( & array[i].elem);
		}
	}
	return nullptr;
}
template<typename T, typename K>
void
Ftable<T, K>::print() {
	for (size_t i = 0; i < size; i++) {
		std::cout<<array[i].key<<'\t'<<array[i].elem<<std::endl;
	}
}
template<typename T, typename K>
Ftable<T, K>::~Ftable() {
	delete[] array;
}