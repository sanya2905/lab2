#pragma once
#include <iostream>
#include "Tbase.h"
template <typename T, typename K>
class Fhtable :public Tbase<T, K> {
public:
	int size;
	int max;
	Element<T, K>* array;
public:
	Fhtable();
	void add(T element, K k) override;
	void del(K k) override;
	void print()override;
	bool check(K k) override;
	T* search(K k) override;
	int hash(K k);
	~Fhtable();

};

template <typename T, typename K>
Fhtable<T, K>::Fhtable() {
	size = 0;
	array = new Element<T, K>[500];
	max = 500;
	for (size_t i = 0; i < max - 1; i++) {
		array[i].key = 0;
	}
}
template<typename T, typename K>
void
Fhtable<T, K>::print() {
	for (size_t i = 0; i < max; i++) {
		std::cout << array[i].key << "  "<< array[i].key<<std::endl;
	}
}
template<typename T, typename K>
int
Fhtable<T, K>::hash(K k) {
	return (max % k);
}
template <typename T, typename K>
void
Fhtable<T, K>::add(T element, K k) {
	if (!check(k)) {
		int key = hash(k);
		size_t count = 0;
		while (true) {
			if (key + count > max) {
				key = 0;
				count = 0;
			}
			if (array[key + count].key == 0) {
				array[key + count].key = k;
				array[key + count].elem = element;
				size++;
				break;
			}
			count++;
	}
	}
	if (size > max*0.8) {
		max *= 1.5;
		Element<T, K>* ta = new Element<T, K>[max];
		std::copy<array, array + max, ta>;
		array = new Element<T, K>[max];
		std::copy<ta, ta + max, array>;
		delete[] ta;
	}
}

template <typename T, typename K>
bool
Fhtable<T, K>::check(K k) {
	int key = hash(k);
	size_t count = 0;
	while (true) {
		if (key + count > max - 1) {
			key = 0;
			count = 0;
		}
		if (array[key + count].key == k) {
			return true;
		}
		if (array[key + count].key == 0 ) {
			break;
		}
		count++;
	}
	return false;
}
template <typename T, typename K>
T*
Fhtable<T, K>::search(K k) {
	int key = hash(k);
	size_t count = 0;
	while (true) {
		if (key + count > max) {
			key = 0;
			count = 0;
		}
		if (array[key + count].key == k) {
			return &array[key].elem;
		}
		if (array[key + count].key == 0) {
			return nullptr;
		}
		count++;
	}
	return nullptr;
}
template<typename T, typename K>
void
Fhtable<T, K>::del(K k) {
	if (size == 0 || !check(k)) {
		return;
	}
	int key = hash(k);
	size_t count = 0;
	while (true) {
		if (key + count > max- 1) {
			key = 0;
			count = 0;
		}
		if (array[key + count].key == k) {
			array[key + count].key = 0;
			return;
		}
		if (array[key + count].key == 0) {
			return;
		}
		count++;
	}
}
template<typename T, typename K>
Fhtable<T, K>::~Fhtable() {
	delete[] array;
}