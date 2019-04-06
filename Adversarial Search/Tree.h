#ifndef TREE_H
#define TREE_H

#include <vector>

#include "Node.h"

class Tree {
public:
	Tree() = default;
	void read_file(std::fstream&);
	Node& return_root();
	std::string search_by_depth() const;
	std::string search_by_breadth() const;

protected:
	// member variables
	static const char reference_id = 'A';
	Node m_root;
	unsigned m_no_of_nodes = 0;
	char m_source_id = '\0', m_destination_id = '\0';

	// utility functions
	static void extract_data(std::stringstream&, std::vector<Node>&);
	static void link_nodes(Node& parent, std::vector<Node>&);
};

#endif
