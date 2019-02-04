// includes for IO
#include <iostream>
#include <sstream>
#include <fstream>

// includes for containers
#include <vector>
#include <stack>
#include <queue>
#include <forward_list>

// necessary using declarations
using std::vector;
using std::stack;
using std::queue;
using std::forward_list;
using std::string;
using std::fstream;
using std::stringstream;

struct Vertex
{
	char id = '\0';

	Vertex() = default;
	explicit Vertex(const char id)
	{
		this->id = id;
	}
};

class Graph
{
private:
	vector<forward_list<Vertex>> m_adjacency_list;
	vector<Vertex*> m_vertex_addr;
	unsigned m_no_of_vertices = 0;

public:
	Graph() = default;

	void extract_data(stringstream& ss)
	{
		char parent_id;
		int no_of_edges;
		ss >> parent_id;
		ss >> no_of_edges;

		// create list with parent_id as the head link
		// the vertices connected to parent_id are then pushed sequentially to front of the list
		m_adjacency_list[parent_id - 'A'].push_front(Vertex(parent_id));
		for (int i = 0; i != no_of_edges; ++i) {
			char child_id;
			ss >> child_id;
			m_adjacency_list[parent_id - 'A'].push_front(Vertex(child_id));
		}
		// the list is reversed because insertion was done from the front.
		m_adjacency_list[parent_id - 'A'].reverse();
	}

	void read_file(fstream& fs)
	{
		fs >> m_no_of_vertices;
		// ignore leftover \n from file
		fs.ignore(256, '\n');
		// assign memory for each Vertex
		for (int i = 0; i != m_no_of_vertices; ++i)
			m_vertex_addr.push_back(new Vertex);
		// assign id to respective index of m_vertex_addr
		// i.e. id = 'A' + index, supposing beginnnig vertex is A
		int i = 0;
		for (auto &it : m_vertex_addr) {
			it->id = 'A' + i;
			++i;
		}
		// assign "m_no_of_vertices" empty lists to "m_adjacency_list"
		m_adjacency_list.assign(m_no_of_vertices, forward_list<Vertex>());

		stringstream ss;
		string temp;
		while (getline(fs, temp)) {
			ss.str(temp);
			this->extract_data(ss);

			ss.clear();
		}
	}

	bool search_by_depth(const char source_id, const char destination_id)
	{
		stack<Vertex*> addr_stack;
		vector<bool> is_visited(m_no_of_vertices, false);

		addr_stack.push(m_vertex_addr[source_id - 'A']);
		do {
			Vertex* curr_vertex = addr_stack.top();

			if (addr_stack.top()->id == destination_id)
				return true;
			addr_stack.pop();
			is_visited[curr_vertex->id - 'A'] = true;
			for (auto &i : m_adjacency_list[curr_vertex->id - 'A']) {
				if (!is_visited[i.id - 'A'])
					addr_stack.push(m_vertex_addr[i.id - 'A']);
			}
		} while (!addr_stack.empty());

		return false;
	}

	bool search_by_breadth(const char source_id, const char destination_id)
	{
		queue<Vertex*> addr_queue;
		vector<bool> is_visited(m_no_of_vertices, false);

		addr_queue.push(m_vertex_addr[source_id - 'A']);
		do {
			Vertex* curr_vertex = addr_queue.front();

			if (addr_queue.front()->id == destination_id)
				return true;
			addr_queue.pop();
			is_visited[curr_vertex->id - 'A'] = true;
			for (auto &i : m_adjacency_list[curr_vertex->id - 'A']) {
				if (!is_visited[i.id - 'A'])
					addr_queue.push(m_vertex_addr[i.id - 'A']);
			}
		} while (!addr_queue.empty());

		return false;
	}
};

int main()
{
	Graph graph;
	fstream file;

	file.open("Node.txt", std::ios::in);
	graph.read_file(file);

	char source, destination;
	std::cout << "Enter source: ";
	std::cin >> source;
	std::cout << "Enter destination: ";
	std::cin >> destination;

	const auto is_found = graph.search_by_depth(source, destination);
	if (is_found)
		std::cout << "Search Successful.";
	else std::cout << "Search Failed.";

	return 0;
}
