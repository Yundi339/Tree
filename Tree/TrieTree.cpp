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
		Ptr array[26];	//快查
		Node *head;			//头结点


		//判断是否存在单词
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

		//判断并储存地址
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

		//添加结点
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

		//搜索关键字
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


		//打印
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

		//释放
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
		//构造
		Trie() { head = new Node; }

		//析构
		~Trie() { Realse(head); }

		//清空字典树
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

		//增加单词
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

		//查找单词
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

		//关键词查找
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
		printf("1.清空字典树\n2.增加单词\n3.查找单词\n4.关键词查找...\n");
		int cmd;
		while (cin >> cmd, cmd)
		{
			if (cmd == 1) {
				trie->clean();
			}
			else if (cmd == 2)
			{
				string str;
				printf("退出插入单词模式请输入0回车...\n");
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
				printf("输入你想查找的单词...\n");
				cin >> str;
				if (!regex_match(str, pattern)) {
					printf("输入的不是英文...\n");
				}
				else
				{
					transform(str.begin(), str.end(), str.begin(), ::tolower);
					if (!trie->search(str)) {
						printf("很抱歉！没有找到这个单词...\n");
					}
					else {
						printf("找到啦！\n");
					}
				}
			}
			else if (cmd == 4)
			{
				string str;
				printf("输入你想查找的关键字...\n");
				cin >> str;
				if (!regex_match(str, pattern)) {
					printf("输入的不是英文...\n");
				}
				else
				{
					transform(str.begin(), str.end(), str.begin(), ::tolower);
					if (!trie->search_keywords(str)) {
						printf("很抱歉！没有找到任何含有此关键字的单词...\n");
					}
				}
			}
			else {
				printf("无效指令...\n");
			}
			printf("1.清空字典树\n2.增加单词\n3.查找单词\n4.关键词查找...\n");
		}
		delete trie;
		return 0;
	}
}
