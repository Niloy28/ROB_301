// includes for IO
#include <iostream>
#include <sstream>
#include <fstream>

// includes for containers
#include <vector>
#include <stack>
#include <queue>

// necessary using declartions
using std::vector;
using std::stack;
using std::queue;
using std::string;
using std::fstream;
using std::stringstream;

struct Node
{
	char id;
	int no_of_branches = 0;
	unsigned weight = 0;
	vector<Node*> branches;
};

class Tree
{
private:
	vector<Node*> m_state_addr;
	int m_no_of_states = 0;

public:
	Tree() = default;

	void extract_data(stringstream& ss)
	{
		Node temp;
		ss >> temp.id;

		Node* curr_node;
		// if(node_with_current_id_is_not_allocated)
		//		create new node and assign the address to the respective index of stateAddr
		// else currNode = address_of_existing_node_with_same_id
		if (m_state_addr[temp.id - 'A'] == nullptr) {
			curr_node = new Node;
			curr_node->id = temp.id;
			m_state_addr[curr_node->id - 'A'] = curr_node;
		}
		else curr_node = m_state_addr[temp.id - 'A'];

		ss >> curr_node->no_of_branches;
		// allocate memory to each branch of current node.
		// if that branch is already allocated, assign that address to the branch.
		// otherwise, create new Node* in that branch
		// and assign address of the newly created branch to m_state_addr[respective index].
		for (int i = 0; i != curr_node->no_of_branches; ++i) {
			char branch_id;

			ss >> branch_id;
			if (m_state_addr[branch_id - 'A'] != nullptr) {
				curr_node->branches.push_back(m_state_addr[branch_id - 'A']);
			}
			else {
				curr_node->branches.push_back(new Node);
				curr_node->branches[i]->id = branch_id;
				m_state_addr[curr_node->branches[i]->id - 'A'] = curr_node->branches[i];
			}
		}
	}

	void read_file(fstream& fs)
	{
		fs >> m_no_of_states;

		// create "no_of_branches" of elements and assign nullptr to each.
		// nullptr indicates that the Node has not yet been created.
		m_state_addr.assign(m_no_of_states, nullptr);
		fs.ignore(1, '\n');

		stringstream file_string;
		string temp_string;
		while (getline(fs, temp_string)) {
			file_string.str(temp_string);
			this->extract_data(file_string);

			// reset stringstream to set get pointer to the beginning of stream
			// otherwise further reads will start from end of stream
			file_string.clear();
		}
	}

	bool search_by_depth(const char search_id)
	{
		stack<Node*> addr_stack;
		vector<bool> is_visited(m_no_of_states, false);
		addr_stack.push(m_state_addr[0]);

		Node* curr_node;
		do {
			if (addr_stack.top()->id == search_id)
				return true;
			curr_node = addr_stack.top();
			addr_stack.pop();

			if (!is_visited[curr_node->id - 'A'])
				for (int i = 0; i != curr_node->no_of_branches; ++i)
					addr_stack.push(curr_node->branches[i]);
			is_visited[curr_node->id - 'A'] = true;
		} while (!addr_stack.empty());

		return false;
	}

	bool search_by_breadth(const char search_id)
	{
		queue<Node*> addr_queue;
		vector<bool> is_visited(m_no_of_states, false);
		addr_queue.push(m_state_addr[0]);

		Node* curr_node;
		do {
			if (addr_queue.front()->id == search_id)
				return true;
			curr_node = addr_queue.front();
			addr_queue.pop();

			if (!is_visited[curr_node->id - 'A'])
				for (int i = 0; i != curr_node->no_of_branches; ++i)
					addr_queue.push(curr_node->branches[i]);
			is_visited[curr_node->id - 'A'] = true;
		} while (!addr_queue.empty());

		return false;
	}
};

int main()
{
	Tree tree;
	fstream file;
	file.open("Node.txt", std::ios::in);

	tree.read_file(file);
	char search_term;
	std::cout << "Enter ID of search term: ";
	std::cin >> search_term;
	const bool is_found = tree.search_by_depth(search_term);

	if (is_found)
		std::cout << "Search Successful." << std::endl;
	else std::cout << "Search Failed." << std::endl;

	return 0;
}
