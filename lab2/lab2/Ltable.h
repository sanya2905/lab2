#pragma once
#include <iostream>
#include "Tbase.h"
#include <list>
#include <iterator>
template<typename T, typename K>
class Ltable : public Tbase<T, K>{
public:
	using El = Element<T, K>;
	std::list <El> lst;
public:
	Ltable() {};
	void add(T elem, K k)override;
	void del(K k)override;
	void print()override;
	T* search(K k)override;
	bool check(K k)override;
};
template<typename T, typename K>
void
Ltable<T, K>::add(T val, K k) {
	Element<T, K> tmp;
	tmp.key = k;
	tmp.elem = val;
	if (!check(k)) {
		lst.push_back(tmp);
	}
}
template<typename T, typename K>
void
Ltable<T, K>::print() {
	for (auto itr = lst.begin(); itr != lst.end(); itr++) {
		std::cout << (*itr).key<<'\t'<<(*itr).elem;
	}
}
template<typename T, typename K>
bool
Ltable<T, K>::check(K k) {
	for (auto it : lst) {
		if (it.key == k) {
			return true;
		}
	}
	return false;
}
template< typename T, typename K>
void
Ltable<T, K>::del(K k) {
	if (check(k)) {
		auto it = lst.begin();
		while (it->key != k) {
			it++;
		}
		lst.erase(it);
	}
}
template <typename T, typename K>
T*
Ltable<T, K>::search(K k) {
	if (check(k)) {
		auto it = lst.begin();
		while (it->key != k) {
			it++;
		}
		return &((*it).elem);
	}
	return nullptr;
}