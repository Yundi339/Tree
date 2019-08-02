#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <cmath>
using namespace std;

namespace HuffmanTree
{
	string road[26];
	int key[26] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101 };


	struct Node
	{
		int value = -1;
		int lchild = -1;
		int rchild = -1;
		int parent = -1;
	};

	int Select(Node tree[], int n)
	{
		int min, i = 0;
		for (; i < n; i++)
			if (tree[i].value != -1 && tree[i].parent == -1)
			{
				min = i;
				break;
			}
		for (; i < n; i++)
			if (tree[i].value != -1 && tree[i].parent == -1 && tree[i].value <= tree[min].value)
				min = i;
		return min;
	}

	string search(Node tree[], int i, string s, int num)
	{
		if (tree[i].parent == -1)
			return (tree[i].lchild == num) ? "0" + s : "1" + s;
		if (tree[i].lchild == num)
			return search(tree, tree[i].parent, "0" + s, i);
		else
			return search(tree, tree[i].parent, "1" + s, i);
	}

	void Huffman(Node tree[], int n)
	{
		for (int i = 0; i < n; i++)
			tree[i].value = key[i];
		int m = 2 * n - 1;
		for (int i = n; i < m; i++)
		{
			int lmin, rmin;
			//查找权值最小的两个根节点保存在lmin和rmin中
			lmin = Select(tree, m);
			tree[lmin].parent = i;
			rmin = Select(tree, m);
			tree[rmin].parent = i;
			tree[i].value = tree[lmin].value + tree[rmin].value;
			tree[i].lchild = lmin;
			tree[i].rchild = rmin;
		}
	}

	int run()
	{
		int n = 26;
		int m = n * 2 - 1;
		Node *tree = new Node[m];
		Huffman(tree, n);
		printf("    序号   权值   双亲   左孩   右孩\n");
		for (int i = 0; i < n; i++)
			printf("%c%7d%7d%7d%7d%7d\n", ('a' + i), i, tree[i].value, tree[i].parent, tree[i].lchild, tree[i].rchild);
		for (int i = n; i < m; i++)
			printf(" %7d%7d%7d%7d%7d\n", i, tree[i].value, tree[i].parent, tree[i].lchild, tree[i].rchild);
		printf("   编码\n");
		for (int i = 0; i < n; i++)
		{
			road[i] = search(tree, tree[i].parent, "", i);
			printf("%c  ", ('a' + i));
			cout << road[i] << endl;
		}
		delete[] tree;
		return 0;
	}
}