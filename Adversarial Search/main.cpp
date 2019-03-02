#include <iostream>

#include "Agent.h"
#include <string>

int main()
{
	Agent agent;
	std::string file_name;

	std::cout << "Enter a file name: ";
	std::getline(std::cin, file_name);

	agent.read_file(file_name);

	std::cout << "Maximum achievable result for maximizer: ";
	std::cout << agent.mini_max() << std::endl;

	return 0;
}
