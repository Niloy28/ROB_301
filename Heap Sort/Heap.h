#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <fstream>

using std::vector;

void swapVal(int&, int&);

class Heap
{
protected:
	vector<int> m_heap;
	int length = 0;

public:
	void reheapUp();
	void reheapDown(int parentIndex = 0);
	void read();
	virtual void show();
	inline int getLength()
	{
		return this->length;
	}
};

#endif
