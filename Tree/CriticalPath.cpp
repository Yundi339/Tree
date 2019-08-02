#include <iostream>
#include <cstdio>
#include <stack>
#include <string>
#include <windows.h>
using namespace std;
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
	int *maxValue;   // �·��ֵ
	int *root;      // �游�ڵ�
	int **matrix;   // �ڽӾ���

} graph;

int find_array(string s[], string str, int index)
{
	for (int i = 0; i < index; i++)
		if (s[i] == str)
			return i;
	return -1;
}

void criticalpath(Edge G[])
{
	int index = 0;
	for (int i = 0; i < edge_num; i++)
	{
		int from = G[i].edge_from;
		int to = G[i].edge_to;
		index = graph.maxValue[from];
		if (index + G[i].value > graph.maxValue[to])
		{
			graph.root[to] = from;
			graph.maxValue[to] = index + G[i].value;
		}
	}
}
int CriticalPath_run()
{
	printf("����:\n10 14\nA B 5\nA C 6\nB D 3\nC D 6\nC E 3\nD E 3\nD F 4\nD G 4\nE F 1\nE H 4\nF I 5\nG J 4\nH I 2\nI J 2\n");
	printf("�����붥��ĸ���:\n");
	scanf("%d", &vertex_num);
	int k = 0, temp;
	string *str = new string[vertex_num];
	graph.maxValue = new int[vertex_num];
	graph.root = new int[vertex_num];
	graph.matrix = new int *[vertex_num];
	for (int i = 0; i < vertex_num; i++)
	{
		graph.matrix[i] = new int[vertex_num];
		for (int j = 0; j < vertex_num; j++)
			graph.matrix[i][j] = -1;
		graph.root[i] = -1;
		graph.maxValue[i] = 0;
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
	}
	printf("�ڽӾ���:\n");
	for (int i = 0; i < vertex_num; i++)
	{
		for (int j = 0; j < vertex_num; j++)
			printf("%5d", graph.matrix[i][j]);
		cout << endl;
	}
	criticalpath(edge);
	printf("\n�ؼ�·��:\n");
	for (int i = 0; i < vertex_num; i++)
	{
		stack<string> path;
		path.push(str[i]);
		int index = graph.root[i];
		cout << str[0] << "��" << str[i] << "�����翪ʼʱ��: " << graph.maxValue[i] << endl;
		while (index != -1)
		{
			path.push(str[index]);
			index = graph.root[index];
		}
		cout << "·��:";
		while (!path.empty())
		{
			cout << path.top();
			path.pop();
		}
		cout << endl;
	}
	delete[] str;
	for (int i = 0; i < vertex_num; i++)
		delete[] graph.matrix[i];
	delete[] graph.matrix;
	delete[] edge;
	return 0;
}
