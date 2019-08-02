#pragma once
using namespace std;
template<typename T>
class Node
{
public:
	T data;
	Node<T> *pNode;
	Node() :pNode(nullptr) {}
	Node(T& data) :data(data), pNode(nullptr) {}
	Node(Node<T> &n) :data(n.data), pNode(nullptr) {}
	void display()
	{
		cout << data << ' ';
	}
};

template<typename T>
class Link
{
public:
	Node<T> *head;
	Link()
	{
		head = new Node<T>();
	}
	~Link()
	{
		while (head != nullptr)
		{
			Node<T> *p = head->pNode;
			delete(head);
			head = p;
		}
	}
	void display()
	{
		Node<T> *p = head->pNode;
		while (p != nullptr)
		{
			p->display();
			p = p->pNode;
		}
		cout << endl;
	}
	void insert(Node<T> &n)
	{
		Node<T> *p = head;
		while (p->pNode != nullptr)
		{
			p = p->pNode;
		}
		Node<T> *node = new Node<T>(n);
		p->pNode = node;
	}
	void insert(T &d)
	{
		Node<T> *p = head;
		while (p->pNode != nullptr)
		{
			p = p->pNode;
		}
		Node<T> *node = new Node<T>(d);
		p->pNode = node;
	}
};