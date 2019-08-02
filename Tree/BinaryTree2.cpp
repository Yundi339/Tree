#include <iostream>
#include <stdio.h>
#include <queue>
#include <windows.h>

using namespace std;
//生成二叉树
//打印二叉树
//先序遍历
//中序遍历
//后序遍历
//层序遍历
//二叉树结点数


struct Node
{
	int data;
	Node *left, *right;
};

class BinaryTree
{
private:
	Node *root;//根节点

	int length = 0;//长度

	Node* Create(Node *temp)//创造结点
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

	void Release(Node *temp)//清空节点
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

	void PreOrder(Node *temp)//递归打印前序遍历
	{
		if (temp != nullptr)
		{
			printf("%d ", temp->data);
			PreOrder(temp->left);
			PreOrder(temp->right);
		}
	}

	void InOrder(Node *temp)//递归打印中序遍历
	{
		if (temp != nullptr)
		{
			InOrder(temp->left);
			printf("%d ", temp->data);
			InOrder(temp->right);
		}
	}

	void PostOrder(Node *temp)//递归打印后序遍历
	{
		if (temp != nullptr)
		{
			PostOrder(temp->left);
			PostOrder(temp->right);
			printf("%d ", temp->data);
		}
	}

public:
	BinaryTree()//构造
	{
		root = Create(root);
	}

	~BinaryTree()//析构
	{
		Release(root);
	}

	void display()//打印二叉树
	{
		print(0, root);
		printf("\n");
	}

	void Pre()//前序遍历
	{
		PreOrder(root);
		printf("\n\n");
	}

	void In()//中序遍历
	{
		InOrder(root);
		printf("\n\n");
	}

	void Post()//后序遍历
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
	printf("请输入二叉树:\n");
	BinaryTree *binary = new BinaryTree();//123###4#5##
	printf("打印二叉树:\n");
	binary->display();
	printf("前序遍历:\n");
	binary->Pre();
	printf("中序遍历:\n");
	binary->In();
	printf("后序遍历:\n");
	binary->Post();
	printf("层序遍历:\n");
	binary->LeverOrder();
	printf("二叉树结点数:\n");
	printf("%d\n", binary->getLength());

	delete binary;
	return 0;
}
