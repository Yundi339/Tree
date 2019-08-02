#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;
/**
 **��������
 **������С��
 **�ж��Ƿ������·
 **��������
 **/
namespace Kruskal {
	int vertex_num;
	int edge_num;
	struct Edge
	{
		int edge_from;  // ����1
		int edge_to;    // ����2
		int value;      // ����
	};

	struct Graph
	{
		Edge *vertex;   // ���㼯��
		int *root;      // �游�ڵ�
		int **matrix;   // �ڽӾ���

	} graph;

	// ����
	bool cmp(const Edge &a, const Edge &b)
	{
		return a.value < b.value;
	}

	void all(int index, const int num, int max_index, bool flag[])
	{
		int temp1, temp2;
		for (int i = 0; i < max_index; i++)
		{
			temp1 = graph.vertex[i].edge_from;
			temp2 = graph.vertex[i].edge_to;
			if (flag[temp1] == true && flag[temp2] == true)
				continue;
			if (temp1 == index)
			{
				flag[temp1] = 1;
				graph.root[temp1] = graph.root[temp2] = num;
				all(temp2, num, max_index, flag);
			}
			else if (temp2 == index)
			{
				flag[temp2] = 1;
				graph.root[temp2] = graph.root[temp1] = num;
				all(temp1, num, max_index, flag);
			}
		}
	}

	// ��³˹����
	void Kruskal(Edge G[])
	{
		int index = 0;
		for (int i = 0; i < edge_num && index < vertex_num - 1; i++)
		{
			int from = G[i].edge_from;
			int to = G[i].edge_to;
			if (graph.root[from] == -1 || graph.root[to] == -1 || graph.root[from] != graph.root[to])
			{
				bool flag[500] = { 0 };
				graph.vertex[index++] = G[i];
				if (graph.root[from] == -1 && graph.root[to] == -1)
					graph.root[from] = graph.root[to] = from;
				else if (graph.root[from] != -1)
					all(to, graph.root[from], index, flag);
				else if (graph.root[to] != -1)
					all(from, graph.root[to], index, flag);
			}
		}
	}

	int find_array(string s[], string str, int index)
	{
		for (int i = 0; i < index; i++)
			if (s[i] == str)
				return i;
		return -1;
	}

	int run()
	{
		printf("����:\n7 12\nA B 12\nB C 10\nC D 3\nD E 4\nE F 2\nF G 9\nG A 14\nA F 16\nB F 7\nC F 6\nE G 8\nC E 5\n");
		printf("�����붥��ĸ���:\n");
		scanf("%d", &vertex_num);
		int k = 0, temp;
		string *str = new string[vertex_num];
		graph.vertex = new Edge[vertex_num - 1];
		graph.root = new int[vertex_num];
		graph.matrix = new int *[vertex_num];
		for (int i = 0; i < vertex_num; i++)
		{
			graph.matrix[i] = new int[vertex_num];
			for (int j = 0; j < vertex_num; j++)
				graph.matrix[i][j] = -1;
			graph.root[i] = -1;
		}

		Edge *edge;
		printf("������ߵĸ���:\n");
		scanf("%d", &edge_num);
		edge = new Edge[edge_num];

		printf("����\"���A ���B Ȩֵ\"�ĸ�ʽ����\n���н��,ȨֵΪ������\n");
		for (int i = 0; i < edge_num; i++)
		{
			string a, b;
			cin >> a >> b;
			temp = find_array(str, a, k);
			if (temp != -1)
				edge[i].edge_from = temp;
			else
			{
				str[k] = a;
				edge[i].edge_from = k++;
			}

			temp = find_array(str, b, k);
			if (temp != -1)
				edge[i].edge_to = temp;
			else
			{
				str[k] = b;
				edge[i].edge_to = k++;
			}

			cin >> edge[i].value;
			graph.matrix[edge[i].edge_from][edge[i].edge_to] = edge[i].value;
			graph.matrix[edge[i].edge_to][edge[i].edge_from] = edge[i].value;
		}
		sort(edge, edge + edge_num, cmp);

		Kruskal(edge);

		printf("�ڽӾ���:\n");
		for (int i = 0; i < vertex_num; i++)
		{
			for (int j = 0; j < vertex_num; j++)
				printf("%5d", graph.matrix[i][j]);
			cout << endl;
		}

		printf("\n��С������:\n");
		for (int i = 0; i < vertex_num - 1; i++)
		{
			cout << "<" << str[graph.vertex[i].edge_from] << "," << str[graph.vertex[i].edge_to] << ">" << endl;
		}
		delete[] str;
		for (int i = 0; i < vertex_num; i++)
			delete[] graph.matrix[i];
		delete[] graph.matrix;
		delete[] edge;
		return 0;
	}
}
