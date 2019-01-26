#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <iostream> 
#include <vector>
#include <fstream>

#include "Heap.h"

using std::vector;

class PriorityQueue : public Heap
{
public:
	void enque(int in);
	int deque();
};

#endif
