#pragma once
#include "Link.h"
using namespace std;
template <typename T>
class Queue :public Link<T> {
public:
	Queue() :Link() {}
	void inQueue(T a)
	{
		insert(Node<T>(a));
	}
	T front()
	{
		return head->pNode->data;
	}
	T delQueue()
	{
		T n = head->pNode->data;
		Node<T> *node = head->pNode;
		head->pNode = node->pNode;
		delete node;
		return n;
	}
};
