#include <iostream>

#include "RacingAgent.h"

int main()
{
	RacingAgent racing_agent;

	auto result = racing_agent.value_iteration();

    std::cout << result[0] << "  " << result[1] << "  " << result[2] << std::endl;

	return 0;
}