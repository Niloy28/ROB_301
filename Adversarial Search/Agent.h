#ifndef AGENT_H
#define AGENT_H

#include "Tree.h"

class Agent
{
public:
	Agent() = default;
	void read_file(std::string&);
	std::string search_by_depth() const;
	std::string search_by_breadth() const;
	int mini_max();
	double expectimax();

private:
	static int m_max;
	static int m_min;
	Tree m_tree;

	// utility functions
	int value(Node& state, bool is_max_turn = true, int alpha = m_min, int beta = m_max) const;
	double expected_value(Node& state, bool is_max_turn = true) const;
};

#endif

