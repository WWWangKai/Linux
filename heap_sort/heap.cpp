#include<iostream>
using namespace std;
#include<assert.h>
#include<vector>

/*用仿函数来实现代码的复用*/

template<class T>
struct Less  //升序
{
	bool operator()(const T& l, const T& r)
	{
		return l < r;
	}
};

template<class T>
struct Greater  //降序
{
	bool operator()(const T& l, const T& r)
	{
		return l > r;
	}
};

template<class T,class compare = Greater<T>>
class Heap
{
public:
		Heap()
		{}
		Heap(const T* a, size_t size)
		{
			for (int i = 0; i < size; ++i)
			{
				_root.push_back(a[i]);
			}
			for (int i = (_root.size() - 2) / 2; i >= 0; --i)
			{
				_AdjustDown(i);
			}
		}
		void Push(const T& x)
		{
			_root.push_back(x);
			_AdjustDown(_root.size() -1 );//向上调整
		}
		void Pop()
		{
			assert(_root.size() > 0);
			swap(_root[0], _root[_root.szie() - 1]);
			_root.pop_back();

			_AdjustUp(0)；
		}
		const T& Top()
		{
			assert(_root.size() > 0);
			return _root[0];
		}
		bool Empty()
		{
			return _root.empty();
		}

		size_t Size()
		{
			return _root.size();
		}
private:
		void AddjustDown(int root)//从根向下调整
		{
			int child = root * 2 + 1;
			compare com;
			while (child < _root.size())
			{
				/*找出左右孩子中较大的那个*/
				if ((child + 1 < _root.size()) && com(_root[child + 1], _root[child]))
				{
					++child;
				}
				if (com(_root[child], _root[root]))
				{
					swap(_root[child], _root[root]);
					root = child;
					child = child * 2 + 1;
				}
				else
					break;

			}
		}

		void _AdjustUp(int child)
		{
			while (chuld > 0)
			{
				int parent = (child - 1) / 2;
				if (com(_root[child], _root[parent]))
				{
					swap(_root[child], _root[parent]);
					child = parent;
				}
				else
					break;
			}
		}
protected:
		vector<T> _root;
};
