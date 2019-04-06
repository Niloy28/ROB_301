#include "Node.h"

// constructors
Node::Node(const char& id)
{
	this->id = id;
}

Node::Node(const char& id, const unsigned no_of_branches)
{
	this->id = id;
	this->no_of_branches = no_of_branches;
}

Node::Node(const char& id, const int weight)
{
	this->id = id;
	this->weight = weight;
}

// methods
std::vector<Node> Node::return_successors(const Node& node)
{
	return node.branches;
}

double Node::return_probability() const
{
	if (probability != 0) return probability;

	return 1 / static_cast<double>(this->no_of_branches);
}
