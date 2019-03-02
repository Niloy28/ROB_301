#ifndef TREE_H
#define TREE_H

#include <vector>

struct Node
{
	char id = '\0';
	int weight = 0;
	unsigned no_of_branches = 0;
	std::vector<Node> branches;

	Node() = default;
	explicit Node(const char& id)
	{
		this->id = id;
	}
	explicit Node(const char& id, const unsigned no_of_branches)
	{
		this->id = id;
		this->no_of_branches = no_of_branches;
	}
	explicit Node(const char& id, const int weight)
	{
		this->id = id;
		this->weight = weight;
	}
	static std::vector<Node> return_successors(const Node& node)
	{
		return node.branches;
	}
};

class Tree {
public:
	Tree() = default;
	void read_file(std::fstream&);
	Node& return_root();

protected:
	// member variables
	static const char reference_id = 'A';
	
	Node m_root;
	unsigned m_no_of_nodes = 0;
	char m_source_id = '\0', m_destination_id = '\0';

	// utility functions
	void extract_data(std::stringstream&, std::vector<Node>&);
	void link_nodes(Node& parent, std::vector<Node>&);
};

#endif
