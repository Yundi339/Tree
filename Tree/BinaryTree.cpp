#include<iostream>
#include<math.h>
using namespace std;

const int QueueSize = 1000;
template<class DataType>
class CirQueue
{
private:
	DataType data[QueueSize];
	int front, rear;
public:
	CirQueue()
	{
		front = QueueSize - 1;
		rear = QueueSize - 1;
	}
	~CirQueue()
	{
	}

	void EnQueue(DataType x)
	{
		if ((rear + 1) % QueueSize == front)
			throw "上溢";
		rear = (rear + 1) % QueueSize;
		data[rear] = x;
	}

	DataType DeQueue()
	{
		if (rear == front)
			throw "下溢";
		front = (front + 1) % QueueSize;
		DataType x = data[front];
		return x;
	}

	bool Empty()
	{
		if (rear == front)
			return true;
		else
			return false;
	}
};

template<class DataType>
struct BiNode
{
	DataType data;
	BiNode<DataType> *lchild, *rchild;
};

template<class DataType>
class BiTree
{
private:
	BiNode<DataType> *root;//指向根节点的指针
	BiNode<DataType> *Great(BiNode<DataType>*bt);
	void Release(BiNode<DataType> *bt);
	void PreOrder(BiNode<DataType> *bt);
	void InOrder(BiNode<DataType> *bt);
	void PostOrder(BiNode<DataType> *bt);
	int Depth(BiNode<DataType> *bt);
	void Swop(BiNode<DataType> *bt);
	int Path(BiNode<DataType> *bt, DataType x, DataType p[]);
	void DeleteTree(BiNode<DataType> *bt, DataType x);
	DataType Parents(BiNode<DataType> *bt, DataType x);
	void PostOpposite(BiNode<DataType> *bt);
	void Print(BiNode<DataType> *bt, int n);
public:
	BiTree() { root = Great(root); }
	~BiTree() { Release(root); }
	void PreOrder() { PreOrder(root); }
	void InOrder() { InOrder(root); }
	void PostOrder() { PostOrder(root); }
	int Depth() { return Depth(root); }
	void Swop() { Swop(root); }
	void DeleteTree(DataType x) { DeleteTree(root, x); }
	void PostOpposite() { PostOpposite(root); }
	DataType Parents(DataType x) { if (root->data == x)return '#'; else return Parents(root, x); }
	void LeverOrder();
	int NodeNumber();
	int LeafNumber();
	void LeafNode();
	void Image();
	void Print() { Print(root, 0); }
	void Path(DataType x)
	{
		DataType *p = new DataType[Depth()];
		int k = Path(root, x, p) - 1;
		for (; k >= 0; k--)
			cout << p[k] << '\t';
	}
};

template<class DataType>//构造
BiNode<DataType>* BiTree<DataType>::Great(BiNode<DataType>*bt)
{
	DataType x;
	cin >> x;
	if (x == '#') bt = NULL;
	else
	{
		bt = new BiNode<DataType>;
		bt->data = x;
		bt->lchild = Great(bt->lchild);
		bt->rchild = Great(bt->rchild);
	}
	return bt;
}

template<class DataType>//前序
void BiTree<DataType>::PreOrder(BiNode<DataType>*bt)
{
	if (bt == NULL) return;
	cout << bt->data;
	PreOrder(bt->lchild);
	PreOrder(bt->rchild);
}

template<class DataType>//中序
void BiTree<DataType>::InOrder(BiNode<DataType>*bt)
{
	if (bt == NULL) return;
	InOrder(bt->lchild);
	cout << bt->data;
	InOrder(bt->rchild);
}

template<class DataType>//后序
void BiTree<DataType>::PostOrder(BiNode<DataType>*bt)
{
	if (bt == NULL) return;
	PostOrder(bt->lchild);
	PostOrder(bt->rchild);
	cout << bt->data;
}

template<class DataType>//层序
void BiTree<DataType>::LeverOrder()
{
	CirQueue<BiNode<DataType>*> Q;
	if (root == NULL) return;
	Q.EnQueue(root);
	while (!Q.Empty())
	{
		BiNode<DataType>*q = Q.DeQueue();
		cout << q->data;
		if (q->lchild != NULL)
			Q.EnQueue(q->lchild);
		if (q->rchild != NULL)
			Q.EnQueue(q->rchild);
	}
}

template<class DataType>//虚构
void BiTree<DataType>::Release(BiNode<DataType>*bt)
{
	if (bt != NULL)
	{
		Release(bt->lchild);
		Release(bt->rchild);
		delete bt;
	}
}

template<class DataType>//除支
void BiTree<DataType>::DeleteTree(BiNode<DataType>*bt, DataType x)
{
	if (bt == NULL) return;
	if (bt->data == x)
	{
		bt->lchild = NULL;
		bt->rchild = NULL;
	}
	DeleteTree(bt->lchild, x);
	DeleteTree(bt->rchild, x);
}

template<class DataType>//点数
int BiTree<DataType>::NodeNumber()
{
	CirQueue<BiNode<DataType>*> Q;
	int count = 0;
	if (root == NULL) return count;

	Q.EnQueue(root);
	while (!Q.Empty())
	{
		BiNode<DataType>*q = Q.DeQueue();
		count++;
		if (q->lchild != NULL)
			Q.EnQueue(q->lchild);
		if (q->rchild != NULL)
			Q.EnQueue(q->rchild);
	}
	return count;
}

template<class DataType>//叶子
int BiTree<DataType>::LeafNumber()
{
	CirQueue<BiNode<DataType>*> Q;
	int count = 0;
	if (root == NULL) return count;

	Q.EnQueue(root);
	while (!Q.Empty())
	{
		BiNode<DataType>*q = Q.DeQueue();
		if (q->lchild != NULL)
			Q.EnQueue(q->lchild);
		if (q->rchild != NULL)
			Q.EnQueue(q->rchild);
		if (q->lchild == NULL && q->rchild == NULL)
			count++;
	}
	return count;
}

template<class DataType>//叶子
void BiTree<DataType>::LeafNode()
{
	CirQueue<BiNode<DataType>*> Q;
	int count = 0;
	if (root == NULL) return;
	Q.EnQueue(root);
	while (!Q.Empty())
	{
		BiNode<DataType>*q = Q.DeQueue();
		if (q->lchild != NULL)
			Q.EnQueue(q->lchild);
		if (q->rchild != NULL)
			Q.EnQueue(q->rchild);
		if (q->lchild == NULL && q->rchild == NULL)
			cout << q->data;
	}
}

template<class DataType>//深度
int BiTree<DataType>::Depth(BiNode<DataType> *bt)
{
	if (bt == NULL)
	{
		return 0;
	}
	int a = Depth(bt->lchild) + 1;
	int b = Depth(bt->rchild) + 1;
	if (a > b)
		return a;
	else
		return b;

}

template<class DataType>//双亲
DataType BiTree<DataType>::Parents(BiNode<DataType> *bt, DataType x)
{
	if (bt == NULL) return '#';
	DataType a = Parents(bt->lchild, x);
	DataType b = Parents(bt->rchild, x);
	if (bt->data == x)
		return x;
	if (a == x || b == x)
		return bt->data;
	if (a != '#')
		return a;
	if (b != '#')
		return b;
	return '#';
}

template<class DataType>//换孩
void BiTree<DataType>::Swop(BiNode<DataType> *bt)
{
	if (bt == NULL) return;
	Swop(bt->lchild);
	Swop(bt->rchild);
	BiNode<DataType> *p = bt->lchild;
	bt->lchild = bt->rchild;
	bt->rchild = p;
}

template<class DataType>//路径
int BiTree<DataType>::Path(BiNode<DataType> *bt, DataType x, DataType p[])
{
	if (bt == NULL) return -1;
	int a = Path(bt->lchild, x, p);
	int b = Path(bt->rchild, x, p);
	if (bt->data == x) a = 0;
	else if (a != -1 || b != -1)
	{
		if (a > b)
			a = a + 1;
		else
			a = b + 1;
		p[a - 1] = bt->data;
	}
	else
		a = -1;
	return a;
}

template<class DataType>//后逆
void BiTree<DataType>::PostOpposite(BiNode<DataType> *bt)
{
	if (bt == NULL) return;
	cout << bt->data;
	PostOpposite(bt->rchild);
	PostOpposite(bt->lchild);
}

template<class DataType>//打印
void BiTree<DataType>::Print(BiNode<DataType> *bt, int n)
{
	if (bt != NULL)
	{
		n++;
		Print(bt->rchild, n);
		for (int i = 0; i < n; i++)
			cout << '\t';
		cout << bt->data << endl;
		Print(bt->lchild, n);
	}
}

template<class DataType>//图像
void BiTree<DataType>::Image()
{
	CirQueue<BiNode<DataType>*> Q;
	if (root == NULL) return;
	int n = Depth();
	int b = (1 << (n + 1)) - 1;
	int count = 1;
	int e = 0;
	int t = 1 << (n - 1);
	Q.EnQueue(root);
	for (int i = 0; i < t - 1; i++)
		cout << " ";
	Q.EnQueue(NULL);
	while (count < b)
	{
		BiNode<DataType>*q = Q.DeQueue();
		if (q == NULL)
		{
			cout << endl;
			t = (int)(log(count) / log(2)) + 1;//当前到第t行
			for (int i = 0; i < 2 * (n - t) - 1; i++)
				cout << " ";
			e = 0;
		}
		else
		{
			if (e % 2 == 0 && e > 0)
			{
				int k = n - t;
				for (int i = 0; i < 2 * k; i++)
					cout << " ";
			}
			cout << q->data << " ";
			e++;
			if (e % 2 == 1 && e > 0)
			{
				int k = n - t;
				for (int i = 0; i < 2 * k; i++)
					cout << " ";
			}
			if (q->lchild != NULL)
				Q.EnQueue(q->lchild);
			else
			{
				BiNode<DataType>*s = new BiNode<DataType>();
				s->data = ' ';
				s->lchild = NULL;
				s->rchild = NULL;
				Q.EnQueue(s);
			}
			if (q->rchild != NULL)
				Q.EnQueue(q->rchild);
			else
			{
				BiNode<DataType>*s = new BiNode<DataType>();
				s->data = ' ';
				s->lchild = NULL;
				s->rchild = NULL;
				Q.EnQueue(s);
			}
			count += 2;
			double c = log(count + 1) / log(2);
			if (c == (int)c)
				Q.EnQueue(NULL);
		}
	}
}

int BinaryTree_run()
{
	cout << "构造方式形如：1 2 3 # # 4 # # 5 6 # # 7 # #" << endl << "请构造二叉树：" << endl;
	BiTree<char> Tree;
	char x;
	int flag = -1;
	while (flag)
	{
		cout << "<01>  先序遍历显示" << endl;
		cout << "<02>  中序遍历显示" << endl;
		cout << "<03>  后序遍历显示" << endl;
		cout << "<04>  层序遍历显示" << endl;
		cout << "<05>  二叉树结点数" << endl;
		cout << "<06>  叶子结点个数" << endl;
		cout << "<07>  显示叶子结点" << endl;
		cout << "<08>  二叉树的深度" << endl;
		cout << "<09>  删除选择子树" << endl;
		cout << "<10>  已知结点双亲" << endl;
		cout << "<11>  左右孩子互换" << endl;
		cout << "<12>  求到结点路径" << endl;
		cout << "<13>  后序遍历逆序" << endl;
		cout << "<14>  二叉树图显示" << endl;
		cout << "<0>  退出程序" << endl;
		cout << "请选择操作：";
		cin >> flag;
		cout << "***********************" << endl;
		switch (flag)
		{
		case 1:
			Tree.PreOrder();
			break;
		case 2:
			Tree.InOrder();
			break;
		case 3:
			Tree.PostOrder();
			break;
		case 4:
			Tree.LeverOrder();
			break;
		case 5:
			cout << Tree.NodeNumber();
			break;
		case 6:
			cout << Tree.LeafNumber();
			break;
		case 7:
			Tree.LeafNode();
			break;
		case 8:
			cout << Tree.Depth();
			break;
		case 9:
			cout << "删除以节点为x为根的值为：";
			cin >> x;
			Tree.DeleteTree(x);
			break;
		case 10:
			cout << "已知结点为：";
			cin >> x;
			cout << Tree.Parents(x);
			break;
		case 11:
			Tree.Swop();
			break;
		case 12:
			cout << "寻找的结点为：";
			cin >> x;
			Tree.Path(x);
			break;
		case 13:
			Tree.PostOpposite();
			break;
		case 14:
			//Tree.Image();
			Tree.Print();
			break;
		case 0:
			cout << "谢谢使用";
			break;
		}
		cout << endl << "***********************" << endl;
	}
	return 0;
}

//测试数据：1 2 3 # # 4 # # 5 6 # # 7 # #
