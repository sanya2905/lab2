#pragma once
#include <iostream>
template <typename T, typename K>
struct Element {
	K key;
	T elem;
};
template <typename T, typename K>
class Tbase {
public:
	virtual void add(T elem, K key) = 0;
	virtual void del(K key) = 0;
	virtual T* search(K key) = 0;
	virtual void print() = 0;
	virtual bool check(K k) = 0;
	virtual ~Tbase() = default;
};
