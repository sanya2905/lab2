#pragma once
#include <iostream>
#include "Tbase.h"
template <typename T, typename K>
class Orded : public Tbase<T, K> {
public:
	int size;
	int max;
	Element<T, K>* array;
public:
	Orded();
	int bs(size_t lb, size_t rb, K k);
	void add(T elem, K key)override;
	void del(K k)override;
	void print() override;
	T* search(K k) override;
	bool check(K k) override;
	~Orded();
};
template<typename T, typename K>
Orded<T, K>::Orded() {
	size = 0;
	array = new Element<T, K>[10];
	max = 20;
}
template<typename T, typename K>
void
Orded<T, K>::add(T el, K k) {
	if (size == 0) {
		size++;
		array[0].key = k;
		array[0].elem = el;
	}
	else {
		bool fl = true;
		if (!check(k)) {
			if (size > max) {
				max *= 1.5;
				Element<T, K>* ta = new Element<T, K>[max];
				std::copy<array, array + max, ta>;
				array = new Element<T, K>[max];
				std::copy<ta, ta + max, array>;
				delete[] ta;
			}
			for (size_t i = 0; i < size; i++) {
				if (k < array[i].key) {
					Element<T, K> tmp;
					for (size_t j = size; j > i; j--) {
						tmp = array[j];
						array[j] = array[j - 1];
						array[j - 1] = tmp;
					}
					array[i].elem = el;
					array[i].key = k;
					size++;
					fl = false;
					break;
				}
			}
		}
		if (fl == true) {
			array[size].key = k;
			array[size].elem = el;
			size++;
		}
	}
}
template<typename T, typename K>
void
Orded<T, K>::del(K k) {
	if (size > 0 && check(k)) {
		size_t check = bs(0, size, k);
		if (array[check].key == k) {
			Element<T, K> tmp;
			for (size_t j = check; j < size - 1; j++) {
				Element<T, K> tp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tp;
			}
			array[size - 1] = tmp;
			size--;

		}
	}
}
template<typename T, typename K>
bool
Orded<T, K>::check(K k) {
	int check = bs(0, size, k);
	if (check == -1) {
		return false;
	}
	return true;
}
template<typename T, typename K>
int
Orded<T, K>::bs(size_t lb, size_t rb, K k) {
	int middle;
	while (true) {
		middle = (lb + rb) / 2;
		if (lb >= rb) {
			return -1;
		}
		if (array[middle].key == k) {
			return middle;
		}
		if (array[middle].key > k) {
			rb = middle;
		}
		if (array[middle].key < k) {
			lb = middle + 1;
		}
	}
	return -1;
}
template<typename T, typename K>
T*
Orded<T, K>::search(K k) {
	int check = bs(0, size, k);
	if (array[check].key == k) {
		return(&array[check].elem);
	}
	return nullptr;
}
template<typename T, typename K>
void
Orded<T, K>::print() {
	for (size_t i = 0; i < size; i++) {
		std::cout << array[i].key << '\t' << array[i].elem << std::endl;
	}
}
template<typename T, typename K>
Orded<T, K>::~Orded() {
	delete[] array;
}