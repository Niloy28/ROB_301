#include <iostream>

#include "Agent.h"
#include "Tree.h"
#include <string>

int main()
{
	Agent agent;
	std::string file_name;

	std::cout << "Enter a file name: ";
	std::getline(std::cin, file_name);

	agent.read_file(file_name);

	std::cout << "Maximum achievable result for maximizer: ";
	std::cout << agent.expectimax() << std::endl;

	return 0;
}
