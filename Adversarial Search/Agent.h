#ifndef AGENT_H
#define AGENT_H

#include "Tree.h"

class Agent
{
public:
	Agent() = default;
	void read_file(std::string&);
	int mini_max();

private:
	static int m_max;
	static int m_min;
	Tree m_tree;

	// utility functions
	int value(Node& state, bool is_max_turn = true, int alpha = m_min, int beta = m_max) const;
};

#endif

