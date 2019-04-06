#ifndef NODE_H
#define NODE_H

#include <vector>

struct Node
{
	// member variables
	char id = '\0';
	int weight = 0;
	unsigned no_of_branches = 0;
	std::vector<Node> branches;
	std::string path;
	double probability = 0.0;

	// constructors
	Node() = default;
	explicit Node(const char& id);
	explicit Node(const char& id, unsigned no_of_branches);
	explicit Node(const char& id, int weight);

	// methods
	static std::vector<Node> return_successors(const Node& node);
	double return_probability() const;
};

#endif