#include "RacingAgent.h"
#include <algorithm>

std::vector<std::vector<actions>> RacingAgent::m_available_actions = { {slow, fast}, {slow, fast}, {} };

// each row depicts a car state
// the 2 sets of each row depict the outcome of each action (slow or fast) in that state
// the 1st set depicts slow and the 2nd set depicts fast action
//
// tuple<0> = state reached after executing the action
// tuple<1> = probability of reaching that state
// tuple<2> = reward for executing the action
std::vector<std::vector<std::vector<std::tuple<car_states, double, int>>>> RacingAgent::m_outcomes = { { { {cool, 1.0, 1} }, { {cool, 0.5, 2}, {warm, 0.5, 2} } },
																									   { { {warm, 0.5, 1}, {cool, 0.5, 1} } , { {overheated, 1.0, -10} } },
																										 {} };

void RacingAgent::read_file(const std::string& file_name)
{
	return;
}

std::vector<double> RacingAgent::value_iteration() const
{
	std::vector<double> current_value(3, 0.0);
	std::vector<double> old_value(current_value);

	unsigned iteration_count = 0;
	do {
		old_value = current_value;

		for (auto state = cool; state <= overheated; state = static_cast<car_states>(static_cast<int>(state) + 1)) {
			std::vector<actions> available_actions = m_available_actions[state];

			for (auto& action : available_actions) {
				current_value[state] = std::max(current_value[state], return_q_value(m_outcomes[state][action], old_value));
			}
		}
		++iteration_count;
	} while (iteration_count != 500 && !has_converged(current_value, old_value, 1.5));

	return current_value;
}

double RacingAgent::return_q_value(std::vector<std::tuple<car_states, double, int>>& outcomes, std::vector<double>& prev_value) const
{
	double q_value = 0.0;

	for(auto& tuple : outcomes) {
		q_value += std::get<1>(tuple) * (std::get<2>(tuple) + prev_value[std::get<0>(tuple)]);
	}

	return q_value;
}

bool has_converged(std::vector<double>& lhs, std::vector<double>& rhs, const double epsilon)
{
	if (lhs.size() != rhs.size()) return false;

	for (unsigned i = 0; i != lhs.size(); ++i) {
		if (lhs[i] - rhs[i] >= epsilon) return false;
	}

	return true;
}
