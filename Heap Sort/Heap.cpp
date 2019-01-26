#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "Heap.h"

using std::vector;


void Heap::read()
{
	std::fstream file;
	file.open("value.txt", std::ios::in);
	int in;
	while (file >> in) {
		m_heap.push_back(in);
		++length;
		this->reheapUp();
	}
}

void Heap::reheapUp()
{
	for (int i = length - 1; i > 0; i = (i - 1) / 2) {
		if (m_heap[i] > m_heap[(i - 1) / 2])
			swapVal(m_heap[i], m_heap[(i - 1) / 2]);
	}
}

void Heap::reheapDown(int parentIndex)
{
	int childIndex = 2 * parentIndex + 1;
	// return if m_heap has a single element
	// this is done by comparing the depth of the heap & the depth of the current node
	// if(depth_of_current_node >= depth_of_heap) return;
	if (static_cast<int>(log2(childIndex)) >= static_cast<int>(log2(length))) return;

	if (m_heap[parentIndex] < m_heap[childIndex]) {
		swapVal(m_heap[parentIndex], m_heap[childIndex]);
		// call reheapDown() on the subtree that has root childIndex
		this->reheapDown(childIndex);
	}

	// check whether vector subscript is out of range for the right branch
	// ++childIndex == subscript_of_right_branch
	if (++childIndex == length) return;
	if (m_heap[parentIndex] < m_heap[childIndex]) {
		swapVal(m_heap[parentIndex], m_heap[childIndex]);
		this->reheapDown(childIndex);
	}
}

void Heap::show()
{
	for (auto &i : this->m_heap)
		std::cout << i << " ";
	std::cout << std::endl;
}

void swapVal(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
