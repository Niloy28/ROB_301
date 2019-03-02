#include <fstream>
#include <sstream>

#include "Tree.h"

void Tree::read_file(std::fstream& fs)
{
	std::vector<Node> nodes;
	fs >> m_no_of_nodes;
	fs.ignore(256, '\n');
	nodes.assign(m_no_of_nodes, Node());

	std::string temp;
	std::stringstream ss;
	while (std::getline(fs, temp)) {
		ss.str(temp);
		this->extract_data(ss, nodes);
		ss.clear();
	}
	m_root = nodes[0];
	this->link_nodes(m_root, nodes);
}

void Tree::extract_data(std::stringstream& ss, std::vector<Node>& nodes)
{
	char parent_id;
	unsigned branches;

	ss >> parent_id >> branches;
	if (branches == 0) {
		int weight;
		ss >> weight;
		nodes[parent_id - reference_id] = Node(parent_id, weight);

		return;
	}

	nodes[parent_id - reference_id] = (Node(parent_id, branches));
	for (unsigned i = 0; i != branches; ++i) {
		char child_id;

		ss >> child_id;
		nodes[parent_id - reference_id].branches.emplace_back(child_id);
	}
}

Node& Tree::return_root()
{
	return m_root;
}

void Tree::link_nodes(Node& parent, std::vector<Node>& nodes)
{
	if (parent.branches.empty()) return;

	for (unsigned i = 0; i != parent.branches.size(); ++i) {
		parent.branches[i] = nodes[parent.branches[i].id - reference_id];
		link_nodes(parent.branches[i], nodes);
	}
}