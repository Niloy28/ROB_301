// includes for IO
#include <iostream>
#include <sstream>
#include <fstream>

// includes for class data members
#include <vector>

// include for stack
#include <stack>

// necessary using declartions
using std::vector;
using std::stack;
using std::string;
using std::fstream;
using std::stringstream;

struct Node
{
	char id;
	int noOfBranches = 0;
	vector<Node*> branches;
};

class StateTree
{
private:
	vector<Node*> stateAddr;

public:
	StateTree() = default;
	void extractData(stringstream& ss)
	{
		Node temp;
		ss >> temp.id;

		Node* currNode;
		// if(node_with_current_id_is_not_allocated)
		//		create new node and assign the address to the respective index of stateAddr
		// else currNode = address_of_existing_node_with_same_id
		if (stateAddr[temp.id - 'A'] == nullptr) {
			currNode = new Node;
			currNode->id = temp.id;
			stateAddr[currNode->id - 'A'] = currNode;
		}
		else currNode = stateAddr[temp.id - 'A'];

		ss >> currNode->noOfBranches;
		// allocate memory to each branch of current node.
		// assign id to each branch and save address into stateAddr in respective index.
		for (int i = 0; i != currNode->noOfBranches; ++i) {
			currNode->branches.push_back(new Node);
			ss >> currNode->branches[i]->id;
			stateAddr[currNode->branches[i]->id - 'A'] = currNode->branches[i];
		}
	}
	void readFile(fstream& fs)
	{
		int noOfStates;
		fs >> noOfStates;

		// create "noOfBranches" of elements and assign nullptr to each
		stateAddr.assign(noOfStates, nullptr);
		fs.ignore(1, '\n');

		stringstream fileString;
		string tempString;
		while (std::getline(fs, tempString)) {
			fileString.str(tempString);
			this->extractData(fileString);

			// reset stringstream state to set get pointer to the beginning of stream
			// otherwise further reads will start from end of stream
			fileString.clear();
		}
	}
	bool searchByDepth(char searchID)
	{
		stack<Node*> addrStack;
		addrStack.push(stateAddr[0]);

		do {
			if (addrStack.top()->id == searchID)
				return true;
			else {
				Node* currNode = addrStack.top();
				addrStack.pop();
				for (int i = 0; i != currNode->noOfBranches; ++i)
					addrStack.push(currNode->branches[i]);
			}
		} while (!(addrStack.empty()));

		return false;
	}
};

int main()
{
	StateTree state;
	fstream file;
	file.open("Node.txt", std::ios::in);

	state.readFile(file);
	char searchTerm;
	std::cin >> searchTerm;
	bool isFound = state.searchByDepth(searchTerm);

	if (isFound)
		std::cout << "DFS Successful." << std::endl;
	else std::cout << "DFS Failed." << std::endl;

	return 0;
}