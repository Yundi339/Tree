#include <iostream>
#include <stdio.h>
#include <queue>
#include <windows.h>

using namespace std;
//���ɶ�����
//��ӡ������
//�������
//�������
//�������
//�������
//�����������


struct Node
{
	int data;
	Node *left, *right;
};

class BinaryTree
{
private:
	Node *root;//���ڵ�

	int length = 0;//����

	Node* Create(Node *temp)//������
	{
		char cache;
		cin >> cache;
		if (cache == '#')
			temp = nullptr;
		else
		{
			length++;
			temp = new Node();
			temp->data = (cache - '0');
			temp->left = Create(temp->left);
			temp->right = Create(temp->right);
		}
		return temp;
	}

	void Release(Node *temp)//��սڵ�
	{
		if (temp != nullptr)
		{
			Release(temp->left);
			Release(temp->right);
			delete temp;
			temp = nullptr;
		}
	}

	void print(int n, Node *temp)
	{
		if (temp != nullptr)
		{
			print(n + 5, temp->right);
			for (int i = 0; i < n; i++)printf(" ");
			printf("%d\n", temp->data);
			print(n + 5, temp->left);
		}
	}

	void PreOrder(Node *temp)//�ݹ��ӡǰ�����
	{
		if (temp != nullptr)
		{
			printf("%d ", temp->data);
			PreOrder(temp->left);
			PreOrder(temp->right);
		}
	}

	void InOrder(Node *temp)//�ݹ��ӡ�������
	{
		if (temp != nullptr)
		{
			InOrder(temp->left);
			printf("%d ", temp->data);
			InOrder(temp->right);
		}
	}

	void PostOrder(Node *temp)//�ݹ��ӡ�������
	{
		if (temp != nullptr)
		{
			PostOrder(temp->left);
			PostOrder(temp->right);
			printf("%d ", temp->data);
		}
	}

public:
	BinaryTree()//����
	{
		root = Create(root);
	}

	~BinaryTree()//����
	{
		Release(root);
	}

	void display()//��ӡ������
	{
		print(0, root);
		printf("\n");
	}

	void Pre()//ǰ�����
	{
		PreOrder(root);
		printf("\n\n");
	}

	void In()//�������
	{
		InOrder(root);
		printf("\n\n");
	}

	void Post()//�������
	{
		PostOrder(root);
		printf("\n\n");
	}

	void LeverOrder()
	{
		queue<Node*> QLeverOrder;
		if (root == nullptr) return;
		QLeverOrder.push(root);
		while (!QLeverOrder.empty())
		{
			Node *temp = QLeverOrder.front();
			QLeverOrder.pop();
			printf("%d ", temp->data);
			if (temp->left != nullptr) QLeverOrder.push(temp->left);
			if (temp->right != nullptr) QLeverOrder.push(temp->right);
		}
		printf("\n\n");
	}

	int getLength() { return length; }
};

int BinaryTree2_run()
{
	printf("�����������:\n");
	BinaryTree *binary = new BinaryTree();//123###4#5##
	printf("��ӡ������:\n");
	binary->display();
	printf("ǰ�����:\n");
	binary->Pre();
	printf("�������:\n");
	binary->In();
	printf("�������:\n");
	binary->Post();
	printf("�������:\n");
	binary->LeverOrder();
	printf("�����������:\n");
	printf("%d\n", binary->getLength());

	delete binary;
	return 0;
}
