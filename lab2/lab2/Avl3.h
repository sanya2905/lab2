#pragma once
#include <iostream>
#include "Tbase.h"
template<typename T, typename K>
struct node {
	Element<T, K> element;
	unsigned char height;
	node* left;
	node* right;
	node() {
		height = 0;
		left = right = 0;
	}
	node(T val, K k) {
		element.key = k;
		element.elem = val;
		left = right = 0;
		height = 1;
	}
};
template<typename T, typename K>
class Avl3 : public Tbase<T, K> {
public:
	size_t size;

	node<T, K>* root;
public:
	Avl3();
	node<T, K>* rotateright(node<T, K>* p);
	node<T, K>* rotateleft(node<T, K>* p);
	node<T, K>* removemin(node<T, K>* p);
	node<T, K>* balance(node<T, K>* p);
	node<T, K>* add_node(node<T, K>* p, T elem, K k);
	node<T, K>* findmin(node<T, K>* p);
	node<T, K>* remove(node<T, K>* p, K k);
	size_t bfactor(node<T, K>* p);
	unsigned char height_of(node<T, K>* p);
	void fixheight(node<T, K>*p);
	void add(T element, K k)override;
	void del(K k)override;
	void print()override;

	bool check(K k)override;

	T* search(K k)override;

	~Avl3();
};
template<typename T, typename K>
Avl3<T, K>::Avl3() {
	size = 0;
	root = new node<T, K>;
}
template<typename T, typename K>
void
Avl3<T, K>::print() {
	node<T, K>* tmp = root;
	while (tmp->left != nullptr) {
		tmp = tmp->left;
		std::cout << tmp->element.key<<'\t'<<tmp->element.elem << std::endl;
	}
	std::cout << root->element.key << '\t'<<root->element.elem << std::endl;
	node<T, K>* tm = root;
	while (tm->right != nullptr) {
		tm = tm->right;
		std::cout << tm->element.key << '\t'<<tm->element.elem << std::endl;
	}
}
template<typename T, typename K>
unsigned char
Avl3<T, K>::height_of(node<T, K>*p) {
	return p ? p->height : 0;
}
template<typename T, typename K>
size_t
Avl3<T, K>::bfactor(node<T ,K>* p) {
	return height_of(p->right) - height_of(p->left);
}
template<typename T, typename K>
void
Avl3<T, K>::fixheight(node<T, K>* p) {
	unsigned char hl = height_of(p->left);
	unsigned char hr = height_of(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}
template<typename T, typename K>
void
Avl3<T, K>::add(T elem, K k) {
	if (!check(k)) {
		add_node(root, elem, k);
	}
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::findmin(node<T, K>* p) {
	return p->left ? findmin(p->left) : p;
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::removemin(node<T, K>* p){
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
template<typename T, typename K>
T*
Avl3<T, K>::search(K k) {
	if (size == 0) {
		return nullptr;
	}
	node<T, K>* tmp = root;
	while (true) {
		if (k > tmp->element.key && tmp->right != nullptr) {
			tmp = tmp->right;
		}
		else if (k < tmp->element.key && tmp->left != nullptr) {
			tmp = tmp->left;
		}
		else if (k == tmp->element.key) {
			return &tmp->element.elem;
		}
		else {
			return nullptr;
		}

	}
}
template<typename T, typename K>
bool
Avl3<T, K>::check(K k) {
	if (size == 0) {
		return false;
	}
	node<T, K>* tmp = root;
	while (true) {
		if (k > tmp->element.key && tmp->right != nullptr) {
			tmp = tmp->right;
		}
		else if (k < tmp->element.key && tmp->left != nullptr) {
			tmp = tmp->left;
		}
		else if (k == tmp->element.key) {
			return true;
		}
		else {
			return false;
		}

	}
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::rotateright(node<T, K>* p) {
	node<T, K>* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::rotateleft(node<T, K>* q) {
	node<T, K>* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::balance(node<T, K>* p) 
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}
template<typename T, typename K>
node<T ,K>*
Avl3<T, K>::add_node(node<T, K>* p, T elem, K k) {
	if (size == 0) {
		root = new node<T, K>(elem, k);
		size++;
		return root;
	}
	if (!p) {
		size++;
		return new node<T, K>(elem, k);
	}
	if (k < p->element.key)
		p->left = add_node(p->left, elem, k);
	else
		p->right = add_node(p->right, elem, k);
	return balance(p);
}
template<typename T, typename K>
void
Avl3<T, K>::del(K k) {
	if (check(k)) {
		remove(root, k);
		size--;
	}
}
template<typename T, typename K>
node<T, K>*
Avl3<T, K>::remove(node<T, K>* p, K k) {
	if (!p) return 0;
	if (k < p->element.key)
		p->left = remove(p->left, k);
	else if (k > p->element.key)
		p->right = remove(p->right, k);
	else  
	{
		node<T, K>* q = p->left;
		node<T, K>* r = p->right;
		delete p;
		if (!r) return q;
		node<T, K>* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}
template<typename T, typename K>
Avl3<T, K>::~Avl3() {
	node<T, K>* tmp;
	while (root->left != nullptr) {
		tmp = root;
		root = root->left;
		delete tmp;
	}
	node<T, K>* tmp2;
	while (root->right != nullptr) {
		tmp2 = root;
		root = root->right;
		delete tmp2;
	}
}