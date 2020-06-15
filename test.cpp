#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <functional>

using namespace std;

/* 双端队列 (逻辑上连续. 物理上不完全连续的线性表, 指针数组+buffer)
队列中放的是指针, 指针数组, 每个指针指向一个缓冲区buffer, 有效位置是从中间位置开始的, 保证其两端插入要有效, 当一端满了之后,再增容,  
插入数据先去填指针数组中间位置的指针所指向的数组开始, 对这个数组进行插入元素, 这些数组空间不连续,
头插和尾插决定其向上添加还是向下添加, 总之两端都可以添加

1. 支持随机访问, 但是效率没有顺序表高, 低的原因在于其底层结构(空间)不是完全连续的, 随机访问时需要换算位置
2. 头删头插,尾删尾插时间复杂度为O(1),  可以把头看做尾也可以把尾看做头, 在任意位置的插入删除就很难受, 还是链表好
3. 需增容, 增容代价小,增容逻辑: 建一个更大的指针数组, 拷贝指针数组的内容, 开新的内存片段,  内存段的地址放入指针数组, 不需要拷贝元素内容, 也不需要释放原有元素的空间 只需要释放原有指针数组
4. 中间插入和删除, 效率低, 时间复杂度O(N),

指针数组中的每个指针都是T*类型, 
map是指针数组的起始位置(T**类型), 相当于是指针数组里存放的指针的地址, 
一次解引用得到指针的值, 两次解引用得到缓冲区元素值, node++ 到下一个buf的指针位置
node:(T**类型) 通过它找到下一个buf的起始位置, 指向缓冲区的起始地址在指针数组中的哪个位置存着 
first: (T*类型)指向这片缓冲区的起始位置, 
last: (T*类型)指向这片缓冲区的最后一个元素的下一个位置

用双端队列作为栈stack和queue的默认实现, 相对优势
deque实现stack的优势:
	1. 栈stack不需要随机访问, vector支持对随机访问
	2. 栈stack是变长的线性表, vector增容代价大, 但是deque的增容代价小
	3. 双端队列是一大片申请, 且不需要释放空间, 空间利用率更高, 不容易造成内存碎片, 虽然list插入效率高, 但是list空间是小片小片申请 容易造成内存碎片, 空间利用率低, 插入申请空间, 删除释放空间
deque实现queue的优势:
	1. 双端队列的头删尾删, 头插尾插效率也高, 且不长内存碎片, 空间利用率高, 而list容易产生内存碎片, 空间利用率低
优先级队列priority_queue默认使用vector实现
	用vector实现的优势在:
	1. vector随机访问效率比deque高(需向上调整/向下调整)
	2. 相比增容(空间)的代价来说 随机访问(效率)更重要 可能每插入/删除一次都要进行向上/向下调整, 但是增容只会影响一时, 
	3. 优先级队列不做头插头删, deque的头插头删效率高在这里显现不出来

template<class T, class Contianer = vector<T>, class Compare  = less<T>>
仿函数 Compare: 实现比较逻辑
		通过不同的仿函数比较规则, 产生不同的堆结构
		不需要修改优先级队列的源代码, 即可实现, 提高了代码的灵活性,通用性

*/
template <class T, class Container = deque<T>>
class Stack
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_back();
	}

	T& top()
	{
		return _c.back();
	}

	size_t size()
	{
		return _c.size();
	}

	bool empty()
	{
		return _c.empty();
	}

private:
	Container _c;
};

void testSt()
{
	Stack<int, vector<int>> st;
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	while (!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}

template <class T, class Container = deque<T>>
class Queue
{
public:
	//push, pop, front, size, empty
	void push(const T& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_front();
	}

	T& front()
	{
		return _c.front();
	}

	T& back()
	{
		return _c.back();
	}

	size_t size()
	{
		return _c.size();
	}

	bool empty()
	{
		return _c.empty();
	}
private:
	Container _c;
};

void testQueue()
{
	Queue<int, deque<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	while (!q.empty())
	{
		cout << q.front() << " ";
		q.pop();
	}
	cout << endl;
}

template <class T, class Container = vector<T>, class Compare = less<T>>
class Priority_Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}

	void pop()
	{
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}

	const T& top()
	{
		return _c.front();
	}

	size_t size()
	{
		return _c.size();
	}

	bool empty()
	{
		return _c.empty();
	}

private:
	void shiftDown(int parent)
	{
		int child = 2 * parent + 1;
		int size = _c.size();
		while (child < size)
		{
			//if (child + 1 < size && _c[child] < _c[child + 1])
			//使用仿函数对象完成元素比较的逻辑
			if (child + 1 < size && _com(_c[child], _c[child + 1]))
				++child;
			//if (_c[parent] < _c[child])
			if (_com(_c[parent], _c[child]))
			{
				swap(_c[parent], _c[child]);
				parent = child;
				child = 2 * parent + 1;
			}
			else
				break;
		}
	}

	void shiftUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			//if (_c[parent] < _c[child])
			if (_com(_c[parent], _c[child]))
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

private:
	Container _c;
	Compare _com;
};

class Date
{
public:
	Date(int y, int m, int d)
		:_y(y), _m(m), _d(d)
	{}

	bool operator<(const Date& d) const
	{
		if (_y < d._y)
			return true;
		else if (_y == d._y)
		{
			if (_m < d._m)
				return true;
			else if (_m == d._m)
			{
				if (_d < d._d)
					return true;
			}
		}
		return false;
	}

	bool operator>(const Date& d) const
	{
		if (_y > d._y)
			return true;
		else if (_y == d._y)
		{
			if (_m > d._m)
				return true;
			else if (_m == d._m)
			{
				if (_d > d._d)
					return true;
			}
		}
		return false;
	}

	//private:
	int _y;
	int _m;
	int _d;
};

ostream& operator<<(ostream& cout, const Date& d)
{
	cout << d._y << "-" << d._m << "-" << d._d << endl;
	return cout;
}

void testPQ()
{
	//Priority_Queue<int> pq;
	Priority_Queue<int, vector<int>, greater<int>> pq;
	//priority_queue<int, vector<int>, greater<int>> pq;
	//priority_queue<int> pq;
	pq.push(9);
	pq.push(19);
	pq.push(8);
	pq.push(1);
	pq.push(3);
	pq.push(40);
	while (!pq.empty())
	{
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;
}

void testPQ2()
{
	//Priority_Queue<Date> pq;
	Priority_Queue<Date, vector<Date>, greater<Date>> pq;
	pq.push(Date(2008, 12, 10));
	pq.push(Date(2018, 12, 10));
	pq.push(Date(2019, 12, 10));
	pq.push(Date(2020, 5, 10));
	pq.push(Date(2020, 12, 10));
	while (!pq.empty())
	{
		cout << pq.top();
		pq.pop();
	}
	cout << endl;
}

int main()
{
	//testSt();
	//testQueue();
	//testPQ();
	testPQ2();
	return 0;
}
