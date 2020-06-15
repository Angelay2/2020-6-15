#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>
#include <list>
#include <vector>
#include <functional>

using namespace std;

/* ˫�˶��� (�߼�������. �����ϲ���ȫ���������Ա�, ָ������+buffer)
�����зŵ���ָ��, ָ������, ÿ��ָ��ָ��һ��������buffer, ��Чλ���Ǵ��м�λ�ÿ�ʼ��, ��֤�����˲���Ҫ��Ч, ��һ������֮��,������,  
����������ȥ��ָ�������м�λ�õ�ָ����ָ������鿪ʼ, �����������в���Ԫ��, ��Щ����ռ䲻����,
ͷ���β�������������ӻ����������, ��֮���˶��������

1. ֧���������, ����Ч��û��˳����, �͵�ԭ��������ײ�ṹ(�ռ�)������ȫ������, �������ʱ��Ҫ����λ��
2. ͷɾͷ��,βɾβ��ʱ�临�Ӷ�ΪO(1),  ���԰�ͷ����βҲ���԰�β����ͷ, ������λ�õĲ���ɾ���ͺ�����, ���������
3. ������, ���ݴ���С,�����߼�: ��һ�������ָ������, ����ָ�����������, ���µ��ڴ�Ƭ��,  �ڴ�εĵ�ַ����ָ������, ����Ҫ����Ԫ������, Ҳ����Ҫ�ͷ�ԭ��Ԫ�صĿռ� ֻ��Ҫ�ͷ�ԭ��ָ������
4. �м�����ɾ��, Ч�ʵ�, ʱ�临�Ӷ�O(N),

ָ�������е�ÿ��ָ�붼��T*����, 
map��ָ���������ʼλ��(T**����), �൱����ָ���������ŵ�ָ��ĵ�ַ, 
һ�ν����õõ�ָ���ֵ, ���ν����õõ�������Ԫ��ֵ, node++ ����һ��buf��ָ��λ��
node:(T**����) ͨ�����ҵ���һ��buf����ʼλ��, ָ�򻺳�������ʼ��ַ��ָ�������е��ĸ�λ�ô��� 
first: (T*����)ָ����Ƭ����������ʼλ��, 
last: (T*����)ָ����Ƭ�����������һ��Ԫ�ص���һ��λ��

��˫�˶�����Ϊջstack��queue��Ĭ��ʵ��, �������
dequeʵ��stack������:
	1. ջstack����Ҫ�������, vector֧�ֶ��������
	2. ջstack�Ǳ䳤�����Ա�, vector���ݴ��۴�, ����deque�����ݴ���С
	3. ˫�˶�����һ��Ƭ����, �Ҳ���Ҫ�ͷſռ�, �ռ������ʸ���, ����������ڴ���Ƭ, ��Ȼlist����Ч�ʸ�, ����list�ռ���СƬСƬ���� ��������ڴ���Ƭ, �ռ������ʵ�, ��������ռ�, ɾ���ͷſռ�
dequeʵ��queue������:
	1. ˫�˶��е�ͷɾβɾ, ͷ��β��Ч��Ҳ��, �Ҳ����ڴ���Ƭ, �ռ������ʸ�, ��list���ײ����ڴ���Ƭ, �ռ������ʵ�
���ȼ�����priority_queueĬ��ʹ��vectorʵ��
	��vectorʵ�ֵ�������:
	1. vector�������Ч�ʱ�deque��(�����ϵ���/���µ���)
	2. �������(�ռ�)�Ĵ�����˵ �������(Ч��)����Ҫ ����ÿ����/ɾ��һ�ζ�Ҫ��������/���µ���, ��������ֻ��Ӱ��һʱ, 
	3. ���ȼ����в���ͷ��ͷɾ, deque��ͷ��ͷɾЧ�ʸ����������ֲ�����

template<class T, class Contianer = vector<T>, class Compare  = less<T>>
�º��� Compare: ʵ�ֱȽ��߼�
		ͨ����ͬ�ķº����ȽϹ���, ������ͬ�Ķѽṹ
		����Ҫ�޸����ȼ����е�Դ����, ����ʵ��, ����˴���������,ͨ����

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
			//ʹ�÷º����������Ԫ�رȽϵ��߼�
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
