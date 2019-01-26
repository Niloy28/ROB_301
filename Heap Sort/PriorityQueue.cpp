#include <iostream> 
#include <vector>
#include <fstream>

#include "PriorityQueue.h"

void PriorityQueue::enque(int in)
{
	m_heap.push_back(in);
	++length;
	this->reheapUp();
}

int PriorityQueue::deque()
{
	int retVal = m_heap[0];

	swapVal(m_heap[0], m_heap[length - 1]);
	--length;
	m_heap.pop_back();
	this->reheapDown();

	return retVal;
}
