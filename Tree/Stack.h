#pragma once
#include "Link.h"
using namespace std;
template <typename T>
class Stack :public Link<T> {
public:
	Stack() :Link() {}
	void push(T a)
	{
		Node<T> *p = head;
		Node<T> *node = new Node<T>(a);
		node->pNode = p->pNode;
		p->pNode = node;
	}
	T top()
	{
		return head->pNode->data;
	}
	T pop()
	{
		T n = head->pNode->data;
		Node<T> *node = head->pNode;
		head->pNode = node->pNode;
		delete node;
		return n;
	}
};
