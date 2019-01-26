#include <iostream>
#include "PriorityQueue.h"

int main()
{
	PriorityQueue pq;

	pq.read();
	std::cout << "Heap: ";
	pq.show();

	int queueLen = pq.getLength();
	vector<int> sortedData;
	for (int i = 0; i < queueLen; ++i)
		sortedData.push_back(pq.deque());

	std::cout << "Sorted Data: ";
	for (auto &i : sortedData)
		std::cout << i << " ";
	std::cout << std::endl;
	
	}