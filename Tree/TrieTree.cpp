#include <iostream>
#include <cstdio>
#include <stack>
#include <queue>
#include <string>
#include <regex>
using namespace std;
namespace TrieTree {
	const regex pattern("^[a-zA-Z]+$");
	//match_results<string::const_iterator> result;

	struct Node
	{
		Node *next = nullptr;
		Node *down = nullptr;
		Node *up = nullptr;
		char ch;
		bool flag = 0;
	};

	struct Ptr
	{
		Node *p = nullptr;
		Ptr *next = nullptr;
	};
	class Trie
	{
	private:
		Ptr array[26];	//���
		Node *head;			//ͷ���


		//�ж��Ƿ���ڵ���
		Node* Exist(Node *temp, const char ch, const bool flag = true)
		{
			while (temp->next != nullptr && temp->ch != ch) {
				temp = temp->next;
			}
			if (temp->ch == ch) {
				return temp;
			}
			else if (flag) {
				return Create(temp, ch);
			}
			else {
				return nullptr;
			}
		}

		//�жϲ������ַ
		void ptr_Exist(Ptr *q, Node *temp)
		{
			while (q->next != nullptr)
			{
				if (q->p == temp) { break; }
				q = q->next;
			}
			if (q->p != temp) {
				q->next = Create(temp);
			}
		}

		//��ӽ��
		Node *Create(Node *temp, const char ch, const bool flag = true)
		{
			Node *newNode = new Node;
			newNode->ch = ch;
			if (flag) {
				temp->next = newNode;
			}
			else {
				temp->down = newNode;
			}
			return newNode;
		}
		Ptr *Create(Node *temp)
		{
			Ptr *newPtr = new Ptr;
			newPtr->p = temp;
			return newPtr;
		}

		//�����ؼ���
		bool searchKeywords(const string &str, Node *pNode)
		{
			Node *root = pNode;
			Node *temp;
			for (int i = 1; i < str.length(); i++)
			{
				if (root->down == nullptr) { return false; }
				temp = Exist(root->down, str[i], false);
				if (temp == nullptr) { return false; }
				root = temp;
			}
			temp = root;
			stack<char> up;
			queue<char> down;
			while (temp->up != nullptr)
			{
				up.push(temp->ch);
				temp = temp->up;
			}
			bfs(up, root->down, down);
			return true;
		}


		//��ӡ
		void print(stack<char> up, queue<char> down)
		{
			while (!up.empty()) {
				printf("%c", up.top());
				up.pop();
			}
			while (!down.empty()) {
				printf("%c", down.front());
				down.pop();
			}
			printf("\n");
		}
		void bfs(stack<char> up, Node *temp, queue<char> down)
		{
			if (temp != nullptr) {
				if (temp->next != nullptr) {
					bfs(up, temp->next, down);
				}
				down.push(temp->ch);
				if (temp->flag == 1 && temp->down != nullptr) {
					print(up, down);
				}
				bfs(up, temp->down, down);
			}
			else {
				print(up, down);
			}
		}

		//�ͷ�
		void Realse(Node *temp)
		{
			if (temp == nullptr) { return; }
			if (temp != nullptr)
			{
				Realse(temp->down);
				temp->down = nullptr;
				Realse(temp->next);
				temp->next = nullptr;
			}
			delete temp;
			temp = nullptr;
		}
		void Realse(Ptr *temp)
		{
			if (temp != nullptr)
			{
				Realse(temp->next);
				temp->next = nullptr;
				temp->p = nullptr;
			}
			delete temp;
			temp = nullptr;
		}

	public:
		//����
		Trie() { head = new Node; }

		//����
		~Trie() { Realse(head); }

		//����ֵ���
		void clean()
		{
			Realse(head->down);
			head->down = nullptr;
			for (int i = 0; i < 26; ++i)
			{
				Realse((array + i)->next);
				array[i].next = nullptr;
			}
		}

		//���ӵ���
		void insert(const string &str)
		{
			Node *root = head;
			Node *temp;
			for (int i = 0; i < str.length(); i++)
			{
				if (root->down == nullptr) {
					temp = Create(root, str[i], false);
				}
				else {
					temp = Exist(root->down, str[i]);
				}
				temp->up = root;
				root = temp;
				ptr_Exist((array + str[i] - 'a'), temp);
			}
			root->flag = 1;
		}

		//���ҵ���
		bool search(const string &str)
		{
			Node *root = head;
			Node *temp = nullptr;
			for (int i = 0; i < str.length(); i++)
			{
				if (root->down == nullptr) {
					return false;
				}
				else {
					temp = Exist(root->down, str[i], false);
				}
				root = temp;
			}
			if (temp == nullptr) {
				return false;
			}
			if (root->flag == 1) {
				return true;
			}
			else {
				return false;
			}
		}

		//�ؼ��ʲ���
		bool search_keywords(const string &str)
		{
			bool flag = false;
			Ptr *q = (array + str[0] - 'a')->next;
			while (q != nullptr)
			{
				if (searchKeywords(str, q->p))
					flag = 1;
				q = q->next;
			}
			return flag;
		}

	};


	int run()
	{
		Trie *trie = new Trie();
		printf("1.����ֵ���\n2.���ӵ���\n3.���ҵ���\n4.�ؼ��ʲ���...\n");
		int cmd;
		while (cin >> cmd, cmd)
		{
			if (cmd == 1) {
				trie->clean();
			}
			else if (cmd == 2)
			{
				string str;
				printf("�˳����뵥��ģʽ������0�س�...\n");
				while (cin >> str, str.compare("0") != 0)
				{
					//if (regex_match(str, result, pattern))
					if (regex_match(str, pattern))
					{
						transform(str.begin(), str.end(), str.begin(), ::tolower);
						trie->insert(str);
					}
					else { break; }
				}
			}
			else if (cmd == 3)
			{
				string str;
				printf("����������ҵĵ���...\n");
				cin >> str;
				if (!regex_match(str, pattern)) {
					printf("����Ĳ���Ӣ��...\n");
				}
				else
				{
					transform(str.begin(), str.end(), str.begin(), ::tolower);
					if (!trie->search(str)) {
						printf("�ܱ�Ǹ��û���ҵ��������...\n");
					}
					else {
						printf("�ҵ�����\n");
					}
				}
			}
			else if (cmd == 4)
			{
				string str;
				printf("����������ҵĹؼ���...\n");
				cin >> str;
				if (!regex_match(str, pattern)) {
					printf("����Ĳ���Ӣ��...\n");
				}
				else
				{
					transform(str.begin(), str.end(), str.begin(), ::tolower);
					if (!trie->search_keywords(str)) {
						printf("�ܱ�Ǹ��û���ҵ��κκ��д˹ؼ��ֵĵ���...\n");
					}
				}
			}
			else {
				printf("��Чָ��...\n");
			}
			printf("1.����ֵ���\n2.���ӵ���\n3.���ҵ���\n4.�ؼ��ʲ���...\n");
		}
		delete trie;
		return 0;
	}
}
