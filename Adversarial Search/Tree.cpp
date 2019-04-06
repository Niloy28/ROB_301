#include <fstream>
#include <sstream>

#include "Tree.h"
#include <stack>
#include <functional>
#include <queue>

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
		Tree::extract_data(ss, nodes);
		ss.clear();
	}
	m_root = nodes[0];
	Tree::link_nodes(m_root, nodes);
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

std::string Tree::search_by_depth() const
{
	std::stack<Node> node_stack;
	std::vector<bool> is_visited(m_no_of_nodes, false);

	node_stack.push(m_root);
	while (!node_stack.empty()) {
		Node start_node = node_stack.top();

		start_node.path.push_back(start_node.id);
		node_stack.pop();
		if (start_node.id == m_destination_id)
			return start_node.path;
		is_visited[start_node.id - reference_id] = true;

		std::vector<Node> successors = start_node.branches;
		for (auto& linked_node : successors) {
			if (!is_visited[linked_node.id - reference_id]) {
				linked_node.path = start_node.path;
				linked_node.path.append("->");
				node_stack.push(linked_node);
			}
		}
	}

	return "";
}

std::string Tree::search_by_breadth() const
{
	std::queue<Node> node_stack;
	std::vector<bool> is_visited(m_no_of_nodes, false);

	node_stack.push(m_root);
	while (!node_stack.empty()) {
		Node start_node = node_stack.front();

		start_node.path.push_back(start_node.id);
		node_stack.pop();
		if (start_node.id == m_destination_id)
			return start_node.path;
		is_visited[start_node.id - reference_id] = true;

		std::vector<Node> successors = start_node.branches;
		for (auto& linked_node : successors) {
			if (!is_visited[linked_node.id - reference_id]) {
				linked_node.path = start_node.path;
				linked_node.path.append("->");
				node_stack.push(linked_node);
			}
		}
	}

	return "";
}

void Tree::link_nodes(Node& parent, std::vector<Node>& nodes)
{
	if (parent.branches.empty()) return;

	for (unsigned i = 0; i != parent.branches.size(); ++i) {
		parent.branches[i] = nodes[parent.branches[i].id - reference_id];
		link_nodes(parent.branches[i], nodes);
	}
}
