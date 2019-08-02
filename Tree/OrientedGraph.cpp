#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include <string>
#include <limits.h>
#include <queue>
using namespace std;
namespace OrientedGraph {
	int num = 0;
	int minValue;
	queue<string>road;//����
	bool *fff;
	bool flag;
	struct Node
	{
		string s1;
		string s2;
		int value;

	};

	void search(Node graph[], string s1, string s2, int value, queue<string> temp)//DFS
	{
		for (int i = 0; i < num; i++)
		{
			if (!fff[i])
			{
				if ((graph[i].s1 == s1 && graph[i].s2 == s2))
				{
					queue<string>cache = temp;
					cache.push(s1);
					flag = 1;
					if (value + graph[i].value < minValue)
					{
						minValue = value + graph[i].value;
						road = cache;
					}
				}
				else if (graph[i].s1 == s1 && value + graph[i].value < minValue)
				{
					fff[i] = 1;
					queue<string>cache = temp;
					cache.push(s1);
					search(graph, graph[i].s2, s2, value + graph[i].value, cache);
					fff[i] = 0;
				}
			}
		}
	}
	int run()
	{
		int value;
		string first, second;
		printf("������ߵĸ���:\n");
		cin >> num;
		Node *graph = new Node[num];
		fff = new bool[num];
		printf("����\"���A ���B Ȩֵ\"�ĸ�ʽ����,�߶��ǵ����\n���н��Ϊ�ַ���,ȨֵΪ������\n");
		for (int i = 0; i < num; i++)
		{
			cin >> first >> second >> value;
			graph[i].s1 = first;
			graph[i].s2 = second;
			graph[i].value = value;
		}
		while (true)
		{
			printf("1:���� 2.�˳�\n");
			int kind;
			cin >> kind;
			if (kind == 1)
			{
				minValue = INT_MAX;
				flag = false;
				for (int i = 0; i < num; i++)
					fff[i] = false;
				printf("����\"A B\"�ĸ�ʽ������A�ͽ��B�Ľ����\n");
				cin >> first >> second;
				queue<string> temp;
				search(graph, first, second, 0, temp);
				cout << first << "��" << second << "֮��";
				if (flag)
				{
					cout << "���ٴ���Ϊ" << minValue << endl;
					while (!road.empty())
					{
						cout << road.front() << "->";
						road.pop();
					}
					cout << second << endl;
				}
				else
					cout << "û��·��" << endl;
			}
			else if (kind == 2)
				break;
		}

		delete[] graph;
		delete[] fff;
		system("pause");
		return 0;
	}
}